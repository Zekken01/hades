/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/RenderInterfaceD3D9.hpp"
#include "Web/Rml/SystemInterface.hpp"

#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"

#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/DecorationTypes.h>
#include <RmlUi/Core/Dictionary.h>
#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/Log.h>
#include <RmlUi/Core/Vertex.h>

#include <d3dx9.h>

#include <algorithm>
#include <cstdio>
#include <cstring>

// fxc output (ElDorito/Shaders/Rml/build_shaders.py)
#include "Web/Rml/Shaders/rml_vs.h"
#include "Web/Rml/Shaders/rml_ps_color.h"
#include "Web/Rml/Shaders/rml_ps_texture.h"
#include "Web/Rml/Shaders/rml_ps_gradient.h"

/* ---------- private code */

namespace
{
	template <typename T>
	void SafeRelease(T *&object)
	{
		if (object)
		{
			object->Release();
			object = nullptr;
		}
	}

	void LogError(const std::string &message)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Error, "RmlUi D3D9: " + message);
	}

	// Rml::Vertex { Vector2f position; ColourbPremultiplied colour; Vector2f tex_coord; }
	static_assert(sizeof(::Rml::Vertex) == 20, "Rml::Vertex layout changed; update the vertex declaration");

	bool TraceEnabled()
	{
		static int enabled = -1;
		if (enabled < 0)
			enabled = GetEnvironmentVariableA("HADES_RML_TRACE", nullptr, 0) > 0 ? 1 : 0;
		return enabled == 1;
	}

#define RML_TRACE(...) do { if (TraceEnabled()) { char _b[256]; sprintf_s(_b, __VA_ARGS__); OutputDebugStringA(_b); fputs(_b, stdout); } } while (0)

	bool FormatHasStencil(D3DFORMAT format)
	{
		switch (format)
		{
		case D3DFMT_D24S8:
		case D3DFMT_D24X4S4:
		case D3DFMT_D15S1:
		case D3DFMT_D24FS8:
			return true;
		default:
			return false;
		}
	}
}

namespace Web
{
	namespace RmlUi
	{
		RenderInterfaceD3D9::RenderInterfaceD3D9(IDirect3DDevice9 *device) : m_device(device)
		{
			m_device->AddRef();
			m_projection = ::Rml::Matrix4f::Identity();
			m_transform = m_projection;
		}

		RenderInterfaceD3D9::~RenderInterfaceD3D9()
		{
			for (auto *slot : std::vector<TextureSlot *>(m_slots.begin(), m_slots.end()))
				DestroySlot(slot);
			ReleaseShaders();
			SafeRelease(m_vertexDeclaration);
			SafeRelease(m_stateBlock);
			SafeRelease(m_ownDepthStencil);
			SafeRelease(m_device);
		}

		bool RenderInterfaceD3D9::Initialize()
		{
			D3DCAPS9 caps = {};
			if (SUCCEEDED(m_device->GetDeviceCaps(&caps)))
				m_supportsUByte4N = (caps.DeclTypes & D3DDTCAPS_UBYTE4N) != 0;

			// position @0, premultiplied colour @8 (RGBA bytes), uv @12
			D3DVERTEXELEMENT9 elements[] = {
				{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 8, m_supportsUByte4N ? (BYTE)D3DDECLTYPE_UBYTE4N : (BYTE)D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
				{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};
			if (FAILED(m_device->CreateVertexDeclaration(elements, &m_vertexDeclaration)))
			{
				LogError("CreateVertexDeclaration failed");
				return false;
			}
			if (!CreateShaders())
				return false;
			return true;
		}

		bool RenderInterfaceD3D9::CreateShaders()
		{
			if (FAILED(m_device->CreateVertexShader(reinterpret_cast<const DWORD *>(g_rml_vs), &m_vertexShader)) ||
				FAILED(m_device->CreatePixelShader(reinterpret_cast<const DWORD *>(g_rml_ps_color), &m_pixelShaderColor)) ||
				FAILED(m_device->CreatePixelShader(reinterpret_cast<const DWORD *>(g_rml_ps_texture), &m_pixelShaderTexture)) ||
				FAILED(m_device->CreatePixelShader(reinterpret_cast<const DWORD *>(g_rml_ps_gradient), &m_pixelShaderGradient)))
			{
				LogError("shader creation failed (the device must support vs_3_0 / ps_3_0)");
				ReleaseShaders();
				return false;
			}
			return true;
		}

		void RenderInterfaceD3D9::ReleaseShaders()
		{
			SafeRelease(m_vertexShader);
			SafeRelease(m_pixelShaderColor);
			SafeRelease(m_pixelShaderTexture);
			SafeRelease(m_pixelShaderGradient);
		}

		void RenderInterfaceD3D9::SetViewport(int width, int height)
		{
			m_width = std::max(width, 1);
			m_height = std::max(height, 1);
			// D3D9 samples pixel centres at integer coordinates, hence the half-pixel shift.
			m_projection = ::Rml::Matrix4f::ProjectOrtho(0.f, (float)m_width, (float)m_height, 0.f, -10000.f, 10000.f) * ::Rml::Matrix4f::Translate(-0.5f, -0.5f, 0.f);
			if (!m_hasTransform)
				m_transform = m_projection;
		}

		void RenderInterfaceD3D9::OnPreReset()
		{
			// Rml::ReleaseCompiledGeometry()/ReleaseTextures() (called by the owner) have already
			// freed the D3DPOOL_DEFAULT buffers and textures through this interface.
			SafeRelease(m_stateBlock);
			SafeRelease(m_ownDepthStencil);
		}

		void RenderInterfaceD3D9::OnPostReset()
		{
			SetViewport(m_width, m_height);
		}

		bool RenderInterfaceD3D9::EnsureDepthStencil(IDirect3DSurface9 *renderTarget)
		{
			D3DSURFACE_DESC rtDesc = {};
			if (!renderTarget || FAILED(renderTarget->GetDesc(&rtDesc)))
				return false;

			if (m_savedDepthStencil)
			{
				D3DSURFACE_DESC dsDesc = {};
				if (SUCCEEDED(m_savedDepthStencil->GetDesc(&dsDesc)) && FormatHasStencil(dsDesc.Format) &&
					dsDesc.Width >= rtDesc.Width && dsDesc.Height >= rtDesc.Height && dsDesc.MultiSampleType == rtDesc.MultiSampleType)
					return true; // the game's own depth-stencil can carry the clip mask
			}

			if (m_ownDepthStencil)
			{
				D3DSURFACE_DESC ownDesc = {};
				m_ownDepthStencil->GetDesc(&ownDesc);
				if (ownDesc.Width != rtDesc.Width || ownDesc.Height != rtDesc.Height || ownDesc.MultiSampleType != rtDesc.MultiSampleType)
					SafeRelease(m_ownDepthStencil);
			}
			if (!m_ownDepthStencil)
			{
				if (FAILED(m_device->CreateDepthStencilSurface(rtDesc.Width, rtDesc.Height, D3DFMT_D24S8, rtDesc.MultiSampleType, rtDesc.MultiSampleQuality, TRUE, &m_ownDepthStencil, nullptr)))
				{
					LogError("CreateDepthStencilSurface(D24S8) failed; clip masks disabled this frame");
					return false;
				}
			}
			m_device->SetDepthStencilSurface(m_ownDepthStencil);
			return true;
		}

		void RenderInterfaceD3D9::ApplyUiState()
		{
			// Premultiplied alpha blending, no depth, no culling, no fixed-function lighting.
			m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			m_device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
			m_device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
			m_device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);
			m_device->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
			m_device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			m_device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
			m_device->SetRenderState(D3DRS_FOGENABLE, FALSE);
			m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			m_device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
			m_device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
			m_device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
			m_device->SetRenderState(D3DRS_SCISSORTESTENABLE, m_scissorEnabled ? TRUE : FALSE);
			m_device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
			m_device->SetRenderState(D3DRS_STENCILMASK, 0xFF);
			m_device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFF);
			m_device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
			m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);

			m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
			m_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			m_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			m_device->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, FALSE);
			m_device->SetTexture(0, nullptr);

			D3DVIEWPORT9 viewport = { 0, 0, (DWORD)m_width, (DWORD)m_height, 0.f, 1.f };
			m_device->SetViewport(&viewport);

			m_device->SetVertexDeclaration(m_vertexDeclaration);
			m_device->SetVertexShader(m_vertexShader);
			m_device->SetPixelShader(m_pixelShaderColor);
			UploadTransform();
		}

		void RenderInterfaceD3D9::BeginFrame()
		{
			if (!m_stateBlock)
				m_device->CreateStateBlock(D3DSBT_ALL, &m_stateBlock);
			if (m_stateBlock)
				m_stateBlock->Capture();
			// State blocks do not record the bound surfaces.
			m_device->GetRenderTarget(0, &m_savedRenderTarget);
			m_device->GetDepthStencilSurface(&m_savedDepthStencil);
			m_device->GetViewport(&m_savedViewport);
			EnsureDepthStencil(m_savedRenderTarget);

			m_hasTransform = false;
			m_transform = m_projection;
			m_scissorEnabled = false;
			m_clipMaskEnabled = false;
			m_stencilRef = 0;
			m_inFrame = true;
			ApplyUiState();
		}

		void RenderInterfaceD3D9::EndFrame()
		{
			m_inFrame = false;
			if (m_stateBlock)
				m_stateBlock->Apply();
			if (m_savedRenderTarget)
				m_device->SetRenderTarget(0, m_savedRenderTarget);
			m_device->SetDepthStencilSurface(m_savedDepthStencil); // may be null
			m_device->SetViewport(&m_savedViewport);
			SafeRelease(m_savedRenderTarget);
			SafeRelease(m_savedDepthStencil);
		}

		void RenderInterfaceD3D9::UploadTransform()
		{
			// Column-major in memory; the HLSL default packing puts column k in c[k].
			m_device->SetVertexShaderConstantF(0, m_transform.data(), 4);
		}

		void RenderInterfaceD3D9::SetTranslation(::Rml::Vector2f translation)
		{
			const float constant[4] = { translation.x, translation.y, 0.f, 0.f };
			m_device->SetVertexShaderConstantF(4, constant, 1);
		}

		/* geometry */

		::Rml::CompiledGeometryHandle RenderInterfaceD3D9::CompileGeometry(::Rml::Span<const ::Rml::Vertex> vertices, ::Rml::Span<const int> indices)
		{
			if (vertices.size() == 0 || indices.size() == 0 || vertices.size() > 0xFFFF)
				return 0;

			auto *geometry = new Geometry();
			geometry->numVertices = (UINT)vertices.size();
			geometry->numIndices = (UINT)indices.size();

			const UINT vbSize = geometry->numVertices * sizeof(::Rml::Vertex);
			if (FAILED(m_device->CreateVertexBuffer(vbSize, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &geometry->vertexBuffer, nullptr)))
			{
				delete geometry;
				return 0;
			}
			void *vbData = nullptr;
			if (SUCCEEDED(geometry->vertexBuffer->Lock(0, vbSize, &vbData, 0)))
			{
				if (m_supportsUByte4N)
					std::memcpy(vbData, vertices.data(), vbSize);
				else
				{
					// D3DCOLOR reads BGRA; swizzle the RGBA bytes RmlUi hands us.
					auto *dst = static_cast<::Rml::Vertex *>(vbData);
					std::memcpy(dst, vertices.data(), vbSize);
					for (size_t i = 0; i < vertices.size(); i++)
						std::swap(dst[i].colour.red, dst[i].colour.blue);
				}
				geometry->vertexBuffer->Unlock();
			}

			const UINT ibSize = geometry->numIndices * sizeof(uint16_t);
			if (FAILED(m_device->CreateIndexBuffer(ibSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &geometry->indexBuffer, nullptr)))
			{
				SafeRelease(geometry->vertexBuffer);
				delete geometry;
				return 0;
			}
			void *ibData = nullptr;
			if (SUCCEEDED(geometry->indexBuffer->Lock(0, ibSize, &ibData, 0)))
			{
				auto *dst = static_cast<uint16_t *>(ibData);
				for (size_t i = 0; i < indices.size(); i++)
					dst[i] = (uint16_t)indices.data()[i];
				geometry->indexBuffer->Unlock();
			}
			return reinterpret_cast<::Rml::CompiledGeometryHandle>(geometry);
		}

		void RenderInterfaceD3D9::DrawGeometry(const Geometry &geometry)
		{
			m_device->SetStreamSource(0, geometry.vertexBuffer, 0, sizeof(::Rml::Vertex));
			m_device->SetIndices(geometry.indexBuffer);
			m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, geometry.numVertices, 0, geometry.numIndices / 3);
		}

		void RenderInterfaceD3D9::RenderGeometry(::Rml::CompiledGeometryHandle handle, ::Rml::Vector2f translation, ::Rml::TextureHandle texture)
		{
			if (!handle || !m_inFrame)
				return;
			auto *geometry = reinterpret_cast<Geometry *>(handle);
			RML_TRACE("[rml] RenderGeometry verts=%u t=(%.1f,%.1f) tex=%d\n", geometry->numVertices, translation.x, translation.y, texture != 0);
			SetTranslation(translation);
			if (texture)
			{
				auto *slot = reinterpret_cast<TextureSlot *>(texture);
				if (!slot->texture)
					return; // still pending; draw nothing rather than a white box
				m_device->SetTexture(0, slot->texture);
				m_device->SetPixelShader(m_pixelShaderTexture);
			}
			else
			{
				m_device->SetTexture(0, nullptr);
				m_device->SetPixelShader(m_pixelShaderColor);
			}
			DrawGeometry(*geometry);
		}

		void RenderInterfaceD3D9::ReleaseGeometry(::Rml::CompiledGeometryHandle handle)
		{
			if (!handle)
				return;
			auto *geometry = reinterpret_cast<Geometry *>(handle);
			SafeRelease(geometry->vertexBuffer);
			SafeRelease(geometry->indexBuffer);
			delete geometry;
		}

		/* textures */

		TextureSlot *RenderInterfaceD3D9::CreateSlot(const std::string &source, ::Rml::Vector2i size)
		{
			auto *slot = new TextureSlot();
			slot->source = source;
			slot->size = size;
			m_slots.insert(slot);
			return slot;
		}

		void RenderInterfaceD3D9::DestroySlot(TextureSlot *slot)
		{
			if (!slot || !m_slots.erase(slot))
				return;
			if (m_slotReleased)
				m_slotReleased(slot);
			SafeRelease(slot->texture);
			delete slot;
		}

		IDirect3DTexture9 *RenderInterfaceD3D9::CreateGpuTextureFromStaging(IDirect3DTexture9 *staging, UINT width, UINT height)
		{
			// D3D9Ex refuses D3DPOOL_MANAGED and DEFAULT textures cannot be locked, so every
			// texture is filled through a SYSTEMMEM staging copy.
			IDirect3DTexture9 *gpu = nullptr;
			if (FAILED(m_device->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &gpu, nullptr)))
				return nullptr;
			if (FAILED(m_device->UpdateTexture(staging, gpu)))
			{
				SafeRelease(gpu);
				return nullptr;
			}
			return gpu;
		}

		bool RenderInterfaceD3D9::LoadImageIntoSlot(TextureSlot &slot, const void *data, size_t size)
		{
			D3DXIMAGE_INFO info = {};
			IDirect3DTexture9 *staging = nullptr;
			HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(m_device, data, (UINT)size, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
				D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, nullptr, &staging);
			if (FAILED(hr) || !staging)
			{
				LogError("image decode failed for \"" + slot.source + "\"");
				return false;
			}
			D3DSURFACE_DESC desc = {};
			staging->GetLevelDesc(0, &desc);
			D3DLOCKED_RECT locked = {};
			if (SUCCEEDED(staging->LockRect(0, &locked, nullptr, 0)))
			{
				// D3DX gives straight alpha; RmlUi expects premultiplied.
				for (UINT y = 0; y < desc.Height; y++)
				{
					auto *row = reinterpret_cast<uint8_t *>(locked.pBits) + y * locked.Pitch;
					for (UINT x = 0; x < desc.Width; x++)
					{
						uint8_t *px = row + x * 4;
						const unsigned a = px[3];
						if (a != 255)
						{
							px[0] = (uint8_t)((px[0] * a + 127) / 255);
							px[1] = (uint8_t)((px[1] * a + 127) / 255);
							px[2] = (uint8_t)((px[2] * a + 127) / 255);
						}
					}
				}
				staging->UnlockRect(0);
			}
			IDirect3DTexture9 *gpu = CreateGpuTextureFromStaging(staging, desc.Width, desc.Height);
			SafeRelease(staging);
			if (!gpu)
				return false;
			SafeRelease(slot.texture);
			slot.texture = gpu;
			slot.size = { (int)desc.Width, (int)desc.Height };
			slot.pending = false;
			return true;
		}

		bool RenderInterfaceD3D9::LoadRgbaIntoSlot(TextureSlot &slot, const uint8_t *rgba, ::Rml::Vector2i size, bool alreadyPremultiplied)
		{
			if (size.x <= 0 || size.y <= 0)
				return false;
			IDirect3DTexture9 *staging = nullptr;
			if (FAILED(m_device->CreateTexture(size.x, size.y, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &staging, nullptr)))
				return false;
			D3DLOCKED_RECT locked = {};
			if (FAILED(staging->LockRect(0, &locked, nullptr, 0)))
			{
				SafeRelease(staging);
				return false;
			}
			for (int y = 0; y < size.y; y++)
			{
				const uint8_t *src = rgba + (size_t)y * size.x * 4;
				auto *dst = reinterpret_cast<uint8_t *>(locked.pBits) + y * locked.Pitch;
				for (int x = 0; x < size.x; x++, src += 4, dst += 4)
				{
					const unsigned a = src[3];
					if (alreadyPremultiplied || a == 255)
					{
						dst[0] = src[2];
						dst[1] = src[1];
						dst[2] = src[0];
					}
					else
					{
						dst[0] = (uint8_t)((src[2] * a + 127) / 255);
						dst[1] = (uint8_t)((src[1] * a + 127) / 255);
						dst[2] = (uint8_t)((src[0] * a + 127) / 255);
					}
					dst[3] = (uint8_t)a;
				}
			}
			staging->UnlockRect(0);
			IDirect3DTexture9 *gpu = CreateGpuTextureFromStaging(staging, size.x, size.y);
			SafeRelease(staging);
			if (!gpu)
				return false;
			SafeRelease(slot.texture);
			slot.texture = gpu;
			slot.size = size;
			slot.pending = false;
			return true;
		}

		::Rml::TextureHandle RenderInterfaceD3D9::LoadTexture(::Rml::Vector2i &texture_dimensions, const ::Rml::String &rawSource)
		{
			const std::string source = SystemInterface::NormalizePath(rawSource);
			if (m_sourceHook)
			{
				if (TextureSlot *slot = m_sourceHook(source))
				{
					texture_dimensions = slot->size;
					return reinterpret_cast<::Rml::TextureHandle>(slot);
				}
			}

			::Rml::String data;
			if (!::Rml::GetFileInterface()->LoadFile(source, data) || data.empty())
			{
				LogError("cannot read texture \"" + source + "\"");
				return 0;
			}
			TextureSlot *slot = CreateSlot(source, { 0, 0 });
			if (!LoadImageIntoSlot(*slot, data.data(), data.size()))
			{
				DestroySlot(slot);
				return 0;
			}
			texture_dimensions = slot->size;
			return reinterpret_cast<::Rml::TextureHandle>(slot);
		}

		::Rml::TextureHandle RenderInterfaceD3D9::GenerateTexture(::Rml::Span<const ::Rml::byte> source, ::Rml::Vector2i source_dimensions)
		{
			// RmlUi hands us premultiplied RGBA8 (glyph atlases, generated decorator textures).
			TextureSlot *slot = CreateSlot("", source_dimensions);
			if (!LoadRgbaIntoSlot(*slot, source.data(), source_dimensions, true))
			{
				DestroySlot(slot);
				return 0;
			}
			return reinterpret_cast<::Rml::TextureHandle>(slot);
		}

		void RenderInterfaceD3D9::ReleaseTexture(::Rml::TextureHandle texture)
		{
			DestroySlot(reinterpret_cast<TextureSlot *>(texture));
		}

		/* scissor, clip mask, transform */

		void RenderInterfaceD3D9::EnableScissorRegion(bool enable)
		{
			RML_TRACE("[rml] EnableScissor %d\n", enable);
			m_scissorEnabled = enable;
			m_device->SetRenderState(D3DRS_SCISSORTESTENABLE, enable ? TRUE : FALSE);
		}

		void RenderInterfaceD3D9::SetScissorRegion(::Rml::Rectanglei region)
		{
			RML_TRACE("[rml] Scissor %d %d %d %d\n", region.Left(), region.Top(), region.Right(), region.Bottom());
			RECT rect = { region.Left(), region.Top(), region.Right(), region.Bottom() };
			rect.left = std::clamp<LONG>(rect.left, 0, m_width);
			rect.top = std::clamp<LONG>(rect.top, 0, m_height);
			rect.right = std::clamp<LONG>(rect.right, rect.left, m_width);
			rect.bottom = std::clamp<LONG>(rect.bottom, rect.top, m_height);
			m_device->SetScissorRect(&rect);
		}

		void RenderInterfaceD3D9::EnableClipMask(bool enable)
		{
			RML_TRACE("[rml] EnableClipMask %d ref=%lu\n", enable, m_stencilRef);
			m_clipMaskEnabled = enable;
			m_device->SetRenderState(D3DRS_STENCILENABLE, enable ? TRUE : FALSE);
			if (enable)
			{
				m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
				m_device->SetRenderState(D3DRS_STENCILREF, m_stencilRef);
				m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
				m_device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
				m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			}
		}

		void RenderInterfaceD3D9::RenderToClipMask(::Rml::ClipMaskOperation operation, ::Rml::CompiledGeometryHandle handle, ::Rml::Vector2f translation)
		{
			if (!handle || !m_inFrame)
				return;
			auto *geometry = reinterpret_cast<Geometry *>(handle);
			RML_TRACE("[rml] RenderToClipMask op=%d verts=%u t=(%.1f,%.1f)\n", (int)operation, geometry->numVertices, translation.x, translation.y);

			DWORD nextRef = m_stencilRef;
			switch (operation)
			{
			case ::Rml::ClipMaskOperation::Set:
				m_device->Clear(0, nullptr, D3DCLEAR_STENCIL, 0, 1.f, 0);
				m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				m_device->SetRenderState(D3DRS_STENCILREF, 1);
				nextRef = 1;
				break;
			case ::Rml::ClipMaskOperation::SetInverse:
				m_device->Clear(0, nullptr, D3DCLEAR_STENCIL, 0, 1.f, 0);
				m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				m_device->SetRenderState(D3DRS_STENCILREF, 1);
				nextRef = 0;
				break;
			case ::Rml::ClipMaskOperation::Intersect:
				m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
				nextRef = m_stencilRef + 1;
				break;
			}

			m_device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			m_device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
			m_device->SetTexture(0, nullptr);
			m_device->SetPixelShader(m_pixelShaderColor);
			SetTranslation(translation);
			DrawGeometry(*geometry);

			m_stencilRef = nextRef;
			m_device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
			m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			m_device->SetRenderState(D3DRS_STENCILREF, m_stencilRef);
			m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
			m_device->SetRenderState(D3DRS_STENCILENABLE, m_clipMaskEnabled ? TRUE : FALSE);
		}

		void RenderInterfaceD3D9::SetTransform(const ::Rml::Matrix4f *transform)
		{
			m_hasTransform = transform != nullptr;
			if (transform)
			{
				const float *m = transform->data();
				RML_TRACE("[rml] SetTransform [%.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f]\n",
					m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
			}
			else
				RML_TRACE("[rml] SetTransform none\n");
			m_transform = transform ? (m_projection * (*transform)) : m_projection;
			UploadTransform();
		}

		/* shaders (gradients) */

		::Rml::CompiledShaderHandle RenderInterfaceD3D9::CompileShader(const ::Rml::String &name, const ::Rml::Dictionary &parameters)
		{
			GradientFunc func;
			::Rml::Vector2f p, v;
			const bool repeating = ::Rml::Get(parameters, "repeating", false);
			if (name == "linear-gradient")
			{
				func = repeating ? GradientFunc::RepeatingLinear : GradientFunc::Linear;
				p = ::Rml::Get(parameters, "p0", ::Rml::Vector2f(0.f));
				v = ::Rml::Get(parameters, "p1", ::Rml::Vector2f(0.f)) - p;
			}
			else if (name == "radial-gradient")
			{
				func = repeating ? GradientFunc::RepeatingRadial : GradientFunc::Radial;
				p = ::Rml::Get(parameters, "center", ::Rml::Vector2f(0.f));
				v = ::Rml::Vector2f(1.f) / ::Rml::Get(parameters, "radius", ::Rml::Vector2f(1.f));
			}
			else if (name == "conic-gradient")
			{
				func = repeating ? GradientFunc::RepeatingConic : GradientFunc::Conic;
				p = ::Rml::Get(parameters, "center", ::Rml::Vector2f(0.f));
				const float angle = ::Rml::Get(parameters, "angle", 0.f);
				v = { ::Rml::Math::Cos(angle), ::Rml::Math::Sin(angle) };
			}
			else
				return 0; // "shader" (creation) and anything else is unsupported

			auto it = parameters.find("color_stop_list");
			if (it == parameters.end() || it->second.GetType() != ::Rml::Variant::COLORSTOPLIST)
				return 0;
			const ::Rml::ColorStopList &stops = it->second.GetReference<::Rml::ColorStopList>();
			const int numStops = std::min((int)stops.size(), 16);
			if (numStops == 0)
				return 0;

			auto *shader = new GradientShader();
			shader->params[0] = (float)(int)func;
			shader->params[1] = (float)numStops;
			shader->params[2] = stops[0].position.number;
			shader->params[3] = stops[numStops - 1].position.number;
			shader->p[0] = p.x;
			shader->p[1] = p.y;
			shader->v[0] = v.x;
			shader->v[1] = v.y;
			for (int i = 0; i < numStops; i++)
			{
				const ::Rml::ColorStop &stop = stops[i];
				shader->colors[i][0] = stop.color.red / 255.f;
				shader->colors[i][1] = stop.color.green / 255.f;
				shader->colors[i][2] = stop.color.blue / 255.f;
				shader->colors[i][3] = stop.color.alpha / 255.f;
				shader->positions[i][0] = stop.position.number;
			}
			return reinterpret_cast<::Rml::CompiledShaderHandle>(shader);
		}

		void RenderInterfaceD3D9::RenderShader(::Rml::CompiledShaderHandle shaderHandle, ::Rml::CompiledGeometryHandle geometryHandle, ::Rml::Vector2f translation, ::Rml::TextureHandle)
		{
			if (!shaderHandle || !geometryHandle || !m_inFrame)
				return;
			auto *shader = reinterpret_cast<GradientShader *>(shaderHandle);
			auto *geometry = reinterpret_cast<Geometry *>(geometryHandle);
			m_device->SetPixelShader(m_pixelShaderGradient);
			m_device->SetPixelShaderConstantF(0, shader->params, 1);
			m_device->SetPixelShaderConstantF(1, shader->p, 1);
			m_device->SetPixelShaderConstantF(2, shader->v, 1);
			m_device->SetPixelShaderConstantF(3, &shader->colors[0][0], 16);
			m_device->SetPixelShaderConstantF(19, &shader->positions[0][0], 16);
			m_device->SetTexture(0, nullptr);
			SetTranslation(translation);
			DrawGeometry(*geometry);
		}

		void RenderInterfaceD3D9::ReleaseShader(::Rml::CompiledShaderHandle shader)
		{
			delete reinterpret_cast<GradientShader *>(shader);
		}
	}
}

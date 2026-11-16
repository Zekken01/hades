#ifndef __WEB_RML_RENDERINTERFACED3D9_HPP__
#define __WEB_RML_RENDERINTERFACED3D9_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Core/RenderInterface.h>
#include <RmlUi/Core/Types.h>

#include <d3d9.h>

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		// A texture as RmlUi sees it.  The GPU texture behind a slot may arrive later (emblems
		// rendered by the game, images downloaded over HTTP), so RmlUi only ever holds the slot
		// pointer and the inner texture can be swapped while the slot stays valid.
		struct TextureSlot
		{
			IDirect3DTexture9 *texture = nullptr;
			::Rml::Vector2i size;
			std::string source;
			bool pending = false;
		};

		// Rml::RenderInterface over the game's IDirect3DDevice9 (D3D9Ex).  Implements the required
		// set plus clip masks (stencil), transforms and gradient shaders.  Layers, filters and
		// render-to-texture are not implemented, so `filter`, `backdrop-filter`, `mask-image` and
		// `box-shadow` are ignored by RmlUi.
		class RenderInterfaceD3D9 final : public ::Rml::RenderInterface
		{
		public:
			// Called by the asset code when LoadTexture sees a source it does not know how to read
			// (emblems://, http://).  Returns a slot, or nullptr to fall back to the file interface.
			using SourceHook = std::function<TextureSlot *(const std::string &source)>;

			explicit RenderInterfaceD3D9(IDirect3DDevice9 *device);
			~RenderInterfaceD3D9() override;

			bool Initialize();
			void SetViewport(int width, int height);
			void BeginFrame();
			void EndFrame();
			void OnPreReset();
			void OnPostReset();

			IDirect3DDevice9 *GetDevice() const { return m_device; }
			void SetSourceHook(SourceHook hook) { m_sourceHook = std::move(hook); }
			void SetSlotReleasedHook(std::function<void(TextureSlot *)> hook) { m_slotReleased = std::move(hook); }

			// Slot management for deferred textures.
			TextureSlot *CreateSlot(const std::string &source, ::Rml::Vector2i size);
			bool IsSlotAlive(TextureSlot *slot) const { return m_slots.count(slot) != 0; }
			// Decodes PNG/JPG/BMP/TGA/DDS bytes with D3DX, premultiplies, and installs the result.
			bool LoadImageIntoSlot(TextureSlot &slot, const void *data, size_t size);
			// Installs straight RGBA8 pixels (premultiplied on the way in unless already so).
			bool LoadRgbaIntoSlot(TextureSlot &slot, const uint8_t *rgba, ::Rml::Vector2i size, bool alreadyPremultiplied);

			// Rml::RenderInterface -- required
			::Rml::CompiledGeometryHandle CompileGeometry(::Rml::Span<const ::Rml::Vertex> vertices, ::Rml::Span<const int> indices) override;
			void RenderGeometry(::Rml::CompiledGeometryHandle geometry, ::Rml::Vector2f translation, ::Rml::TextureHandle texture) override;
			void ReleaseGeometry(::Rml::CompiledGeometryHandle geometry) override;
			::Rml::TextureHandle LoadTexture(::Rml::Vector2i &texture_dimensions, const ::Rml::String &source) override;
			::Rml::TextureHandle GenerateTexture(::Rml::Span<const ::Rml::byte> source, ::Rml::Vector2i source_dimensions) override;
			void ReleaseTexture(::Rml::TextureHandle texture) override;
			void EnableScissorRegion(bool enable) override;
			void SetScissorRegion(::Rml::Rectanglei region) override;

			// Rml::RenderInterface -- optional
			void EnableClipMask(bool enable) override;
			void RenderToClipMask(::Rml::ClipMaskOperation operation, ::Rml::CompiledGeometryHandle geometry, ::Rml::Vector2f translation) override;
			void SetTransform(const ::Rml::Matrix4f *transform) override;
			::Rml::CompiledShaderHandle CompileShader(const ::Rml::String &name, const ::Rml::Dictionary &parameters) override;
			void RenderShader(::Rml::CompiledShaderHandle shader, ::Rml::CompiledGeometryHandle geometry, ::Rml::Vector2f translation, ::Rml::TextureHandle texture) override;
			void ReleaseShader(::Rml::CompiledShaderHandle shader) override;

		private:
			struct Geometry
			{
				IDirect3DVertexBuffer9 *vertexBuffer = nullptr;
				IDirect3DIndexBuffer9 *indexBuffer = nullptr;
				UINT numVertices = 0;
				UINT numIndices = 0;
			};

			enum class GradientFunc : int
			{
				Linear = 0,
				Radial = 1,
				Conic = 2,
				RepeatingLinear = 3,
				RepeatingRadial = 4,
				RepeatingConic = 5,
			};

			struct GradientShader
			{
				float params[4] = {}; // func, num_stops, first stop position, last stop position
				float p[4] = {};
				float v[4] = {};
				float colors[16][4] = {};
				float positions[16][4] = {};
			};

			bool CreateShaders();
			void ReleaseShaders();
			bool EnsureDepthStencil(IDirect3DSurface9 *renderTarget);
			void ApplyUiState();
			void UploadTransform();
			void SetTranslation(::Rml::Vector2f translation);
			void DrawGeometry(const Geometry &geometry);
			IDirect3DTexture9 *CreateGpuTextureFromStaging(IDirect3DTexture9 *staging, UINT width, UINT height);
			void DestroySlot(TextureSlot *slot);

			IDirect3DDevice9 *m_device;
			IDirect3DVertexDeclaration9 *m_vertexDeclaration = nullptr;
			IDirect3DVertexShader9 *m_vertexShader = nullptr;
			IDirect3DPixelShader9 *m_pixelShaderColor = nullptr;
			IDirect3DPixelShader9 *m_pixelShaderTexture = nullptr;
			IDirect3DPixelShader9 *m_pixelShaderGradient = nullptr;
			IDirect3DStateBlock9 *m_stateBlock = nullptr;
			IDirect3DSurface9 *m_ownDepthStencil = nullptr;
			IDirect3DSurface9 *m_savedRenderTarget = nullptr;
			IDirect3DSurface9 *m_savedDepthStencil = nullptr;
			D3DVIEWPORT9 m_savedViewport = {};
			::Rml::Matrix4f m_projection;
			::Rml::Matrix4f m_transform;
			bool m_hasTransform = false;
			int m_width = 0;
			int m_height = 0;
			bool m_inFrame = false;
			bool m_scissorEnabled = false;
			bool m_clipMaskEnabled = false;
			DWORD m_stencilRef = 0;
			bool m_supportsUByte4N = true;
			std::unordered_set<TextureSlot *> m_slots;
			SourceHook m_sourceHook;
			std::function<void(TextureSlot *)> m_slotReleased;
		};
	}
}

#endif // __WEB_RML_RENDERINTERFACED3D9_HPP__

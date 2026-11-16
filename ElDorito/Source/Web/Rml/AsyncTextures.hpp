#ifndef __WEB_RML_ASYNCTEXTURES_HPP__
#define __WEB_RML_ASYNCTEXTURES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/RenderInterfaceD3D9.hpp"

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Http
{
	class IHttpRequest;
}

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		class FileInterface;

		// Textures whose pixels arrive later than RmlUi asks for them:
		//   emblems://...  rendered by the game GPU (Player::Emblems::PlayerEmblemRenderer)
		//   http(s)://...  downloaded with the game's WinHTTP client into data/cache/ui
		// RmlUi gets a slot straight away; Pump() fills it when the bytes are in.
		class AsyncTextures
		{
		public:
			using FetchCallback = std::function<void(bool ok, const std::string &cacheUrl)>;

			AsyncTextures(RenderInterfaceD3D9 &render, FileInterface &files);
			~AsyncTextures();

			// RenderInterfaceD3D9 source hook: returns a slot for the schemes above, else nullptr.
			TextureSlot *Request(const std::string &source);
			// Download an image for Lua; the callback runs from Pump() with a dew://cache/ url.
			void FetchImage(const std::string &url, FetchCallback callback);
			// Finish completed loads; call once per frame on the game/render thread.
			void Pump();
			void OnSlotReleased(TextureSlot *slot);
			void CancelAll();

		private:
			struct Pending;
			class EmblemSink;

			void StartEmblem(std::shared_ptr<Pending> pending, const std::string &source);
			void StartHttp(std::shared_ptr<Pending> pending, const std::string &url);
			std::string CacheFileFor(const std::string &url) const;

			RenderInterfaceD3D9 &m_render;
			FileInterface &m_files;
			std::mutex m_mutex;
			std::vector<std::shared_ptr<Pending>> m_pending;
		};
	}
}

#endif // __WEB_RML_ASYNCTEXTURES_HPP__

/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/AsyncTextures.hpp"

#include "Common/Http/HttpRequest.hpp"
#include "Player/PlayerEmblemRenderer.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Rml/FileInterface.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>

/* ---------- prototypes */

namespace Http { extern std::shared_ptr<Http::IHttpRequest> CreateRequest(); }
namespace Player { namespace Emblems { extern bool ParseURL(std::string const &url, s_player_emblem_configuration &config); } }

/* ---------- private code */

namespace
{
	const int kEmblemPlaceholderSize = 256;

	void LogWarning(const std::string &message)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Warning, "RmlUi textures: " + message);
	}

	std::string Fnv1aHex(const std::string &text)
	{
		uint64_t hash = 1469598103934665603ull;
		for (unsigned char c : text)
		{
			hash ^= c;
			hash *= 1099511628211ull;
		}
		char buffer[17];
		sprintf_s(buffer, "%016llx", hash);
		return buffer;
	}

	bool StartsWithNoCase(const std::string &text, const char *prefix)
	{
		const size_t length = strlen(prefix);
		return text.size() >= length && _strnicmp(text.c_str(), prefix, length) == 0;
	}
}

namespace Web
{
	namespace RmlUi
	{
		enum class PendingState : int
		{
			Loading = 0,
			Done,
			Failed,
			Finished,
		};

		struct AsyncTextures::Pending
		{
			TextureSlot *slot = nullptr;        // null when the slot was released before completion
			std::string source;
			std::string cachePath;              // http only
			std::string cacheUrl;               // http only
			std::vector<uint8_t> bytes;
			std::atomic<int> state = (int)PendingState::Loading;
			std::shared_ptr<EmblemSink> sink;
			std::shared_ptr<Http::IHttpRequest> request;
			std::shared_ptr<Player::Emblems::IPlayerEmblemStream> stream;
			AsyncTextures::FetchCallback callback;
			std::mutex bytesMutex;
		};

		// Collects the PNG the emblem renderer streams out (it runs during EndScene).
		class AsyncTextures::EmblemSink final : public Player::Emblems::IPlayerEmblemRenderCallbacks
		{
		public:
			explicit EmblemSink(std::weak_ptr<Pending> pending) : m_pending(std::move(pending)) {}

			void OnRenderStart(Player::Emblems::PlayerEmblemRenderMetadata const &, std::shared_ptr<Player::Emblems::IPlayerEmblemStream> stream) override
			{
				if (auto pending = m_pending.lock())
				{
					std::lock_guard<std::mutex> lock(pending->bytesMutex);
					pending->stream = std::move(stream);
				}
			}

			void OnRenderDataAvailable() override
			{
				auto pending = m_pending.lock();
				if (!pending)
					return;
				std::lock_guard<std::mutex> lock(pending->bytesMutex);
				if (!pending->stream)
					return;
				char chunk[16 * 1024];
				int read = 0;
				while (pending->stream->Read(chunk, sizeof(chunk), &read) && read > 0)
					pending->bytes.insert(pending->bytes.end(), chunk, chunk + read);
			}

			void OnRenderComplete() override
			{
				if (auto pending = m_pending.lock())
				{
					OnRenderDataAvailable();
					pending->state = (int)PendingState::Done;
				}
			}

		private:
			std::weak_ptr<Pending> m_pending;
		};

		AsyncTextures::AsyncTextures(RenderInterfaceD3D9 &render, FileInterface &files) : m_render(render), m_files(files)
		{
		}

		AsyncTextures::~AsyncTextures()
		{
			CancelAll();
		}

		TextureSlot *AsyncTextures::Request(const std::string &source)
		{
			if (StartsWithNoCase(source, "emblems://"))
			{
				auto pending = std::make_shared<Pending>();
				pending->source = source;
				pending->slot = m_render.CreateSlot(source, { kEmblemPlaceholderSize, kEmblemPlaceholderSize });
				pending->slot->pending = true;
				StartEmblem(pending, source);
				return pending->slot;
			}
			if (StartsWithNoCase(source, "http://") || StartsWithNoCase(source, "https://"))
			{
				auto pending = std::make_shared<Pending>();
				pending->source = source;
				pending->slot = m_render.CreateSlot(source, { kEmblemPlaceholderSize, kEmblemPlaceholderSize });
				pending->slot->pending = true;
				StartHttp(pending, source);
				return pending->slot;
			}
			return nullptr;
		}

		void AsyncTextures::FetchImage(const std::string &url, FetchCallback callback)
		{
			auto pending = std::make_shared<Pending>();
			pending->source = url;
			pending->callback = std::move(callback);
			// Already cached: answer on the next Pump() without a request.
			pending->cachePath = CacheFileFor(url);
			pending->cacheUrl = "dew://cache/" + std::filesystem::path(pending->cachePath).filename().string();
			std::error_code ec;
			if (std::filesystem::exists(pending->cachePath, ec))
			{
				pending->state = (int)PendingState::Done;
				std::lock_guard<std::mutex> lock(m_mutex);
				m_pending.push_back(pending);
				return;
			}
			StartHttp(pending, url);
		}

		std::string AsyncTextures::CacheFileFor(const std::string &url) const
		{
			std::string extension = ".png";
			const size_t query = url.find_first_of("?#");
			const std::string path = url.substr(0, query);
			const size_t dot = path.find_last_of('.');
			const size_t slash = path.find_last_of('/');
			if (dot != std::string::npos && (slash == std::string::npos || dot > slash) && path.size() - dot <= 5)
				extension = path.substr(dot);
			return (m_files.GetCacheDirectory() / (Fnv1aHex(url) + extension)).string();
		}

		void AsyncTextures::StartEmblem(std::shared_ptr<Pending> pending, const std::string &source)
		{
			s_player_emblem_configuration config = {};
			if (!Player::Emblems::ParseURL(source, config))
				config = {};
			pending->sink = std::make_shared<EmblemSink>(pending);
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_pending.push_back(pending);
			}
			if (!Player::Emblems::PlayerEmblemRenderer::StartRender(config, pending->sink))
				pending->state = (int)PendingState::Failed;
		}

		void AsyncTextures::StartHttp(std::shared_ptr<Pending> pending, const std::string &url)
		{
			if (pending->cachePath.empty())
			{
				pending->cachePath = CacheFileFor(url);
				pending->cacheUrl = "dew://cache/" + std::filesystem::path(pending->cachePath).filename().string();
			}
			std::error_code ec;
			if (std::filesystem::exists(pending->cachePath, ec))
			{
				// Serve from the cache: Pump() reads the file.
				pending->state = (int)PendingState::Done;
				std::lock_guard<std::mutex> lock(m_mutex);
				m_pending.push_back(pending);
				return;
			}

			std::weak_ptr<Pending> weak = pending;
			auto request = Http::CreateRequest();
			if (!request)
			{
				pending->state = (int)PendingState::Failed;
				std::lock_guard<std::mutex> lock(m_mutex);
				m_pending.push_back(pending);
				return;
			}
			request->SetMethod("GET");
			request->SetUrl(url);
			request->SetMaxRedirects(5);
			request->SetReceiver([weak](const char *data, unsigned int length) -> bool {
				auto p = weak.lock();
				if (!p)
					return false;
				std::lock_guard<std::mutex> lock(p->bytesMutex);
				p->bytes.insert(p->bytes.end(), data, data + length);
				return true;
			});
			request->SetOnCompleted([weak](std::shared_ptr<Http::IHttpRequest> req, bool success) {
				auto p = weak.lock();
				if (!p)
					return;
				int code = 0;
				if (auto response = req->GetResponse())
					code = response->GetResponseCode();
				p->state = (int)((success && code >= 200 && code < 300) ? PendingState::Done : PendingState::Failed);
			});
			pending->request = request;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_pending.push_back(pending);
			}
			if (!request->Send())
				pending->state = (int)PendingState::Failed;
		}

		void AsyncTextures::Pump()
		{
			std::vector<std::shared_ptr<Pending>> ready;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				for (auto it = m_pending.begin(); it != m_pending.end();)
				{
					const int state = (*it)->state.load();
					if (state == (int)PendingState::Done || state == (int)PendingState::Failed)
					{
						ready.push_back(*it);
						it = m_pending.erase(it);
					}
					else
						++it;
				}
			}

			for (auto &pending : ready)
			{
				bool ok = pending->state.load() == (int)PendingState::Done;
				std::vector<uint8_t> bytes;
				{
					std::lock_guard<std::mutex> lock(pending->bytesMutex);
					bytes.swap(pending->bytes);
					pending->stream.reset();
				}
				pending->request.reset();
				pending->sink.reset();

				if (ok && !pending->cachePath.empty())
				{
					std::error_code ec;
					if (bytes.empty() && std::filesystem::exists(pending->cachePath, ec))
					{
						std::ifstream in(pending->cachePath, std::ios::binary);
						bytes.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
					}
					else if (!bytes.empty())
					{
						std::filesystem::create_directories(m_files.GetCacheDirectory(), ec);
						std::ofstream out(pending->cachePath, std::ios::binary | std::ios::trunc);
						out.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
					}
				}
				if (ok && bytes.empty())
					ok = false;

				if (pending->slot && m_render.IsSlotAlive(pending->slot))
				{
					if (ok)
						ok = m_render.LoadImageIntoSlot(*pending->slot, bytes.data(), bytes.size());
					pending->slot->pending = false;
				}
				if (!ok)
					LogWarning("failed to load \"" + pending->source + "\"");
				if (pending->callback)
					pending->callback(ok, ok ? pending->cacheUrl : std::string());
				pending->state = (int)PendingState::Finished;
			}
		}

		void AsyncTextures::OnSlotReleased(TextureSlot *slot)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			for (auto &pending : m_pending)
				if (pending->slot == slot)
					pending->slot = nullptr;
		}

		void AsyncTextures::CancelAll()
		{
			std::vector<std::shared_ptr<Pending>> pending;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				pending.swap(m_pending);
			}
			for (auto &p : pending)
			{
				if (p->request)
					p->request->Cancel();
				p->slot = nullptr;
			}
		}
	}
}

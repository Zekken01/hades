/* ---------- headers */

#include "Player/PlayerEmblemRenderer.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "mods/mod_package_updater.hpp"
#include "Patches/CustomPackets.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/ostreamwrapper.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/stream.h"

#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct ID3DXBuffer;
struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		class IPlayerEmblemRenderCallbacks;
		class IPlayerEmblemStream;
		class PlayerEmblemD3DXBufferStream;
		class PlayerEmblemFileStream;
		class PlayerEmblemRenderer;
		struct PlayerEmblemRenderMetadata;
		struct PlayerEmblemRenderTask;
	}
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	namespace Emblems
	{
		// hades: moved from hades/recovered_types.h, where its member types were not visible
		struct PlayerEmblemRenderTask
		{
			s_player_emblem_configuration config; // 0x0
			std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks> callback; // 0x14
		public:
			PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask &&);
			PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask const &);
			PlayerEmblemRenderTask();
			~PlayerEmblemRenderTask();
		};
		static_assert32(sizeof(PlayerEmblemRenderTask) == 28, "Invalid PlayerEmblemRenderTask size");
	}
}

namespace Player
{
	namespace Emblems
	{
		// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
		struct PlayerEmblemFileStream :
			public Player::Emblems::IPlayerEmblemStream
		{
			virtual ~PlayerEmblemFileStream();
			virtual bool Read(void *, int, int *);
			_iobuf * m_fp; // 0x4
		public:
			void Close();
			PlayerEmblemFileStream();
		};
		static_assert32(sizeof(PlayerEmblemFileStream) == 8, "Invalid PlayerEmblemFileStream size");

		// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
		struct PlayerEmblemD3DXBufferStream :
			public Player::Emblems::PlayerEmblemFileStream
		{
			virtual ~PlayerEmblemD3DXBufferStream();
			virtual bool Read(void *, int, int *);
			ID3DXBuffer * m_buff; // 0x8
			bool m_ownsBuff; // 0xC
			unsigned char __pad0[3]; // 0xD
			int m_pos; // 0x10
			int m_size; // 0x14
			unsigned __int8 * m_data; // 0x18
		public:
			PlayerEmblemD3DXBufferStream(ID3DXBuffer *, bool);
		public:
			PlayerEmblemD3DXBufferStream();
		};
		static_assert32(sizeof(PlayerEmblemD3DXBufferStream) == 28, "Invalid PlayerEmblemD3DXBufferStream size");
	}
}

// Player::Emblems::PlayerEmblemRenderTask is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Player::Emblems::PlayerEmblemFileStream is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

typedef IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9;
namespace Player
{
	typedef rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> JsonWriter;
}

// Player::Emblems::PlayerEmblemD3DXBufferStream is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Player
{
	namespace Emblems
	{
		extern void ProcessRenderTask(Player::Emblems::PlayerEmblemRenderTask const &task);
	}
}

/* ---------- globals */

namespace Player
{
	namespace Emblems
	{
		std::queue<Player::Emblems::PlayerEmblemRenderTask> g_renderTaskQueue; // 0x1138E3D4
		std::mutex g_renderTaskQueueMutex; // 0x1138E3E8
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		_inline PlayerEmblemFileStream::PlayerEmblemFileStream() // 0x107E6FB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0PlayerEmblemFileStream@Emblems@Player@@QAE@XZ");

			m_fp = nullptr;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerEmblemRenderMetadata@Emblems@Player@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@$$QAU012@@Z"); no body to assert in
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask &&__that) = default; // 0x107E7070

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@ABU012@@Z"); no body to assert in
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask const &__that) = default; // 0x107E7110

		_inline PlayerEmblemFileStream::~PlayerEmblemFileStream() // 0x107E7620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1PlayerEmblemFileStream@Emblems@Player@@UAE@XZ");

			Close();
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@XZ"); no body to assert in
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask() = default; // 0x107E71B0

		// mangled_x86(MANGLED_DEFAULT, "??1PlayerEmblemRenderMetadata@Emblems@Player@@QAE@XZ"); no body to assert in
		_inline PlayerEmblemRenderMetadata::~PlayerEmblemRenderMetadata() = default; // 0x107E76C0
	}
}

// hades: s_player_emblem_configuration's constructor is implicit (0x107E7210)

namespace Player
{
	namespace Emblems
	{
		// mangled_x86(MANGLED_DEFAULT, "??1PlayerEmblemRenderTask@Emblems@Player@@QAE@XZ"); no body to assert in
		_inline PlayerEmblemRenderTask::~PlayerEmblemRenderTask() = default; // 0x107E7710

		_inline void PlayerEmblemFileStream::Close() // 0x107E7BF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Close@PlayerEmblemFileStream@Emblems@Player@@QAEXXZ");

			if (m_fp)
			{
				fclose(m_fp);
				m_fp = nullptr;
			}
		}

		_inline bool PlayerEmblemFileStream::Read(void *data, __int32 bytesToRead, __int32 *bytesRead) // 0x107E8130
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Read@PlayerEmblemFileStream@Emblems@Player@@UAE_NPAXHPAH@Z");

			if (!m_fp)
			{
				return false;
			}

			*bytesRead = fread(data, 1, bytesToRead, m_fp);
			if (ferror(m_fp) != 0)
			{
				return false;
			}

			return true;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0IPlayerEmblemStream@Emblems@Player@@QAE@XZ"); no body to assert in

		_inline PlayerEmblemD3DXBufferStream::PlayerEmblemD3DXBufferStream(ID3DXBuffer *buff, bool owner) // 0x107E6EA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0PlayerEmblemD3DXBufferStream@Emblems@Player@@QAE@PAUID3DXBuffer@@_N@Z");

			m_buff = buff;
			m_ownsBuff = owner;
			m_pos = 0;
			m_size = buff->GetBufferSize();
			m_data = (unsigned char *)buff->GetBufferPointer();
		}

		_inline PlayerEmblemD3DXBufferStream::~PlayerEmblemD3DXBufferStream() // 0x107E7550
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1PlayerEmblemD3DXBufferStream@Emblems@Player@@UAE@XZ");

			if (m_ownsBuff)
				m_buff->Release();
			m_buff = nullptr;
		}

		_inline bool PlayerEmblemD3DXBufferStream::Read(void *data, __int32 bytesToRead, __int32 *bytesRead) // 0x107E8070
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Read@PlayerEmblemD3DXBufferStream@Emblems@Player@@UAE_NPAXHPAH@Z");

			int n = std::min(bytesToRead, m_size - m_pos);
			memcpy(data, m_data, n);
			*bytesRead = n;
			m_pos += n;
			return true;
		}

		void ProcessRenderTask(Player::Emblems::PlayerEmblemRenderTask const &task) // 0x107E7DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessRenderTask@Emblems@Player@@YAXABUPlayerEmblemRenderTask@12@@Z");

			IDirect3DTexture9 *texture;
			if (GenerateEmblem(task.config, &texture, false))
			{
				ID3DXBuffer *buff;
				if (D3DXSaveTextureToFileInMemory(&buff, D3DXIFF_PNG, texture, nullptr) >= 0)
				{
					std::shared_ptr<PlayerEmblemD3DXBufferStream> stream = std::make_shared<PlayerEmblemD3DXBufferStream>(buff, true);
					PlayerEmblemRenderMetadata metadata;
					metadata.mimeType = "image/png";
					task.callback->OnRenderStart(metadata, stream);
					task.callback->OnRenderDataAvailable();
					task.callback->OnRenderComplete();
				}
			}
		}

		bool PlayerEmblemRenderer::StartRender(s_player_emblem_configuration const &config, std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks> handler) // 0x107E81D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartRender@PlayerEmblemRenderer@Emblems@Player@@SA_NABUs_player_emblem_configuration@@V?$shared_ptr@VIPlayerEmblemRenderCallbacks@Emblems@Player@@@std@@@Z");

			PlayerEmblemRenderTask task;
			task.config = config;
			task.callback = std::move(handler);
			std::scoped_lock<std::mutex> lock(g_renderTaskQueueMutex);
			g_renderTaskQueue.push(task);
			return true;
		}

		void PlayerEmblemRenderer::DoRender() // 0x107E7C60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DoRender@PlayerEmblemRenderer@Emblems@Player@@SAXXZ");

			std::queue<PlayerEmblemRenderTask> queue;
			{
				std::scoped_lock<std::mutex> lock(g_renderTaskQueueMutex);
				queue = std::move(g_renderTaskQueue);
			}
			while (!queue.empty())
			{
				PlayerEmblemRenderTask task = std::move(queue.front());
				queue.pop();
				ProcessRenderTask(task);
			}
		}
	}
}

/* ---------- private code */

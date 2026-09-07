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

// Player::Emblems::PlayerEmblemRenderTask is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Player::Emblems::PlayerEmblemFileStream is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

typedef IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9;
namespace Player
{
	typedef rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> JsonWriter;
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
		extern std::queue<Player::Emblems::PlayerEmblemRenderTask,std::deque<Player::Emblems::PlayerEmblemRenderTask,std::allocator<Player::Emblems::PlayerEmblemRenderTask> > > g_renderTaskQueue; // 0x1138E3D4
		extern std::mutex g_renderTaskQueueMutex; // 0x1138E3E8
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		extern PlayerEmblemFileStream* _sub_107E6FB0(Player::Emblems::PlayerEmblemFileStream *const);
		_inline PlayerEmblemFileStream::PlayerEmblemFileStream() // 0x107E6FB0
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemFileStream@Emblems@Player@@QAE@XZ");
			// Player::Emblems::PlayerEmblemFileStream *const this;
			todo("implement");
			_sub_107E6FB0(this);
		}

		extern PlayerEmblemRenderMetadata* _sub_107E7020(Player::Emblems::PlayerEmblemRenderMetadata *const);
		_inline PlayerEmblemRenderMetadata::PlayerEmblemRenderMetadata() // 0x107E7020
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemRenderMetadata@Emblems@Player@@QAE@XZ");
			// Player::Emblems::PlayerEmblemRenderMetadata *const this;
			compiler_generated();
			todo("implement");
			_sub_107E7020(this);
		}

		extern PlayerEmblemRenderTask* _sub_107E7070(Player::Emblems::PlayerEmblemRenderTask *const, Player::Emblems::PlayerEmblemRenderTask &);
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask &&__that) // 0x107E7070
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@$$QAU012@@Z");
			// Player::Emblems::PlayerEmblemRenderTask &__that;
			compiler_generated();
			todo("implement");
			_sub_107E7070(this, __that);
		}

		extern PlayerEmblemRenderTask* _sub_107E7110(Player::Emblems::PlayerEmblemRenderTask *const, Player::Emblems::PlayerEmblemRenderTask const &);
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask(Player::Emblems::PlayerEmblemRenderTask const &__that) // 0x107E7110
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@ABU012@@Z");
			// Player::Emblems::PlayerEmblemRenderTask const &__that;
			compiler_generated();
			todo("implement");
			_sub_107E7110(this, __that);
		}

		_extern void _sub_107E7620(Player::Emblems::PlayerEmblemFileStream *const);
		_inline PlayerEmblemFileStream::~PlayerEmblemFileStream() // 0x107E7620
		{
			mangled_x86(MANGLED_TODO, "??1PlayerEmblemFileStream@Emblems@Player@@UAE@XZ");
			// Player::Emblems::PlayerEmblemFileStream *const this;
			todo("implement");
			_sub_107E7620(this);
		}

		extern PlayerEmblemRenderTask* _sub_107E71B0(Player::Emblems::PlayerEmblemRenderTask *const);
		_inline PlayerEmblemRenderTask::PlayerEmblemRenderTask() // 0x107E71B0
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemRenderTask@Emblems@Player@@QAE@XZ");
			// Player::Emblems::PlayerEmblemRenderTask *const this;
			compiler_generated();
			todo("implement");
			_sub_107E71B0(this);
		}

		_extern void _sub_107E76C0(Player::Emblems::PlayerEmblemRenderMetadata *const);
		_inline PlayerEmblemRenderMetadata::~PlayerEmblemRenderMetadata() // 0x107E76C0
		{
			mangled_x86(MANGLED_TODO, "??1PlayerEmblemRenderMetadata@Emblems@Player@@QAE@XZ");
			// Player::Emblems::PlayerEmblemRenderMetadata *const this;
			compiler_generated();
			todo("implement");
			_sub_107E76C0(this);
		}
	}
}

extern s_player_emblem_configuration* _sub_107E7210(s_player_emblem_configuration *const);
_inline s_player_emblem_configuration::s_player_emblem_configuration() // 0x107E7210
{
	mangled_x86(MANGLED_TODO, "??0s_player_emblem_configuration@@QAE@XZ");
	// s_player_emblem_configuration *const this;
	compiler_generated();
	todo("implement");
	_sub_107E7210(this);
}

namespace Player
{
	namespace Emblems
	{
		_extern void _sub_107E7710(Player::Emblems::PlayerEmblemRenderTask *const);
		_inline PlayerEmblemRenderTask::~PlayerEmblemRenderTask() // 0x107E7710
		{
			mangled_x86(MANGLED_TODO, "??1PlayerEmblemRenderTask@Emblems@Player@@QAE@XZ");
			// Player::Emblems::PlayerEmblemRenderTask *const this;
			compiler_generated();
			todo("implement");
			_sub_107E7710(this);
		}

		_extern void _sub_107E7BF0(Player::Emblems::PlayerEmblemFileStream *const);
		_inline void PlayerEmblemFileStream::Close() // 0x107E7BF0
		{
			mangled_x86(MANGLED_TODO, "?Close@PlayerEmblemFileStream@Emblems@Player@@QAEXXZ");
			// Player::Emblems::PlayerEmblemFileStream *const this;
			todo("implement");
			_sub_107E7BF0(this);
		}

		_extern bool _sub_107E8130(Player::Emblems::PlayerEmblemFileStream *const, void *, __int32, __int32 *);
		_inline bool PlayerEmblemFileStream::Read(void *data, __int32 bytesToRead, __int32 *bytesRead) // 0x107E8130
		{
			mangled_x86(MANGLED_TODO, "?Read@PlayerEmblemFileStream@Emblems@Player@@UAE_NPAXHPAH@Z");
			// __int32 *bytesRead;
			todo("implement");
			bool __result = _sub_107E8130(this, data, bytesToRead, bytesRead);
			return __result;
		}

		extern IPlayerEmblemStream* _sub_107E6E70(Player::Emblems::IPlayerEmblemStream *const);
		_inline IPlayerEmblemStream::IPlayerEmblemStream() // 0x107E6E70
		{
			mangled_x86(MANGLED_TODO, "??0IPlayerEmblemStream@Emblems@Player@@QAE@XZ");
			// Player::Emblems::IPlayerEmblemStream *const this;
			compiler_generated();
			todo("implement");
			_sub_107E6E70(this);
		}

		extern PlayerEmblemD3DXBufferStream* _sub_107E6EA0(Player::Emblems::PlayerEmblemD3DXBufferStream *const, ID3DXBuffer *, bool);
		_inline PlayerEmblemD3DXBufferStream::PlayerEmblemD3DXBufferStream(ID3DXBuffer *buff, bool owner) // 0x107E6EA0
		{
			mangled_x86(MANGLED_TODO, "??0PlayerEmblemD3DXBufferStream@Emblems@Player@@QAE@PAUID3DXBuffer@@_N@Z");
			// bool owner;
			// function call : unsigned long ()
			// function call : void *()
			todo("implement");
			_sub_107E6EA0(this, buff, owner);
		}

		_extern void _sub_107E7550(Player::Emblems::PlayerEmblemD3DXBufferStream *const);
		_inline PlayerEmblemD3DXBufferStream::~PlayerEmblemD3DXBufferStream() // 0x107E7550
		{
			mangled_x86(MANGLED_TODO, "??1PlayerEmblemD3DXBufferStream@Emblems@Player@@UAE@XZ");
			// Player::Emblems::PlayerEmblemD3DXBufferStream *const this;
			// function call : unsigned long ()
			todo("implement");
			_sub_107E7550(this);
		}

		_extern bool _sub_107E8070(Player::Emblems::PlayerEmblemD3DXBufferStream *const, void *, __int32, __int32 *);
		_inline bool PlayerEmblemD3DXBufferStream::Read(void *data, __int32 bytesToRead, __int32 *bytesRead) // 0x107E8070
		{
			mangled_x86(MANGLED_TODO, "?Read@PlayerEmblemD3DXBufferStream@Emblems@Player@@UAE_NPAXHPAH@Z");
			// __int32 *bytesRead;
			// __int32 n;
			todo("implement");
			bool __result = _sub_107E8070(this, data, bytesToRead, bytesRead);
			return __result;
		}

		_extern void _sub_107E7DF0(Player::Emblems::PlayerEmblemRenderTask const &);
		void ProcessRenderTask(Player::Emblems::PlayerEmblemRenderTask const &task) // 0x107E7DF0
		{
			mangled_x86(MANGLED_TODO, "?ProcessRenderTask@Emblems@Player@@YAXABUPlayerEmblemRenderTask@12@@Z");
			// static ...; // 0x107E7FE5
			// static ...; // 0x107E7FE0
			// static ...; // 0x107E7FD9
			// static ...; // 0x107E7FD0
			// static ...; // 0x107E7FA0
			// static ...; // 0x107E7F98
			// Player::Emblems::PlayerEmblemRenderTask const &task;
			// IDirect3DTexture9 *texture;
			{
				// ID3DXBuffer *buff;
				{
					// Player::Emblems::PlayerEmblemRenderMetadata metadata;
					// std::shared_ptr<Player::Emblems::PlayerEmblemD3DXBufferStream> stream;
				}
			}
			// function call : void (Player::Emblems::PlayerEmblemRenderMetadata const &, std::shared_ptr<Player::Emblems::IPlayerEmblemStream>)
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_107E7DF0(task);
		}

		_extern bool _sub_107E81D0(s_player_emblem_configuration const &, std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks>);
		bool PlayerEmblemRenderer::StartRender(s_player_emblem_configuration const &config, std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks> handler) // 0x107E81D0
		{
			mangled_x86(MANGLED_TODO, "?StartRender@PlayerEmblemRenderer@Emblems@Player@@SA_NABUs_player_emblem_configuration@@V?$shared_ptr@VIPlayerEmblemRenderCallbacks@Emblems@Player@@@std@@@Z");
			// static ...; // 0x107E82F8
			// static ...; // 0x107E82E0
			// static ...; // 0x107E82D8
			// s_player_emblem_configuration const &config;
			// std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks> handler;
			// std::scoped_lock<std::mutex> lock;
			// Player::Emblems::PlayerEmblemRenderTask task;
			todo("implement");
			bool __result = _sub_107E81D0(config, handler);
			return __result;
		}

		_extern void _sub_107E7C60();
		void PlayerEmblemRenderer::DoRender() // 0x107E7C60
		{
			mangled_x86(MANGLED_TODO, "?DoRender@PlayerEmblemRenderer@Emblems@Player@@SAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x107E7D9A
			// static ...; // 0x107E7D95
			// static ...; // 0x107E7D90
			// static ...; // 0x107E7D6C
			// static ...; // 0x107E7D64
			// std::queue<Player::Emblems::PlayerEmblemRenderTask,std::deque<Player::Emblems::PlayerEmblemRenderTask,std::allocator<Player::Emblems::PlayerEmblemRenderTask> > > queue;
			{
				// std::scoped_lock<std::mutex> lock;
			}
			{
				// Player::Emblems::PlayerEmblemRenderTask task;
			}
			todo("implement");
			_sub_107E7C60();
		}
	}
}

/* ---------- private code */

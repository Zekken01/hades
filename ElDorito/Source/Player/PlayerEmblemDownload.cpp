/* ---------- headers */

#include "Player/PlayerEmblemDownload.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Network.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Singleton.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
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

struct lambda_1;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
	class IHttpResponse;
}
namespace Player
{
	class PlayerEmblemDownload;
}
namespace hades_file_local
{
	struct PlayerEmblem;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

namespace hades_file_local
{
	enum State
	{
		eEmpty = 0,
		eFailed,
		eGenerate,
		eDownloading,
		eFinishedDownload,
		eReady,
		eRemoving,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	struct PlayerEmblem
	{
		std::mutex mutex; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > data; // 0x30
		IDirect3DTexture9 *texture; // 0x4C
		bool active; // 0x50
		unsigned char __pad0[3]; // 0x51
		State state; // 0x54
		unsigned long long uid; // 0x58
		unsigned short player_join_number; // 0x60
		unsigned short attempts; // 0x62
		long attemptTick; // 0x64
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > generatedEmblemUrl; // 0x68
		s_player_emblem_configuration emblemConfig; // 0x84
		PlayerEmblem(); /* compiler_generated() */
		~PlayerEmblem(); /* compiler_generated() */
		public:
		void set_emblem_texture(long sampler, long player_index, bool use_generic, bool screen_emblem);
		void set_emblem_customization_biped(long sampler, bool use_generic, bool screen_emblem);
	};
	static_assert(sizeof(PlayerEmblem) == 152, "Invalid PlayerEmblem size");
}
using namespace hades_file_local;
//class Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1>
//{
//public:
//	void operator()(Blam::Network::LifeCycleState) const;
//	<lambda_1>(Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1> &);
//	<lambda_1>(Player::PlayerEmblemDownload *);
//private:
//	Player::PlayerEmblemDownload *__this; // 0x0
//public:
//	Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1> &operator=(Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1>) == 4, "Invalid Player::PlayerEmblemDownload::{ctor}::__l2::<lambda_1> size");

namespace Http
{
	typedef std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> HttpRequestCompletedCallback;
	typedef std::shared_ptr<Http::IHttpRequest> HttpRequestPtr;
	typedef std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> HttpResponseCallback;
	typedef std::function<bool __cdecl(char const *,unsigned int)> HttpContentReceiver;
	typedef std::shared_ptr<Http::IHttpResponse> HttpResponsePtr;
}

/* ---------- prototypes */

namespace Player
{
	extern void StartImageDownload(std::basic_string<char,std::char_traits<char>,std::allocator<char> > url, __int32 player_index);
	extern void ResetCosmeticSlot(__int32 player_index);
	extern void InvalidateCosmeticSlot(__int32 player_index);
	extern void DXInitEmblem(__int32 player_index);
	extern void DXGenerateEmblem(__int32 player_index);
	extern void CheckDirty(__int32 player_index);
	extern void InitPlayer(__int32 player_index, bool is_customization_biped);
	extern void RetrySlot(__int32 player_index);
}

/* ---------- globals */

namespace Player
{
	extern IDirect3DTexture9 *generic_emblem; // 0x124083D0
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	_extern void _sub_108FE180(std::string, __int32);
	void StartImageDownload(std::basic_string<char,std::char_traits<char>,std::allocator<char> > url, __int32 player_index) // 0x108FE180
	{
		mangled_x86(MANGLED_TODO, "?StartImageDownload@Player@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
		// static ...; // 0x108FE5CC
		// static ...; // 0x108FE5C4
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > url;
		// __int32 player_index;
		// std::shared_ptr<Http::IHttpRequest> req;
		// function call : void (std::string)
		// function call : void (std::string)
		// function call : void (Http::CHttpHeaders)
		// function call : void (std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &)
		// function call : void (std::function<bool __cdecl(char const *,unsigned int)> &)
		// function call : void (std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &)
		// function call : bool ()
		todo("implement");
		_sub_108FE180(url, player_index);
	}

	_extern void _sub_108FDE10(__int32);
	void ResetCosmeticSlot(__int32 player_index) // 0x108FDE10
	{
		mangled_x86(MANGLED_TODO, "?ResetCosmeticSlot@Player@@YAXH@Z");
		// __int32 player_index;
		// function call : unsigned long ()
		todo("implement");
		_sub_108FDE10(player_index);
	}

	_extern void _sub_108FD3F0(__int32);
	void InvalidateCosmeticSlot(__int32 player_index) // 0x108FD3F0
	{
		mangled_x86(MANGLED_TODO, "?InvalidateCosmeticSlot@Player@@YAXH@Z");
		// __int32 player_index;
		todo("implement");
		_sub_108FD3F0(player_index);
	}

	_extern void _sub_108FCCD0(__int32);
	void DXInitEmblem(__int32 player_index) // 0x108FCCD0
	{
		mangled_x86(MANGLED_TODO, "?DXInitEmblem@Player@@YAXH@Z");
		// __int32 player_index;
		// IDirect3DDevice9 *device;
		// HRESULT result;
		// function call : unsigned long ()
		todo("implement");
		_sub_108FCCD0(player_index);
	}

	_extern void _sub_108FCBD0(__int32);
	void DXGenerateEmblem(__int32 player_index) // 0x108FCBD0
	{
		mangled_x86(MANGLED_TODO, "?DXGenerateEmblem@Player@@YAXH@Z");
		// __int32 player_index;
		// function call : unsigned long ()
		todo("implement");
		_sub_108FCBD0(player_index);
	}

	_extern void _sub_108FC890(__int32);
	void CheckDirty(__int32 player_index) // 0x108FC890
	{
		mangled_x86(MANGLED_TODO, "?CheckDirty@Player@@YAXH@Z");
		// static ...; // 0x108FCB1F
		// static ...; // 0x108FCB14
		// static ...; // 0x108FCAFC
		// static ...; // 0x108FCAF4
		// __int32 player_index;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > url;
		{
			// s_player_emblem_configuration tempConfig;
		}
		todo("implement");
		_sub_108FC890(player_index);
	}

	_extern void _sub_108FCFF0(__int32, bool);
	void InitPlayer(__int32 player_index, bool is_customization_biped) // 0x108FCFF0
	{
		mangled_x86(MANGLED_TODO, "?InitPlayer@Player@@YAXH_N@Z");
		// static ...; // 0x108FD314
		// static ...; // 0x108FD2FC
		// static ...; // 0x108FD2F4
		// __int32 player_index;
		// bool is_customization_biped;
		// unsigned short player_slot_join_number;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > url;
		{
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &emblemGeneratorURL;
			}
		}
		todo("implement");
		_sub_108FCFF0(player_index, is_customization_biped);
	}

	_extern void _sub_108FDF30(__int32);
	void RetrySlot(__int32 player_index) // 0x108FDF30
	{
		mangled_x86(MANGLED_TODO, "?RetrySlot@Player@@YAXH@Z");
		// __int32 player_index;
		{
			// float secondsSince;
		}
		// function call : float (*const)(float)
		// function call : long (*const)()
		// function call : float (*const)(float)
		// function call : long (*const)()
		// function call : long (*const)()
		todo("implement");
		_sub_108FDF30(player_index);
	}

	extern PlayerEmblemDownload* _sub_108FC480(::Player::PlayerEmblemDownload *const);
	PlayerEmblemDownload::PlayerEmblemDownload() // 0x108FC480
	{
		mangled_x86(MANGLED_TODO, "??0PlayerEmblemDownload@Player@@QAE@XZ");
		// Player::PlayerEmblemDownload *const this;
		{
			// __int32 i;
		}
		todo("implement");
		_sub_108FC480(this);
	}

	_extern void _sub_108FD420(::Player::PlayerEmblemDownload *const, IDirect3DDevice9 *);
	void PlayerEmblemDownload::LoadGenericEmblem(IDirect3DDevice9 *device) // 0x108FD420
	{
		mangled_x86(MANGLED_TODO, "?LoadGenericEmblem@PlayerEmblemDownload@Player@@QAEXPAUIDirect3DDevice9@@@Z");
		// IDirect3DDevice9 *device;
		// HRESULT res;
		todo("implement");
		_sub_108FD420(this, device);
	}

	_extern void _sub_108FE700(::Player::PlayerEmblemDownload *const);
	void PlayerEmblemDownload::Tick() // 0x108FE700
	{
		mangled_x86(MANGLED_TODO, "?Tick@PlayerEmblemDownload@Player@@QAEXXZ");
		// static ...; // 0x108FEACD
		// static ...; // 0x108FEAC8
		// static ...; // 0x108FEAB0
		// static ...; // 0x108FEAA8
		// Player::PlayerEmblemDownload *const this;
		// float secondsSince;
		// Blam::Network::Session *session;
		{
			// __int32 player;
			{
				// std::unique_lock<std::mutex> lock;
			}
		}
		{
			// std::scoped_lock<std::mutex> lock;
		}
		// function call : float (*const)(float)
		// function call : long (*const)()
		// function call : float (*const)(float)
		// function call : bool (*const)()
		todo("implement");
		_sub_108FE700(this);
	}

	_extern void _sub_108FDAE0(::Player::PlayerEmblemDownload *const, IDirect3DDevice9 *);
	void PlayerEmblemDownload::OnEndScene(IDirect3DDevice9 *device) // 0x108FDAE0
	{
		mangled_x86(MANGLED_TODO, "?OnEndScene@PlayerEmblemDownload@Player@@QAEXPAUIDirect3DDevice9@@@Z");
		// static ...; // 0x108FDC10
		// static ...; // 0x108FDC08
		// Player::PlayerEmblemDownload *const this;
		// IDirect3DDevice9 *device;
		{
			// __int32 player;
			{
				// std::scoped_lock<std::mutex> lock;
			}
		}
		todo("implement");
		_sub_108FDAE0(this, device);
	}

	_extern void _sub_108FEBD0(::Player::PlayerEmblemDownload *const);
	void PlayerEmblemDownload::UpdateLocalEmblem() // 0x108FEBD0
	{
		mangled_x86(MANGLED_TODO, "?UpdateLocalEmblem@PlayerEmblemDownload@Player@@QAEXXZ");
		// Player::PlayerEmblemDownload *const this;
		todo("implement");
		_sub_108FEBD0(this);
	}

	_extern void _sub_108FE150(::Player::PlayerEmblemDownload *const, long);
	void PlayerEmblemDownload::SetLastJoinTime(long time) // 0x108FE150
	{
		mangled_x86(MANGLED_TODO, "?SetLastJoinTime@PlayerEmblemDownload@Player@@QAEXJ@Z");
		// long time;
		todo("implement");
		_sub_108FE150(this, time);
	}
}

extern IDirect3DTexture9 *_sub_108FCE40(::Player::PlayerEmblemDownload *const, long, bool);
namespace Player
{
	IDirect3DTexture9 *PlayerEmblemDownload::GetPlayerEmblem(long player_index, bool use_generic) // 0x108FCE40
	{
		mangled_x86(MANGLED_TODO, "?GetPlayerEmblem@PlayerEmblemDownload@Player@@QAEPAUIDirect3DTexture9@@J_N@Z");
		// static ...; // 0x108FCF78
		// Player::PlayerEmblemDownload *const this;
		// long player_index;
		// bool use_generic;
		{
			// std::unique_lock<std::mutex> lock;
		}
		todo("implement");
		IDirect3DTexture9 * __result = _sub_108FCE40(this, player_index, use_generic);
		return __result;
	}

	_extern void _sub_108FD6B0(::Player::PlayerEmblemDownload *const, __int32, std::shared_ptr<Http::IHttpRequest>);
	void PlayerEmblemDownload::OnDownloadResponse(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request) // 0x108FD6B0
	{
		mangled_x86(MANGLED_TODO, "?OnDownloadResponse@PlayerEmblemDownload@Player@@QAEXHV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");
		// static ...; // 0x108FD9F1
		// static ...; // 0x108FD9EC
		// static ...; // 0x108FD9BC
		// static ...; // 0x108FD9B4
		// Player::PlayerEmblemDownload *const this;
		// __int32 player_index;
		// std::shared_ptr<Http::IHttpRequest> request;
		// Http::CHttpHeaders headers;
		// long long length;
		// std::shared_ptr<Http::IHttpResponse> response;
		{
			// std::unique_lock<std::mutex> lock;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *data;
		}
		// function call : std::shared_ptr<Http::IHttpResponse> ()
		// function call : __int32 () const
		// function call : void ()
		// function call : Http::CHttpHeaders const &() const
		// function call : void ()
		todo("implement");
		_sub_108FD6B0(this, player_index, request);
	}

	_extern void _sub_108FD490(::Player::PlayerEmblemDownload *const, __int32, std::shared_ptr<Http::IHttpRequest>, bool);
	void PlayerEmblemDownload::OnDownloadComplete(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request, bool success) // 0x108FD490
	{
		mangled_x86(MANGLED_TODO, "?OnDownloadComplete@PlayerEmblemDownload@Player@@QAEXHV?$shared_ptr@VIHttpRequest@Http@@@std@@_N@Z");
		// Player::PlayerEmblemDownload *const this;
		// __int32 player_index;
		// std::shared_ptr<Http::IHttpRequest> request;
		// bool success;
		// std::unique_lock<std::mutex> lock;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *data;
		}
		todo("implement");
		_sub_108FD490(this, player_index, request, success);
	}

	_extern bool _sub_108FDC80(::Player::PlayerEmblemDownload *const, __int32, char const *, unsigned __int32);
	bool PlayerEmblemDownload::OnRecieve(__int32 player_index, char const *buffer, unsigned __int32 length) // 0x108FDC80
	{
		mangled_x86(MANGLED_TODO, "?OnRecieve@PlayerEmblemDownload@Player@@QAE_NHPBDI@Z");
		// Player::PlayerEmblemDownload *const this;
		// __int32 player_index;
		// char const *buffer;
		// unsigned __int32 length;
		// std::unique_lock<std::mutex> lock;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *data;
		todo("implement");
		bool __result = _sub_108FDC80(this, player_index, buffer, length);
		return __result;
	}
}

/* ---------- private code */

_extern void _sub_108FC5B0(PlayerEmblem *const);
_inline PlayerEmblem::~PlayerEmblem() // 0x108FC5B0
{
	// `anonymous-namespace'::PlayerEmblem::~PlayerEmblem
	// PlayerEmblem *const this;
	compiler_generated();
	todo("implement");
	_sub_108FC5B0(this);
}

extern PlayerEmblem* _sub_108FC400(PlayerEmblem *const);
_inline PlayerEmblem::PlayerEmblem() // 0x108FC400
{
	// `anonymous-namespace'::PlayerEmblem::PlayerEmblem
	// PlayerEmblem *const this;
	compiler_generated();
	todo("implement");
	_sub_108FC400(this);
}

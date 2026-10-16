/* ---------- headers */

#include "Player/PlayerEmblemDownload.hpp"
#include "Patches/Network.hpp"
extern long (*const game_time_get)();
extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x108FDF30
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
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"

#include "Modules/ModulePlayer.hpp"  // hades: added for 0x108FCFF0

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
		std::string data; // 0x30
		IDirect3DTexture9 *texture; // 0x4C
		bool active; // 0x50
		unsigned char __pad0[3]; // 0x51
		State state; // 0x54
		unsigned long long uid; // 0x58
		unsigned short player_join_number; // 0x60
		unsigned short attempts; // 0x62
		long attemptTick; // 0x64
		std::string generatedEmblemUrl; // 0x68
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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_is_ui_shell = reinterpret_cast<bool (*)()>(0x531E90);
}

namespace Http { extern std::shared_ptr<Http::IHttpRequest> CreateRequest(); } namespace Utils { namespace Version { extern std::string GetVersionString(); } }  // hades: added for 0x108FE180

#include "Player/PlayerInfo.hpp"  // hades: added for 0x108FC890
namespace Player { namespace Emblems { extern bool ParseURL(std::string const &url, s_player_emblem_configuration &config); } }  // hades: added for 0x108FC890

namespace Player
{
	extern void StartImageDownload(std::string url, __int32 player_index);
	extern void ResetCosmeticSlot(__int32 player_index);
	extern void InvalidateCosmeticSlot(__int32 player_index);
	extern void DXInitEmblem(__int32 player_index);
	extern void DXGenerateEmblem(__int32 player_index);
	extern void CheckDirty(__int32 player_index);
	extern void InitPlayer(__int32 player_index, bool is_customization_biped);
	extern void RetrySlot(__int32 player_index);
}

/* ---------- globals */

PlayerEmblem player_emblems[17]; // 0x124083D8

namespace Player
{
	extern IDirect3DTexture9 *generic_emblem; // 0x124083D0
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	void StartImageDownload(std::string url, __int32 player_index) // 0x108FE180
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?StartImageDownload@Player@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");

		std::shared_ptr<Http::IHttpRequest> req = Http::CreateRequest();
		req->SetUrl(url);
		req->SetMethod("GET");
		req->SetHeaders({ { "User-Agent", "ElDewrito/" + Utils::Version::GetVersionString() }, { "content-type", "image/png" } });
		req->SetOnResponse(std::bind_front(&PlayerEmblemDownload::OnDownloadResponse, &PlayerEmblemDownload::Instance(), player_index));
		req->SetReceiver(std::bind_front(&PlayerEmblemDownload::OnRecieve, &PlayerEmblemDownload::Instance(), player_index));
		req->SetOnCompleted(std::bind_front(&PlayerEmblemDownload::OnDownloadComplete, &PlayerEmblemDownload::Instance(), player_index));
		req->Send();
		player_emblems[player_index].generatedEmblemUrl = url;
	}

	void ResetCosmeticSlot(__int32 player_index) // 0x108FDE10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ResetCosmeticSlot@Player@@YAXH@Z");

		player_emblems[player_index].active = false;
		player_emblems[player_index].attempts = 0;
		player_emblems[player_index].player_join_number = 0;
		player_emblems[player_index].uid = 0;
		player_emblems[player_index].data.clear();
		if (player_emblems[player_index].texture)
			player_emblems[player_index].texture->Release();
		player_emblems[player_index].texture = nullptr;
		player_emblems[player_index].state = eEmpty;
	}

	void InvalidateCosmeticSlot(__int32 player_index) // 0x108FD3F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InvalidateCosmeticSlot@Player@@YAXH@Z");

		player_emblems[player_index].active = false;
	}

	void DXInitEmblem(__int32 player_index) // 0x108FCCD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DXInitEmblem@Player@@YAXH@Z");

		IDirect3DDevice9 *device = *(IDirect3DDevice9 **)0x50daddc;
		if (player_emblems[player_index].texture)
			player_emblems[player_index].texture->Release();
		player_emblems[player_index].texture = nullptr;
		HRESULT result = D3DXCreateTextureFromFileInMemory(device, &player_emblems[player_index].data[0], player_emblems[player_index].data.size(), &player_emblems[player_index].texture);
		player_emblems[player_index].data.clear();
		if (result)
			player_emblems[player_index].state = eFailed;
		else
			player_emblems[player_index].state = eReady;
	}

	void DXGenerateEmblem(__int32 player_index) // 0x108FCBD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DXGenerateEmblem@Player@@YAXH@Z");

		if (player_emblems[player_index].texture)
			player_emblems[player_index].texture->Release();
		player_emblems[player_index].texture = nullptr;
		if (GenerateEmblem(player_emblems[player_index].emblemConfig, &player_emblems[player_index].texture, true))
			player_emblems[player_index].state = eReady;
		else
			player_emblems[player_index].state = eFailed;
	}

	void CheckDirty(__int32 player_index) // 0x108FC890
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CheckDirty@Player@@YAXH@Z");

			std::string url;
			url = CPlayersInfo::GeEmblemUrl(player_index);
			if (url.empty())
				return;
			if (url.starts_with("emblems://"))
			{
				s_player_emblem_configuration tempConfig = {};
				if (Emblems::ParseURL(url, tempConfig) && !(tempConfig == player_emblems[player_index].emblemConfig))
					player_emblems[player_index].state = eRemoving;
			}
			else if (!player_emblems[player_index].emblemConfig.isUninitialized())
			{
				player_emblems[player_index].emblemConfig = {};
				player_emblems[player_index].state = eRemoving;
			}
			else if (url != player_emblems[player_index].generatedEmblemUrl)
			{
				player_emblems[player_index].state = eRemoving;
			}
	}

	void InitPlayer(__int32 player_index, bool is_customization_biped) // 0x108FCFF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitPlayer@Player@@YAXH_N@Z");

		std::string url;
		if (is_customization_biped)
		{
			rapidjson::Document dewrito = Utils::DewritoReader::Instance().GetDewritoJson();
			if (dewrito.HasMember("emblemgenerator"))
			{
				rapidjson::Value &emblemGeneratorURL = dewrito["emblemgenerator"];
				url = emblemGeneratorURL.GetString() + Modules::ModulePlayer::Instance().VarPlayerEmblem->ValueString;
			}
		}
		else
		{
			url = CPlayersInfo::GeEmblemUrl(player_index);
			if (url.empty())
				return;
		}
		if (url.starts_with("emblems://"))
		{
			if (!Emblems::ParseURL(url, player_emblems[player_index].emblemConfig))
				player_emblems[player_index].emblemConfig = {};
			player_emblems[player_index].state = eGenerate;
		}
		else
		{
			player_emblems[player_index].state = eDownloading;
			StartImageDownload(url, player_index);
		}
		player_emblems[player_index].active = true;
		player_emblems[player_index].player_join_number++;
		unsigned short player_slot_join_number = player_emblems[player_index].player_join_number;
		player_emblems[player_index].data.clear();
	}

	void RetrySlot(__int32 player_index) // 0x108FDF30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RetrySlot@Player@@YAXH@Z");

		if (player_emblems[player_index].attempts > 15)
		{
			float secondsSince = game_ticks_to_seconds((float)game_time_get()) - game_ticks_to_seconds((float)player_emblems[player_index].attemptTick);
			if (secondsSince < 0.0f)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "EMBLEMS: negative secondsSince in RetrySlot(): %d", secondsSince);
				player_emblems[player_index].attemptTick = game_time_get();
				return;
			}
			if (secondsSince < 3.0f)
				return;
		}
		player_emblems[player_index].attempts++;
		player_emblems[player_index].attemptTick = game_time_get();
		InitPlayer(player_index, false);
	}


	PlayerEmblemDownload::PlayerEmblemDownload() : // 0x108FC480
		server_join_tick(0),
		failedInit(false),
		emblemUpdate(false)
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0PlayerEmblemDownload@Player@@QAE@XZ");
		// Player::PlayerEmblemDownload *const this;

		for (__int32 i = 0; i < 17; i++)
		{
			ResetCosmeticSlot(i);
		}

		Patches::Network::OnLifeCycleStateChanged([this](Blam::Network::LifeCycleState state)
		{
			if (state == Blam::Network::eLifeCycleStateLeaving)
			{
				for (__int32 i = 0; i < 16; i++)
				{
					std::unique_lock<std::mutex> lock(player_emblems[i].mutex);
					InvalidateCosmeticSlot(i);
					lock.unlock();
				}
			}
			else if (state == Blam::Network::eLifeCycleStateJoining)
			{
				SetLastJoinTime(game_time_get());
			}
		});
	}

	void PlayerEmblemDownload::LoadGenericEmblem(IDirect3DDevice9 *device) // 0x108FD420
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadGenericEmblem@PlayerEmblemDownload@Player@@QAEXPAUIDirect3DDevice9@@@Z");

		HRESULT result = D3DXCreateTextureFromFileA(device, "ui/assets/emblems/generic.png", &generic_emblem);
		if (result)
			failedInit = true;
	}

	void PlayerEmblemDownload::Tick() // 0x108FE700
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@PlayerEmblemDownload@Player@@QAEXXZ");

		if (failedInit)
			return;
		float secondsSince = game_ticks_to_seconds((float)game_time_get()) - game_ticks_to_seconds((float)server_join_tick);
		if (secondsSince < 0.0f)
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "EMBLEMS: negative secondsSince in Tick(): %d", secondsSince);
		if (secondsSince < 1.0f)
			return;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
		{
			__int32 player = session->MembershipInfo.FindFirstPlayer();
			while (player != -1)
			{
				std::unique_lock<std::mutex> lock(player_emblems[player].mutex);
				if (player_emblems[player].uid != session->MembershipInfo.PlayerSessions[player].Properties.host.player_uid)
				{
					if (player_emblems[player].state == eReady)
						player_emblems[player].state = eRemoving;
					if (player_emblems[player].state == eEmpty)
						player_emblems[player].uid = session->MembershipInfo.PlayerSessions[player].Properties.host.player_uid;
				}
				if (!player_emblems[player].active)
				{
					InitPlayer(player, false);
				}
				else
				{
					switch (player_emblems[player].state)
					{
					case eFailed:
						RetrySlot(player);
						break;
					case eEmpty:
						InitPlayer(player, false);
						break;
					case eReady:
						CheckDirty(player);
						break;
					}
				}
				lock.unlock();
				player = session->MembershipInfo.FindNextPlayer(player);
			}
		}
		if (eldorado::game_is_ui_shell() && emblemUpdate)
		{
			std::scoped_lock<std::mutex> lock(player_emblems[16].mutex);
			emblemUpdate = false;
			InitPlayer(16, true);
		}
	}

	void PlayerEmblemDownload::OnEndScene(IDirect3DDevice9 *device) // 0x108FDAE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnEndScene@PlayerEmblemDownload@Player@@QAEXPAUIDirect3DDevice9@@@Z");

		if (failedInit)
			return;
		for (__int32 player = 0; player < 17; player++)
		{
			std::scoped_lock<std::mutex> lock(player_emblems[player].mutex);
			switch (player_emblems[player].state)
			{
			case eGenerate:
				DXGenerateEmblem(player);
				break;
			case eFinishedDownload:
				DXInitEmblem(player);
				break;
			case eRemoving:
				ResetCosmeticSlot(player);
				break;
			}
		}
	}

	void PlayerEmblemDownload::UpdateLocalEmblem() // 0x108FEBD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateLocalEmblem@PlayerEmblemDownload@Player@@QAEXXZ");

		emblemUpdate = true;
	}

	void PlayerEmblemDownload::SetLastJoinTime(long time) // 0x108FE150
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastJoinTime@PlayerEmblemDownload@Player@@QAEXJ@Z");

		server_join_tick = time;
	}
}


namespace Player
{
	IDirect3DTexture9 *PlayerEmblemDownload::GetPlayerEmblem(long player_index, bool use_generic) // 0x108FCE40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerEmblem@PlayerEmblemDownload@Player@@QAEPAUIDirect3DTexture9@@J_N@Z");

		if (player_index > -1 && player_index <= 16)
		{
			std::unique_lock<std::mutex> lock(player_emblems[player_index].mutex);
			if (use_generic || !player_emblems[player_index].texture || player_emblems[player_index].state == eFailed)
				return generic_emblem;
			else
				return player_emblems[player_index].texture;
			lock.unlock();
		}
		else
			return generic_emblem;
	}

	void PlayerEmblemDownload::OnDownloadResponse(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request) // 0x108FD6B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadResponse@PlayerEmblemDownload@Player@@QAEXHV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");

		std::shared_ptr<Http::IHttpResponse> response = request->GetResponse();
		if (response->GetResponseCode() != 200)
			request->Cancel();
		Http::CHttpHeaders headers = response->GetHeaders();
		long long length;
		if (headers.GetInt("Content-Length", length))
		{
			if (length > 0x200000)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "Image was too large: %d", length);
				request->Cancel();
				return;
			}
			else
			{
				std::unique_lock<std::mutex> lock(player_emblems[player_index].mutex);
				std::string *data = &player_emblems[player_index].data;
				if (data->capacity() < length)
					data->reserve(length);
				lock.unlock();
			}
		}
	}

	void PlayerEmblemDownload::OnDownloadComplete(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request, bool success) // 0x108FD490
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadComplete@PlayerEmblemDownload@Player@@QAEXHV?$shared_ptr@VIHttpRequest@Http@@@std@@_N@Z");

		std::unique_lock<std::mutex> lock(player_emblems[player_index].mutex);
		if (!success)
		{
			player_emblems[player_index].state = eFailed;
		}
		else
		{
			std::string *data = &player_emblems[player_index].data;
			if (data->at(0) != '\x89' || data->at(1) != 'P' || data->at(2) != 'N' || data->at(3) != 'G' || data->at(4) != '\r' || data->at(5) != '\n' || data->at(6) != '\x1a' || data->at(7) != '\n')
				player_emblems[player_index].state = eFailed;
			else
				player_emblems[player_index].state = eFinishedDownload;
		}
		lock.unlock();
	}

	bool PlayerEmblemDownload::OnRecieve(__int32 player_index, char const *buffer, unsigned __int32 length) // 0x108FDC80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnRecieve@PlayerEmblemDownload@Player@@QAE_NHPBDI@Z");

		std::unique_lock<std::mutex> lock(player_emblems[player_index].mutex);
		std::string *data = &player_emblems[player_index].data;
		if (data->size() > 0x200000LL)
			return false;

		data->append(buffer, length);
		lock.unlock();
		return true;
	}
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??1PlayerEmblem@hades_file_local@@QAE@XZ"); no body to assert in
_inline PlayerEmblem::~PlayerEmblem() = default; // 0x108FC5B0

// mangled_x86(MANGLED_DEFAULT, "??0PlayerEmblem@hades_file_local@@QAE@XZ"); no body to assert in
_inline PlayerEmblem::PlayerEmblem() = default; // 0x108FC400

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Player { IDirect3DTexture9 *generic_emblem; }

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cutscene/podium_settings.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_statborg.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/ModGlobals.hpp"
#include "Patches/Core.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

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
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>
#include "Modules/ModuleServer.hpp"  // hades: added for 0x106DF530
#include "Player/PlayerInfo.hpp"  // hades: added for 0x106E0330
#include <span>

/* ---------- forward declarations */

class c_network_session;
struct c_game_engine;
struct c_game_statborg;
struct real_euler_angles3d;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_damage_owner;
struct s_game_globals;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_multiplayer_globals_definition;
struct s_object_data;
struct s_object_placement_data;
struct s_player_datum;
struct s_player_model_customization;
struct s_podium_biped;
struct s_podium_settings;
struct s_scenario;
struct s_scenario_cutscene_camera_point;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Player
{
	namespace PlayerPodium
	{
		struct HaloScriptPlayerModelState;
		struct PlayerPlace;
		struct PodiumState;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace Forge {}
using namespace ::Forge;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

// Player::PlayerPodium::PlayerPlace is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Player::PlayerPodium::HaloScriptPlayerModelState is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Player::PlayerPodium::PodiumState is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x106DD850
extern void (*const player_refresh_object_appearance_full)(long, long);  // hades: added for 0x106DD850

extern bool (*const game_is_multiplayer)();  // hades: added for 0x106DF660  // hades: added for 0x106DF660

namespace Forge { namespace PodiumPoint { extern long FindPodiumObject(); } }  // hades: added for 0x106DFDA0
namespace Player { extern real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance); }  // hades: added for 0x106DFDA0
extern void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles);  // hades: added for 0x106DFDA0
extern s_scenario **g_scenario_definition;  // hades: added for 0x106DFDA0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x106DFDA0

namespace Player { namespace PlayerNetworkUtil { extern long get_session_player_index_from_player_datum_index(long player_datum_index); } }  // hades: added for 0x106E0FB0

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x106DEB10
namespace Player { namespace PlayerNetworkUtil { extern long get_player_datum_index_from_session_index(__int32 player_session_index); } } namespace Player { namespace Emblems { extern std::string BuildUrl(s_player_emblem_configuration emblem); } } extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x106DEB10, 0x106E0330

namespace Player
{
	namespace PlayerNetworkUtil { extern s_player_datum *get_player_from_session_index(__int32 player_session_index); }  // hades: added for 0x106DE730
	namespace PlayerPodium
	{
		extern long GetModgCharacterIndexFromPlayer(s_player_datum *player);
		extern void RespawnPlayerOffset(short player_session_idx, short cutscene_camera_point_index, float distance_offset, float horizontal_offset, float vertical_offset, float yaw_offset, float pitch);
		extern void RespawnPlayer(short player_session_idx, real_point3d const &position, float yaw, float pitch);
		extern void ShowPlace(short desiredPlace, short stats_player_session_idx);
		extern short GetPlayerAnimationCount(short player_session_idx);
		extern long GetPlayerAnimationGraph(short player_session_idx);
		extern unsigned long GetPlayerAnimationString(short player_session_idx, short animationType, short animationIndex);
		extern long GetAnimationWeaponIndex(short player_session_idx, short animationIndex, bool isPrimary);
		extern float GetAnimationOffset(short player_session_idx, short animationIndex);
		extern void ResetStates();
		extern void HandleEvent(char const *eventString);
		extern bool PodiumEnabled();
		extern bool PodiumStarted();
		extern bool PodiumhasInitialized();
		extern bool PodiumIsReady();
		extern bool ForgeCanOverride();
		extern void SetForgeCanOverride(bool allowed);
		extern void OnMapLoaded(char const *mapPath);
		extern void PodiumTick();
		extern short GetPlayerSessionIndexByLeaderboardPlace(short leaderboardPlace);
		extern long GetPodiumRespawnEffectIndex(short place);
		extern float GetPodiumBipedOffset(char const *offset_type, short place);
		extern long GetPodiumBipedSpawnDelay(short place);
		extern long GetPodiumTickDelay();
		extern void DoSpawnPlayer(long target_player_datum_index, real_point3d position, real_vector3d forward);
		extern void UpdatePlayer(long player_datum_index);
		extern void UpdatePlayerState(long player_session_idx, real_point3d position, float yaw, float pitch, bool respawn);
		extern void Init();
	}
}

/* ---------- globals */

namespace Scripting { namespace HS { extern void ExecuteScript(std::string_view name, std::span<hs_value const> arguments); } }

namespace Player
{
	namespace PlayerPodium
	{
		extern ::Player::PlayerPodium::HaloScriptPlayerModelState s_PodiumPlayerStates; // 0x113880A8
		extern ::Player::PlayerPodium::PodiumState s_PodiumStates; // 0x11388228
		extern bool podiumReady; // 0x1138822B
		extern bool forgeOverrideAllowed; // 0x1138822C
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace PlayerPodium
	{
		_inline bool PlayerPlace::operator<(::Player::PlayerPodium::PlayerPlace const &other_player) const // 0x106DD530
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??MPlayerPlace@PlayerPodium@Player@@QBE_NABU012@@Z");
			// Player::PlayerPodium::PlayerPlace const &other_player;

			if (player_place == other_player.player_place)
				return player_session_idx < other_player.player_session_idx;
			return player_place < other_player.player_place;
		}

		long GetModgCharacterIndexFromPlayer(s_player_datum *player) // 0x106DE4F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetModgCharacterIndexFromPlayer@PlayerPodium@Player@@YAJPAUs_player_datum@@@Z");
			// s_player_datum *player;
			// s_mod_globals_definition *const modg;
				// __int32 i;
					// s_mod_globals_player_character_customization *const character;

			s_mod_globals_definition *mod_globals = mod_globals_get_definition();

			if (mod_globals)
			{
				for (long i = 0; i < mod_globals->player_character_customizations.count; i++)
				{
					if (mod_globals->player_character_customizations[i].global_player_character_type_index == player->character_type_index)
					{
						s_mod_globals_player_character_customization *customization = mod_globals->player_character_customizations.get_element(i);

						if (customization)
						{
							return i;
						}
					}
				}
			}

			return -1;
		}

		void RespawnPlayerOffset(short player_session_idx, short cutscene_camera_point_index, float distance_offset, float horizontal_offset, float vertical_offset, float yaw_offset, float pitch) // 0x106DFDA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RespawnPlayerOffset@PlayerPodium@Player@@YAXFFMMMMM@Z");
			// static ...; // 0x106E0138
			// static ...; // 0x106E0130
			// short player_session_idx;
			// short cutscene_camera_point_index;
			// float distance_offset;
			// float horizontal_offset;
			// float vertical_offset;
			// float yaw_offset;
			// float pitch;
			// Blam::Network::Session *session;
				// s_scenario *const scnr;
					// s_player_datum *player;
					// c_tag_block<s_scenario_cutscene_camera_point> cutscenes;
						// real_point3d newUnitPoint;
						// float yaw;
						// s_scenario_cutscene_camera_point cutscene_camera;
						// bool isPodiumHack;
						// s_scenario_cutscene_camera_point podiumCamera;
							// long s_PodiumObjectIndex;
							// s_object_data *scenObject;
								// real_matrix4x3 podiumObjectTransform;
								// real_euler_angles3d podiumObjectOrientation;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_scenario *const scnr = *g_scenario_definition;
				if (scnr)
				{
					s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
					if (!player)
					{
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player index '{}' failed to spawn because the player was not in the session.", player_session_idx));
						return;
					}
					c_tag_block<s_scenario_cutscene_camera_point> cutscenes = scnr->cutscene_camera_points;
					if (cutscenes.count > 0 && cutscene_camera_point_index < cutscenes.count)
					{
						s_scenario_cutscene_camera_point cutscene_camera = static_cast<s_scenario_cutscene_camera_point const &>(cutscenes[cutscene_camera_point_index]);
						bool isPodiumHack = cutscene_camera.flags & 4;
						s_scenario_cutscene_camera_point podiumCamera = static_cast<s_scenario_cutscene_camera_point const &>(cutscene_camera);
						if (isPodiumHack && ForgeCanOverride())
						{
							long s_PodiumObjectIndex = Forge::PodiumPoint::FindPodiumObject();
							s_object_data *scenObject = object_try_and_get_and_verify_type(s_PodiumObjectIndex, 0x80);
							if (s_PodiumObjectIndex != -1 && scenObject)
							{
								real_matrix4x3 podiumObjectTransform;
								real_euler_angles3d podiumObjectOrientation;
								((real_matrix4x3 *(*const)(long, real_matrix4x3 *))0xB2EC60)(s_PodiumObjectIndex, &podiumObjectTransform);
								matrix4x3_rotation_to_angles(&podiumObjectTransform, &podiumObjectOrientation);
								podiumCamera.position.x = podiumObjectTransform.position.x;
								podiumCamera.position.y = podiumObjectTransform.position.y;
								podiumCamera.position.z = podiumObjectTransform.position.z;
								podiumCamera.orientation.yaw = podiumObjectOrientation.yaw;
								podiumCamera.orientation.pitch = 0.0f;
								podiumCamera.orientation.roll = 0.0f;
							}
						}
						float yaw = podiumCamera.orientation.yaw * 57.29578f + yaw_offset;
						real_point3d newUnitPoint = CalculateBipedPosition(&podiumCamera.position, &podiumCamera.orientation, distance_offset, -horizontal_offset);
						newUnitPoint.z += vertical_offset + 0.02;
						UpdatePlayerState(player_session_idx, newUnitPoint, yaw, pitch, true);
					}
				}
			}
		}

		void RespawnPlayer(short player_session_idx, real_point3d const &position, float yaw, float pitch) // 0x106DFC60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RespawnPlayer@PlayerPodium@Player@@YAXFABUreal_point3d@@MM@Z");
			// float pitch;
				// s_player_datum *player;
			// function call : bool (*const)()

			if (((bool (*const)())0x5319C0)())
			{
				if (s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx))
					UpdatePlayerState(player_session_idx, position, yaw, pitch, true);
				else
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player index '{}' failed to spawn because the player was not in the session.", player_session_idx));
			}
		}

		void ShowPlace(short desiredPlace, short stats_player_session_idx) // 0x106E0330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ShowPlace@PlayerPodium@Player@@YAXFF@Z");
			// static ...; // 0x106E0D18
			// static ...; // 0x106E0D0C
			// static ...; // 0x106E0D01
			// static ...; // 0x106E0CF6
			// static ...; // 0x106E0CF2
			// static ...; // 0x106E0CE7
			// static ...; // 0x106E0CDC
			// static ...; // 0x106E0CD8
			// static ...; // 0x106E0C6C
			// static ...; // 0x106E0C64
			// short desiredPlace;
			// short stats_player_session_idx;
			// long (*const game_engine_get_player_place)(long);
			// c_network_session *session;
				// c_game_statborg *scoreboard;
				// std::vector<Player::PlayerPodium::PlayerPlace> player_places;
					// long i;
						// s_player_datum *player;
						// long player_datum_index;
							// long place;
					// s_player_datum *extra_stats_player;
					// std::string playersInfo;
						// short player_session_idx;
							// s_player_datum *player;
							// long player_datum_index;
								// char uid[17];
								// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
								// c_game_statborg::s_player_row const &scores;
								// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
							// char uid[17];
							// c_game_statborg::s_player_row const &scores;
			// function call : bool (*const)(c_network_session **)
			// function call : long (*const)(long)
			// function call : c_game_statborg *(*const)()

			long (*const game_engine_get_player_place)(long) = (long (*)(long))0x5506F0;
			c_network_session *session;
			if (network_session_interface_get_squad_session(&session))
			{
				if (desiredPlace == -1 && stats_player_session_idx == -1)
				{
					Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Podium, "podium_hide", "{}");
				}
				else
				{
					desiredPlace = desiredPlace - 1;
					std::vector<PlayerPlace> player_places;
					for (long i = 0; i < 16; i++)
					{
						if (session->get_session_membership()->is_player_valid(i))
						{
							long player_datum_index = PlayerNetworkUtil::get_player_datum_index_from_session_index(i);
							s_player_datum *player = players_get()->try_and_get(player_datum_index);
							if (player)
							{
								long place = game_engine_get_player_place(player_datum_index);
								player_places.push_back({ (short)i, (short)place });
							}
						}
					}
					std::sort(player_places.begin(), player_places.end());
					c_game_statborg *scoreboard = ((c_game_statborg *(*const)())0x550B80)();
					if (scoreboard)
					{
						std::string playersInfo = Modules::ModuleServer::Instance().VarPlayersInfoClient->ValueString;
						if (playersInfo.empty() || playersInfo == "{}")
							playersInfo = Player::CPlayersInfo::GeneratePlayerInfo();
						if (player_places.size() > 0 && desiredPlace < (short)player_places.size())
						{
							short player_session_idx = player_places[desiredPlace].player_session_idx;
							if (session->get_session_membership()->is_player_valid(player_session_idx))
							{
								long player_datum_index = PlayerNetworkUtil::get_player_datum_index_from_session_index(player_session_idx);
								s_player_datum *player = players_get()->try_and_get(player_datum_index);
								if (player)
								{
									rapidjson::StringBuffer jsonBuffer;
									rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
									c_game_statborg::s_player_row const &scores = scoreboard->players[player_datum_index & 0xF];
									jsonWriter.StartObject();
									jsonWriter.Key("extraStats");
									jsonWriter.Bool(false);
									jsonWriter.Key("place");
									jsonWriter.Int(desiredPlace);
									jsonWriter.Key("playerIndex");
									jsonWriter.Int(player_session_idx);
									jsonWriter.Key("playername");
									jsonWriter.String(Utils::String::ThinString(player->configuration.host.player_name).c_str());
									jsonWriter.Key("uid");
									char uid[17];
									player_format_uid(uid, player->configuration.host.player_uid);
									jsonWriter.String(uid);
									jsonWriter.Key("score");
									jsonWriter.Int(scores.total_score);
									jsonWriter.Key("playersInfo");
									jsonWriter.RawValue(playersInfo.c_str(), playersInfo.size(), rapidjson::kObjectType);
									jsonWriter.Key("emblem");
									jsonWriter.String(Player::Emblems::BuildUrl(player->configuration.host.appearance.emblem_config).c_str());
									jsonWriter.EndObject();
									Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Podium, "podium", jsonBuffer.GetString());
								}
							}
						}
						s_player_datum *extra_stats_player = PlayerNetworkUtil::get_player_from_session_index(stats_player_session_idx);
						if (stats_player_session_idx != -1 && extra_stats_player && extra_stats_player)
						{
							rapidjson::StringBuffer jsonBuffer;
							rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
							long player_datum_index = PlayerNetworkUtil::get_player_datum_index_from_session_index(stats_player_session_idx);
							s_player_datum *player = players_get()->try_and_get(player_datum_index);
							if (player)
							{
								c_game_statborg::s_player_row const &scores = scoreboard->players[player_datum_index & 0xF];
								jsonWriter.StartObject();
								jsonWriter.Key("extraStats");
								jsonWriter.Bool(true);
								jsonWriter.Key("kills");
								jsonWriter.Int(scores.kills);
								jsonWriter.Key("assists");
								jsonWriter.Int(scores.assists);
								jsonWriter.Key("deaths");
								jsonWriter.Int(scores.deaths);
								jsonWriter.Key("streak");
								jsonWriter.Int(scores.consecutive_kills);
								jsonWriter.Key("uid");
								char uid[17];
								player_format_uid(uid, extra_stats_player->configuration.host.player_uid);
								jsonWriter.String(uid);
								jsonWriter.Key("playersInfo");
								jsonWriter.RawValue(playersInfo.c_str(), playersInfo.size(), rapidjson::kObjectType);
								jsonWriter.EndObject();
								Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Podium, "podium", jsonBuffer.GetString());
							}
						}
					}
				}
			}
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_scenario_cutscene_camera_point@@QAE@ABU0@@Z"); no body to assert in
_inline s_scenario_cutscene_camera_point::s_scenario_cutscene_camera_point(s_scenario_cutscene_camera_point const &__that) = default; // 0x106DCED0

namespace Player
{
	namespace PlayerPodium
	{
		short GetPlayerAnimationCount(short player_session_idx) // 0x106DE5D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerAnimationCount@PlayerPodium@Player@@YAFF@Z");
			// short player_session_idx;
			// Blam::Network::Session *session;
				// s_player_datum *player;
				// s_game_globals *matg;
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
			// function call : void *(*const)(unsigned long, long)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
				s_game_globals *matg = game_globals_get();
				if (player && matg)
				{
					s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
					long characterTypeIndex = GetModgCharacterIndexFromPlayer(player);
					if (mulg && characterTypeIndex >= 0 && characterTypeIndex < matg->player_character_types.count && characterTypeIndex < mulg->universal->podium_animations.count)
						return mulg->universal->podium_animations[characterTypeIndex].move_animations.count;
				}
			}
			return -1;
		}

		long GetPlayerAnimationGraph(short player_session_idx) // 0x106DE730
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerAnimationGraph@PlayerPodium@Player@@YAJF@Z");
			// short player_session_idx;
			// Blam::Network::Session *session;
				// s_player_datum *player;
				// s_game_globals *matg;
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
			// function call : void *(*const)(unsigned long, long)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
				s_game_globals *matg = game_globals_get();
				if (player && matg)
				{
					s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
					long characterTypeIndex = GetModgCharacterIndexFromPlayer(player);
					if (mulg && characterTypeIndex >= 0 && characterTypeIndex < mulg->universal->podium_animations.count)
						return mulg->universal->podium_animations[characterTypeIndex].animation_graph.index;
				}
			}
			return -1;
		}

		unsigned long GetPlayerAnimationString(short player_session_idx, short animationType, short animationIndex) // 0x106DE880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerAnimationString@PlayerPodium@Player@@YAKFFF@Z");
			// short animationIndex;
			// Blam::Network::Session *session;
				// s_player_datum *player;
				// s_game_globals *matg;
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
			// function call : void *(*const)(unsigned long, long)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
				s_game_globals *matg = game_globals_get();
				if (player && matg)
				{
					s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
					long characterTypeIndex = GetModgCharacterIndexFromPlayer(player);
					if (mulg && characterTypeIndex >= 0 && characterTypeIndex < mulg->universal->podium_animations.count && animationIndex >= 0 && animationIndex < mulg->universal->podium_animations[characterTypeIndex].move_animations.count)
					{
						if (animationType == 0)
							return mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].in_animation;
						if (animationType == 1)
							return mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].loop_animation;
						if (animationType == 2)
							return mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].out_animation;
					}
				}
			}
			return -1;
		}

		long GetAnimationWeaponIndex(short player_session_idx, short animationIndex, bool isPrimary) // 0x106DE2C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetAnimationWeaponIndex@PlayerPodium@Player@@YAJFF_N@Z");
			// bool isPrimary;
			// Blam::Network::Session *session;
				// s_player_datum *player;
				// s_game_globals *matg;
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
						// unsigned long weapon;
			// function call : void *(*const)(unsigned long, long)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
				s_game_globals *matg = game_globals_get();
				if (player && matg)
				{
					s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
					long characterTypeIndex = GetModgCharacterIndexFromPlayer(player);
					if (mulg && characterTypeIndex >= 0 && characterTypeIndex < mulg->universal->podium_animations.count && animationIndex >= 0 && animationIndex < mulg->universal->podium_animations[characterTypeIndex].move_animations.count)
					{
						unsigned long weapon;
						if (isPrimary)
							weapon = mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].primary_weapon.index;
						else
							weapon = mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].secondary_weapon.index;
						return weapon;
					}
				}
			}
			return -1;
		}

		float GetAnimationOffset(short player_session_idx, short animationIndex) // 0x106DE110
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetAnimationOffset@PlayerPodium@Player@@YAMFF@Z");
			// short animationIndex;
			// Blam::Network::Session *session;
				// s_player_datum *player;
				// s_game_globals *matg;
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
			// function call : void *(*const)(unsigned long, long)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = PlayerNetworkUtil::get_player_from_session_index(player_session_idx);
				s_game_globals *matg = game_globals_get();
				if (player && matg)
				{
					s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
					long characterTypeIndex = GetModgCharacterIndexFromPlayer(player);
					if (mulg && characterTypeIndex >= 0 && characterTypeIndex < mulg->universal->podium_animations.count && animationIndex >= 0 && animationIndex < mulg->universal->podium_animations[characterTypeIndex].move_animations.count)
						return mulg->universal->podium_animations[characterTypeIndex].move_animations[animationIndex].biped_offset_distance;
				}
			}
			return 0.0f;
		}

		void ResetStates() // 0x106DFC20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResetStates@PlayerPodium@Player@@YAXXZ");
			// procedure flags: nofpo

			s_PodiumStates.podiumInit = false;
			s_PodiumStates.inPostGame = false;
			s_PodiumStates.podiumStarted = false;
		}

		void HandleEvent(char const *eventString) // 0x106DF310
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HandleEvent@PlayerPodium@Player@@YAXPBD@Z");
			// char const *eventString;

			if (!strcmp(eventString, "podium_init"))
			{
				s_PodiumStates.podiumInit = true;
				return;
			}
			else if (!strcmp(eventString, "podium_start"))
			{
				s_PodiumStates.podiumStarted = true;
				return;
			}
			else if (!strcmp(eventString, "podium_end"))
			{
				s_PodiumStates.podiumStarted = false;
			}
		}

		bool PodiumEnabled() // 0x106DF530
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PodiumEnabled@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo
			// unsigned long PodiumEnabledValue;
			// __int32 lobbytype;

			__int32 lobbytype = Blam::Network::GetLobbyType();
			unsigned long PodiumEnabledValue = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPodiumEnabledClient->ValueInt;

			if (lobbytype == 3)
				return (PodiumEnabledValue == 1 || PodiumEnabledValue == 2) && Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPodiumForgeEnabledClient->ValueInt == 1;
			else if (lobbytype == 2)
				return PodiumEnabledValue == 1 || PodiumEnabledValue == 2;

			return false;
		}

		bool PodiumStarted() // 0x106DF640
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PodiumStarted@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo

			return s_PodiumStates.podiumStarted;
		}

		bool PodiumhasInitialized() // 0x106DFB80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PodiumhasInitialized@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo

			return s_PodiumStates.podiumInit;
		}

		bool PodiumIsReady() // 0x106DF620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PodiumIsReady@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo

			return podiumReady;
		}

		bool ForgeCanOverride() // 0x106DE0F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ForgeCanOverride@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo

			return forgeOverrideAllowed;
		}

		void SetForgeCanOverride(bool allowed) // 0x106E0300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeCanOverride@PlayerPodium@Player@@YAX_N@Z");
			// bool allowed;

			forgeOverrideAllowed = allowed;
		}

		void OnMapLoaded(char const *mapPath) // 0x106DF490
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoaded@PlayerPodium@Player@@YAXPBD@Z");
			// char const *mapPath;
			// function call : bool (*const)()

			ResetStates();
			if (!((bool(*)())0x531E90)())
			{
				Scripting::HS::ExecuteScript("podium_init", {});
			}
		}

		void PodiumTick() // 0x106DF660
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PodiumTick@PlayerPodium@Player@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x106DFA6B
			// static ...; // 0x106DFA60
			// static ...; // 0x106DFA48
			// static ...; // 0x106DFA40
			// static bool (*IsMapLoading)(); // 0x1134D6CC
			// static bool (*InPrematchState)(char); // 0x1134D6C8
			// long roundTime;
				// long s_PodiumObjectIndex;
				// s_object_data *scenObject;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
			// function call : long (*const)()
			// function call : bool (*const)()
			// function call : bool (*)(char)
			// function call : bool (*const)()
			// function call : c_game_engine *(*const)()
			// function call : bool (*const)()
			// function call : c_game_statborg *(*const)()
			// function call : c_game_statborg *(*const)()
			// function call : bool (*const)()
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : c_game_engine *(*const)()
			// function call : bool (*const)()
			// function call : bool (*)()

			static bool (*InPrematchState)(char) = (bool (*)(char))0x5523A0;
			static bool (*IsMapLoading)() = (bool (*)())0x5670E0;
			long roundTime = ((long (*const)())0x5523D0)();
			if (!game_is_multiplayer())
				return;
			if (InPrematchState(4))
			{
				podiumReady = false;
				return;
			}
			if (((bool (*const)())0x550F90)())
				podiumReady = true;
			if (((c_game_engine *(*const)())0x5CE150)() && ((bool (*const)())0x531B20)() && ((c_game_statborg *(*const)())0x550B80)() && ((c_game_statborg *(*const)())0x550B80)()->finalized && podiumReady && !s_PodiumStates.inPostGame && PodiumEnabled())
			{
				if (((bool (*const)())0x5319C0)())
				{
					long s_PodiumObjectIndex = Forge::PodiumPoint::FindPodiumObject();
					s_object_data *scenObject = object_try_and_get_and_verify_type(s_PodiumObjectIndex, 0x80);
					if (Modules::ModuleServer::Instance().VarServerPodiumEnabled->ValueInt == 2 && s_PodiumObjectIndex != -1 && scenObject)
						Scripting::HS::ExecuteScript("podium", {});
					else if (Modules::ModuleServer::Instance().VarServerPodiumEnabled->ValueInt == 1)
						Scripting::HS::ExecuteScript("podium", {});
				}
				s_PodiumStates.inPostGame = true;
			}
			else if (((c_game_engine *(*const)())0x5CE150)() && !((bool (*const)())0x531B20)() && s_PodiumStates.inPostGame)
			{
				s_PodiumStates.inPostGame = false;
			}
			if (IsMapLoading() && s_PodiumStates.inPostGame)
			{
				rapidjson::StringBuffer jsonBuffer;
				rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
				jsonWriter.StartObject();
				jsonWriter.Key("scoreboard");
				jsonWriter.Bool(false);
				jsonWriter.EndObject();
				Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Podium, "podium_hide", jsonBuffer.GetString());
				ResetStates();
				podiumReady = false;
				forgeOverrideAllowed = false;
			}
		}

		short GetPlayerSessionIndexByLeaderboardPlace(short leaderboardPlace) // 0x106DEB10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerSessionIndexByLeaderboardPlace@PlayerPodium@Player@@YAFF@Z");
			// static ...; // 0x106DED46
			// static ...; // 0x106DED38
			// static ...; // 0x106DED20
			// static ...; // 0x106DED18
			// short leaderboardPlace;
			// long (*const game_engine_get_player_place)(long);
			// c_network_session *session;
				// std::vector<Player::PlayerPodium::PlayerPlace> player_places;
					// long i;
						// s_player_datum *player;
						// long datum_index;
							// long place;
					// short player_session_idx;
			// function call : bool (*const)(c_network_session **)
			// function call : long (*const)(long)

			leaderboardPlace = leaderboardPlace - 1;
			long (*const game_engine_get_player_place)(long) = (long (*)(long))0x5506F0;
			c_network_session *session;
			if (network_session_interface_get_squad_session(&session))
			{
				std::vector<PlayerPlace> player_places;
				for (long i = 0; i < 16; i++)
				{
					if (session->get_session_membership()->is_player_valid(i))
					{
						long datum_index = PlayerNetworkUtil::get_player_datum_index_from_session_index(i);
						s_player_datum *player = players_get()->try_and_get(datum_index);
						if (player)
						{
							long place = game_engine_get_player_place(datum_index);
							player_places.push_back({ (short)i, (short)place });
						}
					}
				}
				if (player_places.size() > 0 && leaderboardPlace < (short)player_places.size())
				{
					std::sort(player_places.begin(), player_places.end());
					short player_session_idx = player_places[leaderboardPlace].player_session_idx;
					return player_session_idx;
				}
			}
			return -1;
		}

		long GetPodiumRespawnEffectIndex(short place) // 0x106DF130
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPodiumRespawnEffectIndex@PlayerPodium@Player@@YAJF@Z");
			// short place;
			// s_game_globals *matg;
				// void *podium;
					// s_podium_settings *podium_settings;
			// function call : void *(*const)(unsigned long, long)

			s_game_globals *matg = game_globals_get();
			if (matg)
			{
				void *podium = tag_try_and_get_and_verify_group(0x70646D21, matg->PodiumDefinition.index);
				if (podium)
				{
					s_podium_settings *podium_settings = (s_podium_settings *)tag_get(0x70646D21, matg->PodiumDefinition.index);
					if (podium_settings && place >= 0 && place < podium_settings->podium_bipeds.count)
						return podium_settings->podium_bipeds[place].spawn_effect.index;
				}
			}

			return -1;
		}

		float GetPodiumBipedOffset(char const *offset_type, short place) // 0x106DEDE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPodiumBipedOffset@PlayerPodium@Player@@YAMPBDF@Z");
			// static ...; // 0x106DEF84
		// $LN12:
		// $LN11:
		// $LN10:
		// $LN9:
		// $LN8:
		// $LN7:
		// $LN2:
			// char const *offset_type;
			// short place;
			// s_game_globals *matg;
				// void *podium;
					// s_podium_settings *podium_settings;
						// s_podium_biped const &biped;
			// function call : void *(*const)(unsigned long, long)

			s_game_globals *matg = game_globals_get();
			if (matg)
			{
				void *podium = tag_try_and_get_and_verify_group(0x70646D21, matg->PodiumDefinition.index);
				if (podium)
				{
					s_podium_settings *podium_settings = (s_podium_settings *)tag_get(0x70646D21, matg->PodiumDefinition.index);
					if (podium_settings && place >= 0 && place < podium_settings->podium_bipeds.count)
					{
						s_podium_biped const &biped = podium_settings->podium_bipeds[place];
						switch (offset_type[0])
						{
						case 'x':
							return biped.offset_x;
						case 'y':
							return biped.offset_y;
						case 'z':
							return biped.offset_z;
						case 'i':
							return biped.orientation_offset_y * 57.29577951308232;
						case 'j':
							return biped.orientation_offset_p * 57.29577951308232;
						case 'k':
							return biped.orientation_offset_r * 57.29577951308232;
						}
					}
				}
			}
			return 0.0f;
		}

		long GetPodiumBipedSpawnDelay(short place) // 0x106DF030
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPodiumBipedSpawnDelay@PlayerPodium@Player@@YAJF@Z");
			// short place;
			// s_game_globals *matg;
				// void *podium;
					// s_podium_settings *podium_settings;
			// function call : void *(*const)(unsigned long, long)

			s_game_globals *matg = game_globals_get();
			if (matg)
			{
				void *podium = tag_try_and_get_and_verify_group(0x70646D21, matg->PodiumDefinition.index);
				if (podium)
				{
					s_podium_settings *podium_settings = (s_podium_settings *)tag_get(0x70646D21, matg->PodiumDefinition.index);
					if (podium_settings && place >= 0 && place < podium_settings->podium_bipeds.count)
						return podium_settings->podium_bipeds[place].spawn_delay;
				}
			}

			return 0;
		}

		long GetPodiumTickDelay() // 0x106DF240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPodiumTickDelay@PlayerPodium@Player@@YAJXZ");
			// procedure flags: nofpo
			// s_game_globals *matg;
				// void *podium;
					// s_podium_settings *podium_settings;
			// function call : void *(*const)(unsigned long, long)

			s_game_globals *matg = game_globals_get();
			if (matg)
			{
				void *podium = tag_try_and_get_and_verify_group(0x70646D21, matg->PodiumDefinition.index);
				if (podium)
				{
					s_podium_settings *podium_settings = (s_podium_settings *)tag_get(0x70646D21, matg->PodiumDefinition.index);
					if (podium_settings)
						return podium_settings->tick_delay;
				}
			}

			return 0;
		}

		void DoSpawnPlayer(long target_player_datum_index, real_point3d position, real_vector3d forward) // 0x106DD850
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DoSpawnPlayer@PlayerPodium@Player@@YAXJUreal_point3d@@Ureal_vector3d@@@Z");
			// static ...; // 0x106DDF04
			// static ...; // 0x106DDEE0
			// static ...; // 0x106DDED8
			// long target_player_datum_index;
			// real_point3d position;
			// real_vector3d forward;
			// long biped_definition_index;
			// s_player_datum *player;
			// unsigned long variant_name;
			// void (*const player_find_player_character_unit_and_variant_info)(long, long *, unsigned long *);
			// void (*const player_model_customize)(void *, long);
			// s_object_placement_data placement_data;
			// void (*const objects_scripting_set_scale)(unsigned __int32, float, float);
			// long biped_index;
			// s_player_model_customization *(*const player_get_model_customization)(s_player_datum *);
			// void (*const player_set_unit_index)(long, long);
			// function call : void (*const)(long, long *, unsigned long *)
			// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
			// function call : long (*const)(s_object_placement_data *)
			// function call : void (*const)(long, long)
			// function call : void (*const)(long, long)
			// function call : s_player_model_customization *(*const)(s_player_datum *)
			// function call : void (*const)(void *, long)
			// function call : void (*const)(long)

			void (*const player_find_player_character_unit_and_variant_info)(long, long *, unsigned long *) = (void (*)(long, long *, unsigned long *))0x539F70;
			void (*const player_set_unit_index)(long, long) = (void (*)(long, long))0x53CA80;
			s_player_model_customization *(*const player_get_model_customization)(s_player_datum *) = (s_player_model_customization *(*)(s_player_datum *))0x536000;
			void (*const player_model_customize)(void *, long) = (void (*)(void *, long))0x5A4430;
			void (*const objects_scripting_set_scale)(unsigned __int32, float, float) = (void (*)(unsigned __int32, float, float))0xB965C0;
			long biped_definition_index = -1;
			unsigned long variant_name = 0;
			s_player_datum *player = player_get(target_player_datum_index);
			if (!player)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player index '{}' failed to spawn because the player could not be found.", target_player_datum_index));
				return;
			}
			if (player->character_type_index == -1)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player '{}' '{}' failed to spawn because they did not have a character type set", target_player_datum_index, Utils::String::ThinString(player->configuration.host.player_name)));
				return;
			}
			player_find_player_character_unit_and_variant_info(target_player_datum_index, &biped_definition_index, &variant_name);
			if (biped_definition_index == -1)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player '{}' '{}' failed to spawn because the player biped definition index was null.", target_player_datum_index, Utils::String::ThinString(player->configuration.host.player_name)));
				return;
			}
			player->powerup_pickup_times[0] = 0;
			player->powerup_pickup_times[1] = 0;
			player->powerup_pickup_times[2] = 0;
			s_object_placement_data placement_data = {};
			object_placement_data_new(&placement_data, biped_definition_index, -1, nullptr);
			placement_data.variant_name = variant_name;
			placement_data.relative_position = { position.x, position.y, position.z };
			placement_data.forward = forward;
			placement_data.up = global_up3d;
			long biped_index = ((long (*)(s_object_placement_data *))0xB30440)(&placement_data);
			if (biped_index == -1)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("Podium :: Player '{}' '{}' failed to spawn because of an unknown error creating the object.", target_player_datum_index, Utils::String::ThinString(player->configuration.host.player_name)));
				return;
			}
			player_set_unit_index(target_player_datum_index, biped_index);
			player_refresh_object_appearance_full(target_player_datum_index, biped_index);
			player_model_customize(player_get_model_customization(player), biped_index);
			((void (*)(long))0x4B2CD0)(biped_index);
		}

		void UpdatePlayer(long player_datum_index) // 0x106E0FB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePlayer@PlayerPodium@Player@@YAXJ@Z");
			// static ...; // 0x106E118C
			// static ...; // 0x106E1184
			// static ...; // 0x106E116C
			// static ...; // 0x106E1164
			// long player_datum_index;
			// void (*const simulation_action_object_update)(long, c_flags<long,__int64> *);
			// Blam::Network::Session *session;
				// long player_session_idx;
					// Player::PlayerPodium::HaloScriptPlayerModelState::PlayerPositions playerState;
						// real_vector3d forward;
						// float angle_radians_vertical;
						// float angle_radians_horizontal;
			// function call : bool (*const)()

			void (*const simulation_action_object_update)(long, c_flags<long, __int64> *) = reinterpret_cast<void (*)(long, c_flags<long, __int64> *)>(0x4B3010);
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session)
			{
				long player_session_idx = Player::PlayerNetworkUtil::get_session_player_index_from_player_datum_index(player_datum_index);
				if (player_session_idx != -1)
				{
					HaloScriptPlayerModelState::PlayerPositions playerState = s_PodiumPlayerStates.player[player_session_idx];
					if (((bool (*const)())0x5319C0)() && playerState.dirty)
					{
						real_vector3d forward;
						float angle_radians_vertical = playerState.yaw / 180.0f * 3.1415927f;
						float angle_radians_horizontal = playerState.pitch / 180.0f * 3.1415927f;
						forward.i = cos(angle_radians_vertical);
						forward.j = sin(angle_radians_vertical);
						forward.k = -cos(angle_radians_horizontal);
						DoSpawnPlayer(player_datum_index, playerState.position, forward);
						s_PodiumPlayerStates.player[player_session_idx].dirty = false;
						s_PodiumPlayerStates.player[player_session_idx].forceRespawn = false;
					}
				}
			}
		}

		void UpdatePlayerState(long player_session_idx, real_point3d position, float yaw, float pitch, bool respawn) // 0x106E1220
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePlayerState@PlayerPodium@Player@@YAXJUreal_point3d@@MM_N@Z");
			// bool respawn;

			#line 1227 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Player\\PlayerPodium.cpp"
				assert(player_session_idx >= 0 && player_session_idx < 16);
				#line 1233 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Player\\PlayerPodium.cpp"
			s_PodiumPlayerStates.player[player_session_idx] = {};
			s_PodiumPlayerStates.player[player_session_idx].position = position;
			s_PodiumPlayerStates.player[player_session_idx].yaw = yaw;
			s_PodiumPlayerStates.player[player_session_idx].pitch = pitch;
			s_PodiumPlayerStates.player[player_session_idx].forceRespawn = respawn;
			s_PodiumPlayerStates.player[player_session_idx].dirty = true;
		}

		void Init() // 0x106DF3C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@PlayerPodium@Player@@YAXXZ");
			// procedure flags: nofpo

			Patches::Core::OnMapLoaded(Player::PlayerPodium::OnMapLoaded);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_mod_globals_player_character_customization>::try_get_element(__int32, s_mod_globals_player_character_customization **) const;
template bool c_tag_block<s_multiplayer_move_animations>::try_get_element(__int32, s_multiplayer_move_animations **) const;
template bool c_tag_block<s_multiplayer_podium_animations>::try_get_element(__int32, s_multiplayer_podium_animations **) const;
template bool c_tag_block<s_multiplayer_universal_globals_definition>::try_get_element(__int32, s_multiplayer_universal_globals_definition **) const;
template bool c_tag_block<s_podium_biped>::try_get_element(__int32, s_podium_biped **) const;
template bool c_tag_block<s_scenario_cutscene_camera_point>::try_get_element(__int32, s_scenario_cutscene_camera_point **) const;
template c_enum<enum e_scenario_cutscene_camera_point_type,unsigned short>::c_enum(c_enum<enum e_scenario_cutscene_camera_point_type,unsigned short> const &);
template c_enum<enum e_scenario_cutscene_camera_point_type,unsigned short>::c_enum(unsigned short const &);
template s_mod_globals_player_character_customization & c_tag_block<s_mod_globals_player_character_customization>::operator[](__int32);
template s_mod_globals_player_character_customization * c_tag_block<s_mod_globals_player_character_customization>::get_element(__int32) const;
template s_multiplayer_move_animations & c_tag_block<s_multiplayer_move_animations>::operator[](__int32);
template s_multiplayer_move_animations * c_tag_block<s_multiplayer_move_animations>::get_element(__int32) const;
template s_multiplayer_podium_animations & c_tag_block<s_multiplayer_podium_animations>::operator[](__int32);
template s_multiplayer_podium_animations * c_tag_block<s_multiplayer_podium_animations>::get_element(__int32) const;
template s_multiplayer_universal_globals_definition * c_tag_block<s_multiplayer_universal_globals_definition>::get_element(__int32) const;
template s_multiplayer_universal_globals_definition * c_tag_block<s_multiplayer_universal_globals_definition>::operator->();
template s_podium_biped & c_tag_block<s_podium_biped>::operator[](__int32);
template s_podium_biped * c_tag_block<s_podium_biped>::get_element(__int32) const;
template s_scenario_cutscene_camera_point & c_tag_block<s_scenario_cutscene_camera_point>::operator[](__int32);
template s_scenario_cutscene_camera_point * c_tag_block<s_scenario_cutscene_camera_point>::get_element(__int32) const;

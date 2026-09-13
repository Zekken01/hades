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

namespace Player
{
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

		_extern long _sub_106DE4F0(s_player_datum *);
		long GetModgCharacterIndexFromPlayer(s_player_datum *player) // 0x106DE4F0
		{
			mangled_x86(MANGLED_TODO, "?GetModgCharacterIndexFromPlayer@PlayerPodium@Player@@YAJPAUs_player_datum@@@Z");
			// s_player_datum *player;
			// s_mod_globals_definition *const modg;
			{
				// __int32 i;
				{
					// s_mod_globals_player_character_customization *const character;
				}
			}
			todo("implement");
			long __result = _sub_106DE4F0(player);
			return __result;
		}

		_extern void _sub_106DFDA0(short, short, float, float, float, float, float);
		void RespawnPlayerOffset(short player_session_idx, short cutscene_camera_point_index, float distance_offset, float horizontal_offset, float vertical_offset, float yaw_offset, float pitch) // 0x106DFDA0
		{
			mangled_x86(MANGLED_TODO, "?RespawnPlayerOffset@PlayerPodium@Player@@YAXFFMMMMM@Z");
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
			{
				// s_scenario *const scnr;
				{
					// s_player_datum *player;
					// c_tag_block<s_scenario_cutscene_camera_point> cutscenes;
					{
						// real_point3d newUnitPoint;
						// float yaw;
						// s_scenario_cutscene_camera_point cutscene_camera;
						// bool isPodiumHack;
						// s_scenario_cutscene_camera_point podiumCamera;
						{
							// long s_PodiumObjectIndex;
							// s_object_data *scenObject;
							{
								// real_matrix4x3 podiumObjectTransform;
								// real_euler_angles3d podiumObjectOrientation;
							}
						}
					}
				}
			}
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			todo("implement");
			_sub_106DFDA0(player_session_idx, cutscene_camera_point_index, distance_offset, horizontal_offset, vertical_offset, yaw_offset, pitch);
		}

		_extern void _sub_106DFC60(short, real_point3d const &, float, float);
		void RespawnPlayer(short player_session_idx, real_point3d const &position, float yaw, float pitch) // 0x106DFC60
		{
			mangled_x86(MANGLED_TODO, "?RespawnPlayer@PlayerPodium@Player@@YAXFABUreal_point3d@@MM@Z");
			// float pitch;
			{
				// s_player_datum *player;
			}
			// function call : bool (*const)()
			todo("implement");
			_sub_106DFC60(player_session_idx, position, yaw, pitch);
		}

		_extern void _sub_106E0330(short, short);
		void ShowPlace(short desiredPlace, short stats_player_session_idx) // 0x106E0330
		{
			mangled_x86(MANGLED_TODO, "?ShowPlace@PlayerPodium@Player@@YAXFF@Z");
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
			{
				// c_game_statborg *scoreboard;
				// std::vector<Player::PlayerPodium::PlayerPlace> player_places;
				{
					// long i;
					{
						// s_player_datum *player;
						// long player_datum_index;
						{
							// long place;
						}
					}
				}
				{
					// s_player_datum *extra_stats_player;
					// std::string playersInfo;
					{
						// short player_session_idx;
						{
							// s_player_datum *player;
							// long player_datum_index;
							{
								// char uid[17];
								// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
								// c_game_statborg::s_player_row const &scores;
								// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
							}
						}
					}
					{
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
						{
							// char uid[17];
							// c_game_statborg::s_player_row const &scores;
						}
					}
				}
			}
			// function call : bool (*const)(c_network_session **)
			// function call : long (*const)(long)
			// function call : c_game_statborg *(*const)()
			todo("implement");
			_sub_106E0330(desiredPlace, stats_player_session_idx);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_scenario_cutscene_camera_point@@QAE@ABU0@@Z"); no body to assert in
_inline s_scenario_cutscene_camera_point::s_scenario_cutscene_camera_point(s_scenario_cutscene_camera_point const &__that) = default; // 0x106DCED0

namespace Player
{
	namespace PlayerPodium
	{
		_extern short _sub_106DE5D0(short);
		short GetPlayerAnimationCount(short player_session_idx) // 0x106DE5D0
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerAnimationCount@PlayerPodium@Player@@YAFF@Z");
			// short player_session_idx;
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// s_game_globals *matg;
				{
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			short __result = _sub_106DE5D0(player_session_idx);
			return __result;
		}

		_extern long _sub_106DE730(short);
		long GetPlayerAnimationGraph(short player_session_idx) // 0x106DE730
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerAnimationGraph@PlayerPodium@Player@@YAJF@Z");
			// short player_session_idx;
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// s_game_globals *matg;
				{
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			long __result = _sub_106DE730(player_session_idx);
			return __result;
		}

		_extern unsigned long _sub_106DE880(short, short, short);
		unsigned long GetPlayerAnimationString(short player_session_idx, short animationType, short animationIndex) // 0x106DE880
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerAnimationString@PlayerPodium@Player@@YAKFFF@Z");
			// short animationIndex;
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// s_game_globals *matg;
				{
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			unsigned long __result = _sub_106DE880(player_session_idx, animationType, animationIndex);
			return __result;
		}

		_extern long _sub_106DE2C0(short, short, bool);
		long GetAnimationWeaponIndex(short player_session_idx, short animationIndex, bool isPrimary) // 0x106DE2C0
		{
			mangled_x86(MANGLED_TODO, "?GetAnimationWeaponIndex@PlayerPodium@Player@@YAJFF_N@Z");
			// bool isPrimary;
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// s_game_globals *matg;
				{
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
					{
						// unsigned long weapon;
					}
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			long __result = _sub_106DE2C0(player_session_idx, animationIndex, isPrimary);
			return __result;
		}

		_extern float _sub_106DE110(short, short);
		float GetAnimationOffset(short player_session_idx, short animationIndex) // 0x106DE110
		{
			mangled_x86(MANGLED_TODO, "?GetAnimationOffset@PlayerPodium@Player@@YAMFF@Z");
			// short animationIndex;
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// s_game_globals *matg;
				{
					// s_multiplayer_globals_definition *mulg;
					// long characterTypeIndex;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			float __result = _sub_106DE110(player_session_idx, animationIndex);
			return __result;
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

		_extern bool _sub_106DF530();
		bool PodiumEnabled() // 0x106DF530
		{
			mangled_x86(MANGLED_TODO, "?PodiumEnabled@PlayerPodium@Player@@YA_NXZ");
			// procedure flags: nofpo
			// unsigned long PodiumEnabledValue;
			// __int32 lobbytype;
			todo("implement");
			bool __result = _sub_106DF530();
			return __result;
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

		_extern void _sub_106DF490(char const *);
		void OnMapLoaded(char const *mapPath) // 0x106DF490
		{
			mangled_x86(MANGLED_TODO, "?OnMapLoaded@PlayerPodium@Player@@YAXPBD@Z");
			// char const *mapPath;
			// function call : bool (*const)()
			todo("implement");
			_sub_106DF490(mapPath);
		}

		_extern void _sub_106DF660();
		void PodiumTick() // 0x106DF660
		{
			mangled_x86(MANGLED_TODO, "?PodiumTick@PlayerPodium@Player@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x106DFA6B
			// static ...; // 0x106DFA60
			// static ...; // 0x106DFA48
			// static ...; // 0x106DFA40
			// static bool (*IsMapLoading)(); // 0x1134D6CC
			// static bool (*InPrematchState)(char); // 0x1134D6C8
			// long roundTime;
			{
				// long s_PodiumObjectIndex;
				// s_object_data *scenObject;
			}
			{
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
			}
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
			todo("implement");
			_sub_106DF660();
		}

		_extern short _sub_106DEB10(short);
		short GetPlayerSessionIndexByLeaderboardPlace(short leaderboardPlace) // 0x106DEB10
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerSessionIndexByLeaderboardPlace@PlayerPodium@Player@@YAFF@Z");
			// static ...; // 0x106DED46
			// static ...; // 0x106DED38
			// static ...; // 0x106DED20
			// static ...; // 0x106DED18
			// short leaderboardPlace;
			// long (*const game_engine_get_player_place)(long);
			// c_network_session *session;
			{
				// std::vector<Player::PlayerPodium::PlayerPlace> player_places;
				{
					// long i;
					{
						// s_player_datum *player;
						// long datum_index;
						{
							// long place;
						}
					}
				}
				{
					// short player_session_idx;
				}
			}
			// function call : bool (*const)(c_network_session **)
			// function call : long (*const)(long)
			todo("implement");
			short __result = _sub_106DEB10(leaderboardPlace);
			return __result;
		}

		_extern long _sub_106DF130(short);
		long GetPodiumRespawnEffectIndex(short place) // 0x106DF130
		{
			mangled_x86(MANGLED_TODO, "?GetPodiumRespawnEffectIndex@PlayerPodium@Player@@YAJF@Z");
			// short place;
			// s_game_globals *matg;
			{
				// void *podium;
				{
					// s_podium_settings *podium_settings;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			long __result = _sub_106DF130(place);
			return __result;
		}

		_extern float _sub_106DEDE0(char const *, short);
		float GetPodiumBipedOffset(char const *offset_type, short place) // 0x106DEDE0
		{
			mangled_x86(MANGLED_TODO, "?GetPodiumBipedOffset@PlayerPodium@Player@@YAMPBDF@Z");
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
			{
				// void *podium;
				{
					// s_podium_settings *podium_settings;
					{
						// s_podium_biped const &biped;
					}
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			float __result = _sub_106DEDE0(offset_type, place);
			return __result;
		}

		_extern long _sub_106DF030(short);
		long GetPodiumBipedSpawnDelay(short place) // 0x106DF030
		{
			mangled_x86(MANGLED_TODO, "?GetPodiumBipedSpawnDelay@PlayerPodium@Player@@YAJF@Z");
			// short place;
			// s_game_globals *matg;
			{
				// void *podium;
				{
					// s_podium_settings *podium_settings;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			long __result = _sub_106DF030(place);
			return __result;
		}

		_extern long _sub_106DF240();
		long GetPodiumTickDelay() // 0x106DF240
		{
			mangled_x86(MANGLED_TODO, "?GetPodiumTickDelay@PlayerPodium@Player@@YAJXZ");
			// procedure flags: nofpo
			// s_game_globals *matg;
			{
				// void *podium;
				{
					// s_podium_settings *podium_settings;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			long __result = _sub_106DF240();
			return __result;
		}

		_extern void _sub_106DD850(long, real_point3d, real_vector3d);
		void DoSpawnPlayer(long target_player_datum_index, real_point3d position, real_vector3d forward) // 0x106DD850
		{
			mangled_x86(MANGLED_TODO, "?DoSpawnPlayer@PlayerPodium@Player@@YAXJUreal_point3d@@Ureal_vector3d@@@Z");
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
			todo("implement");
			_sub_106DD850(target_player_datum_index, position, forward);
		}

		_extern void _sub_106E0FB0(long);
		void UpdatePlayer(long player_datum_index) // 0x106E0FB0
		{
			mangled_x86(MANGLED_TODO, "?UpdatePlayer@PlayerPodium@Player@@YAXJ@Z");
			// static ...; // 0x106E118C
			// static ...; // 0x106E1184
			// static ...; // 0x106E116C
			// static ...; // 0x106E1164
			// long player_datum_index;
			// void (*const simulation_action_object_update)(long, c_flags<long,__int64> *);
			// Blam::Network::Session *session;
			{
				// long player_session_idx;
				{
					// Player::PlayerPodium::HaloScriptPlayerModelState::PlayerPositions playerState;
					{
						// real_vector3d forward;
						// float angle_radians_vertical;
						// float angle_radians_horizontal;
					}
				}
			}
			// function call : bool (*const)()
			todo("implement");
			_sub_106E0FB0(player_datum_index);
		}

		_extern void _sub_106E1220(long, real_point3d, float, float, bool);
		void UpdatePlayerState(long player_session_idx, real_point3d position, float yaw, float pitch, bool respawn) // 0x106E1220
		{
			mangled_x86(MANGLED_TODO, "?UpdatePlayerState@PlayerPodium@Player@@YAXJUreal_point3d@@MM_N@Z");
			// bool respawn;
			todo("implement");
			_sub_106E1220(player_session_idx, position, yaw, pitch, respawn);
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

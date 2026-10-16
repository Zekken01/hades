/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "Scripting/HaloScript/HsThreadStorage.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class c_network_session;
struct hs_value;
struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_object_data;
struct s_player_datum;
struct s_starting_weapon_info;
struct s_tag_reference;
struct s_unit_data;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x106FBB30

namespace Player { namespace PlayerNetworkUtil { long get_session_player_index_from_player_datum_index(long player_datum_index); } }  // hades: added for 0x106FB5A0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x106FC270

namespace Player { namespace PlayerNetworkUtil { extern s_player_datum *get_player_from_session_index(__int32 player_session_index); } }  // hades: added for 0x106FB730

namespace Player
{
	namespace PlayerPodium
	{
		// hades: declared only in Player/PlayerPodium.cpp.
		extern short GetPlayerSessionIndexByLeaderboardPlace(short);
	}
}

namespace Player
{
	namespace PlayerPodium
	{
		// hades: declared only in Player/PlayerPodium.cpp.
		extern short GetPlayerSessionIndexByLeaderboardPlace(short leaderboardPlace);
	}
}

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Player
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_player_get_uid_evaluate(short op, long thread_index, bool initial);
void hs_player_name_evaluate(short op, long thread_index, bool initial);
void hs_player_get_by_idx_evaluate(short op, long thread_index, bool initial);
void hs_get_player_idx_by_unit_evaluate(short op, long thread_index, bool initial);
void hs_player_get_idx_by_place_evaluate(short op, long thread_index, bool initial);
void hs_player_reset_sprint_evaluate(short op, long thread_index, bool initial);
void hs_unit_give_weapon_evaluate(short op, long thread_index, bool initial);
void hs_player_get_local_idx_evaluate(short op, long thread_index, bool initial);
void hs_player_get_local_team_designator_evaluate(short op, long thread_index, bool initial);
void hs_set_player_character_type_evaluate(short op, long thread_index, bool initial);
void hs_set_team_character_type_evaluate(short op, long thread_index, bool initial);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0s_game_globals_player_character_type@@QAE@ABU0@@Z"); no body to assert in
_inline s_game_globals_player_character_type::s_game_globals_player_character_type(s_game_globals_player_character_type const &__that) = default; // 0x106FA980

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Player
			{
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106FABC0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMethods@Player@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");

					methods.AddMethod("player_get_uid", "Gets a player uid from for the given player session index", NetworkSafe, hs_player_get_uid_evaluate, _hs_type_string, { { _hs_type_short, "idx", "The index of a player in the session" } });
					methods.AddMethod("player_get_name", "Gets the player name for the given player session index", NetworkSafe, hs_player_name_evaluate, _hs_type_string, { { _hs_type_short, "idx", "The index of a player in the session" } });
					methods.AddMethod("player_get_by_idx", "Get a player object by their session index", NetworkSafe, hs_player_get_by_idx_evaluate, _hs_type_object, { { _hs_type_short, "idx", "The player session index" } });
					methods.AddMethod("get_player_idx_by_unit", "Get a player idx by their unit object", NetworkSafe, hs_get_player_idx_by_unit_evaluate, _hs_type_short, { { _hs_type_object, "player_object", "The player object" } });
					methods.AddMethod("player_get_idx_by_place", "Get a players session index by a leaderboard place", NetworkSafe, hs_player_get_idx_by_place_evaluate, _hs_type_short, { { _hs_type_short, "place", "The desired place" } });
					methods.AddMethod("give_unit_weapon", "Gives a weapon to a player unit", HostOnly, hs_unit_give_weapon_evaluate, _hs_type_void, { { _hs_type_unit, "unit", "Target unit" }, { _hs_type_any_tag, "primary_weapon", "Primary Weapon" }, { _hs_type_any_tag, "secondary_weapon", "Secondary Weapon" } });
					methods.AddMethod("player_get_local_idx", "Get the Local player session index", NetworkSafe, hs_player_get_local_idx_evaluate, _hs_type_short, {});
					methods.AddMethod("get_local_team_designator", "Get the Local player team designator", NetworkSafe, hs_player_get_local_team_designator_evaluate, _hs_type_short, {});
					methods.AddMethod("player_reset_sprint", "Resets the sprint of the local player. Mainly used to stop sprint bobbing once player_enable_input is set to false", NetworkSafe, hs_player_reset_sprint_evaluate, _hs_type_void, {});
					methods.AddMethod("set_player_character_type", "Forces the character type for the player to respawn as.", HostOnly, hs_set_player_character_type_evaluate, _hs_type_void, { { _hs_type_short, "idx", "The player session index" }, { _hs_type_string_id, "character_type_name", "The name from Player Character Types of the desired character. Use the stringid \"default\" Here to reset" }, { _hs_type_boolean, "force_respawn", "Forcibly respawn the player to use the new character type" } });
					methods.AddMethod("set_team_character_type", "Forces the character type for the team to respawn as.", HostOnly, hs_set_team_character_type_evaluate, _hs_type_void, { { _hs_type_mp_team, "team", "The desired team to change" }, { _hs_type_string_id, "character_type_name", "The name from Player Character Types of the desired character. Use the stringid \"default\" Here to reset" }, { _hs_type_boolean, "force_respawn", "Forcibly respawn the player to use the new character type" } });
				}
			}
		}
	}
}

/* ---------- private code */

void hs_player_get_uid_evaluate(short op, long thread_index, bool initial) // 0x106FBD10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_get_uid_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short idx = args[0].short_value;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session->IsEstablished())
		{
			Blam::Network::PlayerSession &playerSession = session->MembershipInfo.PlayerSessions[idx];
			std::string buff;
			Utils::String::BytesToHexString(&playerSession.Properties.host.player_uid, sizeof(playerSession.Properties.host.player_uid), buff);
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_string(Scripting::HS::HsThreadString(thread_index, buff)));
			return;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_string(""));
	}
}

void hs_player_name_evaluate(short op, long thread_index, bool initial) // 0x106FBF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_name_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short idx = args[0].short_value;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session->IsEstablished())
		{
			Blam::Network::PlayerSession &playerSession = session->MembershipInfo.PlayerSessions[idx];
			std::string name = Utils::String::ThinString(playerSession.Properties.host.player_name);
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_string(Scripting::HS::HsThreadString(thread_index, name)));
			return;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_string(""));
	}
}

void hs_player_get_by_idx_evaluate(short op, long thread_index, bool initial) // 0x106FB730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_get_by_idx_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short session_player_index = args[0].short_value;
		s_player_datum *player = Player::PlayerNetworkUtil::get_player_from_session_index(session_player_index);
		if (player && player->unit_index)
		{
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(player->unit_index));
		}
		else
		{
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(-1));
		}
	}
}

void hs_get_player_idx_by_unit_evaluate(short op, long thread_index, bool initial) // 0x106FB5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_get_player_idx_by_unit_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long unit_object = args[0].long_value;
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_object, 0x2003);
		if (unit)
		{
			s_player_datum *player = player_get(unit->player_index);
			if (player)
			{
				long player_session_index = Player::PlayerNetworkUtil::get_session_player_index_from_player_datum_index(unit->player_index);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(player_session_index));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(-1));
	}
}

void hs_player_get_idx_by_place_evaluate(short op, long thread_index, bool initial) // 0x106FB860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_get_idx_by_place_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short input = args[0].short_value;
		auto result = Player::PlayerPodium::GetPlayerSessionIndexByLeaderboardPlace(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(result));
	}
}

void hs_player_reset_sprint_evaluate(short op, long thread_index, bool initial) // 0x106FC180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_reset_sprint_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long player_index = ((long(__cdecl *)(long))0x589C30)(0);
		if (player_index != -1)
		{
			s_player_datum *player = player_get(player_index);
			if (player)
				player->ticks_sprinting = 0;
		}

		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_unit_give_weapon_evaluate(short op, long thread_index, bool initial) // 0x106FC920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_unit_give_weapon_evaluate@@YAXFJ_N@Z");

	long (*const unit_create_starting_weapon)(long, s_starting_weapon_info *, bool) = reinterpret_cast<long (*)(long, s_starting_weapon_info *, bool)>(0xB3E9F0);
	void (*const unit_delete_all_weapons)(long) = reinterpret_cast<void (*)(long)>(0xB3FAD0);
	bool (*const unit_add_weapon_to_inventory)(long, long, long) = reinterpret_cast<bool (*)(long, long, long)>(0xB393D0);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long player_unit = args[0].long_value;
		long primary_weapon = args[1].long_value;
		long secondary_weapon = args[2].long_value;
		if (((bool(__cdecl *)())0x5319C0)())
		{
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_tag_reference primary = {};
				primary.index = primary_weapon;
				primary.group_tag = 'weap';
				s_tag_reference secondary = {};
				secondary.index = secondary_weapon;
				secondary.group_tag = 'weap';
				if (player_unit != -1)
				{
					s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(player_unit, 0x2003);
					if (unit)
					{
						unit_delete_all_weapons(player_unit);
						if (primary_weapon != -1)
						{
							s_starting_weapon_info weapon_info = {};
							weapon_info.weapon = primary;
							weapon_info.rounds_total = 32;
							weapon_info.rounds_loaded = 32;
							long weapon_index = unit_create_starting_weapon(player_unit, &weapon_info, false);
							if (weapon_index != -1 && !unit_add_weapon_to_inventory(player_unit, weapon_index, 1))
								((void(__cdecl *)(long))0xB2CD10)(weapon_index);
						}
						if (secondary_weapon != -1)
						{
							s_starting_weapon_info weapon_info = {};
							weapon_info.weapon = secondary;
							weapon_info.rounds_total = 32;
							weapon_info.rounds_loaded = 32;
							long weapon_index = unit_create_starting_weapon(player_unit, &weapon_info, false);
							if (weapon_index != -1 && !unit_add_weapon_to_inventory(player_unit, weapon_index, 1))
								((void(__cdecl *)(long))0xB2CD10)(weapon_index);
						}
					}
				}
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_player_get_local_idx_evaluate(short op, long thread_index, bool initial) // 0x106FB940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_get_local_idx_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		c_network_session *session;
		if (network_session_interface_get_squad_session(&session))
		{
			s_player_datum *player = players_get()->try_and_get(((unsigned long(__cdecl *)(long))0x589C30)(0));
			Blam::Network::Session *blam_session = Blam::Network::GetActiveSession();
			if (session && player)
			{
				long peer_player = blam_session->MembershipInfo.GetPeerPlayer(player->machine_index);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(peer_player));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(-1));
	}
}

void hs_player_get_local_team_designator_evaluate(short op, long thread_index, bool initial) // 0x106FBB30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_player_get_local_team_designator_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		c_network_session *session;
		if (network_session_interface_get_squad_session(&session))
		{
			s_player_datum *player = nullptr;
			unsigned long playerIndex = ((unsigned long(__cdecl *)(long))0x589C30)(0);
			if (playerIndex != -1)
			{
				player = players_get()->try_and_get(playerIndex);
				if (player)
				{
					long team = game_engine_get_team_designator(playerIndex);
					if (team != -1)
					{
						((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(team));
						return;
					}
				}
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(-1));
	}
}

void hs_set_player_character_type_evaluate(short op, long thread_index, bool initial) // 0x106FC270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_set_player_character_type_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		if (((bool(__cdecl *)())0x5319C0)())
		{
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				short session_player_index = args[0].short_value;
				long desired_character_type_string_id = args[1].long_value;
				bool force_respawn = args[2].bool_value;
				__int32 character_type_index = -1;
				s_game_globals *game_globals = game_globals_get();
				if (game_globals)
				{
					if (desired_character_type_string_id == 1)
						character_type_index = -1;
					else
					{
						for (long i = 0; i < game_globals->player_character_types.count; i++)
						{
							s_game_globals_player_character_type character = static_cast<s_game_globals_player_character_type const &>(game_globals->player_character_types[i]);
							if (character.name == desired_character_type_string_id)
							{
								character_type_index = i;
								break;
							}
						}
					}
				}
				s_player_datum *player = Player::PlayerNetworkUtil::get_player_from_session_index(session_player_index);
				if (player)
				{
					player->hsc_forced_character_type_index = character_type_index;
					s_object_data *unit = object_try_and_get_and_verify_type(player->unit_index, 0x2003);
					if (unit && force_respawn)
						((void(__cdecl *)(long))0xB2CD10)(player->unit_index);
				}
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_set_team_character_type_evaluate(short op, long thread_index, bool initial) // 0x106FC540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_set_team_character_type_evaluate@@YAXFJ_N@Z");

	long (*const player_get_team_index)(long) = reinterpret_cast<long (*)(long)>(0x591F30);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		if (((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x5565E0)())
		{
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				short mp_team = args[0].short_value;
				long desired_character_type_string_id = args[1].long_value;
				bool force_respawn = args[2].bool_value;
				__int32 character_type_index = -1;
				s_game_globals *game_globals = game_globals_get();
				if (game_globals)
				{
					if (desired_character_type_string_id == 1)
						character_type_index = -1;
					else
					{
						for (__int32 i = 0; i < game_globals->player_character_types.count; i++)
						{
							s_game_globals_player_character_type character = static_cast<s_game_globals_player_character_type const &>(game_globals->player_character_types[i]);
							if (character.name == desired_character_type_string_id)
							{
								character_type_index = i;
								break;
							}
						}
					}
				}
				c_data_array<s_player_datum> *players = players_get();
				for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
				{
					unsigned long player_index = it.current_datum_index;
					s_player_datum *player = player_get(player_index);
					if (player)
					{
						long team = player_get_team_index(player_index);
						if (team == mp_team)
						{
							player->hsc_forced_character_type_index = character_type_index;
							s_object_data *unit = object_try_and_get_and_verify_type(player->unit_index, 0x2003);
							if (unit && force_respawn)
								((void(__cdecl *)(long))0xB2CD10)(player->unit_index);
						}
					}
				}
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_tag_block_index<s_chud_per_character_globals,char>::c_tag_block_index(c_tag_block_index<s_chud_per_character_globals,char> const &);
template c_tag_block_index<s_chud_per_character_globals,char>::c_tag_block_index(char);
template c_tag_block_index<s_game_globals_player_information,char>::c_tag_block_index(c_tag_block_index<s_game_globals_player_information,char> const &);
template c_tag_block_index<s_game_globals_player_information,char>::c_tag_block_index(char);
template c_tag_block_index<s_game_globals_player_representation,char>::c_tag_block_index(c_tag_block_index<s_game_globals_player_representation,char> const &);
template c_tag_block_index<s_game_globals_player_representation,char>::c_tag_block_index(char);
template c_tag_block_index<s_model_customization_selection,char>::c_tag_block_index(c_tag_block_index<s_model_customization_selection,char> const &);
template c_tag_block_index<s_model_customization_selection,char>::c_tag_block_index(char);
template c_tag_block_index<s_weapon_first_person_interface_definition,char>::c_tag_block_index(c_tag_block_index<s_weapon_first_person_interface_definition,char> const &);
template c_tag_block_index<s_weapon_first_person_interface_definition,char>::c_tag_block_index(char);

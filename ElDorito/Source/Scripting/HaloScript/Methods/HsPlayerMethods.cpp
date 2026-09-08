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

_inline s_game_globals_player_character_type::s_game_globals_player_character_type(s_game_globals_player_character_type const &__that) // 0x106FA980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_game_globals_player_character_type@@QAE@ABU0@@Z");
	// s_game_globals_player_character_type const &__that;

	compiler_generated();
}

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Player
			{
				_extern void _sub_106FABC0(Scripting::HS::ScriptMethodMap &);
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106FABC0
				{
					mangled_x86(MANGLED_TODO, "?RegisterMethods@Player@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;
					todo("implement");
					_sub_106FABC0(methods);
				}
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_106FBD10(short, long, bool);
void hs_player_get_uid_evaluate(short op, long thread_index, bool initial) // 0x106FBD10
{
	// `anonymous-namespace'::hs_player_get_uid_evaluate
	// static ...; // 0x106FBEB4
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// short idx;
			{
				// Blam::Network::Session *session;
				{
					// Blam::Network::PlayerSession &playerSession;
					// std::string buff;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FBD10(op, thread_index, initial);
}

_extern void _sub_106FBF40(short, long, bool);
void hs_player_name_evaluate(short op, long thread_index, bool initial) // 0x106FBF40
{
	// `anonymous-namespace'::hs_player_name_evaluate
	// static ...; // 0x106FC0E8
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// short idx;
			{
				// Blam::Network::Session *session;
				{
					// Blam::Network::PlayerSession &playerSession;
					// std::string name;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FBF40(op, thread_index, initial);
}

_extern void _sub_106FB730(short, long, bool);
void hs_player_get_by_idx_evaluate(short op, long thread_index, bool initial) // 0x106FB730
{
	// `anonymous-namespace'::hs_player_get_by_idx_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// s_player_datum *player;
			// short session_player_index;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FB730(op, thread_index, initial);
}

_extern void _sub_106FB5A0(short, long, bool);
void hs_get_player_idx_by_unit_evaluate(short op, long thread_index, bool initial) // 0x106FB5A0
{
	// `anonymous-namespace'::hs_get_player_idx_by_unit_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// s_unit_data *unit;
			// long unit_object;
			{
				// s_player_datum *player;
				{
					// long player_session_index;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FB5A0(op, thread_index, initial);
}

_extern void _sub_106FB860(short, long, bool);
void hs_player_get_idx_by_place_evaluate(short op, long thread_index, bool initial) // 0x106FB860
{
	// `anonymous-namespace'::hs_player_get_idx_by_place_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short place;
			// short player_session_index;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FB860(op, thread_index, initial);
}

_extern void _sub_106FC180(short, long, bool);
void hs_player_reset_sprint_evaluate(short op, long thread_index, bool initial) // 0x106FC180
{
	// `anonymous-namespace'::hs_player_reset_sprint_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// unsigned long player_datum_index;
			{
				// s_player_datum *player;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FC180(op, thread_index, initial);
}

_extern void _sub_106FC920(short, long, bool);
void hs_unit_give_weapon_evaluate(short op, long thread_index, bool initial) // 0x106FC920
{
	// `anonymous-namespace'::hs_unit_give_weapon_evaluate
	// static ...; // 0x106FCCE0
	// static ...; // 0x106FCCD4
	// static ...; // 0x106FCCA4
	// static ...; // 0x106FCC9C
	// short op;
	// long thread_index;
	// bool initial;
	// bool (*const unit_add_weapon_to_inventory)(long, long, long);
	// long (*const unit_create_starting_weapon)(long, s_starting_weapon_info *, bool);
	// void (*const unit_delete_all_weapons)(long);
	{
		// hs_value *args;
		{
			// long player_unit;
			// long secondary_weapon;
			// long primary_weapon;
			{
				// Blam::Network::Session *session;
				{
					// s_tag_reference primary;
					// s_tag_reference secondary;
					{
						// s_unit_data *unit;
						{
							// long weapon_index;
							// s_starting_weapon_info weapon_info;
						}
						{
						}
					}
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : long (*const)(long, s_starting_weapon_info *, bool)
	// function call : bool (*const)(long, long, long)
	// function call : void (*const)(long)
	// function call : long (*const)(long, s_starting_weapon_info *, bool)
	// function call : bool (*const)(long, long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FC920(op, thread_index, initial);
}

_extern void _sub_106FB940(short, long, bool);
void hs_player_get_local_idx_evaluate(short op, long thread_index, bool initial) // 0x106FB940
{
	// `anonymous-namespace'::hs_player_get_local_idx_evaluate
	// static ...; // 0x106FBAAC
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// c_network_session *session;
			{
				// s_player_datum *player;
				// Blam::Network::Session *blam_session;
				{
					// __int32 player_session_index;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)(c_network_session **)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FB940(op, thread_index, initial);
}

_extern void _sub_106FBB30(short, long, bool);
void hs_player_get_local_team_designator_evaluate(short op, long thread_index, bool initial) // 0x106FBB30
{
	// `anonymous-namespace'::hs_player_get_local_team_designator_evaluate
	// static ...; // 0x106FBC88
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// c_network_session *session;
			{
				// s_player_datum *player;
				// unsigned long playerIndex;
				{
					// long team_designator;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)(c_network_session **)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FBB30(op, thread_index, initial);
}

_extern void _sub_106FC270(short, long, bool);
void hs_set_player_character_type_evaluate(short op, long thread_index, bool initial) // 0x106FC270
{
	// `anonymous-namespace'::hs_set_player_character_type_evaluate
	// static ...; // 0x106FC48C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// s_player_datum *player;
				// long desired_character_type_string_id;
				// s_game_globals *game_globals;
				// bool force_respawn;
				// short session_player_index;
				// __int32 character_type_index;
				{
					// __int32 i;
					{
						// s_game_globals_player_character_type character;
					}
				}
				{
					// s_unit_data *player_unit;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FC270(op, thread_index, initial);
}

_extern void _sub_106FC540(short, long, bool);
void hs_set_team_character_type_evaluate(short op, long thread_index, bool initial) // 0x106FC540
{
	// `anonymous-namespace'::hs_set_team_character_type_evaluate
	// static ...; // 0x106FC82C
	// static ...; // 0x106FC824
	// short op;
	// long thread_index;
	// bool initial;
	// long (*const player_get_team_index)(long);
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// long desired_character_type_string_id;
				// s_game_globals *game_globals;
				// bool force_respawn;
				// c_data_array<s_player_datum> *players;
				// short mp_team;
				// __int32 character_type_index;
				{
					// __int32 i;
					{
						// s_game_globals_player_character_type character;
					}
				}
				{
					// c_data_iterator<s_player_datum> it;
					{
						// s_player_datum *player;
						// unsigned long player_index;
						{
							// long player_team;
							{
								// s_unit_data *player_unit;
							}
						}
					}
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FC540(op, thread_index, initial);
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

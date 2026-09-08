/* ---------- headers */

#include "Player/PlayerCharacterSystem.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/main_render.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/networking/logic/network_life_cycle.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Network.hpp"
#include "Player/PlayerCustomizationBuilder.hpp"
#include "Player/PlayerCustomizationDB.hpp"
#include "Pointer.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class IMod;
class IModListener;
class c_cache_file_tag_cache;
class c_mod_package_manager;
class c_network_session;
class c_wait_for_render_thread;
struct c_game_engine;
struct lambda_1;
struct s_game_globals;
struct s_mod_globals_definition;
struct s_mod_globals_player_character;
struct s_mod_globals_player_character_set;
struct s_multiplayer_globals_definition;
struct s_object_data;
struct s_player_appearance;
struct s_player_character_customiztion;
struct s_player_datum;
struct s_player_model_customization;
struct s_unit_data;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}
namespace Player
{
	class CPlayerCharacterCustomizationBuilder;
	class CPlayerCustomizationDB;
	struct CPlayerCharacterSystem;
}
namespace Server
{
	namespace Voting
	{
		struct HaloType;
		struct MapAndType;
	}
}
namespace hades_file_local
{
	class ModListener;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Mods {}
using namespace ::Mods;
namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class game_engine_get_random_global_player_character_type_index::__l2::<lambda_1>
//{
//public:
//	float operator()(s_mod_globals_player_character const &) const;
//};
//static_assert(sizeof(game_engine_get_random_global_player_character_type_index::__l2::<lambda_1>) == 1, "Invalid game_engine_get_random_global_player_character_type_index::__l2::<lambda_1> size");

//class game_engine_get_random_global_player_character_set_index::__l2::<lambda_1>
//{
//public:
//	float operator()(s_mod_globals_player_character_set const &) const;
//};
//static_assert(sizeof(game_engine_get_random_global_player_character_set_index::__l2::<lambda_1>) == 1, "Invalid game_engine_get_random_global_player_character_set_index::__l2::<lambda_1> size");

namespace hades_file_local
{
	class ModListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener(); /* compiler_generated() */
		virtual ~ModListener(); /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

long game_engine_get_random_global_player_character_type_index(long character_set_index);
long game_engine_get_random_global_player_character_set_index();
long game_engine_get_player_character_type_index(long character_set_index, long index);
std::string const GetPlayerTeamDesginatorName(__int32 playerIndex);
long game_engine_get_player_character_type_index(long player_index);
void *GetCharacterChudGlobals(__int32 characterTypeIndex);
__int32 GetPreferredCharacterType(__int32 playerIndex);
std::string GetPreferredCharacterName();
__int32 OverridePlayerCharacter(__int32 playerIndex);
void OnLifeCycleChanged(Blam::Network::LifeCycleState newState);
void OnServerVotePassed(Server::Voting::MapAndType const &winner);
bool RequestPlayerPropertiesUpdate(__int32 userIndex);
void MaybeUpdatePeerProperties();

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x12408FF8
			extern std::string const DefaultTypeNames[8]; // 0x124090D8
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace hades_file_local
{
	extern std::map<std::string,Server::Voting::HaloType::CharacterOverride> votingCharacterOverrides; // 0x124091B8
	extern __int32 prevUpdateNumber; // 0x124091C4
	extern __int32 currentUpdateNumber; // 0x124091C8
	extern std::shared_ptr<c_cache_file_tag_cache> globalBaseTagCache; // 0x124091CC
	extern std::shared_ptr<Blam::Cache::StringIDCache> globalBaseStringCache; // 0x124091D4
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	// mangled_x86(MANGLED_DEFAULT, "??0CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::CPlayerCharacterCustomizationBuilder() = default; // 0x10900CB0

	// mangled_x86(MANGLED_DEFAULT, "??0SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::SBaseCacheReference::SBaseCacheReference() = default; // 0x10900DC0

	// mangled_x86(MANGLED_DEFAULT, "??1CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::~CPlayerCharacterCustomizationBuilder() = default; // 0x10900F80

	// mangled_x86(MANGLED_DEFAULT, "??1SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::SBaseCacheReference::~SBaseCacheReference() = default; // 0x10901050

	_extern void _sub_109023F0();
	void CPlayerCharacterSystem::Init() // 0x109023F0
	{
		mangled_x86(MANGLED_TODO, "?Init@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x10902767
		// static ...; // 0x10902764
		// static ...; // 0x1090274C
		// static ...; // 0x10902744
		{
			// std::string prefsName;
			{
				// std::stringstream ss;
			}
		}
		// function call : void (IModListener *)
		todo("implement");
		_sub_109023F0();
	}

	_extern void _sub_109032C0();
	void CPlayerCharacterSystem::Tick() // 0x109032C0
	{
		mangled_x86(MANGLED_TODO, "?Tick@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// function call : bool (*const)()
		todo("implement");
		_sub_109032C0();
	}

	_extern void _sub_10902990(bool, std::shared_ptr<c_cache_file_tag_cache>, std::shared_ptr<Blam::Cache::StringIDCache>);
	void CPlayerCharacterSystem::NotifyTagsLoaded(bool isMainMenuMod, std::shared_ptr<c_cache_file_tag_cache> baseCache, std::shared_ptr<Blam::Cache::StringIDCache> baseStringCache) // 0x10902990
	{
		mangled_x86(MANGLED_TODO, "?NotifyTagsLoaded@CPlayerCharacterSystem@Player@@SAX_NV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@V?$shared_ptr@UStringIDCache@Cache@Blam@@@4@@Z");
		// std::shared_ptr<Blam::Cache::StringIDCache> baseStringCache;
		todo("implement");
		_sub_10902990(isMainMenuMod, baseCache, baseStringCache);
	}

	_extern void _sub_10903320();
	void CPlayerCharacterSystem::UpdateLocalPlayerHudGlobals() // 0x10903320
	{
		mangled_x86(MANGLED_TODO, "?UpdateLocalPlayerHudGlobals@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x109033F0
		// static ...; // 0x109033E4
		// static ...; // 0x109033DC
		// s_player_datum *player;
		// __int32 playerIndex;
		// void **hudGlobalsPointer;
		// void *hudGlobals;
		{
			// c_wait_for_render_thread renderThreadLock;
		}
		// function call : unsigned long (*const)(long)
		todo("implement");
		_sub_10903320();
	}

	_extern void _sub_10901700(__int32);
	void CPlayerCharacterSystem::AssignPlayerCharacter(__int32 playerIndex) // 0x10901700
	{
		mangled_x86(MANGLED_TODO, "?AssignPlayerCharacter@CPlayerCharacterSystem@Player@@SAXH@Z");
		// static ...; // 0x10901840
		// static ...; // 0x10901834
		// static ...; // 0x1090182C
		// __int32 playerIndex;
		// __int32 characterTypeIndex;
		{
			// s_player_datum *player;
			// unsigned long long componentMask;
		}
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : void (*const)(short, unsigned long long const *)
		todo("implement");
		_sub_10901700(playerIndex);
	}

	_extern void _sub_10902F20(__int32);
	void CPlayerCharacterSystem::PlayerCharacterEditor(__int32 playerIndex) // 0x10902F20
	{
		mangled_x86(MANGLED_TODO, "?PlayerCharacterEditor@CPlayerCharacterSystem@Player@@SAXH@Z");
		// static ...; // 0x109030C8
		// static ...; // 0x109030BC
		// static ...; // 0x109030B4
		// __int32 playerIndex;
		{
			// s_player_datum *player;
			// unsigned long long componentMask;
			{
				// s_unit_data *unit;
				// s_multiplayer_globals_definition *mulg;
				// s_game_globals *globals;
			}
		}
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : void *(*const)(unsigned long, long)
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : void (*const)(short, unsigned long long const *)
		todo("implement");
		_sub_10902F20(playerIndex);
	}

	_extern bool _sub_109018B0(std::string const &, s_player_model_customization &);
	bool CPlayerCharacterSystem::BuildCharacterCustomization(std::string const &characterName, s_player_model_customization &customization) // 0x109018B0
	{
		mangled_x86(MANGLED_TODO, "?BuildCharacterCustomization@CPlayerCharacterSystem@Player@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_model_customization@@@Z");
		// static ...; // 0x109019C4
		// static ...; // 0x109019AC
		// static ...; // 0x109019A4
		// std::string const &characterName;
		// s_player_model_customization &customization;
		// Player::CPlayerCharacterCustomizationBuilder builder;
		// s_player_character_customiztion tmp;
		todo("implement");
		bool __result = _sub_109018B0(characterName, customization);
		return __result;
	}

	_extern bool _sub_10901A20(s_player_appearance &);
	bool CPlayerCharacterSystem::BuildCustomizations(s_player_appearance &appearance) // 0x10901A20
	{
		mangled_x86(MANGLED_TODO, "?BuildCustomizations@CPlayerCharacterSystem@Player@@SA_NAAUs_player_appearance@@@Z");
		// static ...; // 0x10901B20
		// static ...; // 0x10901B14
		// static ...; // 0x10901B0C
		// s_player_appearance &appearance;
		// Player::CPlayerCharacterCustomizationBuilder builder;
		todo("implement");
		bool __result = _sub_10901A20(appearance);
		return __result;
	}

	_extern void _sub_10903150();
	void CPlayerCharacterSystem::ReloadCustomizations() // 0x10903150
	{
		mangled_x86(MANGLED_TODO, "?ReloadCustomizations@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10903150();
	}
}

/* ---------- private code */

_extern long _sub_10903BD0(long);
long game_engine_get_random_global_player_character_type_index(long character_set_index) // 0x10903BD0
{
	// `anonymous-namespace'::game_engine_get_random_global_player_character_type_index
	// static ...; // 0x10903D00
	// static ...; // 0x10903CF4
	// static ...; // 0x10903CEC
	// long character_set_index;
	// s_mod_globals_definition *mod_globals;
	// long index;
	// s_mod_globals_player_character_set *character_set;
	todo("implement");
	long __result = _sub_10903BD0(character_set_index);
	return __result;
}

_extern long _sub_10903B00();
long game_engine_get_random_global_player_character_set_index() // 0x10903B00
{
	// `anonymous-namespace'::game_engine_get_random_global_player_character_set_index
	// procedure flags: nofpo
	// s_mod_globals_definition *mod_globals;
	todo("implement");
	long __result = _sub_10903B00();
	return __result;
}

_extern long _sub_109039D0(long, long);
long game_engine_get_player_character_type_index(long character_set_index, long index) // 0x109039D0
{
	// `anonymous-namespace'::game_engine_get_player_character_type_index
	// static ...; // 0x10903AA4
	// static ...; // 0x10903A8C
	// static ...; // 0x10903A84
	// long character_set_index;
	// long index;
	// s_mod_globals_definition *mod_globals;
	// s_mod_globals_player_character_set *character_set;
	// s_mod_globals_player_character *character;
	todo("implement");
	long __result = _sub_109039D0(character_set_index, index);
	return __result;
}

extern std::string const _sub_10901C20(__int32);
std::string const GetPlayerTeamDesginatorName(__int32 playerIndex) // 0x10901C20
{
	// `anonymous-namespace'::GetPlayerTeamDesginatorName
	// __int32 playerIndex;
	// long (*get_player_team_desginator)(c_game_engine *, __int32);
	// c_game_engine *gameEngine;
	// long teamDesignator;
	// function call : c_game_engine *(*const)()
	// function call : long (*)(c_game_engine *, __int32)
	todo("implement");
	std::string const __result = _sub_10901C20(playerIndex);
	return __result;
}

_extern long _sub_10903890(long);
long game_engine_get_player_character_type_index(long player_index) // 0x10903890
{
	// `anonymous-namespace'::game_engine_get_player_character_type_index
	// long player_index;
	// s_player_datum *player;
	// long player_character_set_index;
	{
		// long random_character_set_index;
	}
	todo("implement");
	long __result = _sub_10903890(player_index);
	return __result;
}

_extern void *_sub_10901B70(__int32);
void *GetCharacterChudGlobals(__int32 characterTypeIndex) // 0x10901B70
{
	// `anonymous-namespace'::GetCharacterChudGlobals
	// __int32 characterTypeIndex;
	// __int32 hudGlobalsIndex;
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	void * __result = _sub_10901B70(characterTypeIndex);
	return __result;
}

_extern __int32 _sub_109022A0(__int32);
__int32 GetPreferredCharacterType(__int32 playerIndex) // 0x109022A0
{
	// `anonymous-namespace'::GetPreferredCharacterType
	// __int32 playerIndex;
	// s_player_datum *player;
	// s_game_globals const *matg;
	// s_mod_globals_definition *mod_globals;
	// long desiredIndex;
	{
		// __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_109022A0(playerIndex);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in
_inline ModListener::ModListener() = default; // 0x10900D60

_inline ModListener::~ModListener() // 0x10901000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ModListener@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::ModListener::~ModListener
	// ModListener *const this;

	compiler_generated();
}

extern std::string _sub_10901DF0();
std::string GetPreferredCharacterName() // 0x10901DF0
{
	// `anonymous-namespace'::GetPreferredCharacterName
	// procedure flags: nofpo
	// static ...; // 0x10902194
	// static ...; // 0x1090218C
	// static ...; // 0x10902187
	// static ...; // 0x10902181
	// static ...; // 0x10902178
	// static ...; // 0x1090213C
	// static ...; // 0x10902134
	// std::string modHash;
	// Player::CPlayerCustomizationDB &customizationDB;
	// std::string preferredCharacter;
	{
		// c_mod_package_manager::s_entry entry;
		// unsigned char hash[20];
		{
			// std::string filename;
		}
	}
	todo("implement");
	std::string __result = _sub_10901DF0();
	return __result;
}

_extern __int32 _sub_10902BE0(__int32);
__int32 OverridePlayerCharacter(__int32 playerIndex) // 0x10902BE0
{
	// `anonymous-namespace'::OverridePlayerCharacter
	// static ...; // 0x10902E63
	// static ...; // 0x10902E60
	// static ...; // 0x10902E48
	// static ...; // 0x10902E40
	// __int32 playerIndex;
	// std::string teamDesignator;
	{
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,Server::Voting::HaloType::CharacterOverride> > > > it;
		{
			// __int32 characterSetIndex;
			{
				// long characterSetIndex;
			}
			{
				// __int32 characterIndex;
			}
		}
	}
	todo("implement");
	__int32 __result = _sub_10902BE0(playerIndex);
	return __result;
}

_extern void _sub_10902AE0(Blam::Network::LifeCycleState);
void OnLifeCycleChanged(Blam::Network::LifeCycleState newState) // 0x10902AE0
{
	// `anonymous-namespace'::OnLifeCycleChanged
	// Blam::Network::LifeCycleState newState;
	todo("implement");
	_sub_10902AE0(newState);
}

_extern void _sub_10902B90(Server::Voting::MapAndType const &);
void OnServerVotePassed(Server::Voting::MapAndType const &winner) // 0x10902B90
{
	// `anonymous-namespace'::OnServerVotePassed
	// Server::Voting::MapAndType const &winner;
	todo("implement");
	_sub_10902B90(winner);
}

_extern bool _sub_109031B0(__int32);
bool RequestPlayerPropertiesUpdate(__int32 userIndex) // 0x109031B0
{
	// `anonymous-namespace'::RequestPlayerPropertiesUpdate
	// static ...; // 0x10903280
	// static ...; // 0x10903274
	// static ...; // 0x1090326C
	// __int32 userIndex;
	// char *user;
	// void (*const user_interface_controller_update_network_properties)(__int32);
	// c_network_session *session;
	// function call : void (*const)(__int32)
	todo("implement");
	bool __result = _sub_109031B0(userIndex);
	return __result;
}

_extern void _sub_10902860();
void MaybeUpdatePeerProperties() // 0x10902860
{
	// `anonymous-namespace'::MaybeUpdatePeerProperties
	// procedure flags: nofpo
	{
		// IMod *mod;
	}
	// function call : bool (*const)()
	// function call : IMod *(EModIndex) const
	// function call : bool () const
	// function call : bool () const
	todo("implement");
	_sub_10902860();
}

_extern void _sub_10902B60(ModListener *const, EModIndex, IMod *);
_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10902B60
{
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;
	todo("implement");
	_sub_10902B60(this, index, mod);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_game_globals_interface_tag_references>::try_get_element(__int32, s_game_globals_interface_tag_references **) const;
template c_tag_block_index<s_model_customization_selection,char>::operator char() const;
template s_game_globals_interface_tag_references * c_tag_block<s_game_globals_interface_tag_references>::get_element(__int32) const;
template s_game_globals_interface_tag_references * c_tag_block<s_game_globals_interface_tag_references>::operator->();

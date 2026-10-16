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

#include "mods/mod_system.hpp"  // hades: added for 0x10902860

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
	namespace hades_file_local_PlayerCharacterSystem { class ModListener; } using namespace hades_file_local_PlayerCharacterSystem;
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
	namespace hades_file_local_PlayerCharacterSystem { class ModListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener() = default; /* compiler_generated() */
		virtual ~ModListener() = default; /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	}; }  // hades_file_local_PlayerCharacterSystem: ModListener is a different class in each translation unit
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_is_authoritative = reinterpret_cast<bool (*)()>(0x5319C0);
	static auto const simulation_action_game_engine_player_update = reinterpret_cast<void (*)(short, unsigned long long const *)>(0x4B26B0);
}

namespace Server { namespace Voting { extern void OnVotePassed(std::function<void __cdecl(Server::Voting::MapAndType)> &&callback); } }  // hades: added for 0x109023F0

float real_random_range(float min, float max); template<typename t_entry, typename t_weight_function> long compute_weighted_random_index(t_entry entries, long count, t_weight_function get_weight) { if (!count) return -1; float total_weight = 0.0f; for (long i = 0; i < count; i++) total_weight += get_weight(entries[i]); float random = real_random_range(0.0f, total_weight); for (long i = 0; i < count; i++) { float weight = get_weight(entries[i]); if (weight != 0.0f && weight > random) return i; random -= weight; } return -1; }  // hades: added for 0x10903B00

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

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10901700
extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x10902F20
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10902F20
extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0X10901B70
extern long player_find_character_type_by_name(unsigned long name);

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x12408FF8  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x124090D8  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace hades_file_local
{
	std::map<std::string,Server::Voting::HaloType::CharacterOverride> votingCharacterOverrides; // 0x124091B8
	extern __int32 prevUpdateNumber; // 0x124091C4
	extern __int32 currentUpdateNumber; // 0x124091C8
	std::shared_ptr<c_cache_file_tag_cache> globalBaseTagCache; // 0x124091CC
	std::shared_ptr<Blam::Cache::StringIDCache> globalBaseStringCache; // 0x124091D4
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	// mangled_x86(MANGLED_DEFAULT, "??0CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??1CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::~CPlayerCharacterCustomizationBuilder() = default; // 0x10900F80

	// mangled_x86(MANGLED_DEFAULT, "??1SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ"); no body to assert in
	_inline CPlayerCharacterCustomizationBuilder::SBaseCacheReference::~SBaseCacheReference() = default; // 0x10901050

	void CPlayerCharacterSystem::Init() // 0x109023F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x10902767
		// static ...; // 0x10902764
		// static ...; // 0x1090274C
		// static ...; // 0x10902744
			// std::string prefsName;
				// std::stringstream ss;
		// function call : void (IModListener *)

		if (!Utils::Singleton<ElDorito>::Instance().IsDedicated())
		{
			std::string prefsName = "player_customization.json";
			if (!(Utils::Singleton<ElDorito>::Instance().GetInstanceName() == ""))
			{
				std::stringstream ss;
				ss << "player_customization_" << Utils::Singleton<ElDorito>::Instance().GetInstanceName() << ".json";
				prefsName = ss.str();
			}
			Utils::Singleton<Player::CPlayerCustomizationDB>::Instance().Load("data\\" + prefsName);
		}
		Server::Voting::OnVotePassed(OnServerVotePassed);
		Patches::Network::OnLifeCycleStateChanged(OnLifeCycleChanged);
		c_mod_system::GetModManager().AddListener(new ModListener());
	}

	void CPlayerCharacterSystem::Tick() // 0x109032C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// function call : bool (*const)()

		MaybeUpdatePeerProperties();
		if (((bool(__cdecl *)())0x5314B0)())
			Player::CPlayerCharacterSystem::UpdateLocalPlayerHudGlobals();
	}

	void CPlayerCharacterSystem::NotifyTagsLoaded(bool isMainMenuMod, std::shared_ptr<c_cache_file_tag_cache> baseCache, std::shared_ptr<Blam::Cache::StringIDCache> baseStringCache) // 0x10902990
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyTagsLoaded@CPlayerCharacterSystem@Player@@SAX_NV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@V?$shared_ptr@UStringIDCache@Cache@Blam@@@4@@Z");
		// std::shared_ptr<Blam::Cache::StringIDCache> baseStringCache;

		if (isMainMenuMod)
		{
			globalBaseTagCache = baseCache;
			globalBaseStringCache = baseStringCache;
		}
		else
		{
			globalBaseTagCache = nullptr;
			globalBaseStringCache = nullptr;
		}
		currentUpdateNumber++;
		MaybeUpdatePeerProperties();
	}

	void CPlayerCharacterSystem::UpdateLocalPlayerHudGlobals() // 0x10903320
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateLocalPlayerHudGlobals@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x109033F0
		// static ...; // 0x109033E4
		// static ...; // 0x109033DC
		// s_player_datum *player;
		// __int32 playerIndex;
		// void **hudGlobalsPointer;
		// void *hudGlobals;
			// c_wait_for_render_thread renderThreadLock;
		// function call : unsigned long (*const)(long)

		__int32 playerIndex = ((unsigned long(*)(long))0x589C30)(0);
		if (playerIndex == -1)
			return;
		s_player_datum *player = player_get(playerIndex);
		if (!player)
			return;
		void **hudGlobalsPointer = (void **)0x5257C40;
		void *hudGlobals = GetCharacterChudGlobals(player->character_type_index);
		if (hudGlobals != *hudGlobalsPointer)
		{
			c_wait_for_render_thread renderThreadLock;
			InterlockedExchangePointer(hudGlobalsPointer, hudGlobals);
		}
	}

	void CPlayerCharacterSystem::AssignPlayerCharacter(__int32 playerIndex) // 0x10901700
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AssignPlayerCharacter@CPlayerCharacterSystem@Player@@SAXH@Z");
		// static ...; // 0x10901840
		// static ...; // 0x10901834
		// static ...; // 0x1090182C
		// __int32 playerIndex;
		// __int32 characterTypeIndex;
			// s_player_datum *player;
			// unsigned long long componentMask;
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : void (*const)(short, unsigned long long const *)

		if (!game_is_multiplayer())
			return;
		__int32 characterTypeIndex = -1;
		if (eldorado::game_is_authoritative())
		{
			s_player_datum *player = player_get(playerIndex);
			if (characterTypeIndex == -1)
				characterTypeIndex = player->hsc_forced_character_type_index;
			if (characterTypeIndex == -1)
				characterTypeIndex = OverridePlayerCharacter(playerIndex);
			if (characterTypeIndex == -1)
				characterTypeIndex = game_engine_get_player_character_type_index(playerIndex);
			if (characterTypeIndex == -1)
				characterTypeIndex = GetPreferredCharacterType(playerIndex);
			if (characterTypeIndex == -1)
				characterTypeIndex = 0;
			player->character_type_index = characterTypeIndex;
			player->previous_character_type_index = characterTypeIndex;
			unsigned long long componentMask = 0x20000;
			eldorado::simulation_action_game_engine_player_update(playerIndex, &componentMask);
		}
		UpdateLocalPlayerHudGlobals();
	}

	void CPlayerCharacterSystem::PlayerCharacterEditor(__int32 playerIndex) // 0x10902F20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerCharacterEditor@CPlayerCharacterSystem@Player@@SAXH@Z");
		// static ...; // 0x109030C8
		// static ...; // 0x109030BC
		// static ...; // 0x109030B4
		// __int32 playerIndex;
			// s_player_datum *player;
			// unsigned long long componentMask;
				// s_unit_data *unit;
				// s_multiplayer_globals_definition *mulg;
				// s_game_globals *globals;
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : void *(*const)(unsigned long, long)
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : void (*const)(short, unsigned long long const *)

		if (!game_is_multiplayer())
			return;
		if (eldorado::game_is_authoritative() && game_engine_is_sandbox())
		{
			s_player_datum *player = player_get(playerIndex);
			if (player->unit_index != -1)
			{
				s_game_globals *globals = game_globals_get();
				s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', globals->MultiplayerGlobals.index);
				s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(player->unit_index, 0x2003);
				if (unit && unit->definition_index == mulg->runtime->sandbox_editor_unit.index)
					player->character_type_index = player_find_character_type_by_name(0x111B);
				else
					player->character_type_index = player->previous_character_type_index;
			}
			unsigned long long componentMask = 0x20000;
			eldorado::simulation_action_game_engine_player_update(playerIndex, &componentMask);
		}
		UpdateLocalPlayerHudGlobals();
	}

	bool CPlayerCharacterSystem::BuildCharacterCustomization(std::string const &characterName, s_player_model_customization &customization) // 0x109018B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildCharacterCustomization@CPlayerCharacterSystem@Player@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_model_customization@@@Z");
		// static ...; // 0x109019C4
		// static ...; // 0x109019AC
		// static ...; // 0x109019A4
		// std::string const &characterName;
		// s_player_model_customization &customization;
		// Player::CPlayerCharacterCustomizationBuilder builder;
		// s_player_character_customiztion tmp;

		Player::CPlayerCharacterCustomizationBuilder builder;
		s_player_character_customiztion tmp;
		if (!builder.BuildSingleCharacterCustomization(characterName, &tmp))
			return false;
		memcpy(&customization, tmp.customization, sizeof(tmp.customization));
		return true;
	}

	bool CPlayerCharacterSystem::BuildCustomizations(s_player_appearance &appearance) // 0x10901A20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildCustomizations@CPlayerCharacterSystem@Player@@SA_NAAUs_player_appearance@@@Z");
		// static ...; // 0x10901B20
		// static ...; // 0x10901B14
		// static ...; // 0x10901B0C
		// s_player_appearance &appearance;
		// Player::CPlayerCharacterCustomizationBuilder builder;


		CPlayerCharacterCustomizationBuilder builder;

		return builder.BuildCharacterCustomizations(GetPreferredCharacterName(), &appearance);
	}

	void CPlayerCharacterSystem::ReloadCustomizations() // 0x10903150
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReloadCustomizations@CPlayerCharacterSystem@Player@@SAXXZ");
		// procedure flags: nofpo

		Player::CPlayerCustomizationDB::Instance().Reload();
		currentUpdateNumber++;
	}
}

/* ---------- private code */

long game_engine_get_random_global_player_character_type_index(long character_set_index) // 0x10903BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_random_global_player_character_type_index@@YAJJ@Z");
	// `anonymous-namespace'::game_engine_get_random_global_player_character_type_index
	// static ...; // 0x10903D00
	// static ...; // 0x10903CF4
	// static ...; // 0x10903CEC
	// long character_set_index;
	// s_mod_globals_definition *mod_globals;
	// long index;
	// s_mod_globals_player_character_set *character_set;

	s_mod_globals_definition *mod_globals = mod_globals_get_definition();
	if (!mod_globals)
		return -1;
	s_mod_globals_player_character_set *character_set;
	if (!mod_globals->player_character_sets.try_get_element(character_set_index, &character_set))
		return -1;
	long index = compute_weighted_random_index(&character_set->characters[0], character_set->characters.count, [](s_mod_globals_player_character const &character) { return character.random_chance; });
	if (index != -1)
		index = player_find_character_type_by_name(character_set->characters[index].name);
	return index;
}

long game_engine_get_random_global_player_character_set_index() // 0x10903B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_random_global_player_character_set_index@@YAJXZ");
	// `anonymous-namespace'::game_engine_get_random_global_player_character_set_index
	// procedure flags: nofpo
	// s_mod_globals_definition *mod_globals;

	s_mod_globals_definition *mod_globals = mod_globals_get_definition();
	if (!mod_globals)
		return -1;
	return compute_weighted_random_index(&mod_globals->player_character_sets[0], mod_globals->player_character_sets.count, [](s_mod_globals_player_character_set const &character_set) { return character_set.random_chance; });
}

long game_engine_get_player_character_type_index(long character_set_index, long index) // 0x109039D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_character_type_index@@YAJJJ@Z");
	// `anonymous-namespace'::game_engine_get_player_character_type_index
	// static ...; // 0x10903AA4
	// static ...; // 0x10903A8C
	// static ...; // 0x10903A84
	// long character_set_index;
	// long index;
	// s_mod_globals_definition *mod_globals;
	// s_mod_globals_player_character_set *character_set;
	// s_mod_globals_player_character *character;


	s_mod_globals_definition *mod_globals = mod_globals_get_definition();
	if (!mod_globals)
	{
		return -1;
	}

	s_mod_globals_player_character_set *character_set;
	s_mod_globals_player_character *character;
	if (mod_globals->player_character_sets.try_get_element(character_set_index, &character_set) && character_set->characters.try_get_element(index, &character))
	{
		return player_find_character_type_by_name(character->name);
	}

	return -1;
}

std::string const GetPlayerTeamDesginatorName(__int32 playerIndex) // 0x10901C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerTeamDesginatorName@@YA?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
	// `anonymous-namespace'::GetPlayerTeamDesginatorName
	// __int32 playerIndex;
	// long (*get_player_team_desginator)(c_game_engine *, __int32);
	// c_game_engine *gameEngine;
	// long teamDesignator;
	// function call : c_game_engine *(*const)()
	// function call : long (*)(c_game_engine *, __int32)

	c_game_engine *gameEngine = ((c_game_engine *(__cdecl *)())0x5CE150)();
	if (!gameEngine)
		return "";

	long (__thiscall *get_player_team_desginator)(c_game_engine *, __int32) = *(long (__thiscall **)(c_game_engine *, __int32))(*(char **)gameEngine + 0xB4);
	long teamDesignator = get_player_team_desginator(gameEngine, playerIndex);
	if (teamDesignator < 0 || teamDesignator > 8)
		return {};

	return "team" + std::to_string(teamDesignator);
}

long game_engine_get_player_character_type_index(long player_index) // 0x10903890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_character_type_index@@YAJJ@Z");
	// `anonymous-namespace'::game_engine_get_player_character_type_index
	// long player_index;
	// s_player_datum *player;
	// long player_character_set_index;
		// long random_character_set_index;

	s_player_datum *player = player_get(player_index);
	if (player->traits.extended.player_model_set < 2 || player->traits.extended.player_model_set >= 8)
		return -1;

	if (player->traits.extended.player_model_set == 2)
	{
		long random_character_set_index = game_engine_get_random_global_player_character_set_index();
		return game_engine_get_random_global_player_character_type_index(random_character_set_index);
	}

	long player_character_set_index = player->traits.extended.player_model_set - 3;
	if (player->traits.extended.player_model == 2)
	{
		return game_engine_get_random_global_player_character_type_index(player_character_set_index);
	}
	else
	{
		return game_engine_get_player_character_type_index(player_character_set_index, player->traits.extended.player_model - 3);
	}
}

void *GetCharacterChudGlobals(__int32 characterTypeIndex) // 0x10901B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterChudGlobals@@YAPAXH@Z");
	// `anonymous-namespace'::GetCharacterChudGlobals
	// __int32 characterTypeIndex;
	// __int32 hudGlobalsIndex;
	// function call : void *(*const)(unsigned long, long)

	__int32 hudGlobalsIndex = Mods::CModGlobals::GetCharacterHudGlobals(characterTypeIndex);
	if (hudGlobalsIndex == NONE)
	{
		hudGlobalsIndex = game_globals_get()->InterfaceTags->HudGlobals.index;
	}

	return tag_get(0x63686764, hudGlobalsIndex);
}

__int32 GetPreferredCharacterType(__int32 playerIndex) // 0x109022A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPreferredCharacterType@@YAHH@Z");
	// `anonymous-namespace'::GetPreferredCharacterType
	// __int32 playerIndex;
	// s_player_datum *player;
	// s_game_globals const *matg;
	// s_mod_globals_definition *mod_globals;
	// long desiredIndex;
		// __int32 i;

	s_player_datum *player = player_get(playerIndex);
	if (!player)
		return -1;
	s_mod_globals_definition *mod_globals = mod_globals_get_definition();
	if (!mod_globals)
		return -1;
	s_game_globals const *matg = game_globals_get();
	if (!matg)
		return -1;
	long desiredIndex = player_find_character_type_by_name(player->configuration.host.appearance.preferred_character);
	for (__int32 i = 0; i < mod_globals->player_character_customizations.count; i++)
	{
		if (mod_globals->player_character_customizations[i].global_player_character_type_index == desiredIndex)
		{
			if ((char)matg->player_character_types[desiredIndex].multiplayer_armor_customization_block_index == -1)
				return -1;
			return desiredIndex;
		}
	}
	return -1;
}

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in
// hades: ModListener() is defaulted in-class (0x10900D60) - Init value-initialises it


std::string GetPreferredCharacterName() // 0x10901DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPreferredCharacterName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
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
		// c_mod_package_manager::s_entry entry;
		// unsigned char hash[20];
			// std::string filename;

	Player::CPlayerCustomizationDB &customizationDB = Utils::Singleton<Player::CPlayerCustomizationDB>::Instance();
	std::string preferredCharacter;
	std::string modHash = c_mod_system::get_current_package_hash();
	if (!modHash.empty())
	{
		unsigned char hash[20];
		Utils::String::HexStringToBytes(modHash, hash, sizeof(hash));
		c_mod_package_manager::s_entry entry;
		if (c_mod_system::get_package_manager().find_package_by_hash(hash, &entry))
		{
			if (entry.modtype.character)
			{
				preferredCharacter = customizationDB.GetPreferredCharacter(modHash);
				if (preferredCharacter.empty())
				{
					std::string filename = std::filesystem::path(entry.file.filename).filename().string();
					preferredCharacter = customizationDB.GetPreferredCharacter(filename);
				}
			}
			else
			{
				preferredCharacter = customizationDB.GetPreferredCharacter("default");
			}
		}
	}
	else
	{
		preferredCharacter = customizationDB.GetPreferredCharacter("default");
	}
	return preferredCharacter;
}

__int32 OverridePlayerCharacter(__int32 playerIndex) // 0x10902BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OverridePlayerCharacter@@YAHH@Z");
	// `anonymous-namespace'::OverridePlayerCharacter
	// static ...; // 0x10902E63
	// static ...; // 0x10902E60
	// static ...; // 0x10902E48
	// static ...; // 0x10902E40
	// __int32 playerIndex;
	// std::string teamDesignator;
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,Server::Voting::HaloType::CharacterOverride> > > > it;
			// __int32 characterSetIndex;
				// long characterSetIndex;
				// __int32 characterIndex;

	std::string teamDesignator = GetPlayerTeamDesginatorName(playerIndex);
	if (auto it = votingCharacterOverrides.find(teamDesignator); it != votingCharacterOverrides.end())
	{
		if (it->second.characterSetName == "random")
		{
			long characterSetIndex = game_engine_get_random_global_player_character_set_index();
			return game_engine_get_random_global_player_character_type_index(characterSetIndex);
		}
		__int32 characterSetIndex = Mods::CModGlobals::FindCharacterSet(it->second.characterSetName);
		if (it->second.characterName == "random")
			return game_engine_get_random_global_player_character_type_index(characterSetIndex);
		else
		{
			__int32 characterIndex = Mods::CModGlobals::FindCharacterInSet(characterSetIndex, it->second.characterName);
			return game_engine_get_player_character_type_index(characterSetIndex, characterIndex);
		}
	}
	return -1;
}

void OnLifeCycleChanged(Blam::Network::LifeCycleState newState) // 0x10902AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnLifeCycleChanged@@YAXW4LifeCycleState@Network@Blam@@@Z");
	// `anonymous-namespace'::OnLifeCycleChanged
	// Blam::Network::LifeCycleState newState;

	switch (newState)
	{
	case Blam::Network::eLifeCycleStateNone:
		votingCharacterOverrides = {};
		break;
	}
}

void OnServerVotePassed(Server::Voting::MapAndType const &winner) // 0x10902B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnServerVotePassed@@YAXABUMapAndType@Voting@Server@@@Z");
	// `anonymous-namespace'::OnServerVotePassed
	// Server::Voting::MapAndType const &winner;

	votingCharacterOverrides = winner.haloType.characterOverrides;
}

bool RequestPlayerPropertiesUpdate(__int32 userIndex) // 0x109031B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestPlayerPropertiesUpdate@@YA_NH@Z");
	// `anonymous-namespace'::RequestPlayerPropertiesUpdate
	// static ...; // 0x10903280
	// static ...; // 0x10903274
	// static ...; // 0x1090326C
	// __int32 userIndex;
	// char *user;
	// void (*const user_interface_controller_update_network_properties)(__int32);
	// c_network_session *session;
	// function call : void (*const)(__int32)


	void (*const user_interface_controller_update_network_properties)(__int32) = (void (*const)(__int32))0xa95170;

	c_network_session *session;
	if (!network_life_cycle_in_squad_session(&session) || !session->established())
	{
		return false;
	}

	char *user = (char *)(0x19a03d8 + userIndex * 0x1698);
	*(__int32 *)(user + 0x1630) += 1;
	*(__int32 *)(user + 0x1678) = session->get_index();

	user_interface_controller_update_network_properties(0);

	return true;
}

void MaybeUpdatePeerProperties() // 0x10902860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MaybeUpdatePeerProperties@@YAXXZ");
	// `anonymous-namespace'::MaybeUpdatePeerProperties
	// procedure flags: nofpo
		// IMod *mod;
	// function call : bool (*const)()
	// function call : IMod *(EModIndex) const
	// function call : bool () const
	// function call : bool () const

	if (!((bool (*)())0x5314B0)())
		return;
	if (prevUpdateNumber != currentUpdateNumber)
	{
		IMod *mod = c_mod_system::GetModManager().GetMod(EModIndex(0));
		if (mod && (mod->GetPakIsLoading() || mod->GetCacheIsLoading()))
			return;
		if (RequestPlayerPropertiesUpdate(0))
			prevUpdateNumber = currentUpdateNumber;
	}
}

_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10902B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModListener@hades_file_local@@EAEXW4EModIndex@@PAVIMod@@@Z");
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;

	currentUpdateNumber = currentUpdateNumber + 1;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_game_globals_interface_tag_references>::try_get_element(__int32, s_game_globals_interface_tag_references **) const;
template c_tag_block_index<s_model_customization_selection,char>::operator char() const;
template s_game_globals_interface_tag_references * c_tag_block<s_game_globals_interface_tag_references>::get_element(__int32) const;
template s_game_globals_interface_tag_references * c_tag_block<s_game_globals_interface_tag_references>::operator->();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { __int32 prevUpdateNumber; }
namespace hades_file_local { __int32 currentUpdateNumber; }

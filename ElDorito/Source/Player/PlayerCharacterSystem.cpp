/* ---------- headers */

#include "Player/PlayerCharacterSystem.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
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
class c_wait_for_render_thread;
struct lambda_1;
struct s_game_globals;
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
	struct CPlayerCharacterSystem;
}
namespace Server
{
	namespace Voting
	{
		struct HaloType;
	}
}
namespace
{
	class ModListener;
}

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

namespace
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
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x12408FF8
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x124090D8
		}
	}
}
namespace
{
	extern std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Server::Voting::HaloType::CharacterOverride,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Server::Voting::HaloType::CharacterOverride> > > votingCharacterOverrides; // 0x124091B8
	extern __int32 prevUpdateNumber; // 0x124091C4
	extern __int32 currentUpdateNumber; // 0x124091C8
	extern std::shared_ptr<c_cache_file_tag_cache> globalBaseTagCache; // 0x124091CC
	extern std::shared_ptr<Blam::Cache::StringIDCache> globalBaseStringCache; // 0x124091D4
}
/* ---------- public code */

namespace Player
{
	extern CPlayerCharacterCustomizationBuilder* _sub_10900CB0(::Player::CPlayerCharacterCustomizationBuilder *const);
	_inline CPlayerCharacterCustomizationBuilder::CPlayerCharacterCustomizationBuilder() // 0x10900CB0
	{
		mangled_x86(MANGLED_TODO, "??0CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ");
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		compiler_generated();
		todo("implement");
		_sub_10900CB0(this);
	}

	extern CPlayerCharacterCustomizationBuilder::SBaseCacheReference* _sub_10900DC0(::Player::CPlayerCharacterCustomizationBuilder::SBaseCacheReference *const);
	_inline CPlayerCharacterCustomizationBuilder::SBaseCacheReference::SBaseCacheReference() // 0x10900DC0
	{
		mangled_x86(MANGLED_TODO, "??0SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ");
		// Player::CPlayerCharacterCustomizationBuilder::SBaseCacheReference *const this;
		compiler_generated();
		todo("implement");
		_sub_10900DC0(this);
	}

	_extern void _sub_10900F80(::Player::CPlayerCharacterCustomizationBuilder *const);
	_inline CPlayerCharacterCustomizationBuilder::~CPlayerCharacterCustomizationBuilder() // 0x10900F80
	{
		mangled_x86(MANGLED_TODO, "??1CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ");
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		compiler_generated();
		todo("implement");
		_sub_10900F80(this);
	}

	_extern void _sub_10901050(::Player::CPlayerCharacterCustomizationBuilder::SBaseCacheReference *const);
	_inline CPlayerCharacterCustomizationBuilder::SBaseCacheReference::~SBaseCacheReference() // 0x10901050
	{
		mangled_x86(MANGLED_TODO, "??1SBaseCacheReference@CPlayerCharacterCustomizationBuilder@Player@@QAE@XZ");
		// Player::CPlayerCharacterCustomizationBuilder::SBaseCacheReference *const this;
		compiler_generated();
		todo("implement");
		_sub_10901050(this);
	}

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
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > prefsName;
			{
				// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
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

	_extern bool _sub_109018B0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, s_player_model_customization &);
	bool CPlayerCharacterSystem::BuildCharacterCustomization(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, s_player_model_customization &customization) // 0x109018B0
	{
		mangled_x86(MANGLED_TODO, "?BuildCharacterCustomization@CPlayerCharacterSystem@Player@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_model_customization@@@Z");
		// static ...; // 0x109019C4
		// static ...; // 0x109019AC
		// static ...; // 0x109019A4
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName;
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

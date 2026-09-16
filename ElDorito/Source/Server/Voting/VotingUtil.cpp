/* ---------- headers */

#include "Server/Voting/VotingUtil.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/saved_games/blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/MapFile.hpp"
#include "ElDorito.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Modules/ModuleGame.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
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
#include <random>
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

class CMapFile;
class c_file_open_scope;
class c_file_reference;
class c_mod_package;
class c_mod_package_manager;
struct lambda_1;
struct lambda_2;
struct s_blf_map_information;
struct s_cache_file_header;
namespace Modules
{
	class ModuleGame;
}
namespace Server
{
	namespace Voting
	{
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
		struct SMapListItem;
	}
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
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class Server::Voting::getMapInfo::__l10::<lambda_1>
//{
//public:
//	<lambda_1>(Server::Voting::getMapInfo::__l10::<lambda_1> &);
//	<lambda_1>(__int32 const &);
//private:
//	__int32 mapId; // 0x0
//public:
//	Server::Voting::getMapInfo::__l10::<lambda_1> &operator=(Server::Voting::getMapInfo::__l10::<lambda_1> const &);
//};
//static_assert(sizeof(Server::Voting::getMapInfo::__l10::<lambda_1>) == 4, "Invalid Server::Voting::getMapInfo::__l10::<lambda_1> size");

//class Server::Voting::getMapInfo::__l15::<lambda_2>
//{
//public:
//	<lambda_2>(Server::Voting::getMapInfo::__l15::<lambda_2> &);
//	<lambda_2>(std::string const &);
//private:
//	std::string const &mapName; // 0x0
//public:
//	Server::Voting::getMapInfo::__l15::<lambda_2> &operator=(Server::Voting::getMapInfo::__l15::<lambda_2> const &);
//};
//static_assert(sizeof(Server::Voting::getMapInfo::__l15::<lambda_2>) == 4, "Invalid Server::Voting::getMapInfo::__l15::<lambda_2> size");

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern __int32 getCustomMapID(std::string mapName);
		extern bool findMapInfoInModPackage(__int32 mapId, std::string const &mapName, std::string const &identifier, Server::Voting::SMapListItem *info);
		extern bool getMapInfo(std::string const &mapName, std::string const &modpack, Server::Voting::SMapListItem *info);
		extern unsigned __int32 FindMapByName(std::vector<Server::Voting::HaloMap> const &maps, std::string const &name);
		extern unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name);
		extern void BuildRandomPlaylist(std::vector<Server::Voting::MapAndType> &playlist, unsigned __int32 size, std::vector<Server::Voting::HaloType> const &types, std::vector<Server::Voting::HaloMap> const &maps);
		extern std::vector<Server::Voting::SMapListItem> const &GetDefaultMapList();
	}
}

/* ---------- globals */

namespace Server
{
	namespace Voting
	{
		extern std::vector<Server::Voting::SMapListItem> MapList; // 0x11389018
		extern bool MapListValid; // 0x11388E50
	}
}

namespace Utils
{
	Modules::ModuleGame *Utils::Singleton<Modules::ModuleGame>::m_instance; // 0x1138CE68
}

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x11388E58
			extern std::string const DefaultTypeNames[8]; // 0x11388F38
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_extern __int32 _sub_10751AB0(std::string);
		__int32 getCustomMapID(std::string mapName) // 0x10751AB0
		{
			mangled_x86(MANGLED_TODO, "?getCustomMapID@Voting@Server@@YAHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10751CAD
			// static ...; // 0x10751CA2
			// static ...; // 0x10751C9C
			// static ...; // 0x10751C78
			// static ...; // 0x10751C70
			// std::string mapName;
			// std::string variantFileName;
			// std::ifstream mapVariant;
			{
				// __int32 mapId;
			}
			todo("implement");
			__int32 __result = _sub_10751AB0(mapName);
			return __result;
		}

		_extern bool _sub_10751560(__int32, std::string const &, std::string const &, Server::Voting::SMapListItem *);
		bool findMapInfoInModPackage(__int32 mapId, std::string const &mapName, std::string const &identifier, Server::Voting::SMapListItem *info) // 0x10751560
		{
			mangled_x86(MANGLED_TODO, "?findMapInfoInModPackage@Voting@Server@@YA_NHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAUSMapListItem@12@@Z");
			// static ...; // 0x10751952
			// static ...; // 0x1075194C
			// static ...; // 0x10751944
			// static ...; // 0x107518FC
			// static ...; // 0x107518F4
			// __int32 mapId;
			// std::string const &mapName;
			// std::string const &identifier;
			// Server::Voting::SMapListItem *info;
			// c_mod_package::e_error err;
			// c_mod_package package;
			// c_mod_package_manager::s_entry packageEntry;
			// c_file_reference file;
			// c_file_open_scope scope;
			{
				// __int32 i;
				{
					// static s_cache_file_header mapHeader; // 0x11389028
					{
						// s_blf_map_information mapInfo;
					}
				}
			}
			todo("implement");
			bool __result = _sub_10751560(mapId, mapName, identifier, info);
			return __result;
		}

		_extern bool _sub_10751D40(std::string const &, std::string const &, Server::Voting::SMapListItem *);
		bool getMapInfo(std::string const &mapName, std::string const &modpack, Server::Voting::SMapListItem *info) // 0x10751D40
		{
			mangled_x86(MANGLED_TODO, "?getMapInfo@Voting@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAUSMapListItem@12@@Z");
			// static ...; // 0x107520C4
			// static ...; // 0x107520A0
			// static ...; // 0x10752098
			// std::string const &mapName;
			// std::string const &modpack;
			// Server::Voting::SMapListItem *info;
			// Modules::ModuleGame const &moduleGame;
			// std::vector<Server::Voting::SMapListItem> const &defaultMaps;
			// __int32 mapId;
			{
				// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<Server::Voting::SMapListItem> > > it;
			}
			{
			}
			todo("implement");
			bool __result = _sub_10751D40(mapName, modpack, info);
			return __result;
		}

		_extern unsigned __int32 _sub_1074DDB0(std::vector<Server::Voting::HaloMap> const &, std::string const &);
		unsigned __int32 FindMapByName(std::vector<Server::Voting::HaloMap> const &maps, std::string const &name) // 0x1074DDB0
		{
			mangled_x86(MANGLED_TODO, "?FindMapByName@Voting@Server@@YAIABV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
			// std::string const &name;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			unsigned __int32 __result = _sub_1074DDB0(maps, name);
			return __result;
		}

		_extern unsigned __int32 _sub_1074DE50(std::vector<Server::Voting::HaloType> const &, std::string const &);
		unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name) // 0x1074DE50
		{
			mangled_x86(MANGLED_TODO, "?FindTypeByName@Voting@Server@@YAIABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
			// std::string const &name;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			unsigned __int32 __result = _sub_1074DE50(types, name);
			return __result;
		}

		_extern void _sub_1074DA70(std::vector<Server::Voting::MapAndType> &, unsigned __int32, std::vector<Server::Voting::HaloType> const &, std::vector<Server::Voting::HaloMap> const &);
		void BuildRandomPlaylist(std::vector<Server::Voting::MapAndType> &playlist, unsigned __int32 size, std::vector<Server::Voting::HaloType> const &types, std::vector<Server::Voting::HaloMap> const &maps) // 0x1074DA70
		{
			mangled_x86(MANGLED_TODO, "?BuildRandomPlaylist@Voting@Server@@YAXAAV?$vector@UMapAndType@Voting@Server@@V?$allocator@UMapAndType@Voting@Server@@@std@@@std@@IABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@4@ABV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@4@@Z");
			// static ...; // 0x1074DCFC
			// static ...; // 0x1074DCCC
			// static ...; // 0x1074DCC4
			// std::vector<Server::Voting::MapAndType> &playlist;
			// unsigned __int32 size;
			// std::vector<Server::Voting::HaloType> const &types;
			// std::vector<Server::Voting::HaloMap> const &maps;
			// std::random_device rd;
			// std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253> g;
			{
				// unsigned __int32 i;
				{
					// Server::Voting::HaloType ht;
					// Server::Voting::HaloMap hm;
				}
			}
			todo("implement");
			_sub_1074DA70(playlist, size, types, maps);
		}
	}
}

extern std::vector<Server::Voting::SMapListItem> const &_sub_1074DEF0();
namespace Server
{
	namespace Voting
	{
		std::vector<Server::Voting::SMapListItem> const &GetDefaultMapList() // 0x1074DEF0
		{
			mangled_x86(MANGLED_TODO, "?GetDefaultMapList@Voting@Server@@YAABV?$vector@USMapListItem@Voting@Server@@V?$allocator@USMapListItem@Voting@Server@@@std@@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1074E44E
			// static ...; // 0x1074E446
			// static ...; // 0x1074E442
			// static ...; // 0x1074E439
			// static ...; // 0x1074E431
			// static ...; // 0x1074E42C
			// static ...; // 0x1074E3E4
			// static ...; // 0x1074E3DC
			{
				// std::filesystem::directory_iterator end_itr;
				// std::filesystem::path mapFolderPath;
				{
					// std::filesystem::directory_iterator itr;
					{
						// std::string fullPath;
						// CMapFile mapFile;
						// Server::Voting::SMapListItem item;
					}
				}
			}
			todo("implement");
			std::vector<Server::Voting::SMapListItem> const & __result = _sub_1074DEF0();
			return __result;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0SMapListItem@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline SMapListItem::SMapListItem(Server::Voting::SMapListItem &&__that) = default; // 0x1074C140

		// mangled_x86(MANGLED_DEFAULT, "??0SMapListItem@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline SMapListItem::SMapListItem(Server::Voting::SMapListItem const &__that) = default; // 0x1074C1E0
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_blf_map_information@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1CMapFile@@QAE@XZ"); no body to assert in
_inline CMapFile::~CMapFile() = default; // 0x1074CD80

namespace Server
{
	namespace Voting
	{
		// mangled_x86(MANGLED_DEFAULT, "??4SMapListItem@Voting@Server@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline Server::Voting::SMapListItem &SMapListItem::operator=(Server::Voting::SMapListItem const &__that) = default; // 0x1074D140
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleGame & Utils::Singleton<Modules::ModuleGame>::Instance();
template c_flags<enum e_blf_scenario_flags,long>::c_flags();
template c_flags<enum e_file_permission_flags,long>::c_flags(long const &);

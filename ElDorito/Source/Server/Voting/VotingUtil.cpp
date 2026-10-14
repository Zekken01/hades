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

#include "mods/mod_system.hpp"  // hades: added for 0x10751560  // hades: added for 0x10751560
#include "Utils/Logger.hpp"  // hades: added for 0x10751560  // hades: added for 0x10751560

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
			// extern std::string const DefaultTypes[8]; // 0x11388E58  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x11388F38  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		__int32 getCustomMapID(std::string mapName) // 0x10751AB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?getCustomMapID@Voting@Server@@YAHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10751CAD
			// static ...; // 0x10751CA2
			// static ...; // 0x10751C9C
			// static ...; // 0x10751C78
			// static ...; // 0x10751C70
			// std::string mapName;
			// std::string variantFileName;
			// std::ifstream mapVariant;
				// __int32 mapId;

			std::string variantFileName = "data/map_variants/" + mapName + "/sandbox.map";
			std::ifstream mapVariant(variantFileName, std::ios::binary);
			if (mapVariant.is_open())
			{
				__int32 mapId = 0;
				mapVariant.seekg(0x120);
				mapVariant.read((char *)&mapId, sizeof(mapId));
				return mapId;
			}
			return -1;
		}

		bool findMapInfoInModPackage(__int32 mapId, std::string const &mapName, std::string const &identifier, Server::Voting::SMapListItem *info) // 0x10751560
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?findMapInfoInModPackage@Voting@Server@@YA_NHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAUSMapListItem@12@@Z");
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
				// __int32 i;
					// static s_cache_file_header mapHeader; // 0x11389028
						// s_blf_map_information mapInfo;

			c_mod_package_manager::s_entry packageEntry;
			if (!c_mod_system::get_mod_info_by_identifier(identifier.c_str(), &packageEntry))
				return false;
			c_mod_package package(packageEntry.file.filename);
			c_mod_package::e_error err;
			if (!package.initialize(&err))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "VotingUtil::findMapInfoInModPackage Failed to open mod package '%s'. Error: %s", packageEntry.file.filename, c_mod_package::get_error_string(err));
				return false;
			}
			c_file_reference file = package.get_file();
			c_file_open_scope scope(file, 1);
			for (__int32 i = 0; i < package.get_map_count(); i++)
			{
				static s_cache_file_header mapHeader;
				if (package.read_map_cache_file_header(file, i, &mapHeader))
				{
					if ((mapId != -1 && mapHeader.map_id == mapId) || (mapId == -1 && strcmp(mapHeader.map_name, mapName.c_str()) == 0))
					{
						s_blf_map_information mapInfo;
						if (!package.read_map_blf_map_information(file, i, &mapInfo))
							continue;
						info->mapId = mapHeader.map_id;
						info->name = mapHeader.map_name;
						info->displayName = Utils::String::ThinString(mapInfo.map_names[0]);
						return true;
					}
				}
			}
			return false;
		}

		bool getMapInfo(std::string const &mapName, std::string const &modpack, Server::Voting::SMapListItem *info) // 0x10751D40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?getMapInfo@Voting@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAUSMapListItem@12@@Z");
			// static ...; // 0x107520C4
			// static ...; // 0x107520A0
			// static ...; // 0x10752098
			// std::string const &mapName;
			// std::string const &modpack;
			// Server::Voting::SMapListItem *info;
			// Modules::ModuleGame const &moduleGame;
			// std::vector<Server::Voting::SMapListItem> const &defaultMaps;
			// __int32 mapId;
				// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<Server::Voting::SMapListItem> > > it;

			Modules::ModuleGame const &moduleGame = Modules::ModuleGame::Instance();
			info->mapId = -1;
			__int32 mapId = getCustomMapID(mapName);
			if (!modpack.empty() && findMapInfoInModPackage(mapId, mapName, modpack, info))
				return true;
			std::vector<Server::Voting::SMapListItem> const &defaultMaps = GetDefaultMapList();
			if (mapId != -1)
			{
			{
			{
			{
				auto it = std::find_if(std::begin(defaultMaps), std::end(defaultMaps), [mapId](auto const &item) { return item.mapId == mapId; });
				if (it != std::end(MapList))
				{
					*info = *it;
					return true;
				}
			}
			}
			}
			}
			else
			{
				auto it = std::find_if(std::begin(defaultMaps), std::end(defaultMaps), [&mapName](auto const &item) { return item.name == mapName; });
				if (it != std::end(MapList))
				{
					*info = *it;
					return true;
				}
			}
			return false;
		}

		unsigned __int32 FindMapByName(std::vector<Server::Voting::HaloMap> const &maps, std::string const &name) // 0x1074DDB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindMapByName@Voting@Server@@YAIABV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
			// std::string const &name;
				// unsigned __int32 i;

			for (unsigned __int32 i = 0; i < maps.size(); i++)
			{
				if (maps[i].mapName == name)
					return i;
			}
			return -1;
		}

		unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name) // 0x1074DE50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindTypeByName@Voting@Server@@YAIABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
			// std::string const &name;
				// unsigned __int32 i;

			for (unsigned __int32 i = 0; i < types.size(); i++)
			{
				if (types[i].typeName == name)
					return i;
			}
			return -1;
		}

		void BuildRandomPlaylist(std::vector<Server::Voting::MapAndType> &playlist, unsigned __int32 size, std::vector<Server::Voting::HaloType> const &types, std::vector<Server::Voting::HaloMap> const &maps) // 0x1074DA70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BuildRandomPlaylist@Voting@Server@@YAXAAV?$vector@UMapAndType@Voting@Server@@V?$allocator@UMapAndType@Voting@Server@@@std@@@std@@IABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@4@ABV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@4@@Z");
			// static ...; // 0x1074DCFC
			// static ...; // 0x1074DCCC
			// static ...; // 0x1074DCC4
			// std::vector<Server::Voting::MapAndType> &playlist;
			// unsigned __int32 size;
			// std::vector<Server::Voting::HaloType> const &types;
			// std::vector<Server::Voting::HaloMap> const &maps;
			// std::random_device rd;
			// std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253> g;
				// unsigned __int32 i;
					// Server::Voting::HaloType ht;
					// Server::Voting::HaloMap hm;

			std::random_device rd;
			std::mt19937 g(rd());
			for (unsigned __int32 i = 0; i < std::min(size, types.size()); i++)
			{
				Server::Voting::HaloType ht = types[g() % types.size()];
				Server::Voting::HaloMap hm;
				if (!ht.specificMaps.empty())
					hm = ht.specificMaps[g() % ht.specificMaps.size()];
				else
					hm = maps[g() % maps.size()];
				playlist.push_back(Server::Voting::MapAndType(hm, ht));
			}
		}
	}
}


namespace Server
{
	namespace Voting
	{
		std::vector<Server::Voting::SMapListItem> const &GetDefaultMapList() // 0x1074DEF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetDefaultMapList@Voting@Server@@YAABV?$vector@USMapListItem@Voting@Server@@V?$allocator@USMapListItem@Voting@Server@@@std@@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1074E44E
			// static ...; // 0x1074E446
			// static ...; // 0x1074E442
			// static ...; // 0x1074E439
			// static ...; // 0x1074E431
			// static ...; // 0x1074E42C
			// static ...; // 0x1074E3E4
			// static ...; // 0x1074E3DC
				// std::filesystem::directory_iterator end_itr;
				// std::filesystem::path mapFolderPath;
					// std::filesystem::directory_iterator itr;
						// std::string fullPath;
						// CMapFile mapFile;
						// Server::Voting::SMapListItem item;

			if (!MapListValid)
			{
				MapList.clear();
				MapListValid = true;
				std::filesystem::path mapFolderPath = ElDorito::Instance().GetMapsFolder();
				std::filesystem::directory_iterator end_itr;
				if (std::filesystem::exists(mapFolderPath))
				{
					for (std::filesystem::directory_iterator itr(mapFolderPath); itr != end_itr; ++itr)
					{
						if (!itr->is_regular_file() || itr->path().extension() != ".map")
							continue;
						std::string fullPath = std::filesystem::canonical(itr->path()).string();
						CMapFile mapFile(fullPath);
						if (!mapFile.IsValid())
							continue;
						Server::Voting::SMapListItem item;
						item.name = mapFile.GetScenarioName();
						item.mapId = mapFile.GetMapId();
						if (mapFile.HasMapInfo())
							item.displayName = Utils::String::ThinString(mapFile.GetDisplayName(0));
						else
							item.displayName = Utils::String::TitleCase(mapFile.GetScenarioName());
						MapList.push_back(item);
					}
				}
			}
			return MapList;
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

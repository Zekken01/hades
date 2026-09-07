/* ---------- headers */

#include "Forge/Prefab.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_sandbox.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUtil.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/map_variant_loader.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <bitset>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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

struct real_point3d;
struct real_vector3d;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_variant_datum;
namespace Forge
{
	class ObjectSet;
	struct ForgeObjectQuota;
}
namespace Forge
{
	namespace Prefabs
	{
		struct PrefabHeader;
	}
}
namespace
{
	struct PrefabPlacement;
	struct PrefabPaletteEntry;
}

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Prefabs {}
	using namespace Forge::Prefabs;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct PrefabPlacement
	{
		unsigned __int32 Flags; // 0x0
		unsigned __int32 PaletteIndex; // 0x4
		real_point3d Position; // 0x8
		real_vector3d Forward; // 0x14
		real_vector3d Up; // 0x20
		s_map_variant_placement_properties Properties; // 0x2C
		PrefabPlacement(PrefabPlacement &); /* compiler_generated() */
		PrefabPlacement(PrefabPlacement const &); /* compiler_generated() */
		PrefabPlacement(); /* compiler_generated() */
		PrefabPlacement &operator=(PrefabPlacement &); /* compiler_generated() */
		PrefabPlacement &operator=(PrefabPlacement const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(PrefabPlacement) == 68, "Invalid PrefabPlacement size");

	struct PrefabPaletteEntry
	{
		char tag_name[256]; // 0x0
	};
	static_assert(sizeof(PrefabPaletteEntry) == 256, "Invalid PrefabPaletteEntry size");
}
/* ---------- prototypes */

namespace Forge
{
	namespace Prefabs
	{
		extern bool Save(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &author, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
		extern bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
		extern bool ReadHeader(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, Forge::Prefabs::PrefabHeader &header);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	namespace Prefabs
	{
		_extern bool _sub_10970530(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool Save(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &author, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path) // 0x10970530
		{
			mangled_x86(MANGLED_TODO, "?Save@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@0@Z");
			// static ...; // 0x10970D28
			// static ...; // 0x10970D1B
			// static ...; // 0x10970D18
			// static ...; // 0x10970D08
			// static ...; // 0x10970CFB
			// static ...; // 0x10970CF4
			// static ...; // 0x10970C94
			// static ...; // 0x10970C8C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &author;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &name;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// static PrefabPlacement placements[640]; // 0x1240FBA0
			// std::basic_ofstream<char,std::char_traits<char> > fs;
			// long placementCount;
			// std::unordered_map<long,long,std::hash<long>,std::equal_to<long>,std::allocator<std::pair<long const ,long> > > tagIndexToPaletteIndex;
			// Forge::ObjectSet &objectSet;
			// real_point3d const &crosshairPoint;
			// unsigned long playerHandle;
			// static PrefabPaletteEntry palette[256]; // 0x1241A5A8
			// long paletteItemCount;
			// Forge::Prefabs::PrefabHeader header;
			// s_map_variant *mapv;
			// static __int32 $TSS0; // 0x1241A5A0
			{
				// __int32 i;
				{
					// long paletteIndex;
					// s_variant_datum &placement;
					// long tagIndex;
					// PrefabPlacement *prefabPlacement;
					// real_vector3d displacement;
					{
						// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;
						{
							// char const *tag_name;
							// unsigned long group_tag;
							// char group_tag_ascii[5];
							// char *dest_tag_name;
							// unsigned __int32 len;
						}
					}
				}
			}
			// function call : s_map_variant *(*const)()
			// function call : unsigned long (*const)(long)
			todo("implement");
			bool __result = _sub_10970530(author, name, path);
			return __result;
		}
	}
}

extern s_map_variant_placement_properties &_sub_1096F790(s_map_variant_placement_properties *const, s_map_variant_placement_properties const &);
_inline s_map_variant_placement_properties &s_map_variant_placement_properties::operator=(s_map_variant_placement_properties const &__that) // 0x1096F790
{
	mangled_x86(MANGLED_TODO, "??4s_map_variant_placement_properties@@QAEAAU0@ABU0@@Z");
	// s_map_variant_placement_properties const &__that;
	compiler_generated();
	todo("implement");
	s_map_variant_placement_properties & __result = _sub_1096F790(this, __that);
	return __result;
}

namespace Forge
{
	namespace Prefabs
	{
		_extern bool _sub_1096FAB0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path) // 0x1096FAB0
		{
			mangled_x86(MANGLED_TODO, "?Load@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1097016F
			// static ...; // 0x10970168
			// static ...; // 0x10970162
			// static ...; // 0x10970150
			// static ...; // 0x10970147
			// static ...; // 0x1097013D
			// static ...; // 0x10970134
			// static ...; // 0x109700E0
			// static ...; // 0x109700D8
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// static PrefabPlacement placements[640]; // 0x1242A5A8
			// long paletteTagIndices[256];
			// std::basic_ifstream<char,std::char_traits<char> > fs;
			// Forge::ObjectSet &objectSet;
			// real_point3d const &crosshairPoint;
			// __int32 remainingObjects;
			// long playerHandle;
			// Forge::ForgeObjectQuota quota;
			// static PrefabPaletteEntry palette[256]; // 0x12434FA8
			// Forge::Prefabs::PrefabHeader header;
			// s_map_variant *mapv;
			// static __int32 $TSS0; // 0x1241A5A4
			{
				// long needed;
			}
			{
				// __int32 i;
				{
					// char tag_name[256];
					// long tag_index;
					// unsigned long group_tag;
					// PrefabPlacement &prefabPlacement;
				}
			}
			{
				{
					// real_point3d position;
					// long newObjectIndex;
				}
			}
			// function call : s_map_variant *(*const)()
			// function call : unsigned long (*const)(long)
			// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)
			todo("implement");
			bool __result = _sub_1096FAB0(path);
			return __result;
		}

		_extern bool _sub_109703E0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, Forge::Prefabs::PrefabHeader &);
		bool ReadHeader(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, Forge::Prefabs::PrefabHeader &header) // 0x109703E0
		{
			mangled_x86(MANGLED_TODO, "?ReadHeader@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUPrefabHeader@12@@Z");
			// static ...; // 0x109704D8
			// static ...; // 0x109704D0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// Forge::Prefabs::PrefabHeader &header;
			// std::basic_ifstream<char,std::char_traits<char> > fs;
			todo("implement");
			bool __result = _sub_109703E0(path, header);
			return __result;
		}
	}
}

/* ---------- private code */

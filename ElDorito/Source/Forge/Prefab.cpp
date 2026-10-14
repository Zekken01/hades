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
namespace hades_file_local
{
	struct PrefabPlacement;
	struct PrefabPaletteEntry;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

extern char const *tag_get_name(long tag_index); extern char const *tag_to_string(unsigned long tag, char *dest, long dest_length);  // hades: added for 0x10970530  // hades: added for 0x10970530

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x1096FAB0  // hades: added for 0x1096FAB0
namespace hades_file_local { template<typename... t_args> static void DisplayPrefabError(wchar_t const *format, t_args... args); }  // hades: added for 0x1096FAB0  // hades: added for 0x1096FAB0
namespace Forge { namespace Selection { extern Forge::ObjectSet &GetSelection(); } }  // hades: added for 0x1096FAB0  // hades: added for 0x1096FAB0
extern bool parse_tag_file_name(char const *path, char *out_tag_name, unsigned long *out_group_tag); extern long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x1096FAB0  // hades: added for 0x1096FAB0

namespace Forge
{
	namespace Prefabs
	{
		extern bool Save(std::string const &author, std::string &name, std::string const &path);
		extern bool Load(std::string const &path);
		extern bool ReadHeader(std::string const &path, Forge::Prefabs::PrefabHeader &header);
	}
}

bool ReadHeader(std::ifstream &stream, Forge::Prefabs::PrefabHeader &header);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??4s_map_variant_placement_properties@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline s_map_variant_placement_properties &s_map_variant_placement_properties::operator=(s_map_variant_placement_properties const &__that) = default; // 0x1096F790

namespace Forge
{
	namespace Prefabs
	{
		bool Save(std::string const &author, std::string &name, std::string const &path) // 0x10970530
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Save@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@0@Z");
			// static ...; // 0x10970D28
			// static ...; // 0x10970D1B
			// static ...; // 0x10970D18
			// static ...; // 0x10970D08
			// static ...; // 0x10970CFB
			// static ...; // 0x10970CF4
			// static ...; // 0x10970C94
			// static ...; // 0x10970C8C
			// std::string const &author;
			// std::string &name;
			// std::string const &path;
			// static PrefabPlacement placements[640]; // 0x1240FBA0
			// std::ofstream fs;
			// long placementCount;
			// std::unordered_map<long,long> tagIndexToPaletteIndex;
			// Forge::ObjectSet &objectSet;
			// real_point3d const &crosshairPoint;
			// unsigned long playerHandle;
			// static PrefabPaletteEntry palette[256]; // 0x1241A5A8
			// long paletteItemCount;
			// Forge::Prefabs::PrefabHeader header;
			// s_map_variant *mapv;
			// static __int32 $TSS0; // 0x1241A5A0
				// __int32 i;
					// long paletteIndex;
					// s_variant_datum &placement;
					// long tagIndex;
					// PrefabPlacement *prefabPlacement;
					// real_vector3d displacement;
						// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;
							// char const *tag_name;
							// unsigned long group_tag;
							// char group_tag_ascii[5];
							// char *dest_tag_name;
							// unsigned __int32 len;
			// function call : s_map_variant *(*const)()
			// function call : unsigned long (*const)(long)

			static PrefabPaletteEntry palette[256];
			std::ofstream fs(path, std::ios::binary);
			if (!fs.is_open())
				return false;
			Forge::ObjectSet &objectSet = Forge::Selection::GetSelection();
			s_map_variant *mapv = game_engine_get_runtime_map_variant();
			unsigned long playerHandle = ((unsigned long (*)(long))0x589C30)(0);
			real_point3d const &crosshairPoint = get_sandbox_globals()->player_cursor_position[playerHandle & 0xF];
			static PrefabPlacement placements[640];
			long paletteItemCount = 0;
			long placementCount = 0;
			std::unordered_map<long,long> tagIndexToPaletteIndex;
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (!placement.flags.test(_map_variant_occupied_slot_bit) || !objectSet.Contains(placement.object_index))
					continue;
				long tagIndex = mapv->object_quotas[placement.quota_index].definition_index;
				long paletteIndex = -1;
				{
					auto it = tagIndexToPaletteIndex.find(tagIndex);
					if (it == tagIndexToPaletteIndex.end())
					{
						paletteIndex = paletteItemCount++;
						char const *tag_name = tag_get_name(tagIndex);
						if (!tag_name)
							return false;
						char *dest_tag_name = palette[paletteIndex].tag_name;
						unsigned __int32 len = strlen(tag_name);
						if (len > 255)
							return false;
						char group_tag_ascii[5];
						unsigned long group_tag = tag_get_group_tag(tagIndex);
						tag_to_string(group_tag, group_tag_ascii, 5);
						snprintf(dest_tag_name, 256, "%s.%s", tag_name, group_tag_ascii);
						tagIndexToPaletteIndex.insert(std::make_pair(tagIndex, paletteIndex));
					}
					else
						paletteIndex = it->second;
				}
				PrefabPlacement *prefabPlacement = &placements[placementCount++];
				prefabPlacement->PaletteIndex = paletteIndex;
				real_vector3d displacement = placement.position - get_sandbox_globals()->player_cursor_position[0];
				*reinterpret_cast<real_vector3d *>(&prefabPlacement->Position) = displacement;
				prefabPlacement->Forward = placement.forward;
				prefabPlacement->Up = placement.up;
				prefabPlacement->Properties = static_cast<s_map_variant_placement_properties const &>(placement.properties);
			}
			Forge::Prefabs::PrefabHeader header = {};
			header.Magic = 'prfb';
			header.Version = 1;
			header.DateCreated = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
			strncpy_s(header.Name, name.c_str(), _TRUNCATE);
			strncpy_s(header.Author, author.c_str(), _TRUNCATE);
			header.ObjectCount = placementCount;
			header.PaletteCount = paletteItemCount;
			fs.write((char *)&header, sizeof(header));
			fs.write((char *)palette, paletteItemCount * (std::streamsize)sizeof(PrefabPaletteEntry));
			fs.write((char *)placements, placementCount * (std::streamsize)sizeof(PrefabPlacement));
			if (fs.fail())
				return false;
			return true;
		}

		bool Load(std::string const &path) // 0x1096FAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Load@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1097016F
			// static ...; // 0x10970168
			// static ...; // 0x10970162
			// static ...; // 0x10970150
			// static ...; // 0x10970147
			// static ...; // 0x1097013D
			// static ...; // 0x10970134
			// static ...; // 0x109700E0
			// static ...; // 0x109700D8
			// std::string const &path;
			// static PrefabPlacement placements[640]; // 0x1242A5A8
			// long paletteTagIndices[256];
			// std::ifstream fs;
			// Forge::ObjectSet &objectSet;
			// real_point3d const &crosshairPoint;
			// __int32 remainingObjects;
			// long playerHandle;
			// Forge::ForgeObjectQuota quota;
			// static PrefabPaletteEntry palette[256]; // 0x12434FA8
			// Forge::Prefabs::PrefabHeader header;
			// s_map_variant *mapv;
			// static __int32 $TSS0; // 0x1241A5A4
				// long needed;
				// __int32 i;
					// char tag_name[256];
					// long tag_index;
					// unsigned long group_tag;
					// PrefabPlacement &prefabPlacement;
					// real_point3d position;
					// long newObjectIndex;
			// function call : s_map_variant *(*const)()
			// function call : unsigned long (*const)(long)
			// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)

			static PrefabPaletteEntry palette[256];
			std::ifstream fs(path, std::ios::binary);
			if (!fs.is_open())
				return false;
			s_map_variant *mapv = game_engine_get_runtime_map_variant();
			if (!mapv)
				return false;
			Forge::Prefabs::PrefabHeader header;
			if (!::ReadHeader(fs, header))
			{
				DisplayPrefabError(L"Not a valid prefab file");
				return false;
			}
			if (!header.PaletteCount || header.PaletteCount >= 256 || !header.ObjectCount || header.ObjectCount >= 640)
				return false;
			Forge::ForgeObjectQuota quota = Forge::CalculateObjectQuota();
			long playerHandle = ((unsigned long (*)(long))0x589C30)(0);
			real_point3d const &crosshairPoint = get_sandbox_globals()->player_cursor_position[playerHandle & 0xF];
			__int32 remainingObjects = quota.TotalObjectsAvailable - quota.TotalObjectsUsed;
			if (header.ObjectCount > remainingObjects)
			{
				long needed = quota.TotalObjectsUsed + header.ObjectCount - quota.TotalObjectsAvailable;
				DisplayPrefabError(L"Unable to load prefab: out of objects. (%d more objects needed)", needed);
				return false;
			}
			Forge::ObjectSet &objectSet = Forge::Selection::GetSelection();
			objectSet.Clear();
			static PrefabPlacement placements[640];
			long paletteTagIndices[256];
			memset(paletteTagIndices, -1, sizeof(paletteTagIndices));
			fs.read((char *)palette, header.PaletteCount * (std::streamsize)sizeof(PrefabPaletteEntry));
			fs.read((char *)placements, header.ObjectCount * (std::streamsize)sizeof(PrefabPlacement));
			if (fs.fail())
				return false;
			for (__int32 i = 0; i < header.ObjectCount; i++)
			{
				PrefabPlacement &prefabPlacement = placements[i];
				if (prefabPlacement.PaletteIndex >= header.PaletteCount)
					continue;
				char tag_name[256];
				unsigned long group_tag;
				if (!parse_tag_file_name(palette[prefabPlacement.PaletteIndex].tag_name, tag_name, &group_tag))
					return false;
				long tag_index = tag_find_by_name(group_tag, tag_name);
				if (tag_index == -1)
				{
					DisplayPrefabError(L"Could not find tag \"%S\"", palette[prefabPlacement.PaletteIndex].tag_name);
					return false;
				}
				paletteTagIndices[prefabPlacement.PaletteIndex] = tag_index;
			}
			for (__int32 i = 0; i < header.ObjectCount; i++)
			{
				PrefabPlacement &prefabPlacement = placements[i];
				real_point3d position = crosshairPoint + prefabPlacement.Position;
				long newObjectIndex = ((long (__thiscall *)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short))0x582110)(mapv, paletteTagIndices[prefabPlacement.PaletteIndex], 0, -1, &position, &prefabPlacement.Forward, &prefabPlacement.Up, -1, -1, &prefabPlacement.Properties, 0);
				if (newObjectIndex == -1)
				{
					DisplayPrefabError(L"Unable to spawn one or more objects!");
					return false;
				}
				objectSet.Add(newObjectIndex);
			}
			return true;
		}

		bool ReadHeader(std::string const &path, Forge::Prefabs::PrefabHeader &header) // 0x109703E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadHeader@Prefabs@Forge@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUPrefabHeader@12@@Z");
			// static ...; // 0x109704D8
			// static ...; // 0x109704D0
			// std::string const &path;
			// Forge::Prefabs::PrefabHeader &header;
			// std::ifstream fs;

			std::ifstream fs(path, std::ios::binary);
			return fs.is_open() && ::ReadHeader(fs, header);
		}
	}
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0PrefabPlacement@hades_file_local@@QAE@XZ"); no body to assert in
_inline PrefabPlacement::PrefabPlacement() = default; // 0x1096F6D0

bool ReadHeader(std::ifstream &stream, Forge::Prefabs::PrefabHeader &header) // 0x10970330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReadHeader@@YA_NAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@AAUPrefabHeader@Prefabs@Forge@@@Z");
	// `anonymous-namespace'::ReadHeader
	// Forge::Prefabs::PrefabHeader &header;

	stream.read((char *)&header, 56);
	return !stream.fail() && header.Magic == 1886545506 && header.Version == 1;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_multiplayer_object_boundary_shape,char> & c_enum<enum e_multiplayer_object_boundary_shape,char>::operator=(c_enum<enum e_multiplayer_object_boundary_shape,char> const &);
template c_flags<enum e_game_engine_type,unsigned short> & c_flags<enum e_game_engine_type,unsigned short>::operator=(c_flags<enum e_game_engine_type,unsigned short> const &);

namespace hades_file_local
{
	template<typename... t_args>
	static void DisplayPrefabError(wchar_t const *format, t_args... args) // 0x1096F110, 0x1096F1F0, 0x1096F2E0
	{
		wchar_t buffer[4096];
		memset(buffer, 0, sizeof(buffer));
		swprintf_s(buffer, format, args...);
		Forge::PrintKillFeedText(0, buffer, 0);
	}
}

// hades: the instantiations Forge::Prefabs::Load uses (Load itself is not reconstructed yet).
template void hades_file_local::DisplayPrefabError<>(wchar_t const *format);
template void hades_file_local::DisplayPrefabError<long>(wchar_t const *format, long);
template void hades_file_local::DisplayPrefabError<char *>(wchar_t const *format, char *);

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
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
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "CommandScript.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/map_variant_loader.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <limits>
#include <memory>
#include <stack>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct c_object_identifier;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_object_data;
struct s_variant_datum;
struct s_variant_quota;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Forge
{
	class ObjectSet;
}

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge
{
	namespace Selection
	{
		extern Forge::ObjectSet &GetSelection();
	}
}

namespace Forge
{
	extern bool IsEmpty();
	extern long GetCurrentObjectIndex(long playerIndex);
}

namespace Forge
{
	namespace Selection
	{
		extern void SelectAll();
		extern void SelectEverything();
		extern void SelectAllMaterial();
		extern void DeselectAllOf();
		extern void Invert();
		extern void Expand(float amount);
		extern void Clear();
		extern void Delete();
		extern bool Clone();
		extern void Update();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern Forge::ObjectSet s_SelectedObjects; // 0x1244FA70
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	extern ObjectSet &_sub_109749C0();
}

namespace Forge
{
	namespace Selection
	{
		Forge::ObjectSet &GetSelection() // 0x109749C0
		{
			mangled_x86(MANGLED_TODO, "?GetSelection@Selection@Forge@@YAAAVObjectSet@2@XZ");
			// procedure flags: nofpo
			todo("implement");
			Forge::ObjectSet & __result = _sub_109749C0();
			return __result;
		}
	}
}

namespace Forge
{
	_extern bool _sub_10974B50();
	bool IsEmpty() // 0x10974B50
	{
		mangled_x86(MANGLED_TODO, "?IsEmpty@Forge@@YA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_10974B50();
		return __result;
	}

	_extern long _sub_109748B0(long);
	long GetCurrentObjectIndex(long playerIndex) // 0x109748B0
	{
		mangled_x86(MANGLED_TODO, "?GetCurrentObjectIndex@Forge@@YAJJ@Z");
		// static ...; // 0x10974971
		// static ...; // 0x1097495C
		// static ...; // 0x10974944
		// static ...; // 0x1097493C
		// long playerIndex;
		// long heldObjectIndex;
		// long crosshairObjectIndex;
		// function call : bool (*const)(long, long *, long *)
		todo("implement");
		long __result = _sub_109748B0(playerIndex);
		return __result;
	}
}

namespace Forge
{
	namespace Selection
	{
		_extern void _sub_10974C40();
		void SelectAll() // 0x10974C40
		{
			mangled_x86(MANGLED_TODO, "?SelectAll@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_object_data *currentObject;
			// unsigned long playerIndex;
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
				}
			}
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_10974C40();
		}
	}
}

namespace Forge
{
	_inline ObjectSet::ObjectSet() // 0x109734A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ObjectSet@Forge@@QAE@XZ");
		// Forge::ObjectSet *const this;

		compiler_generated();
	}
}

_inline c_object_identifier::c_object_identifier(c_object_identifier const &__that) // 0x109734F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_object_identifier@@QAE@ABU0@@Z");
	// c_object_identifier const &__that;

	compiler_generated();
}

_inline s_map_variant_placement_properties::s_map_variant_placement_properties(s_map_variant_placement_properties const &__that) // 0x109735C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_map_variant_placement_properties@@QAE@ABU0@@Z");
	// s_map_variant_placement_properties const &__that;

	compiler_generated();
}

_inline s_variant_datum::s_variant_datum(s_variant_datum const &__that) // 0x109736F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_variant_datum@@QAE@ABU0@@Z");
	// s_variant_datum const &__that;

	compiler_generated();
}

namespace Forge
{
	namespace Selection
	{
		_extern void _sub_10974F60();
		void SelectEverything() // 0x10974F60
		{
			mangled_x86(MANGLED_TODO, "?SelectEverything@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
					// s_variant_quota &budget;
					// char const *tagName;
				}
			}
			todo("implement");
			_sub_10974F60();
		}

		_extern void _sub_10974D50();
		void SelectAllMaterial() // 0x10974D50
		{
			mangled_x86(MANGLED_TODO, "?SelectAllMaterial@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10974EDC
			// static ...; // 0x10974ED0
			// static ...; // 0x10974EC8
			// s_variant_datum currentObjectPlacement;
			// s_object_data *currentObject;
			// unsigned long playerIndex;
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
				}
			}
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_10974D50();
		}

		_extern void _sub_10974330();
		void DeselectAllOf() // 0x10974330
		{
			mangled_x86(MANGLED_TODO, "?DeselectAllOf@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_object_data *currentObject;
			// unsigned long playerIndex;
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
				}
			}
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_10974330();
		}

		_extern void _sub_109749E0();
		void Invert() // 0x109749E0
		{
			mangled_x86(MANGLED_TODO, "?Invert@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10974AF4
			// static ...; // 0x10974AE8
			// static ...; // 0x10974AE0
			// Forge::ObjectSet newSelection;
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
				}
			}
			todo("implement");
			_sub_109749E0();
		}

		_extern void _sub_10974440(float);
		void Expand(float amount) // 0x10974440
		{
			mangled_x86(MANGLED_TODO, "?Expand@Selection@Forge@@YAXM@Z");
			// static ...; // 0x109747C4
			// static ...; // 0x109747C0
			// static ...; // 0x109747BC
			// static ...; // 0x10974798
			// static ...; // 0x10974790
			// float amount;
			// real_point3d centroid;
			// float radius2;
			// real_point3d min;
			// float s;
			// __int32 selectedObjectCount;
			// real_point3d max;
			// s_map_variant *const mapv;
			{
				// __int32 i;
				{
					// s_variant_datum &placement;
				}
			}
			{
				{
				}
			}
			todo("implement");
			_sub_10974440(amount);
		}

		_extern void _sub_10973BB0();
		void Clear() // 0x10973BB0
		{
			mangled_x86(MANGLED_TODO, "?Clear@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10973BB0();
		}

		_extern void _sub_109741D0();
		void Delete() // 0x109741D0
		{
			mangled_x86(MANGLED_TODO, "?Delete@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_object_data *object;
			// unsigned long playerHandle;
			// long objectIndex;
			// s_map_variant *mapv;
			{
				// __int32 i;
				{
					// s_variant_datum const &placement;
					// s_variant_quota const &budget;
				}
			}
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_109741D0();
		}

		_extern bool _sub_10973C00();
		bool Clone() // 0x10973C00
		{
			mangled_x86(MANGLED_TODO, "?Clone@Selection@Forge@@YA_NXZ");
			// procedure flags: nofpo
			// static ...; // 0x10974097
			// static ...; // 0x10974083
			// static ...; // 0x10974072
			// static ...; // 0x10974061
			// static ...; // 0x10974054
			// static ...; // 0x10974018
			// static ...; // 0x10974010
			// s_object_data *referenceObject;
			// Forge::ObjectSet &selection;
			// real_point3d const &crosshairPoint;
			// unsigned __int32 (*const spawn_object)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short);
			// unsigned long playerHandle;
			// std::stack<unsigned int,std::deque<unsigned int,std::allocator<unsigned int> > > cloneStack;
			// s_map_variant *mapv;
			// real_point3d const &referencePoint;
			{
				// __int32 i;
				{
					// s_variant_datum const &placement;
					// Forge::ObjectSet const &selection;
				}
			}
			{
				// real_point3d new_position;
				// long object_index;
				// real_vector3d crosshair_offset;
				// long new_object_index;
				// s_object_data *object;
				// s_map_variant_placement_properties *variantProperties;
				// real_matrix4x3 object_world_matrix;
				// real_vector3d reference_offset;
			}
			// function call : s_map_variant *(*const)()
			// function call : unsigned long (*const)(long)
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : unsigned __int32 (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short)
			todo("implement");
			bool __result = _sub_10973C00();
			return __result;
		}

		_extern void _sub_109750C0();
		void Update() // 0x109750C0
		{
			mangled_x86(MANGLED_TODO, "?Update@Selection@Forge@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x1097522D
			// static ...; // 0x10975218
			// static ...; // 0x10975200
			// static ...; // 0x109751F8
			// long heldObjectIndex;
			// static bool s_IsPaintSelecting; // 0x1244FB70
			// unsigned long playerIndex;
			// long crosshairObjectIndex;
			// Blam::Input::ActionState *fireRight;
			{
				// Forge::ObjectSet &selection;
			}
			// function call : unsigned long (*const)(long)
			// function call : bool (*const)(long, long *, long *)
			todo("implement");
			_sub_109750C0();
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_multiplayer_object_boundary_shape,char>::c_enum(c_enum<enum e_multiplayer_object_boundary_shape,char> const &);
template c_enum<enum e_multiplayer_object_boundary_shape,char>::c_enum(char const &);
template c_enum<enum e_scenario_object_source,char>::c_enum(c_enum<enum e_scenario_object_source,char> const &);
template c_enum<enum e_scenario_object_source,char>::c_enum(char const &);
template c_flags<enum e_game_engine_type,unsigned short>::c_flags(c_flags<enum e_game_engine_type,unsigned short> const &);
template c_flags<enum e_game_engine_type,unsigned short>::c_flags(unsigned short const &);
template c_flags<enum e_variant_object_placement_flags,unsigned short>::c_flags(c_flags<enum e_variant_object_placement_flags,unsigned short> const &);
template c_flags<enum e_variant_object_placement_flags,unsigned short>::c_flags(unsigned short const &);
template c_flags<enum e_variant_placement_flags,unsigned char>::c_flags(c_flags<enum e_variant_placement_flags,unsigned char> const &);
template c_tag_block_index<s_scenario_structure_bsp_reference,short>::c_tag_block_index(c_tag_block_index<s_scenario_structure_bsp_reference,short> const &);

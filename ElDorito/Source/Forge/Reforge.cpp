/* ---------- headers */

#include "Forge/Reforge.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectSet.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct begin;
struct c_game_engine;
struct end;
struct s_forge_globals_definition;
struct s_model_definition;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_definition;
struct s_render_model;
struct s_tag_reference;
struct s_unit_data;
namespace Forge
{
	struct ReforgeObjectProperties;
}
namespace Forge
{
	namespace Reforge
	{
		struct SRenderMaterialParameters;
	}
}
namespace
{
	struct SReforgeGlobals;
}

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct SReforgeGlobals
	{
		std::bitset<65535> ReforgeObjects; // 0x0
		SReforgeGlobals(); /* compiler_generated() */
	};
	static_assert(sizeof(SReforgeGlobals) == 8192, "Invalid SReforgeGlobals size");
}
/* ---------- prototypes */

namespace Forge
{
	namespace Reforge
	{
		extern void InitializeForNewMap();
		extern bool IsReforgeObject(long objectIndex);
		extern bool IsForgeScenery(long objectIndex);
		extern Forge::ReforgeObjectProperties *GetReforgeObject(long objectIndex);
		extern bool IsMapModifierObject(long objectIndex);
		extern bool IsGarbageCollectionObject(long objectIndex);
		extern bool IsKillVolumeObject(long objectIndex);
		extern bool IsPrematchCameraObject(long objectIndex);
		extern bool IsPodiumPointObject(long objectIndex);
		extern bool IsActiveTeamBarrierObject(long objectIndex);
		extern bool TeamBarrierTestPlayer(long barrierObjectIndex, long playerIndex);
		extern bool TeamBarrierTestUnit(long barrierObjectIndex, long unitIndex);
		extern bool ValidRenderMaterialIndex(long objectIndex, __int32 index);
		extern short GetRenderMaterialOverride(long objectIndex, Forge::Reforge::SRenderMaterialParameters *parameters);

		long get_controlling_unit(long unit_index);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	namespace Reforge
	{
		_extern void _sub_10865AD0();
		void InitializeForNewMap() // 0x10865AD0
		{
			mangled_x86(MANGLED_TODO, "?InitializeForNewMap@Reforge@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_forge_globals_definition *forge_globals;
			{
				// c_tag_block<s_tag_reference> &<range>$L0;
				// s_tag_reference *<begin>$L0;
				// s_tag_reference *<end>$L0;
				{
					// s_tag_reference &reforgeObject;
					{
						// s_render_model *renderModel;
					}
				}
			}
			todo("implement");
			_sub_10865AD0();
		}

		_extern bool _sub_108660A0(long);
		bool IsReforgeObject(long objectIndex) // 0x108660A0
		{
			mangled_x86(MANGLED_TODO, "?IsReforgeObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_108660A0(objectIndex);
			return __result;
		}

		_extern bool _sub_10865CC0(long);
		bool IsForgeScenery(long objectIndex) // 0x10865CC0
		{
			mangled_x86(MANGLED_TODO, "?IsForgeScenery@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865CC0(objectIndex);
			return __result;
		}
	}
}

namespace Forge
{
	extern ReforgeObjectProperties *_sub_108658A0(long);
}

namespace Forge
{
	namespace Reforge
	{
		Forge::ReforgeObjectProperties *GetReforgeObject(long objectIndex) // 0x108658A0
		{
			mangled_x86(MANGLED_TODO, "?GetReforgeObject@Reforge@Forge@@YAPAUReforgeObjectProperties@2@J@Z");
			// long objectIndex;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			todo("implement");
			Forge::ReforgeObjectProperties * __result = _sub_108658A0(objectIndex);
			return __result;
		}

		_extern bool _sub_10865E90(long);
		bool IsMapModifierObject(long objectIndex) // 0x10865E90
		{
			mangled_x86(MANGLED_TODO, "?IsMapModifierObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865E90(objectIndex);
			return __result;
		}

		_extern bool _sub_10865D30(long);
		bool IsGarbageCollectionObject(long objectIndex) // 0x10865D30
		{
			mangled_x86(MANGLED_TODO, "?IsGarbageCollectionObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865D30(objectIndex);
			return __result;
		}

		_extern bool _sub_10865DE0(long);
		bool IsKillVolumeObject(long objectIndex) // 0x10865DE0
		{
			mangled_x86(MANGLED_TODO, "?IsKillVolumeObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865DE0(objectIndex);
			return __result;
		}

		_extern bool _sub_10865FF0(long);
		bool IsPrematchCameraObject(long objectIndex) // 0x10865FF0
		{
			mangled_x86(MANGLED_TODO, "?IsPrematchCameraObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865FF0(objectIndex);
			return __result;
		}

		_extern bool _sub_10865F40(long);
		bool IsPodiumPointObject(long objectIndex) // 0x10865F40
		{
			mangled_x86(MANGLED_TODO, "?IsPodiumPointObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;
			todo("implement");
			bool __result = _sub_10865F40(objectIndex);
			return __result;
		}

		_extern bool _sub_10865C00(long);
		bool IsActiveTeamBarrierObject(long objectIndex) // 0x10865C00
		{
			mangled_x86(MANGLED_TODO, "?IsActiveTeamBarrierObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_multiplayer_object_properties *multiplayer_properties;
			// Forge::ReforgeObjectProperties *reforge_properties;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			todo("implement");
			bool __result = _sub_10865C00(objectIndex);
			return __result;
		}

		_extern bool _sub_10866110(long, long);
		bool TeamBarrierTestPlayer(long barrierObjectIndex, long playerIndex) // 0x10866110
		{
			mangled_x86(MANGLED_TODO, "?TeamBarrierTestPlayer@Reforge@Forge@@YA_NJJ@Z");
			// long playerIndex;
			// s_multiplayer_object_properties *multiplayer_properties;
			// long team_designator;
			// Forge::ReforgeObjectProperties *reforge_properties;
			// function call : bool (*const)()
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			// function call : c_game_engine *(*const)()
			todo("implement");
			bool __result = _sub_10866110(barrierObjectIndex, playerIndex);
			return __result;
		}

		_extern bool _sub_10866280(long, long);
		bool TeamBarrierTestUnit(long barrierObjectIndex, long unitIndex) // 0x10866280
		{
			mangled_x86(MANGLED_TODO, "?TeamBarrierTestUnit@Reforge@Forge@@YA_NJJ@Z");
			// long unitIndex;
			// s_unit_data *unit;
			// long player_index;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			todo("implement");
			bool __result = _sub_10866280(barrierObjectIndex, unitIndex);
			return __result;
		}

		_extern bool _sub_10866360(long, __int32);
		bool ValidRenderMaterialIndex(long objectIndex, __int32 index) // 0x10866360
		{
			mangled_x86(MANGLED_TODO, "?ValidRenderMaterialIndex@Reforge@Forge@@YA_NJH@Z");
			// __int32 index;
			// s_object_data *object;
			// s_model_definition *modelDef;
			// s_object_definition *objectDef;
			// s_render_model *renderModel;
			// function call : void *(*const)(unsigned long, long)
			// function call : void *(*const)(unsigned long, long)
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			bool __result = _sub_10866360(objectIndex, index);
			return __result;
		}

		_extern short _sub_10865930(long, Forge::Reforge::SRenderMaterialParameters *);
		short GetRenderMaterialOverride(long objectIndex, Forge::Reforge::SRenderMaterialParameters *parameters) // 0x10865930
		{
			mangled_x86(MANGLED_TODO, "?GetRenderMaterialOverride@Reforge@Forge@@YAFJPAUSRenderMaterialParameters@12@@Z");
			// Forge::Reforge::SRenderMaterialParameters *parameters;
			// s_multiplayer_object_properties *multiplayerProperties;
			// unsigned char material_index;
			{
				// Forge::ReforgeObjectProperties *reforgeProperties;
				// float kByteToFixedFloat;
			}
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			todo("implement");
			short __result = _sub_10865930(objectIndex, parameters);
			return __result;
		}
	}
}

/* ---------- private code */

namespace Forge
{
	namespace Reforge
	{
		_extern long _sub_108666E0(long);
		long get_controlling_unit(long unit_index) // 0x108666E0
		{
			// Forge::Reforge::get_controlling_unit
			// long unit_index;
			// long object_index;
			// s_unit_data *root_unit;
			// function call : long (*)(long)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			todo("implement");
			long __result = _sub_108666E0(unit_index);
			return __result;
		}
	}
}

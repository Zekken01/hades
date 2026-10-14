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
namespace hades_file_local
{
	struct SReforgeGlobals;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct SReforgeGlobals
	{
		std::bitset<65535> ReforgeObjects; // 0x0
		SReforgeGlobals(); /* compiler_generated() */
	};
	static_assert(sizeof(SReforgeGlobals) == 8192, "Invalid SReforgeGlobals size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x108658A0

struct s_object_data *object_get(unsigned long objectIndex);  // hades: added for 0X108660A0

struct s_forge_globals_definition *forge_globals_get_definition();  // hades: added for 0X10865E90
struct s_object_data *object_get(unsigned long object_index);  // hades: added for 0X10865E90

s_object_data *object_get(unsigned long object_index);  // hades: added for 0X10865F40

s_forge_globals_definition *forge_globals_get_definition();  // hades: added for 0X10865D30
s_object_data *object_get(unsigned long objectIndex);  // hades: added for 0X10865D30

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

s_render_model *GeObjectRenderModel(long objectTagIndex);

/* ---------- globals */

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10866110
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0X10866360
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0X108657A0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);

/* ---------- private variables */

namespace hades_file_local
{
	extern SReforgeGlobals reforgeGlobals; // 0x123AC800
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace Reforge
	{
		void InitializeForNewMap() // 0x10865AD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@Reforge@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_forge_globals_definition *forge_globals;
				// c_tag_block<s_tag_reference> &<range>$L0;
				// s_tag_reference *<begin>$L0;
				// s_tag_reference *<end>$L0;
					// s_tag_reference &reforgeObject;
						// s_render_model *renderModel;

			reforgeGlobals.ReforgeObjects.reset();
			s_forge_globals_definition *forge_globals = forge_globals_get_definition();
			if (!forge_globals)
				return;
			for (s_tag_reference &reforgeObject : forge_globals->reforge_objects)
			{
				if (!tag_loaded(reforgeObject.index))
					continue;
				s_render_model *renderModel = GeObjectRenderModel(reforgeObject.index);
				if (!renderModel)
					continue;
				if (forge_globals->materials.count > 0)
					renderModel->materials = reinterpret_cast<decltype(renderModel->materials) &>(forge_globals->materials);
				reforgeGlobals.ReforgeObjects.set(reforgeObject.index);
			}
		}

		bool IsReforgeObject(long objectIndex) // 0x108660A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsReforgeObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_object_data *object;

			s_object_data *object = object_get(objectIndex);
			if (!object)
			{
				return false;
			}
			return reforgeGlobals.ReforgeObjects.test(object->definition_index);
		}

		bool IsForgeScenery(long objectIndex) // 0x10865CC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgeScenery@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_object_data *object;

			s_object_data *object = object_get(objectIndex);
			if (!object)
			{
				return false;
			}
			return reforgeGlobals.ReforgeObjects.test(object->definition_index);
		}
	}
}

namespace Forge
{

}

namespace Forge
{
	namespace Reforge
	{
		Forge::ReforgeObjectProperties *GetReforgeObject(long objectIndex) // 0x108658A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetReforgeObject@Reforge@Forge@@YAPAUReforgeObjectProperties@2@J@Z");
			// long objectIndex;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)

			if (!Forge::Reforge::IsReforgeObject(objectIndex))
			{
				return nullptr;
			}

			return (Forge::ReforgeObjectProperties *)&object_get_multiplayer(objectIndex)->boundry_width;
		}

		bool IsMapModifierObject(long objectIndex) // 0x10865E90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsMapModifierObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;

			s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
			if (!forgeGlobals)
				return false;
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return false;
			return object->definition_index == forgeGlobals->map_modifier_object.index;
		}

		bool IsGarbageCollectionObject(long objectIndex) // 0x10865D30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsGarbageCollectionObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;

			s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
			if (!forgeGlobals)
				return false;
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return false;
			return object->definition_index == forgeGlobals->garbage_volume_object.index;
		}

		bool IsKillVolumeObject(long objectIndex) // 0x10865DE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsKillVolumeObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;

			s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
			if (!forgeGlobals)
				return false;
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return false;
			return object->definition_index == forgeGlobals->kill_volume_object.index;
		}

		bool IsPrematchCameraObject(long objectIndex) // 0x10865FF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsPrematchCameraObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;

			s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
			if (!forgeGlobals)
				return false;
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return false;
			return object->definition_index == forgeGlobals->prematch_camera_object.index;
		}

		bool IsPodiumPointObject(long objectIndex) // 0x10865F40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsPodiumPointObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_forge_globals_definition *forgeGlobals;
			// s_object_data *object;

			s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
			if (!forgeGlobals)
				return false;
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return false;
			return object->definition_index == forgeGlobals->podium_placement_object.index;
		}

		bool IsActiveTeamBarrierObject(long objectIndex) // 0x10865C00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsActiveTeamBarrierObject@Reforge@Forge@@YA_NJ@Z");
			// long objectIndex;
			// s_multiplayer_object_properties *multiplayer_properties;
			// Forge::ReforgeObjectProperties *reforge_properties;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)

			s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(objectIndex);
			if (!multiplayer_properties)
			{
				return false;
			}

			Forge::ReforgeObjectProperties *reforge_properties = (Forge::ReforgeObjectProperties *)&multiplayer_properties->boundry_width;
			return reforge_properties->TeamBarrier != 0;
		}

		bool TeamBarrierTestPlayer(long barrierObjectIndex, long playerIndex) // 0x10866110
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TeamBarrierTestPlayer@Reforge@Forge@@YA_NJJ@Z");
			// long playerIndex;
			// s_multiplayer_object_properties *multiplayer_properties;
			// long team_designator;
			// Forge::ReforgeObjectProperties *reforge_properties;
			// function call : bool (*const)()
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			// function call : c_game_engine *(*const)()

			if (!game_is_multiplayer())
			{
				return false;
			}

			if (!Forge::Reforge::IsReforgeObject(barrierObjectIndex))
			{
				return false;
			}

			s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(barrierObjectIndex);

			if (!multiplayer_properties)
			{
				return false;
			}

			Forge::ReforgeObjectProperties *reforge_properties = (Forge::ReforgeObjectProperties *)&multiplayer_properties->boundry_width;

			if (!reforge_properties->TeamBarrier)
			{
				return false;
			}

			if (!((c_game_engine *(*)())0x5CE150)())
			{
				return false;
			}

			long team_designator = game_engine_get_team_designator(playerIndex);

			return (reforge_properties->TeamBarrier & (1 << team_designator)) || (reforge_properties->TeamBarrier == 0xFF && team_designator == 8);
		}

		bool TeamBarrierTestUnit(long barrierObjectIndex, long unitIndex) // 0x10866280
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TeamBarrierTestUnit@Reforge@Forge@@YA_NJJ@Z");
			// long unitIndex;
			// s_unit_data *unit;
			// long player_index;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unitIndex, 0x2003);

			if (!unit)
			{
				return false;
			}

			unitIndex = Forge::Reforge::get_controlling_unit(unitIndex);

			if (unitIndex == -1)
			{
				return false;
			}

			long player_index = unit_get_current_or_last_weak_player_index(unitIndex);

			if (player_index == -1)
			{
				return false;
			}

			return Forge::Reforge::TeamBarrierTestPlayer(barrierObjectIndex, player_index);
		}

		bool ValidRenderMaterialIndex(long objectIndex, __int32 index) // 0x10866360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ValidRenderMaterialIndex@Reforge@Forge@@YA_NJH@Z");
			// __int32 index;
			// s_object_data *object;
			// s_model_definition *modelDef;
			// s_object_definition *objectDef;
			// s_render_model *renderModel;
			// function call : void *(*const)(unsigned long, long)
			// function call : void *(*const)(unsigned long, long)
			// function call : void *(*const)(unsigned long, long)

			s_object_data *object = object_get(objectIndex);

			if (!object)
			{
				return false;
			}

			s_object_definition *objectDef = (s_object_definition *)tag_get(0x6F626A65, object->definition_index);
			s_model_definition *modelDef = (s_model_definition *)tag_get(0x686C6D74, objectDef->model.index);
			s_render_model *renderModel = (s_render_model *)tag_get(0x6D6F6465, modelDef->render_model.index);

			return index >= 0 && index < renderModel->materials.count;
		}

		short GetRenderMaterialOverride(long objectIndex, Forge::Reforge::SRenderMaterialParameters *parameters) // 0x10865930
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetRenderMaterialOverride@Reforge@Forge@@YAFJPAUSRenderMaterialParameters@12@@Z");
			// Forge::Reforge::SRenderMaterialParameters *parameters;
			// s_multiplayer_object_properties *multiplayerProperties;
			// unsigned char material_index;
				// Forge::ReforgeObjectProperties *reforgeProperties;
				// float kByteToFixedFloat;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)

			if (!IsReforgeObject(objectIndex))
				return -1;
			s_multiplayer_object_properties *multiplayerProperties = object_get_multiplayer(objectIndex);
			unsigned char material_index = multiplayerProperties->teleporter_channel;
			if (material_index == 0xFF)
				return -1;
			if (!ValidRenderMaterialIndex(objectIndex, material_index))
				return -1;
			if (parameters)
			{
				Forge::ReforgeObjectProperties *reforgeProperties = (Forge::ReforgeObjectProperties *)&multiplayerProperties->boundry_width;
				float kByteToFixedFloat = 1.0f / 255.0f;
				parameters->customTextureMode = reforgeProperties->Flags & Forge::ReforgeObjectProperties::MaterialOverrideTextureCoords;
				if (parameters->customTextureMode)
				{
					parameters->textureScale = 1.0f / (reforgeProperties->TextureData.Scale * kByteToFixedFloat * 4.0f);
					parameters->textureOffsetU = reforgeProperties->TextureData.OffsetX * kByteToFixedFloat;
					parameters->textureOffsetV = reforgeProperties->TextureData.OffsetY * kByteToFixedFloat;
				}
			}
			return material_index;
		}
	}
}

/* ---------- private code */

namespace Forge
{
	namespace Reforge
	{
		long get_controlling_unit(long unit_index) // 0x108666E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?get_controlling_unit@Reforge@Forge@@YAJJ@Z");
			// Forge::Reforge::get_controlling_unit
			// long unit_index;
			// long object_index;
			// s_unit_data *root_unit;
			// function call : long (*)(long)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

			long object_index = ((long(__cdecl *)(long))0x58f590)(unit_index);

			s_unit_data *root_unit = (s_unit_data *)object_try_and_get_and_verify_type(object_index, 0x2003);

			if (!root_unit)
			{
				return 0;
			}

			if (root_unit->motion_control_unit_index == -1)
			{
				return unit_index;
			}

			return root_unit->motion_control_unit_index;
		}
	}
}

s_render_model *GeObjectRenderModel(long objectTagIndex) // 0x108657A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GeObjectRenderModel@@YAPAUs_render_model@@J@Z");
	// `anonymous-namespace'::GeObjectRenderModel
	// long objectTagIndex;
	// s_object_definition *objectDef;
	// s_model_definition *model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	s_object_definition *objectDef = (s_object_definition *)tag_get(0x6F626A65, objectTagIndex);

	if (!objectDef)
	{
		return nullptr;
	}

	s_model_definition *model = (s_model_definition *)tag_get(0x686C6D74, objectDef->model.index);

	if (!model)
	{
		return nullptr;
	}

	return (s_render_model *)tag_get(0x6D6F6465, model->render_model.index);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_tag_reference * c_tag_block<s_tag_reference>::begin();
template s_tag_reference * c_tag_block<s_tag_reference>::end();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { SReforgeGlobals reforgeGlobals; }

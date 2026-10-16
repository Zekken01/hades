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
#include "Forge/Reforge.hpp"
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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const game_engine_is_player_in_edit_mode = reinterpret_cast<bool (*)(long, long *, long *)>(0x59A6F0);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const object_get_world_matrix = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long (*)(long)>(0x589C30);
}

extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x10974440

extern real_vector3d *vector_from_points3d(real_point3d const *p0, real_point3d const *p1, real_vector3d *v);  // hades: added for 0x10973C00
extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x10973C00

namespace Forge { extern void DeleteObject(long player_index, long map_variant_index); }  // hades: added for 0x109741D0

extern s_object_data *object_get(unsigned long object_index);  // hades: added for 0x10974330
namespace Forge { extern s_map_variant *GetMapVariant(); }  // hades: added for 0x10974330
extern char const *tag_get_name(long tag_index);  // hades: added for 0x10974F60

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

}

namespace Forge
{
	namespace Selection
	{
		Forge::ObjectSet &GetSelection() // 0x109749C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSelection@Selection@Forge@@YAAAVObjectSet@2@XZ");

			return s_SelectedObjects;
		}
	}
}

namespace Forge
{
	bool IsEmpty() // 0x10974B50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsEmpty@Forge@@YA_NXZ");

		return !s_SelectedObjects.Any();
	}

	long GetCurrentObjectIndex(long playerIndex) // 0x109748B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCurrentObjectIndex@Forge@@YAJJ@Z");

		long heldObjectIndex;
		long crosshairObjectIndex;

		if (!((bool(__cdecl *)(long, long *, long *))0x59a6f0)(playerIndex, &heldObjectIndex, &crosshairObjectIndex))
		{
			return -1;
		}

		return heldObjectIndex != -1 ? heldObjectIndex : crosshairObjectIndex;
	}
}

namespace Forge
{
	namespace Selection
	{
		void SelectAll() // 0x10974C40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SelectAll@Selection@Forge@@YAXXZ");

			unsigned long playerIndex = ((unsigned long(__cdecl *)(long))0x589C30)(0);
			s_object_data *currentObject = object_get(GetCurrentObjectIndex(playerIndex));
			if (!currentObject)
			{
				return;
			}

			s_map_variant *const mapv = GetMapVariant();
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (placement.object_index == -1 || placement.quota_index == -1)
				{
					continue;
				}

				if (mapv->object_quotas[placement.quota_index].definition_index == currentObject->definition_index)
				{
					s_SelectedObjects.Add(placement.object_index);
				}
			}
		}
	}
}

namespace Forge
{
	// mangled_x86(MANGLED_DEFAULT, "??0ObjectSet@Forge@@QAE@XZ"); no body to assert in
}

// mangled_x86(MANGLED_DEFAULT, "??0c_object_identifier@@QAE@ABU0@@Z"); no body to assert in
// c_object_identifier::c_object_identifier(c_object_identifier const &__that) is implicit; 0x109734F0

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant_placement_properties@@QAE@ABU0@@Z"); no body to assert in
// _inline s_map_variant_placement_properties::s_map_variant_placement_properties(s_map_variant_placement_properties const &__that) = default; // 0x109735C0

// mangled_x86(MANGLED_DEFAULT, "??0s_variant_datum@@QAE@ABU0@@Z"); no body to assert in
_inline s_variant_datum::s_variant_datum(s_variant_datum const &__that) = default; // 0x109736F0

namespace Forge
{
	namespace Selection
	{
		void SelectEverything() // 0x10974F60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SelectEverything@Selection@Forge@@YAXXZ");

			s_map_variant *const mapv = GetMapVariant();
			s_SelectedObjects.Clear();
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (!placement.flags.test(_map_variant_occupied_slot_bit))
					continue;
				s_variant_quota &budget = mapv->object_quotas[placement.quota_index];
				if (budget.definition_index == -1 || budget.cost == -1.0f)
					continue;
				char const *tagName = tag_get_name(budget.definition_index);
				if (tagName && !_stricmp(tagName, "objects\\multi\\spawning\\respawn_point_invisible"))
					continue;
				if (placement.object_index != -1)
					s_SelectedObjects.Add(placement.object_index);
			}
		}

		void SelectAllMaterial() // 0x10974D50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SelectAllMaterial@Selection@Forge@@YAXXZ");

			unsigned long playerIndex = ((unsigned long (*)(long))0x589C30)(0);
			s_object_data *currentObject = object_get(GetCurrentObjectIndex(playerIndex));
			if (!(currentObject && currentObject->map_variant_index != -1))
				return;
			s_map_variant *const mapv = GetMapVariant();
			s_variant_datum currentObjectPlacement = static_cast<s_variant_datum const &>(mapv->objects[currentObject->map_variant_index]);
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (!(placement.flags.test(_map_variant_occupied_slot_bit) && placement.object_index != -1))
					continue;
				if (Reforge::IsReforgeObject(placement.object_index) && placement.properties.shared_storage == currentObjectPlacement.properties.shared_storage)
					s_SelectedObjects.Add(placement.object_index);
			}
		}

		void DeselectAllOf() // 0x10974330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DeselectAllOf@Selection@Forge@@YAXXZ");

			unsigned long playerIndex = ((unsigned long(__cdecl *)(long))0x589C30)(0);
			s_object_data *currentObject = object_get(GetCurrentObjectIndex(playerIndex));
			if (!currentObject)
			{
				return;
			}

			s_map_variant *const mapv = GetMapVariant();
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (placement.object_index == -1 || placement.quota_index == -1)
				{
					continue;
				}

				if (mapv->object_quotas[placement.quota_index].definition_index == currentObject->definition_index)
				{
					s_SelectedObjects.Remove(placement.object_index);
				}
			}
		}

		void Invert() // 0x109749E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Invert@Selection@Forge@@YAXXZ");

			ObjectSet newSelection;
			s_map_variant *mapv = GetMapVariant();
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (placement.object_index != -1 && !s_SelectedObjects.Contains(placement.object_index))
					newSelection.Add(placement.object_index);
			}
			s_SelectedObjects = newSelection;
		}

		void Expand(float amount) // 0x10974440
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Expand@Selection@Forge@@YAXM@Z");

			s_map_variant *const mapv = GetMapVariant();
			real_point3d centroid = { 0.0f, 0.0f, 0.0f };
			real_point3d min = { mapv->world_bounds.x0, mapv->world_bounds.y0, mapv->world_bounds.z0 };
			real_point3d max = { mapv->world_bounds.x1, mapv->world_bounds.y1, mapv->world_bounds.z1 };
			__int32 selectedObjectCount = 0;
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (placement.object_index != -1 && s_SelectedObjects.Contains(placement.object_index))
				{
					centroid.x += placement.position.x;
					centroid.y += placement.position.y;
					centroid.z += placement.position.z;
					if (min.x > placement.position.x)
						min.x = placement.position.x;
					if (min.y > placement.position.y)
						min.y = placement.position.y;
					if (min.z > placement.position.z)
						min.z = placement.position.z;
					if (placement.position.x > max.x)
						max.x = placement.position.x;
					if (placement.position.y > max.y)
						max.y = placement.position.y;
					if (placement.position.z > max.z)
						max.z = placement.position.z;
					selectedObjectCount++;
				}
			}
			if (!selectedObjectCount)
				return;
			float s = 1.0f / selectedObjectCount;
			centroid.x *= s;
			centroid.y *= s;
			centroid.z *= s;
			float radius2 = distance_squared3d(&min, &max) * 0.5f + amount;
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (placement.object_index == -1 || s_SelectedObjects.Contains(placement.object_index))
					continue;
				if (radius2 > distance_squared3d(&placement.position, &centroid))
					s_SelectedObjects.Add(placement.object_index);
			}
		}

		void Clear() // 0x10973BB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@Selection@Forge@@YAXXZ");

					s_SelectedObjects.Clear();
		}

		void Delete() // 0x109741D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Delete@Selection@Forge@@YAXXZ");

			s_map_variant *mapv = GetMapVariant();
			if (!mapv)
				return;
			unsigned long playerHandle = ((unsigned long(*)(long))0x589C30)(0);
			if (playerHandle == -1)
				return;
			unsigned long objectIndex = get_sandbox_globals()->player_cursor_object_index[playerHandle & 0xF];
			s_object_data *object = object_get(objectIndex);
			if (!object)
				return;
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				if (!placement.flags.test(_map_variant_occupied_slot_bit))
					continue;
				auto &quota = mapv->object_quotas[placement.quota_index];
				if (quota.definition_index != object->definition_index)
					continue;
				Forge::DeleteObject(playerHandle & 0xFFFF, i);
			}
		}

		bool Clone() // 0x10973C00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Clone@Selection@Forge@@YA_NXZ");

			unsigned __int32 (__thiscall *const spawn_object)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short) = reinterpret_cast<unsigned __int32 (__thiscall *)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short)>(0x582110);
			std::stack<unsigned int> cloneStack;
			s_map_variant *mapv = game_engine_get_runtime_map_variant();
			for (__int32 i = 0; i < 640; i++)
			{
				s_variant_datum const &placement = mapv->objects[i];
				if (!placement.flags.test(_map_variant_occupied_slot_bit) || placement.object_index == -1)
					continue;
				Forge::ObjectSet const &selection = Forge::Selection::GetSelection();
				if (selection.Contains(placement.object_index))
					cloneStack.push(placement.object_index);
			}
			if (cloneStack.empty())
				return false;
			s_object_data *referenceObject = object_get(cloneStack.top());
			if (!referenceObject)
				return false;
			unsigned long playerHandle = eldorado::player_mapping_get_player_by_input_user(0);
			if (playerHandle == -1)
				return false;
			Forge::ObjectSet &selection = Forge::Selection::GetSelection();
			selection.Clear();
			real_point3d const &crosshairPoint = get_sandbox_globals()->player_cursor_position[playerHandle & 0xF];
			real_point3d const &referencePoint = referenceObject->relative_position;
			while (!cloneStack.empty())
			{
				long object_index = cloneStack.top();
				cloneStack.pop();
				s_object_data *object = object_get(object_index);
				if (!object)
					continue;
				real_matrix4x3 object_world_matrix;
				eldorado::object_get_world_matrix(object_index, &object_world_matrix);
				s_map_variant_placement_properties *variantProperties = nullptr;
				if (object->map_variant_index != -1)
					variantProperties = &mapv->objects[object->map_variant_index].properties;
				real_vector3d crosshair_offset;
				vector_from_points3d(&object_world_matrix.position, &crosshairPoint, &crosshair_offset);
				real_vector3d reference_offset;
				vector_from_points3d(&referencePoint, &object_world_matrix.position, &reference_offset);
				real_point3d new_position = object_world_matrix.position + crosshair_offset + reference_offset;
				long new_object_index = spawn_object(mapv, object->definition_index, 0, -1, &new_position, &object_world_matrix.forward, &object_world_matrix.up, -1, -1, variantProperties, 0);
				if (new_object_index != -1)
					selection.Add(new_object_index);
			}
			return true;
		}

		void Update() // 0x109750C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@Selection@Forge@@YAXXZ");

			unsigned long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
			long heldObjectIndex;
			long crosshairObjectIndex;
			if (!eldorado::game_engine_is_player_in_edit_mode(playerIndex, &heldObjectIndex, &crosshairObjectIndex))
				return;
			Blam::Input::ActionState *fireRight = GetActionState(eGameActionFireRight);
			if (heldObjectIndex != -1)
				return;
			static bool s_IsPaintSelecting = false;
			if (!(fireRight->Flags & eActionStateFlagsHandled) && fireRight->Ticks > 0)
			{
				if (fireRight->Ticks == 1 && crosshairObjectIndex == -1)
					s_IsPaintSelecting = true;
				if (crosshairObjectIndex != -1 && (fireRight->Ticks == 1 || s_IsPaintSelecting))
				{
					Forge::ObjectSet &selection = GetSelection();
					if (selection.Contains(crosshairObjectIndex) && !s_IsPaintSelecting)
						selection.Remove(crosshairObjectIndex);
					else
						selection.Add(crosshairObjectIndex);
				}
			}
			else
			{
				s_IsPaintSelecting = false;
			}
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { Forge::ObjectSet s_SelectedObjects; }

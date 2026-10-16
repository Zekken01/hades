/* ---------- headers */

#include "hades/hades.h"

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
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct real_point3d;
struct s_object_data;
struct s_player_datum;
struct s_rasterizer_globals;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Mods {}
using namespace ::Mods;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Vision {}
	using namespace Patches::Vision;
	namespace Camera {}
	using namespace Patches::Camera;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const object_get_origin = reinterpret_cast<void (*)(long, real_point3d *)>(0xB2E5A0);
	static auto const player_mapping_get_player_by_output_user = reinterpret_cast<unsigned long (*)(long)>(0x589C60);
	static auto const player_mapping_get_player_by_output_user_2 = reinterpret_cast<long (*)(long)>(0x589C60);
}

#include "Blam/game/game_globals.hpp"  // hades: added for 0x108F94B0
#include "Blam/camera/camera.hpp"  // hades: added for 0x108F94B0
namespace Patches { namespace Camera { extern e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x108F94B0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x108F8EF0
extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x108F8EF0
extern bool unit_has_vision(long unit_index);  // hades: added for 0x108F8EF0

#include "mods/ModGlobals.hpp"  // hades: added for 0x108F93D0
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x108F93D0

namespace Patches
{
	namespace Vision
	{
		extern void ApplyAll();
	}
}

void *get_weapon_outline_mask_hook(unsigned long group_tag, long tag_index);
void vision_mode_render_submit_mask_hook(__int32 sampler, long bitmap_group_index, long bitmap_index);
void vision_submit_shader_constants4_hook(__int32 startRegister, __int32 rows, float *data);
void vision_mode_submit_objects_hook(long window_index, long player_index, long unit_index, void const *window_data, long const *object_indices, long object_count, bool pass);
void vision_generate_depth_buffer_clear_hook(long flags, __int32 color, float inverseZ, unsigned char stencil);
void *get_player_vision_mode_globals(long player_index);
void *vision_mode_definition_tag_get_hook(long group_tag, long index);
bool chud_vision_proximity_test_player(real_point3d const *our_position, long player_index);
bool chud_vision_proximity_test_hook();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Vision
	{
		void ApplyAll() // 0x108F7FE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Vision@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x10E5660, vision_submit_shader_constants4_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x62E7FB, vision_mode_submit_objects_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x62E836, vision_mode_submit_objects_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E568B, vision_mode_render_submit_mask_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E6B40, vision_mode_render_submit_mask_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x62E81D, vision_generate_depth_buffer_clear_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x68E5A1, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E3707, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E3BFC, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E3CDB, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E40FC, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10E57FC, vision_mode_definition_tag_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x68E460, chud_vision_proximity_test_hook).Apply();
			Hook(0x10E57FC, get_weapon_outline_mask_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

void *get_weapon_outline_mask_hook(unsigned long group_tag, long tag_index) // 0x108F9270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_weapon_outline_mask_hook@@YAPAXKJ@Z");
	// `anonymous-namespace'::get_weapon_outline_mask_hook
	// long tag_index;
	// long our_player_index;
	// function call : unsigned long (*const)(long)

	int our_player_index = ((int(__cdecl *)(int))0x589c60)(0);
	return get_player_vision_mode_globals(our_player_index);
}

void vision_mode_render_submit_mask_hook(__int32 sampler, long bitmap_group_index, long bitmap_index) // 0x108F94B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vision_mode_render_submit_mask_hook@@YAXHJJ@Z");
	// `anonymous-namespace'::vision_mode_render_submit_mask_hook
	// static ...; // 0x108F9634
	// __int32 sampler;
	// long bitmap_group_index;
	// long bitmap_index;
	// __int32 (*const unit_use_third_person_camera)(unsigned long, __int32 *);
	// s_player_datum *our_player;
	// void (*const rasterizer_set_bitmap)(__int32, unsigned __int32, __int32);
	// long our_player_index;
	// __int32 a2;
		// s_rasterizer_globals *rasg;
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : __int32 (*const)(unsigned long, __int32 *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(__int32, unsigned __int32, __int32)

	void (*const rasterizer_set_bitmap)(__int32, unsigned __int32, __int32) = reinterpret_cast<void (*)(__int32, unsigned __int32, __int32)>(0xA3D130);
	__int32 (*const unit_use_third_person_camera)(unsigned long, __int32 *) = reinterpret_cast<__int32 (*)(unsigned long, __int32 *)>(0x5917E0);
	long our_player_index = ((long (*)(long))0x589C60)(0);
	__int32 a2;
	if (Forge::CForgeVisionRenderer::IsActive())
		bitmap_group_index = Forge::CForgeVisionRenderer::GetMaskBitmap(&bitmap_index);
	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_flying)
		bitmap_group_index = -1;
	s_player_datum *our_player = player_get(our_player_index);
	if (object_try_and_get_and_verify_type(our_player->unit_index, 0x2003) && unit_use_third_person_camera(our_player->unit_index, &a2) == 1)
		bitmap_group_index = -1;
	if (bitmap_group_index == -1)
	{
		s_rasterizer_globals *rasg = (s_rasterizer_globals *)tag_get('rasg', game_globals_get()->RasterizerGlobals.index);
		bitmap_group_index = rasg->default_bitmaps[0].bitmap.index;
	}
	rasterizer_set_bitmap(sampler, bitmap_group_index, bitmap_index);
}

void vision_submit_shader_constants4_hook(__int32 startRegister, __int32 rows, float *data) // 0x108F9780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vision_submit_shader_constants4_hook@@YAXHHPAM@Z");
	// `anonymous-namespace'::vision_submit_shader_constants4_hook
	// float *data;
	// void (*const set_pixel_shader_constant)(long, long, float *);
	// function call : void (*const)(long, long, float *)

	const auto vision_submit_shader_constants4 = (void(*)(__int32, __int32, float *))0xA66270;

	if (Forge::CForgeVisionRenderer::IsActive())
	{
		Forge::CForgeVisionRenderer::GetVisionColors((real_argb_color *)data);
	}

	vision_submit_shader_constants4(startRegister, rows, data);
}

void vision_mode_submit_objects_hook(long window_index, long player_index, long unit_index, void const *window_data, long const *object_indices, long object_count, bool pass) // 0x108F96C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vision_mode_submit_objects_hook@@YAXJJJPBXPBJJ_N@Z");
	// `anonymous-namespace'::vision_mode_submit_objects_hook
	// bool pass;
	// void (*const vision_mode_submit_objects)(long, long, long, void const *, long const *, long, bool);
	// function call : void (*const)(long, long, long, void const *, long const *, long, bool)

	const auto vision_mode_submit_objects = (void(*)(long, long, long, void const *, long const *, long, bool))0xA2C7D0;

	if (Forge::CForgeVisionRenderer::IsActive())
	{
		Forge::CForgeVisionRenderer::Generate(window_index, player_index, unit_index, window_data, pass);
	}
	else
	{
		vision_mode_submit_objects(window_index, player_index, unit_index, window_data, object_indices, object_count, pass);
	}
}

void vision_generate_depth_buffer_clear_hook(long flags, __int32 color, float inverseZ, unsigned char stencil) // 0x108F9340
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vision_generate_depth_buffer_clear_hook@@YAXJHME@Z");
	// `anonymous-namespace'::vision_generate_depth_buffer_clear_hook
	// unsigned char stencil;
	// function call : void (*const)(long, __int32, float, unsigned char)

	if (Forge::CForgeVisionRenderer::IsActive() && !Forge::CForgeVisionRenderer::VisibleThroughWalls())
	{
	}
	else
	{
		((void(__cdecl *)(long, __int32, float, unsigned char))0xa213f0)(flags, color, inverseZ, stencil);
	}
}

void *get_player_vision_mode_globals(long player_index) // 0x108F9170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_vision_mode_globals@@YAPAXJ@Z");
	// `anonymous-namespace'::get_player_vision_mode_globals
	// long player_index;
	// long definition_index;
		// s_player_datum *player;
		// s_rasterizer_globals *rasg;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	long definition_index = -1;
	if (player_index != -1)
	{
		s_player_datum *player = player_get(player_index);
		if (player)
		{
			definition_index = Mods::CModGlobals::GetCharacterVisionModeGlobals(player->character_type_index);
		}
	}

	if (definition_index == -1)
	{
		s_rasterizer_globals *rasg = (s_rasterizer_globals *)tag_get('rasg', game_globals_get()->RasterizerGlobals.index);
		definition_index = rasg->default_vision_mode.index;
	}

	return tag_get('vmdx', definition_index);
}

void *vision_mode_definition_tag_get_hook(long group_tag, long index) // 0x108F93D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vision_mode_definition_tag_get_hook@@YAPAXJJ@Z");
	// `anonymous-namespace'::vision_mode_definition_tag_get_hook
	// long index;
	// long player_index;
		// s_player_datum *player;
			// long new_index;
	// function call : unsigned long (*const)(long)
	// function call : void *(*const)(unsigned long, long)

	long player_index = eldorado::player_mapping_get_player_by_output_user(0);
	if (player_index != -1)
	{
		s_player_datum *player = player_get(player_index);
		if (player && player->character_type_index != -1)
		{
			long new_index = Mods::CModGlobals::GetCharacterVisionModeGlobals(player->character_type_index);
			if (new_index != -1)
			{
				index = new_index;
			}
		}
	}

	return tag_get(group_tag, index);
}

bool chud_vision_proximity_test_player(real_point3d const *our_position, long player_index) // 0x108F8EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_vision_proximity_test_player@@YA_NPBUreal_point3d@@J@Z");
	// `anonymous-namespace'::chud_vision_proximity_test_player
	// static ...; // 0x108F9040
	// static ...; // 0x108F9038
	// real_point3d const *our_position;
	// long player_index;
	// s_player_datum *player;
	// void *vision_mode_def;
	// float max_distance;
	// real_point3d their_position;
	// float distance;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)

	void *vision_mode_def = get_player_vision_mode_globals(player_index);
	if (!vision_mode_def)
		return false;

	s_player_datum *player = player_get(player_index);
	if (!object_try_and_get_and_verify_type(player->unit_index, 0x2003))
		return false;
	if (!unit_has_vision(player->unit_index))
		return false;

	real_point3d their_position;
	((void (__cdecl *)(long, real_point3d *))0xB2E5A0)(player->unit_index, &their_position);
	float max_distance = *(float *)((char *)vision_mode_def + 8);
	float distance = distance_squared3d(our_position, &their_position);
	return max_distance >= distance;
}

bool chud_vision_proximity_test_hook() // 0x108F8D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_vision_proximity_test_hook@@YA_NXZ");
	// `anonymous-namespace'::chud_vision_proximity_test_hook
	// procedure flags: nofpo
	// static ...; // 0x108F8E83
	// static ...; // 0x108F8E80
	// static ...; // 0x108F8E68
	// static ...; // 0x108F8E60
	// s_player_datum *our_player;
	// long our_player_index;
	// c_data_array<s_player_datum> *players;
	// real_point3d our_position;
		// c_data_iterator<s_player_datum> it;
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)

	long our_player_index = eldorado::player_mapping_get_player_by_output_user_2(0);
	s_player_datum *our_player = player_get(our_player_index);
	if (!object_try_and_get_and_verify_type(our_player->unit_index, 0x2003))
		return false;
	real_point3d our_position;
	eldorado::object_get_origin(our_player->unit_index, &our_position);
	c_data_array<s_player_datum> *players = players_get();
	for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
	{
		if (it.current_datum_index == our_player_index)
			continue;
		if (chud_vision_proximity_test_player(&our_position, it.current_datum_index))
			return true;
	}
	return false;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_default_bitmap>::try_get_element(__int32, s_default_bitmap **) const;
template s_default_bitmap & c_tag_block<s_default_bitmap>::operator[](__int32);
template s_default_bitmap * c_tag_block<s_default_bitmap>::get_element(__int32) const;

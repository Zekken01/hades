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
		_extern void _sub_108F7FE0();
		void ApplyAll() // 0x108F7FE0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Vision@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108F7FE0();
		}
	}
}

/* ---------- private code */

_extern void *_sub_108F9270(unsigned long, long);
void *get_weapon_outline_mask_hook(unsigned long group_tag, long tag_index) // 0x108F9270
{
	// `anonymous-namespace'::get_weapon_outline_mask_hook
	// long tag_index;
	// long our_player_index;
	// function call : unsigned long (*const)(long)
	todo("implement");
	void * __result = _sub_108F9270(group_tag, tag_index);
	return __result;
}

_extern void _sub_108F94B0(__int32, long, long);
void vision_mode_render_submit_mask_hook(__int32 sampler, long bitmap_group_index, long bitmap_index) // 0x108F94B0
{
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
	{
		// s_rasterizer_globals *rasg;
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : __int32 (*const)(unsigned long, __int32 *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(__int32, unsigned __int32, __int32)
	todo("implement");
	_sub_108F94B0(sampler, bitmap_group_index, bitmap_index);
}

_extern void _sub_108F9780(__int32, __int32, float *);
void vision_submit_shader_constants4_hook(__int32 startRegister, __int32 rows, float *data) // 0x108F9780
{
	// `anonymous-namespace'::vision_submit_shader_constants4_hook
	// float *data;
	// void (*const set_pixel_shader_constant)(long, long, float *);
	// function call : void (*const)(long, long, float *)
	todo("implement");
	_sub_108F9780(startRegister, rows, data);
}

_extern void _sub_108F96C0(long, long, long, void const *, long const *, long, bool);
void vision_mode_submit_objects_hook(long window_index, long player_index, long unit_index, void const *window_data, long const *object_indices, long object_count, bool pass) // 0x108F96C0
{
	// `anonymous-namespace'::vision_mode_submit_objects_hook
	// bool pass;
	// void (*const vision_mode_submit_objects)(long, long, long, void const *, long const *, long, bool);
	// function call : void (*const)(long, long, long, void const *, long const *, long, bool)
	todo("implement");
	_sub_108F96C0(window_index, player_index, unit_index, window_data, object_indices, object_count, pass);
}

_extern void _sub_108F9340(long, __int32, float, unsigned char);
void vision_generate_depth_buffer_clear_hook(long flags, __int32 color, float inverseZ, unsigned char stencil) // 0x108F9340
{
	// `anonymous-namespace'::vision_generate_depth_buffer_clear_hook
	// unsigned char stencil;
	// function call : void (*const)(long, __int32, float, unsigned char)
	todo("implement");
	_sub_108F9340(flags, color, inverseZ, stencil);
}

_extern void *_sub_108F9170(long);
void *get_player_vision_mode_globals(long player_index) // 0x108F9170
{
	// `anonymous-namespace'::get_player_vision_mode_globals
	// long player_index;
	// long definition_index;
	{
		// s_player_datum *player;
	}
	{
		// s_rasterizer_globals *rasg;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	void * __result = _sub_108F9170(player_index);
	return __result;
}

_extern void *_sub_108F93D0(long, long);
void *vision_mode_definition_tag_get_hook(long group_tag, long index) // 0x108F93D0
{
	// `anonymous-namespace'::vision_mode_definition_tag_get_hook
	// long index;
	// long player_index;
	{
		// s_player_datum *player;
		{
			// long new_index;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	void * __result = _sub_108F93D0(group_tag, index);
	return __result;
}

_extern bool _sub_108F8EF0(real_point3d const *, long);
bool chud_vision_proximity_test_player(real_point3d const *our_position, long player_index) // 0x108F8EF0
{
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
	todo("implement");
	bool __result = _sub_108F8EF0(our_position, player_index);
	return __result;
}

_extern bool _sub_108F8D10();
bool chud_vision_proximity_test_hook() // 0x108F8D10
{
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
	{
		// c_data_iterator<s_player_datum> it;
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)
	todo("implement");
	bool __result = _sub_108F8D10();
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_default_bitmap>::try_get_element(__int32, s_default_bitmap **) const;
template s_default_bitmap & c_tag_block<s_default_bitmap>::operator[](__int32);
template s_default_bitmap * c_tag_block<s_default_bitmap>::get_element(__int32) const;

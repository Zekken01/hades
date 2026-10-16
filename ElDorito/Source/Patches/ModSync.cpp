/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/bitmaps/bitmap_definition.hpp"
#include "Blam/cache/cache_file_tag_resources.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cache/tag_iterator.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_state.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/main/loading.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/multithreading/synchronization/synchronized_int.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/RefCounting.hpp"
#include "ElDorito.hpp"
#include "mods/cache_file_interface.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/map_load_crash_recovery_helper.hpp"
#include "mods/map_load_error_helper.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_cache_tag_remapper.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "mods/tag_resource_memory_size_helper.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Core.hpp"
#include "Patches/CustomPackets.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x10928C40

#include "mods/cache_file_tags.hpp"  // hades: added for 0x10927E90

#include <format>  // hades: added for 0x109267B0
#include "Utils/Logger.hpp"  // hades: added for 0x109267B0
#include "Modules/ModuleGame.hpp"  // hades: added for 0x109267B0

#include "Interface/ErrorDialog.hpp"  // hades: added for 0x10926A30
#include "Web/Ui/ScreenLayer.hpp"  // hades: added for 0x10926A30

#include "mods/cache_file_tag_optimization.hpp"  // hades: added for 0x10925170

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
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
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

class IMod;
class c_cache_file_tag_cache;
class c_file_reference;
class c_map_load_crash_recovery_helper;
class c_mod_cache_tag_remapper;
class c_mod_package;
class c_render_method;
class c_synchronized_int32;
struct begin;
struct c_async_completion_flag;
struct c_cache_file_interface;
struct c_cache_file_tag_resource_page_handler;
struct c_game_variant;
struct c_indirect_cache_file_location_atlas;
struct c_map_load_error_helper;
struct end;
struct lambda_1;
struct s_bitmap_definition;
struct s_cache_file_header;
struct s_cache_file_resource_shared_file;
struct s_cache_file_secure_memory;
struct s_cache_file_tag_globals;
struct s_cache_file_tag_resource_cache_file_header;
struct s_cache_file_tag_resource_table;
struct s_cache_file_tag_resource_table_runtime;
struct s_cache_tag_instance;
struct s_cached_map_file;
struct s_data_array;
struct s_datum;
struct s_file_handle;
struct s_game_options;
struct s_game_player_options;
struct s_hs_syntax_node;
struct s_indirect_cache_file_page;
struct s_level_datum;
struct s_map_variant;
struct s_player_appearance;
struct s_player_configuration;
struct s_player_configuration_from_host;
struct s_scenario;
struct s_scenario_lightmap_bsp_data;
struct s_scenario_structure_bsp;
struct s_structure_collision_material;
struct s_tag_iterator;
struct s_tag_resource;
struct s_tag_resource_data;
struct s_tag_resource_page;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}
namespace hades_file_local
{
	struct s_cache_file_loaded_state;
	struct s_resource_loaded_state;
	struct c_tag_resource_control_datum;
	struct tag_resource_tracking_setup;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
	namespace ModSync {}
	using namespace Patches::ModSync;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct s_cache_file_loaded_state
	{
		c_file_reference base_cache_file; // 0x0
		c_file_reference mod_cache_file; // 0x110
		std::shared_ptr<c_cache_file_tag_cache> base_cache; // 0x220
		std::shared_ptr<c_cache_file_tag_cache> mod_cache; // 0x228
		c_mod_cache_tag_remapper tag_remapper; // 0x230
		bool loading_main_menu; // 0x2B8
		s_cache_file_loaded_state(s_cache_file_loaded_state &); /* compiler_generated() */
		s_cache_file_loaded_state(s_cache_file_loaded_state const &); /* compiler_generated() */
		s_cache_file_loaded_state(); /* compiler_generated() */
		~s_cache_file_loaded_state(); /* compiler_generated() */
		s_cache_file_loaded_state &operator=(s_cache_file_loaded_state &); /* compiler_generated() */
		s_cache_file_loaded_state &operator=(s_cache_file_loaded_state const &); /* compiler_generated() */
		unsigned char __pad0[3]; // 0x2B9
	};
	#pragma pack(pop)
	static_assert(sizeof(s_cache_file_loaded_state) == 700, "Invalid s_cache_file_loaded_state size");

	struct s_resource_loaded_state
	{
		c_mod_package *mod_cache; // 0x0
		unsigned long required_page_memory_size; // 0x4
	};
	static_assert(sizeof(s_resource_loaded_state) == 8, "Invalid s_resource_loaded_state size");
}
using namespace hades_file_local;
//class scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1>
//{
//public:
//	void operator()(long) const;
//};
//static_assert(sizeof(scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1>) == 1, "Invalid scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1> size");

namespace hades_file_local
{
	struct c_tag_resource_control_datum :
		public s_datum
	{
		unsigned short flags; // 0x2
		char state; // 0x4
		unsigned char __pad0[3]; // 0x5
		long page_handle; // 0x8
	};
	static_assert(sizeof(c_tag_resource_control_datum) == 12, "Invalid c_tag_resource_control_datum size");

	struct tag_resource_tracking_setup
	{
		long control_handle; // 0x0
		long page_handle; // 0x4
		void **controller; // 0x8
		c_tag_resource_control_datum *control_state_datum; // 0xC
		void *datum_handler; // 0x10
	};
	static_assert(sizeof(tag_resource_tracking_setup) == 20, "Invalid tag_resource_tracking_setup size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern unsigned long g_file_reference_error;  // hades: added for 0x10928210

extern bool (*const security_incremental_hash_begin)(void *, long, bool);  // hades: added for 0x10924960
extern void (*const security_incremental_hash_update)(void *, long, void const *, unsigned long);  // hades: added for 0x10924960
extern void (*const security_incremental_hash_finish)(void *, long, void *);  // hades: added for 0x10924960
extern bool (*const security_calculate_hash)(void *, long, bool, void *);  // hades: added for 0x10924960
extern bool (*const security_rsa_compute_and_verify_signature)(void const *, void *);  // hades: added for 0x10924960

extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x10924330

extern long (*const cache_file_globals_get_tag)(long);  // hades: added for 0x10924E90
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10924E90

extern bool (*const cache_file_header_verify)(s_cache_file_header *, char const *, bool);  // hades: added for 0x109289F0
extern bool (*const cache_file_open_package)(char const *, s_cache_file_header *);  // hades: added for 0x109289F0
extern void (*const cache_files_tags_reset)();  // hades: added for 0x109289F0

#include "mods/memory/physical_memory_manager.hpp"  // hades: added for 0x10924670
typedef unsigned long ulong;  // hades: added for 0x10924670

bool font_initialize_for_new_map(s_game_options *options);  // hades: added for 0X10928950

namespace Patches
{
	namespace ModSync
	{
		extern void ApplyAll();
		extern void Tick();
	}
}

extern s_cache_tag_instance *cache_tag_instance_get(long tag_index);
extern char const *tag_get_name(long tag_index);
extern long tag_find_by_name(unsigned long group_tag, char const *name);

bool fixup_mod_tag(long tag_index, s_cache_tag_instance *instance);
bool cache_file_load_tag(long tag_index);
bool cache_file_allocate_tags();
void cache_file_compute_and_verify_signature();
void cache_file_invalidate_signature();
bool cache_file_load_allocate_tags();
bool open_mod_package_resource_cache(char const *filepath);
void close_mod_package_resource_cache();
bool do_load_main_menu_mod_package();
void loader_reset();
bool load_string_id_cache();
bool loader_initialize(long map_id, bool is_mainmenu);
bool main_load_map_internal_hook(char const *map_path);
void canonicalize_map_path_hook(char const *path, char *canonical_path);
bool open_mod_package_map_file(EModIndex index, IMod *mod, long map_file_index, char const *virtual_file_path);
bool cache_file_open_internal_hook(long map_file_index, char *map_file_path);
void cache_file_tag_resource_table_read(s_cache_file_tag_resource_table *out_table);
s_tag_resource_data *cache_file_tag_load_resource_table_hook();
bool __fastcall c_cache_file_tag_resource_runtime_manager__get_page_hook(c_indirect_cache_file_location_atlas *thisptr, void *unused, long index, long a4, s_indirect_cache_file_page *out_location);
void display_dirty_disk();
void main_menu_launch_safe();
void dirty_disk_hook();
c_basic_buffer<void> *cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook(c_basic_buffer<void> *buffer);
bool main_game_initialize_for_new_map_hook(bool a1, s_game_options *options);
void scenario_tags_mark_necessary_bitmaps();
void __fastcall begin_tracking_resource_hook(void *thisptr, void *unused, tag_resource_tracking_setup *setup);
static void OnMapLoaded(char const *mapPath);
static void OnShutdown();
void main_menu_launch_force_hook();
void main_menu_launch_hook();

/* ---------- globals */

extern void (*const security_get_working_memory)(long, void **, long *); // 0x1124B98C
extern char const *tag_name_get_directory(char const *tag_name);
extern char const *tag_name_get_filename_without_extension(char const *tag_name);
extern s_cache_file_tag_globals *g_cache_file_tag_globals; // 0x1135A100
extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0X109265E0

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_ModSync { extern char const *const k_mods_mainmenu_virtual_path; } using namespace hades_file_local_ModSync; // 0x11197DC0
	namespace hades_file_local_ModSync { extern char const *const k_mods_game_virtual_path; } using namespace hades_file_local_ModSync; // 0x11197DC4
	extern s_static_array<s_cached_map_file,15> &g_cached_map_files; // 0x113534AC
	extern "C" { c_map_load_crash_recovery_helper crash_recovery_helper; } // 0x12409560  // hades: defined, so its dynamic initializer emits the constructor
	c_map_load_error_helper error_helper; // 0x12409584  // hades: defined, so its dynamic initializer emits the constructor
	extern s_cache_file_loaded_state loader_state; // 0x124095A0
	extern Ref<IMod> current_mod; // 0x1240985C
	extern s_resource_loaded_state resource_loader_state; // 0x12409860
}
using namespace hades_file_local;
/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0c_async_completion_flag@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0c_game_variant@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0c_map_load_crash_recovery_helper@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0c_map_load_error_helper@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0c_mod_cache_tag_remapper@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_game_options@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_game_player_options@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_player_appearance@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_player_configuration@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_player_configuration_from_host@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1c_map_load_crash_recovery_helper@@QAE@XZ"); no body to assert in
_inline c_map_load_crash_recovery_helper::~c_map_load_crash_recovery_helper() = default; // 0x10922050

// mangled_x86(MANGLED_DEFAULT, "??1c_map_load_error_helper@@QAE@XZ"); no body to assert in
_inline c_map_load_error_helper::~c_map_load_error_helper() = default; // 0x109220A0

// mangled_x86(MANGLED_DEFAULT, "??1c_mod_cache_tag_remapper@@QAE@XZ"); no body to assert in
_inline c_mod_cache_tag_remapper::~c_mod_cache_tag_remapper() = default; // 0x109220F0

namespace Patches
{
	namespace ModSync
	{
		void ApplyAll() // 0x10922620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@ModSync@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x1679C4, main_game_initialize_for_new_map_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xEA5EE, main_load_map_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x161E0A, cache_file_tag_load_resource_table_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1AABD9, cache_file_open_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1AA82C, cache_file_open_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1ABFF0, canonicalize_map_path_hook).Apply();
			Pointer(0x1658634).Write<unsigned long>(reinterpret_cast<unsigned long>(c_cache_file_tag_resource_runtime_manager__get_page_hook));
			Pointer(0x561D76).Write<unsigned char>(0x6);
			Hook(0x69F6C0, dirty_disk_hook).Apply();
			Patch(0x105840, { 0xC3 }).Apply();
			Patch(0x66AD7, { 0xEB }).Apply();
			Hook(0x161E27, cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x201B90, { 0xC3 }).Apply();
			Patch(0x1622FB, { 0x90, 0xE9 }).Apply();
			Hook(0xEAAD0, scenario_tags_mark_necessary_bitmaps).Apply();
			Hook(0x5E6780, begin_tracking_resource_hook).Apply();
			Patches::Core::OnMapLoaded(::OnMapLoaded);
			Patches::Core::OnShutdown(::OnShutdown);
			Hook(0x1680E0, main_menu_launch_hook).Apply();
			Hook(0x168190, main_menu_launch_force_hook).Apply();
		}

		void Tick() // 0x10923950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ModSync@Patches@@YAXXZ");
			// procedure flags: nofpo

					crash_recovery_helper.tick();
		}
	}
}

s_cache_tag_instance *cache_tag_instance_get(long tag_index) // 0x109265E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_tag_instance_get@@YAPAUs_cache_tag_instance@@J@Z");
	// long tag_index;
	// long const absolute_index;

	if (tag_index < 0 || tag_index >= k_maximum_number_of_cache_tag_instances)
	{
		return nullptr;
	}

	long const absolute_index = g_cache_file_tag_globals->index_to_absolute_index_map[tag_index];
	if (absolute_index < 0 || absolute_index >= g_cache_file_tag_globals->loaded_instance_count)
	{
		return nullptr;
	}

	return g_cache_file_tag_globals->instances[absolute_index];
}

char const *tag_get_name(long tag_index) // 0x10929D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_get_name@@YAPBDJ@Z");
	// long tag_index;
	// s_cache_tag_instance const *instance;

	if (!g_cache_file_tag_globals->initialized)
	{
		return nullptr;
	}

	s_cache_tag_instance const *instance = cache_tag_instance_get(tag_index);
	if (!instance)
	{
		return nullptr;
	}

	return instance->name;
}

long tag_find_by_name(unsigned long group_tag, char const *name) // 0x10929C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_find_by_name@@YAJKPBD@Z");
	// char const *name;
		// long i;
			// s_cache_tag_instance *instance;
			// long tag_index;

	for (long i = 0; i < g_cache_file_tag_globals->loaded_instance_count; i++)
	{
		long tag_index = g_cache_file_tag_globals->absolute_index_index_map[i];
		if (tag_index == -1)
			return -1;
		s_cache_tag_instance *instance = g_cache_file_tag_globals->instances[i];
		if (!instance)
			return -1;
		if ((group_tag == -1 || instance->group.tags[0] == group_tag || instance->group.tags[1] == group_tag || instance->group.tags[2] == group_tag) && instance->name && !strcmp(instance->name, name))
			return tag_index;
	}
	return -1;
}

/* ---------- private code */

bool fixup_mod_tag(long tag_index, s_cache_tag_instance *instance) // 0x109278B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_mod_tag@@YA_NJPAUs_cache_tag_instance@@@Z");
	// `anonymous-namespace'::fixup_mod_tag
	// s_cache_tag_instance *instance;
	// long **tag_reference_fixups;
	// long *dependencies;
		// long j;
			// long *tag_index_pointer;
			// long remapped_tag_index;
		// s_scenario *scenario;
			// c_tag_block<s_hs_syntax_node> &<range>$L0;
			// s_hs_syntax_node *<begin>$L0;
			// s_hs_syntax_node *<end>$L0;
				// s_hs_syntax_node &expr;
					// long remapped_tag_index;
					// long *ref;
		// long i;
			// long dependency_tag_index;

	long **tag_reference_fixups = reinterpret_cast<long **>(reinterpret_cast<long *>(&instance[1]) + instance->dependency_count + instance->fixup_count + instance->resource_fixup_count);
	for (long j = 0; j < instance->tag_reference_fixup_count; j++)
	{
		long *tag_index_pointer = reinterpret_cast<long *>(reinterpret_cast<char *>(tag_reference_fixups[j]) + reinterpret_cast<unsigned long>(instance) - 0x40000000);
		if (*tag_index_pointer == -1)
			continue;
		#line 595 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
			assert(*tag_index_pointer >= 0 && *tag_index_pointer < 0xffff);
			#line 614 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
		long remapped_tag_index = loader_state.tag_remapper.get_runtime_tag_index(*tag_index_pointer);
		if (remapped_tag_index == -1)
			continue;
		*tag_index_pointer = remapped_tag_index;
	}
	if (instance->group.tags[0] == 'scnr')
	{
		s_scenario *scenario = static_cast<s_scenario *>(offset_pointer(instance, instance->definition_offset));
		if (!scenario)
			return false;
		for (auto &expr : scenario->script_expressions)
		{
			if (expr.type >= _hs_type_sound && expr.type <= _hs_type_any_tag_not_resolving)
			{
				long *ref = reinterpret_cast<long *>(expr.data);
				long remapped_tag_index = loader_state.tag_remapper.get_runtime_tag_index(*ref);
				if (remapped_tag_index != -1)
					*ref = remapped_tag_index;
			}
		}
	}
	long *dependencies = reinterpret_cast<long *>(&instance[1]);
	for (long i = 0; i < instance->dependency_count; i++)
	{
		long dependency_tag_index = dependencies[i];
		if (dependency_tag_index == -1)
			continue;
		long remapped_tag_index = loader_state.tag_remapper.get_runtime_tag_index(dependency_tag_index);
		if (remapped_tag_index != -1)
			dependencies[i] = remapped_tag_index;
	}
	return true;
}

bool cache_file_load_tag(long tag_index) // 0x10925170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_load_tag@@YA_NJ@Z");
	// `anonymous-namespace'::cache_file_load_tag
	// static ...; // 0x109255F4
	// static ...; // 0x109255E8
	// static ...; // 0x109255E0
	// long tag_index;
	// char const *tag_name;
	// unsigned long size;
	// s_cache_tag_instance *instance;
	// s_cache_file_tag_globals *global_state;
	// void *tag_address;
	// c_cache_file_tag_cache *cache;
	// c_file_reference *cache_file;
	// long cache_tag_index;
	// s_cache_tag_instance const *header;
	// long absolute_index;
	// unsigned long *fixups;
	// long *dependencies;
	// long mod_tag_index;
		// s_cache_tag_instance const *mod_tag_instance;
		// long i;
			// long dependency_tag_index;

	s_cache_file_tag_globals *global_state = g_cache_file_tag_globals;
	if (tag_index < 0 || tag_index >= 0xFFFF)
	{
		error_helper.invalid_tag_index();
		return false;
	}
	if (global_state->index_to_absolute_index_map[tag_index] != -1)
		return true;
	c_cache_file_tag_cache *cache = loader_state.base_cache.get();
	c_file_reference *cache_file = &loader_state.base_cache_file;
	long cache_tag_index = tag_index;
	long mod_tag_index = loader_state.tag_remapper.get_mod_tag_index(tag_index);
	if (mod_tag_index != -1)
	{
		cache = loader_state.mod_cache.get();
		cache_file = &loader_state.mod_cache_file;
		cache_tag_index = mod_tag_index;
	}
	char const *tag_name = cache->get_tag_name(cache_tag_index);
	s_cache_tag_instance const *header = cache->get_instance(cache_tag_index);
	if (!header)
	{
		if (loader_state.mod_cache != nullptr)
		{
			s_cache_tag_instance const *mod_tag_instance = loader_state.mod_cache->get_instance(tag_index);
			if (mod_tag_instance && mod_tag_instance->is_empty())
			{
				error_helper.failed_to_find_mod_tag_in_base(&loader_state.mod_cache_file, mod_tag_instance, loader_state.mod_cache->get_tag_name(tag_index));
				return false;
			}
		}
		error_helper.failed_to_find_tag(cache_file, cache_tag_index);
		return false;
	}
	if (!tag_name)
	{
		error_helper.missing_tag_name(cache_file, cache_tag_index);
		return false;
	}
	if (header->size < sizeof(s_cache_tag_instance))
	{
		error_helper.invalid_tag_size(cache_file, tag_name);
		return false;
	}
	if (header->is_empty())
		return false;
	unsigned long size;
	void *tag_address = c_physical_memory_manager::allocate(_physical_memory_stage_tags, tag_name, header->size, 2, &size);
	#line 713 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(tag_address);
		#line 724 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	if (!tag_address)
	{
		error_helper.failed_to_allocate_memory_for_tag(cache_file, tag_name);
		return false;
	}
	s_cache_tag_instance *instance = (s_cache_tag_instance *)tag_address;
	if (!cache->read_tag_data(cache_file, cache_tag_index, 0, header->size, tag_address))
	{
		error_helper.failed_to_read_tag_data(cache_file, tag_name);
		return false;
	}
	instance->name = tag_name;
	long absolute_index = global_state->loaded_instance_count;
	#line 735 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(absolute_index < global_state->total_instance_count);
		#line 740 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	global_state->memory_size += size;
	global_state->memory_used += size;
	if (!global_state->memory)
		global_state->memory = tag_address;
	global_state->index_to_absolute_index_map[tag_index] = absolute_index;
	global_state->absolute_index_index_map[absolute_index] = tag_index;
	global_state->instances[absolute_index] = instance;
	global_state->loaded_instance_count++;
	unsigned long *fixups = (unsigned long *)&instance[1] + instance->dependency_count;
	for (long i = 0; i < instance->fixup_count; i++)
		*(unsigned long *)(fixups[i] + (unsigned long)tag_address - 0x40000000) = (unsigned long)((char *)tag_address + *(unsigned long *)(fixups[i] + (unsigned long)tag_address - 0x40000000) - 0x40000000);
	if (mod_tag_index != -1 && !fixup_mod_tag(mod_tag_index, instance))
		return false;
	cache_file_tags_optimize(tag_index, instance);
	long *dependencies = (long *)&instance[1];
	for (long i = 0; i < instance->dependency_count; i++)
	{
		long dependency_tag_index = dependencies[i];
		if (dependency_tag_index == -1)
			continue;
		if (!cache_file_load_tag(dependency_tag_index))
			return false;
	}
	return true;
}

bool cache_file_allocate_tags() // 0x10924670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_allocate_tags@@YA_NXZ");
	// `anonymous-namespace'::cache_file_allocate_tags
	// procedure flags: nofpo
	// unsigned long const max_table_size;
	// s_cache_file_tag_globals *global_state;
	// long const runtime_tag_count;
	// unsigned long const table_size;

	s_cache_file_tag_globals *global_state = g_cache_file_tag_globals;
	long const runtime_tag_count = loader_state.tag_remapper.get_runtime_tag_count();
	unsigned long const table_size = runtime_tag_count * sizeof(long);
	unsigned long const max_table_size = 0x3FFFC;
	c_physical_memory_manager::push(_physical_memory_stage_tags);
	global_state->index_to_absolute_index_map = (long *)c_physical_memory_manager::allocate(_physical_memory_stage_tags, "tag-index-to-absolute", max_table_size, 0, nullptr);
	global_state->absolute_index_index_map = (long *)c_physical_memory_manager::allocate(_physical_memory_stage_tags, "tag-absolute-index", table_size, 0, nullptr);
	global_state->instances = (s_cache_tag_instance **)c_physical_memory_manager::allocate(_physical_memory_stage_tags, "tag-instances", table_size, 0, nullptr);
	#line 779 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(global_state->index_to_absolute_index_map);
		#line 787 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	if (!global_state->index_to_absolute_index_map)
		return false;
	#line 782 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(global_state->absolute_index_index_map);
		#line 792 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	if (!global_state->absolute_index_index_map)
		return false;
	#line 785 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(global_state->instances);
		#line 797 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	if (!global_state->instances)
		return false;
	#line 789 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert((ulong)global_state->absolute_index_index_map - (ulong)global_state->index_to_absolute_index_map >= max_table_size);
		#line 802 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	#line 790 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert((ulong)global_state->instances - (ulong)global_state->absolute_index_index_map >= table_size);
		#line 805 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	#line 791 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert((ulong)global_state->memory - (ulong)global_state->instances >= table_size);
		#line 808 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	global_state->total_instance_count = runtime_tag_count;
	global_state->loaded_instance_count = 0;
	global_state->memory = nullptr;
	global_state->memory_used = 0;
	global_state->memory_size = 0;
	memset(global_state->index_to_absolute_index_map, -1, max_table_size);
	memset(global_state->absolute_index_index_map, -1, table_size);
	memset(global_state->instances, 0, table_size);
	return true;
}

void cache_file_compute_and_verify_signature() // 0x10924960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_compute_and_verify_signature@@YAXXZ");
	// `anonymous-namespace'::cache_file_compute_and_verify_signature
	// procedure flags: nofpo
	// s_cache_file_secure_memory *(*const cache_file_get_secure_working_memory)();
	// s_cache_file_secure_memory *secure_memory;
	// void (*const cache_file_builder_security_clean_header)(s_cache_file_header *);
		// unsigned char *block;
		// long bytes_remaining;
			// long block_size;
	// function call : s_cache_file_secure_memory *(*const)()
	// function call : void (*const)(s_cache_file_header *)
	// function call : bool (*const)(void *, long, bool)
	// function call : void (*const)(void *, long, void const *, unsigned long)
	// function call : void (*const)()
	// function call : void (*const)(void *, long, void *)
	// function call : bool (*const)(void *, long, bool, void *)
	// function call : void (*const)()
	// function call : s_cache_file_secure_memory *(*const)()
	// function call : bool (*const)(void const *, void *)

	s_cache_file_secure_memory *(*const cache_file_get_secure_working_memory)() = reinterpret_cast<s_cache_file_secure_memory *(*)()>(0x5018F0);
	void (*const cache_file_builder_security_clean_header)(s_cache_file_header *) = reinterpret_cast<void (*)(s_cache_file_header *)>(0x601BF0);
	s_cache_file_secure_memory *secure_memory = cache_file_get_secure_working_memory();
	if (secure_memory)
	{
		secure_memory->valid = 0;
		*(unsigned long *)&secure_memory->input_hash[0] = 0xBBBBBBBB;
		*(unsigned long *)&secure_memory->input_hash[4] = 0xBBBBBBBB;
		*(unsigned long *)&secure_memory->input_hash[8] = 0xBBBBBBBB;
		*(unsigned long *)&secure_memory->input_hash[12] = 0xBBBBBBBB;
		*(unsigned long *)&secure_memory->input_hash[16] = 0xBBBBBBBB;
		*(unsigned long *)&secure_memory->result_hash[0] = 0xCCCCCCCC;
		*(unsigned long *)&secure_memory->result_hash[4] = 0xCCCCCCCC;
		*(unsigned long *)&secure_memory->result_hash[8] = 0xCCCCCCCC;
		*(unsigned long *)&secure_memory->result_hash[12] = 0xCCCCCCCC;
		*(unsigned long *)&secure_memory->result_hash[16] = 0xCCCCCCCC;
		memset(secure_memory->rsa_signature, 0xDD, sizeof(secure_memory->rsa_signature));
		memmove(&secure_memory->header, &g_cache_file_tag_globals->cache_file_header, sizeof(s_cache_file_header));
		cache_file_builder_security_clean_header(&secure_memory->header);
		secure_memory->size = sizeof(s_cache_file_header);
		secure_memory->data = &secure_memory->header;
		unsigned char *block = (unsigned char *)secure_memory->data;
		long bytes_remaining = sizeof(s_cache_file_header);
		if (security_incremental_hash_begin(secure_memory->hash_buffer, sizeof(secure_memory->hash_buffer), true))
		{
			do
			{
				long block_size = bytes_remaining;
				if (bytes_remaining > 0x100000)
					block_size = 0x100000;
				security_incremental_hash_update(secure_memory->hash_buffer, sizeof(secure_memory->hash_buffer), block, block_size);
				((void (*)())0x5063A0)();
				bytes_remaining -= block_size;
				block += block_size;
			} while (bytes_remaining > 0);
			security_incremental_hash_finish(secure_memory->hash_buffer, sizeof(secure_memory->hash_buffer), secure_memory->input_hash);
		}
		security_calculate_hash(secure_memory->input_hash, sizeof(secure_memory->input_hash), true, secure_memory->result_hash);
		memcpy(secure_memory->rsa_signature, g_cache_file_tag_globals->cache_file_header.rsa_signature, sizeof(secure_memory->rsa_signature));
		((void (*)())0x5063A0)();
		secure_memory = cache_file_get_secure_working_memory();
		security_rsa_compute_and_verify_signature(secure_memory->result_hash, secure_memory->rsa_signature);
		secure_memory->valid = 1;
	}
}

void cache_file_invalidate_signature() // 0x10924D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_invalidate_signature@@YAXXZ");
	// `anonymous-namespace'::cache_file_invalidate_signature
	// procedure flags: nofpo
	// static ...; // 0x10924E4F
	// static ...; // 0x10924E3C
	// static ...; // 0x10924E24
	// static ...; // 0x10924E1C
	// void *secure_memory;
	// long secure_memory_size;
	// function call : void (*const)(long, void **, long *)

	void *secure_memory;
	long secure_memory_size;
	security_get_working_memory(0, &secure_memory, &secure_memory_size);

	if (secure_memory_size >= sizeof(s_cache_file_secure_memory) && secure_memory)
	{
		memset(secure_memory, 0, sizeof(s_cache_file_secure_memory));
	}
}

bool cache_file_load_allocate_tags() // 0x10924E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_load_allocate_tags@@YA_NXZ");
	// `anonymous-namespace'::cache_file_load_allocate_tags
	// procedure flags: nofpo
	// long game_globals_tag;
	// bool mainmenu_mod;
	// long scenario_tag_index;
		// long scenario_mod_tag_index;
		// std::shared_ptr<c_cache_file_tag_cache> &mod_cache;
	// function call : long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	cache_file_invalidate_signature();
	long scenario_tag_index = loader_state.base_cache->find_by_name('scnr', g_cache_file_tag_globals->cache_file_header.scenario_path);
	if (loader_state.mod_cache != nullptr)
	{
		std::shared_ptr<c_cache_file_tag_cache> &mod_cache = loader_state.mod_cache;
		long scenario_mod_tag_index = mod_cache->find_by_name('scnr', g_cache_file_tag_globals->cache_file_header.scenario_path);
		if (scenario_mod_tag_index != -1 && !mod_cache->empty_tag(scenario_mod_tag_index))
			scenario_tag_index = loader_state.tag_remapper.get_runtime_tag_index(scenario_mod_tag_index);
	}
	if (!cache_file_allocate_tags())
		return false;
	if (!cache_file_load_tag(0))
		return false;
	if (!cache_file_load_tag(scenario_tag_index))
		return false;
	cache_file_compute_and_verify_signature();
	long game_globals_tag = cache_file_globals_get_tag('matg');
	*reinterpret_cast<long *>(0x189CCF8) = scenario_tag_index;
	*reinterpret_cast<long *>(0x189CCFC) = game_globals_tag;
	*reinterpret_cast<void **>(0x22AAEB4) = tag_get('scnr', scenario_tag_index);
	*reinterpret_cast<void **>(0x22AAEB8) = tag_get('matg', game_globals_tag);
	bool mainmenu_mod = loader_state.loading_main_menu && loader_state.mod_cache;
	Player::CPlayerCharacterSystem::NotifyTagsLoaded(mainmenu_mod, loader_state.base_cache, Blam::Cache::StringIDCache::GetCurrent());
	return true;
}

bool open_mod_package_resource_cache(char const *filepath) // 0x109294C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open_mod_package_resource_cache@@YA_NPBD@Z");
	// `anonymous-namespace'::open_mod_package_resource_cache
	// char const *filepath;
	// constexpr bool (*const `open_mod_package_resource_cache'::`2'::cache_file_open)(s_cached_map_file *, char const *); // constant == 5945824
	// constexpr bool (*const `open_mod_package_resource_cache'::`2'::cache_file_read_header)(__int32); // constant == 5946320
	// function call : bool (*const)(s_cached_map_file *, char const *)
	// function call : bool (*const)(__int32)

	if (!((bool(__cdecl *const)(s_cached_map_file *, char const *))0x5ab9e0)(&g_cached_map_files[6], filepath))
	{
		return false;
	}

	if (!((bool(__cdecl *const)(__int32))0x5abbd0)(6))
	{
		return false;
	}

	strncpy_s(g_cached_map_files[6].file_header.map_path, filepath, 255);
	return true;
}

void close_mod_package_resource_cache() // 0x10926750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?close_mod_package_resource_cache@@YAXXZ");
	// `anonymous-namespace'::close_mod_package_resource_cache
	// procedure flags: nofpo
	// void (*const cached_map_file_close)(long);
	// function call : void (*const)(long)

	void (__cdecl *const close_resource_cache)(int) = (void(__cdecl *const)(int))0x5ab630;

	close_resource_cache(6);
}

bool do_load_main_menu_mod_package() // 0x10926D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?do_load_main_menu_mod_package@@YA_NXZ");
	// `anonymous-namespace'::do_load_main_menu_mod_package
	// procedure flags: nofpo
	// static ...; // 0x10926F4C
	// static ...; // 0x10926F40
	// static ...; // 0x10926F38
	// std::string &MainMenuMod;
	// s_static_string<256> file_path;
	// EModResult result;
	// function call : EModResult (EModIndex, char const *, bool)

	s_static_string<256> file_path;
	std::string &MainMenuMod = Utils::Singleton<Modules::ModuleGame>::Instance().VarMainMenuMod->ValueString;
	if (MainMenuMod.empty())
		return false;
	file_path.print("%s\\%s", c_mod_system::get_package_directory(), MainMenuMod.c_str());
	if (file_path.length() < 1)
		return false;
	if (!std::filesystem::exists(file_path.get_string()))
		return false;
	EModResult result = c_mod_system::GetModManager().SetMod(kMainMenu, file_path, true);
	return result == kSuccess || result == kPending;
}

void loader_reset() // 0x10928790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loader_reset@@YAXXZ");
	// `anonymous-namespace'::loader_reset
	// procedure flags: nofpo

	loader_state.tag_remapper.reset();
	loader_state.base_cache = nullptr;
	loader_state.mod_cache = nullptr;
	if (loader_state.base_cache_file.is_open())
		loader_state.base_cache_file.close();
	loader_state.base_cache_file = {};
	if (loader_state.mod_cache_file.is_open())
		loader_state.mod_cache_file.close();
	loader_state.mod_cache_file = {};
}

bool load_string_id_cache() // 0x10927E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_string_id_cache@@YA_NXZ");
	// `anonymous-namespace'::load_string_id_cache
	// procedure flags: nofpo
	// static ...; // 0x10928146
	// static ...; // 0x1092813C
	// static ...; // 0x10928124
	// static ...; // 0x1092811C
	// IMod *mod;
	// std::shared_ptr<Blam::Cache::StringIDCache> string_id_cache;
		// std::shared_ptr<c_cache_file_interface> mod_cache;
	// function call : IMod *(EModIndex) const
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<Blam::Cache::StringIDCache> () const

	std::shared_ptr<Blam::Cache::StringIDCache> string_id_cache;
	IMod *mod = c_mod_system::GetModManager().GetMod(loader_state.loading_main_menu ? kMainMenu : kGame);
	if (mod)
	{
		std::shared_ptr<c_cache_file_interface> mod_cache = mod->GetCache(true);
		if (!mod_cache)
			return false;
		string_id_cache = mod_cache->get_string_cache();
		if (!string_id_cache)
			return false;
	}
	else
	{
		string_id_cache = c_cache_file_tags::get_open_string_id_cache();
		if (!string_id_cache)
			return false;
	}
	Blam::Cache::StringIDCache::SetCurrent(std::move(string_id_cache));
	return true;
}

bool loader_initialize(long map_id, bool is_mainmenu) // 0x10928210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loader_initialize@@YA_NJ_N@Z");
	// `anonymous-namespace'::loader_initialize
	// static ...; // 0x1092865C
	// static ...; // 0x10928654
	// long map_id;
	// bool is_mainmenu;
	// IMod *mod;
		// std::shared_ptr<c_cache_file_interface> mod_cache;
	// function call : IMod *(EModIndex) const
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const
	// function call : c_mod_package *(bool) const
	// function call : char const *() const

	error_helper.reset();
	loader_reset();
	loader_state.loading_main_menu = is_mainmenu;
	resource_loader_state.mod_cache = nullptr;
	if (!c_cache_file_tags::open_tag_cache())
		return false;
	loader_state.base_cache = c_cache_file_tags::get_open_cache();
	loader_state.base_cache_file = loader_state.base_cache->get_file();
	if (!loader_state.base_cache_file.open(1, &g_file_reference_error))
		return false;
	if (!loader_state.tag_remapper.initialize(loader_state.base_cache.get()))
		return false;
	close_mod_package_resource_cache();
	IMod *mod = c_mod_system::GetModManager().GetMod(is_mainmenu ? kMainMenu : kGame);
	current_mod = static_cast<Ref<IMod> const &>(current_mod);
	if (mod)
	{
		std::shared_ptr<c_cache_file_interface> mod_cache = mod->GetCache(true);
		if (!mod_cache)
			return false;
		loader_state.mod_cache = mod_cache->get_tag_cache();
		loader_state.mod_cache_file = loader_state.mod_cache->get_file();
		if (!loader_state.mod_cache_file.open(1, &g_file_reference_error))
			return false;
		if (!loader_state.tag_remapper.add_mod(loader_state.mod_cache.get()))
			return false;
		resource_loader_state.mod_cache = mod->GetPak(false);
		if (!open_mod_package_resource_cache(mod->GetFilename()))
			return false;
	}
	if (!load_string_id_cache())
		return false;
	return true;
}

bool main_load_map_internal_hook(char const *map_path) // 0x109289F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_load_map_internal_hook@@YA_NPBD@Z");
	// `anonymous-namespace'::main_load_map_internal_hook
	// static ...; // 0x10928BB8
	// static ...; // 0x10928BAC
	// static ...; // 0x10928BA4
	// char const *map_path;
	// s_cache_file_tag_globals *global_state;
	// s_cache_file_header header;
	// function call : bool (*const)(char const *, s_cache_file_header *)
	// function call : bool (*const)(s_cache_file_header *, char const *, bool)
	// function call : void (*const)(e_basic_loading_phase, unsigned long)
	// function call : void (*const)()
	// function call : void (*const)()

	crash_recovery_helper.map_load_start();
	c_physical_memory_manager::prepare_for_new_map();
	s_cache_file_tag_globals *global_state = g_cache_file_tag_globals;
	global_state->initialized = false;
	global_state->tag_load_sequence_number++;
	s_cache_file_header header;
	if (!cache_file_open_package(map_path, &header) && cache_file_header_verify(&header, map_path, false))
		return false;
	csmemmove(&global_state->cache_file_header, &header, sizeof(header));
	if (!loader_initialize(header.map_id, _stricmp(header.map_name, "mainmenu") == 0))
		return false;
	reinterpret_cast<void (*)(long, long)>(0x52EEC0)(1, 1);
	if (cache_file_load_allocate_tags())
		global_state->initialized = true;
	else
	{
		c_physical_memory_manager::pop(_physical_memory_stage_tags);
		cache_files_tags_reset();
	}
	loader_reset();
	reinterpret_cast<void (*)()>(0x52EEF0)();
	return global_state->initialized;
}

void canonicalize_map_path_hook(char const *path, char *canonical_path) // 0x10926660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?canonicalize_map_path_hook@@YAXPBDPAD@Z");
	// `anonymous-namespace'::canonicalize_map_path_hook
	// char *canonical_path;
		// char const *filename;
		// char const *directory;

	if (strstr(path, "mods\\") == path)
	{
		char const *directory = tag_name_get_directory(path);
		char const *filename = tag_name_get_filename_without_extension(path);
		snprintf(canonical_path, 256, "%s\\%s.map", directory, filename);
	}
	else
	{
		char const *filename_without_extension = tag_name_get_filename_without_extension(path);
		snprintf(canonical_path, 256, "maps\\%s.map", filename_without_extension);
	}

	csstrnlwr(canonical_path, 256);
}

bool open_mod_package_map_file(EModIndex index, IMod *mod, long map_file_index, char const *virtual_file_path) // 0x10929090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open_mod_package_map_file@@YA_NW4EModIndex@@PAVIMod@@JPBD@Z");
	// `anonymous-namespace'::open_mod_package_map_file
	// static ...; // 0x109293B0
	// static ...; // 0x109293A8
	// EModIndex index;
	// IMod *mod;
	// long map_file_index;
	// char const *virtual_file_path;
	// s_level_datum datum;
	// s_cached_map_file *map_file;
	// char level_path[260];
	// c_mod_package *package;
	// c_file_reference file;
	// __int32 package_map_file_index;
	// long cache_index;
	// static s_cache_file_header `open_mod_package_map_file'::`2'::header; // 0x12409868
	// EModResult result;
		// char *p;
		// __int32 i;
	// function call : c_mod_package *(bool) const
	// function call : EModResult (EModIndex, __int32, bool)

	c_mod_package *package = mod->GetPak(true);
	if (!package)
		return false;
	if (package->get_map_count() == 0)
		return false;
	char level_path[MAX_PATH];
	strncpy_s(level_path, virtual_file_path, _TRUNCATE);
	if (char *p = strrchr(level_path, '.'))
		*p = 0;
	levels_yield_until_enumerate_done();
	__int32 package_map_file_index = -1;
	s_level_datum datum;
	for (__int32 i = 0; i < package->get_map_count(); i++)
	{
		if (!levels_find_level_by_map_id(package->get_map_file_entry(i)->map_id, &datum))
			continue;
		if (strcmp(datum.file_path, level_path) == 0)
		{
			package_map_file_index = i;
			break;
		}
	}
	if (package_map_file_index == -1)
		return false;
	c_file_reference file = package->get_file();
	static s_cache_file_header header;
	if (!package->read_map_cache_file_header(file, package_map_file_index, &header))
		return false;
	long cache_index = package->get_map_file_entry(package_map_file_index)->tag_cache_index;
	EModResult result = c_mod_system::GetModManager().SetModCache(index, cache_index, true);
	if (result != 0 && result != 4)
		return false;
	s_cached_map_file *map_file = &g_cached_map_files[map_file_index];
	memcpy(&map_file->file_header, &header, sizeof(s_cache_file_header));
	strncpy(map_file->file_header.map_path, virtual_file_path, 255);
	map_file->indirect_file_handle.handle = -1;
	map_file->file_handle2.handle = -1;
	return true;
}

bool cache_file_open_internal_hook(long map_file_index, char *map_file_path) // 0x10925720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_open_internal_hook@@YA_NJPAD@Z");
	// `anonymous-namespace'::cache_file_open_internal_hook
	// static ...; // 0x109258B9
	// long map_file_index;
	// char *map_file_path;
	// char (*const cache_file_open_internal)(__int32, char *);
	// EModIndex index;
	// IMod *mod;
	// function call : IMod *(EModIndex) const
	// function call : IMod *(EModIndex) const
	// function call : char const *() const
	// function call : char (*const)(__int32, char *)

	char (*const cache_file_open_internal)(__int32, char *) = reinterpret_cast<char (*)(__int32, char *)>(0x5ABAD0);
	IMod *mod = nullptr;
	EModIndex index;
	if (strstr(map_file_path, k_mods_mainmenu_virtual_path) == map_file_path)
	{
		mod = c_mod_system::GetModManager().GetMod(kMainMenu);
		index = kMainMenu;
	}
	else if (strstr(map_file_path, k_mods_game_virtual_path) == map_file_path)
	{
		mod = c_mod_system::GetModManager().GetMod(kGame);
		index = kGame;
	}
	if (mod)
	{
		if (open_mod_package_map_file(index, mod, map_file_index, map_file_path))
			return true;
		error_helper.failed_to_open_mod_package_map_file(mod->GetFilename(), map_file_path);
		return false;
	}
	return cache_file_open_internal(map_file_index, map_file_path);
}

void cache_file_tag_resource_table_read(s_cache_file_tag_resource_table *out_table) // 0x109260E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_tag_resource_table_read@@YAXPAUs_cache_file_tag_resource_table@@@Z");
	// `anonymous-namespace'::cache_file_tag_resource_table_read
	// static ...; // 0x109264C9
	// static ...; // 0x109264B9
	// static ...; // 0x109264AC
	// static ...; // 0x10926488
	// static ...; // 0x10926480
	// s_cache_file_tag_resource_table *out_table;
	// constexpr __int32 (*const `cache_file_tag_resource_table_read'::`2'::async_read_position)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *); // constant == 5954176
	// s_cache_file_tag_resource_cache_file_header file_headers[6];
	// long total_resource_count;
	// unsigned long *file_offsets;
	// constexpr void (*const `cache_file_tag_resource_table_read'::`2'::async_yield_until_done_internal)(c_async_completion_flag *, bool, bool); // constant == 5278240
	// c_async_completion_flag completion_flag;
	// s_static_array<s_cached_map_file,15> &cached_map_files;
	// c_synchronized_int32 bytes_read;
	// c_mod_package *current_mod;
		// e_cache_file_tag_resource_location location;
			// long map_file_index;
			// unsigned long base_offset;
		// long offset;
		// long location_index;
			// long table_size;
	// function call : __int32 (*const)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)
	// function call : __int32 (*const)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)

	static __int32 (*const async_read_position)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *) = reinterpret_cast<__int32 (*)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)>(0x5ADA80);
	s_static_array<s_cached_map_file,15> &cached_map_files = *reinterpret_cast<s_static_array<s_cached_map_file,15> *>(0x240B1E8);
	c_synchronized_int32 bytes_read;
	c_async_completion_flag completion_flag;
	static void (*const async_yield_until_done_internal)(c_async_completion_flag *, bool, bool) = reinterpret_cast<void (*)(c_async_completion_flag *, bool, bool)>(0x508A20);
	long total_resource_count = 0;
	unsigned long *file_offsets = nullptr;
	s_cache_file_tag_resource_cache_file_header file_headers[6];
	c_mod_package *current_mod = resource_loader_state.mod_cache;
	out_table->count = 0;
	out_table->file_offsets = nullptr;
	for (e_cache_file_tag_resource_location location = (e_cache_file_tag_resource_location)0; location < 6; location = (e_cache_file_tag_resource_location)(location + 1))
	{
		long map_file_index = location + 1;
		completion_flag.set(0);
		bytes_read.set(0);
		unsigned long base_offset = 0;
		if (location == 5)
		{
			if (!current_mod)
				continue;
			base_offset = current_mod->get_resource_cache_offset();
		}
		async_read_position(cached_map_files[map_file_index].file_handle, &file_headers[location], sizeof(s_cache_file_tag_resource_cache_file_header), base_offset, 0, 9, &bytes_read, &completion_flag);
		async_yield_until_done_internal(&completion_flag, false, false);
		if (bytes_read.peek() != sizeof(s_cache_file_tag_resource_cache_file_header))
		{
			trace_handle("failed to read tag resource cache file header [map_file_index=%d]\n", map_file_index);
			break;
		}
		g_cache_file_tag_globals->tag_resource_counts_by_location[location] = file_headers[location].resource_count;
		total_resource_count += file_headers[location].resource_count;
	}
	file_offsets = (unsigned long *)c_physical_memory_manager::allocate(_physical_memory_stage_tags, "tag-resource-offsets", total_resource_count * sizeof(unsigned long), 0, nullptr);
	for (long location_index = 0, offset = 0; location_index < 6; location_index++)
	{
		long map_file_index = location_index + 1;
		long table_size = file_headers[location_index].resource_count * sizeof(unsigned long);
		unsigned long base_offset = 0;
		if (location_index == 5)
		{
			if (!current_mod)
				continue;
			base_offset = current_mod->get_resource_cache_offset();
		}
		completion_flag.set(0);
		bytes_read.set(0);
		async_read_position(cached_map_files[map_file_index].file_handle, &file_offsets[offset], table_size, file_headers[location_index].table_offset + base_offset, 0, 9, &bytes_read, &completion_flag);
		async_yield_until_done_internal(&completion_flag, false, false);
		if (bytes_read.peek() != table_size)
		{
			trace_handle("failed to read tag resource table [map_file_index=%d, offset=%x, resource_count=%d]\n", map_file_index, file_headers[location_index].table_offset, file_headers[location_index].resource_count);
			break;
		}
		offset += file_headers[location_index].resource_count;
	}
	out_table->file_offsets = file_offsets;
	out_table->count = total_resource_count;
}

s_tag_resource_data *cache_file_tag_load_resource_table_hook() // 0x10925930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_tag_load_resource_table_hook@@YAPAUs_tag_resource_data@@XZ");
	// `anonymous-namespace'::cache_file_tag_load_resource_table_hook
	// procedure flags: nofpo
	// static ...; // 0x10925E20
	// static ...; // 0x10925E14
	// static ...; // 0x10925E0C
	// s_cache_file_tag_resource_table resource_table;
	// long total_resource_count;
	// unsigned long resource_page_memory_scratch_size;
	// s_tag_resource_data *runtime_data;
	// long v10;
	// unsigned long table_size;
	// unsigned long total_uncompressed_size;
	// unsigned long runtime_data_size;
	// long total_fixup_count;
	// unsigned long resource_page_memory_size;
	// c_mod_package *current_mod;
		// long i;
		// __int32 i;
			// long tag_index;
			// unsigned long *resource_fixups;
			// s_cache_tag_instance *tag_instance;
				// __int32 j;
					// long *entry_ptr;
						// s_tag_resource *pageable;
						// bool zero_size;
							// bool (*const bitmap_group_needs_backing_strorage)(long);
							// unsigned long resource_page_size;
							// long offset;
							// long location_index;
								// unsigned long resource_count;
	// function call : bool (*const)(long)

	s_cache_file_tag_resource_table resource_table;
	cache_file_tag_resource_table_read(&resource_table);
	c_mod_package *current_mod = resource_loader_state.mod_cache;
	long total_resource_count = 0;
	for (long i = 0; i < g_cache_file_tag_globals->loaded_instance_count; i++)
		total_resource_count += g_cache_file_tag_globals->instances[i]->resource_fixup_count;
	unsigned long table_size = total_resource_count * sizeof(s_tag_resource *);
	unsigned long runtime_data_size = sizeof(s_tag_resource_data) + table_size * sizeof(long);
	s_tag_resource_data *runtime_data = (s_tag_resource_data *)c_physical_memory_manager::allocate(_physical_memory_stage_tags, "tag-resource-page-table", runtime_data_size, 2, nullptr);
	g_cache_file_tag_globals->tag_resource_data = runtime_data;
	memset(runtime_data, 0, runtime_data_size);
	runtime_data->resources = reinterpret_cast<s_tag_resource **>(&runtime_data[1]);
	long v10 = 0;
	long total_fixup_count = 0;
	unsigned long total_uncompressed_size = 0;
	unsigned long resource_page_memory_size = 0;
	unsigned long resource_page_memory_scratch_size = 0;
	for (__int32 i = 0; i < g_cache_file_tag_globals->loaded_instance_count; i++)
	{
		long tag_index = g_cache_file_tag_globals->absolute_index_index_map[i];
		s_cache_tag_instance *tag_instance = g_cache_file_tag_globals->instances[i];
		unsigned long *resource_fixups = reinterpret_cast<unsigned long *>(&tag_instance[1]) + (tag_instance->fixup_count + tag_instance->dependency_count);
		for (__int32 j = 0; j < tag_instance->resource_fixup_count; j++)
		{
			long *entry_ptr = reinterpret_cast<long *>(resource_fixups[j] + reinterpret_cast<unsigned long>(tag_instance) - 0x40000000);
			if (!*entry_ptr)
			{
				*entry_ptr = -1;
			}
			else
			{
				runtime_data->resources[v10] = reinterpret_cast<s_tag_resource *>(*entry_ptr);
				s_tag_resource *pageable = reinterpret_cast<s_tag_resource *>(*entry_ptr);
				bool zero_size = false;
				if (pageable->index == -1)
				{
					pageable->index = 0;
				}
				else
				{
					unsigned long offset = 0;
					long location_index = 0;
					do
					{
						if (pageable->page_flags & (1 << (location_index + 1)))
							break;
						unsigned long resource_count = g_cache_file_tag_globals->tag_resource_counts_by_location[location_index];
						offset += resource_count;
					} while (location_index++ < 6);
					bool (*const bitmap_group_needs_backing_strorage)(long) = reinterpret_cast<bool (*)(long)>(0x718CA0);
					pageable->index = resource_table.file_offsets[offset + pageable->index];
					unsigned long resource_page_size = (pageable->uncompressed_block_size + 0xFFF) & 0xFFFFF000;
					if (tag_instance->group.tags[0] == 'snd!')
						zero_size = true;
					else if (tag_instance->group.tags[0] != 'bitm' || bitmap_group_needs_backing_strorage(tag_index))
						resource_page_memory_size += resource_page_size;
					else if (resource_page_size > resource_page_memory_scratch_size)
						resource_page_memory_scratch_size = resource_page_size;
				}
				if (!zero_size)
				{
					if (total_uncompressed_size + pageable->uncompressed_block_size < total_uncompressed_size)
					{
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Too many uncompressed resources.");
	#line 1467 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
						assert(!"Exceeded Uncompressed resources limit!");
						#line 1475 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
						abort();
					}
					total_uncompressed_size += pageable->uncompressed_block_size;
				}
				total_fixup_count = 1;
				*entry_ptr = v10++;
			}
		}
	}
	resource_loader_state.required_page_memory_size = resource_page_memory_size + resource_page_memory_scratch_size;
	runtime_data->resource_memory_used = total_uncompressed_size;
	runtime_data->resource_count = v10;
	runtime_data->field_10 = total_fixup_count;
	return runtime_data;
}

bool __fastcall c_cache_file_tag_resource_runtime_manager__get_page_hook(c_indirect_cache_file_location_atlas *thisptr, void *unused, long index, long a4, s_indirect_cache_file_page *out_location) // 0x10924330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_cache_file_tag_resource_runtime_manager__get_page_hook@@YI_NPAUc_indirect_cache_file_location_atlas@@PAXJJPAUs_indirect_cache_file_page@@@Z");
	// `anonymous-namespace'::c_cache_file_tag_resource_runtime_manager__get_page_hook
	// s_indirect_cache_file_page *out_location;
	// s_tag_resource_page *physical_location;
	// unsigned long base_offset;
	// unsigned long shared_file_handle2;
	// long resource_location;
	// s_cache_file_resource_shared_file *shared_file;
	// constexpr s_tag_resource_page *(*const `c_cache_file_tag_resource_runtime_manager__get_page_hook'::`2'::c_cache_file_tag_resource_page_handler__get_physical_location)(c_cache_file_tag_resource_page_handler *, long); // constant == 7260016
	// unsigned long shared_file_handle;
	// c_mod_package *current_mod;
	// function call : s_tag_resource_page *(*const)(c_cache_file_tag_resource_page_handler *, long)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void *(*const)(s_data_array const *, unsigned long)

	static s_tag_resource_page *(__thiscall *const c_cache_file_tag_resource_page_handler__get_physical_location)(c_cache_file_tag_resource_page_handler *, long) = reinterpret_cast<s_tag_resource_page *(__thiscall *)(c_cache_file_tag_resource_page_handler *, long)>(0x6EC770);
	long resource_location = -1;
	unsigned long shared_file_handle;
	unsigned long shared_file_handle2;
	unsigned long base_offset = 0;
	c_mod_package *current_mod = resource_loader_state.mod_cache;
	s_tag_resource_page *physical_location = c_cache_file_tag_resource_page_handler__get_physical_location(thisptr->page_handler, index);
	if (physical_location->page_flags & 2)
	{
		resource_location = 0;
	}
	else if (physical_location->page_flags & 4)
	{
		resource_location = 1;
	}
	else if (physical_location->page_flags & 8)
	{
		resource_location = 2;
	}
	else if (physical_location->page_flags & 16)
	{
		resource_location = 3;
	}
	else if (physical_location->page_flags & 32)
	{
		resource_location = 4;
	}
	else if (physical_location->page_flags & 64)
	{
		resource_location = 5;
		base_offset = current_mod->get_resource_cache_offset();
	}
	shared_file_handle2 = thisptr->cache_file_shared_file_handle_handles[resource_location + 1];
	s_cache_file_resource_shared_file *shared_file = (s_cache_file_resource_shared_file *)datum_try_and_get(thisptr->shared_file_handles, shared_file_handle2);
	out_location->indirect_file_handle = shared_file->indirect_file_handle;
	if (resource_location == -1)
		shared_file_handle = thisptr->cache_file_shared_file_handle_handles[0];
	shared_file_handle = thisptr->cache_file_shared_file_handle_handles[resource_location + 1];
	shared_file = (s_cache_file_resource_shared_file *)datum_try_and_get(thisptr->shared_file_handles, shared_file_handle);
	out_location->offset = physical_location->index + shared_file->base_offset + base_offset;
	out_location->size = physical_location->compressed_block_size;
	return true;
}

void display_dirty_disk() // 0x10926A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?display_dirty_disk@@YAXXZ");
	// `anonymous-namespace'::display_dirty_disk
	// procedure flags: nofpo

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, std::format("Dirty Disk: {}", error_helper.get_last_error()));
	if (Utils::Singleton<ElDorito>::Instance().IsHeadless())
		return;
	if (loader_state.loading_main_menu)
	{
		ErrorDialog::Show("Dirty Disk Error!", std::format("Your tags are invalid or corrupted. ElDewrito will now exit.\n\n{}", error_helper.get_last_error()));
	}
	else
	{
		Web::Ui::ScreenLayer::ShowAlert("Dirty Disk Error!", std::format("Failed to load map due to an invalid or incompatible mod!\n\nCheck the log for details."), (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
	}
}

void main_menu_launch_safe() // 0x10928EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_menu_launch_safe@@YAXXZ");
	// `anonymous-namespace'::main_menu_launch_safe
	// procedure flags: nofpo
	// void (*const network_life_cycle_end)();
	// void (*const network_life_cycle_request_leave)(__int32);
	// bool (*const network_life_cycle_get_state)();
	// function call : bool (*const)()
	// function call : void (*const)(__int32)
	// function call : void (*const)()
	// function call : void (*const)()

	bool (*const main_menu_is_loaded)() = (bool(*const)())0x454db0;
	void (*const main_menu_launch)(int) = (void(*const)(int))0x455260;
	void (*const main_menu_reset)() = (void(*const)())0x454b40;

	if (main_menu_is_loaded())
	{
		main_menu_launch(0);
	}
	else
	{
		main_menu_reset();
	}

	((void(*)())0x5680e0)();
}

void dirty_disk_hook() // 0x109267B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dirty_disk_hook@@YAXXZ");
	// `anonymous-namespace'::dirty_disk_hook
	// procedure flags: nofpo
	// function call : unsigned long ()
	// function call : IMod *(EModIndex) const

	if (*(bool *)0x22B7FAF)
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, std::format("Dirty Disk: Failed to load font package"));
	if (GetCurrentThreadId() != ElDorito::GetMainThreadID())
		return;
	crash_recovery_helper.dirty_disk();
	display_dirty_disk();
	if (loader_state.loading_main_menu)
	{
		if (!c_mod_system::GetModManager().GetMod(kMainMenu))
		{
			Patches::Core::ExecuteShutdownCallbacks();
			exit(0);
			return;
		}
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable(Utils::Singleton<Modules::ModuleGame>::Instance().VarMainMenuMod, "", true);
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("writeconfig");
	}
	main_menu_launch_safe();
}

c_basic_buffer<void> *cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook(c_basic_buffer<void> *buffer) // 0x10925F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook@@YAPAV?$c_basic_buffer@X@@PAV1@@Z");
	// `anonymous-namespace'::cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook
	// static ...; // 0x10926080
	// static ...; // 0x10926074
	// static ...; // 0x1092606C
	// c_basic_buffer<void> *buffer;
	// unsigned long actual_size;
	// unsigned long overhead;
	// void (*const physical_memory_stage_push)(__int32);
	// unsigned long required_size;
	// void *memory;
	// function call : void (*const)(__int32)

	void (*const physical_memory_stage_push)(__int32) = reinterpret_cast<void (*)(__int32)>(0x51DC00);
	physical_memory_stage_push(1);
	unsigned long overhead = 0x3200000;
	unsigned long required_size = resource_loader_state.required_page_memory_size + overhead;
	c_physical_memory_manager::push(_physical_memory_stage_resources);
	unsigned long actual_size = 0;
	void *memory = c_physical_memory_manager::allocate(_physical_memory_stage_resources, "resource-memory", required_size, 12, &actual_size);
	if (!memory)
	{
		error_helper.failed_to_allocate_tag_resource_memory();
		dirty_disk_hook();
		return nullptr;
	}
	#line 1648 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\ModSync.cpp"
		assert(((ulong)memory >= ((ulong)g_cache_file_tag_globals->memory + g_cache_file_tag_globals->memory_size)));
		#line 1659 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\ModSync.cpp"
	buffer->address = memory;
	buffer->size = actual_size;
	return buffer;
}

bool main_game_initialize_for_new_map_hook(bool a1, s_game_options *options) // 0x10928950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_game_initialize_for_new_map_hook@@YA_N_NPAUs_game_options@@@Z");
	// `anonymous-namespace'::main_game_initialize_for_new_map_hook
	// s_game_options *options;
	// bool (*const main_game_initialize_for_new_map)(bool, s_game_options *);
	// function call : bool (*const)(bool, s_game_options *)

	bool (*const main_game_initialize_for_new_map)(bool, s_game_options *) = (bool(*const)(bool, s_game_options *))0x567560;

	if (!a1 && !font_initialize_for_new_map(options))
	{
		error_helper.failed_to_initialize_font_cache();
		return false;
	}

	return main_game_initialize_for_new_map(a1, options);
}

void scenario_tags_mark_necessary_bitmaps() // 0x10929660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scenario_tags_mark_necessary_bitmaps@@YAXXZ");
	// `anonymous-namespace'::scenario_tags_mark_necessary_bitmaps
	// procedure flags: nofpo
	// static ...; // 0x109299A3
	// static ...; // 0x10929996
	// static ...; // 0x10929991
	// static ...; // 0x1092998C
	// static ...; // 0x1092995C
	// static ...; // 0x10929954
	// s_tag_iterator tag_iterator;
	// scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1> mark_bitmap;
		// s_scenario_lightmap_bsp_data *lbsp;
		// s_scenario_structure_bsp *sbsp;
			// c_tag_block<s_structure_collision_material> &<range>$L0;
			// s_structure_collision_material *<begin>$L0;
			// s_structure_collision_material *<end>$L0;
				// s_structure_collision_material const &element;
					// c_render_method *rm;
						// __int32 const *<end>$L1;
						// __int32 const *<begin>$L1;
						// std::initializer_list<int> &<range>$L1;
							// __int32 i;
								// long texture_index;
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	auto mark_bitmap = [](long bitmap_index)
	{
		if (bitmap_index == -1)
			return;
		s_bitmap_definition *bitmap = (s_bitmap_definition *)tag_get('bitm', bitmap_index);
		bitmap->runtime_flags |= 0x80;
	};
	s_tag_iterator tag_iterator;
	((void(__cdecl *)(s_tag_iterator *, unsigned long))0x5033E0)(&tag_iterator, 'Lbsp');
	while (((long(__cdecl *)(s_tag_iterator *))0x503400)(&tag_iterator) != -1)
	{
		s_scenario_lightmap_bsp_data *lbsp = (s_scenario_lightmap_bsp_data *)tag_get('Lbsp', tag_iterator.tag_index);
		mark_bitmap(((s_tag_reference *)lbsp->lightmap_sh_coefficients_bitmap)->index);
		mark_bitmap(((s_tag_reference *)lbsp->lightmap_dominant_light_direction_bitmap)->index);
	}
	((void(__cdecl *)(s_tag_iterator *, unsigned long))0x5033E0)(&tag_iterator, 'sbsp');
	while (((long(__cdecl *)(s_tag_iterator *))0x503400)(&tag_iterator) != -1)
	{
		s_scenario_structure_bsp *sbsp = (s_scenario_structure_bsp *)tag_get('sbsp', tag_iterator.tag_index);
		for (s_structure_collision_material const &element : sbsp->collision_materials)
		{
			if (element.render_method.index == -1)
				continue;
			c_render_method *rm = (c_render_method *)tag_get('rm  ', element.render_method.index);
			for (int i : { 0, 1, 2, 3, 5 })
			{
				long texture_index = (*(c_tag_block<s_render_method_postprocess_definition> *)((char *)rm + 0x28))->queryable_properties[i];
				if (texture_index < 0 || texture_index >= (*(c_tag_block<s_render_method_postprocess_definition> *)((char *)rm + 0x28))->texture_constants.count)
					continue;
				mark_bitmap((*(c_tag_block<s_render_method_postprocess_definition> *)((char *)rm + 0x28))->texture_constants[texture_index].bitmap.index);
			}
		}
	}
}

void __fastcall begin_tracking_resource_hook(void *thisptr, void *unused, tag_resource_tracking_setup *setup) // 0x10924170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin_tracking_resource_hook@@YIXPAX0PAUtag_resource_tracking_setup@hades_file_local@@@Z");
	// `anonymous-namespace'::begin_tracking_resource_hook
	// tag_resource_tracking_setup *setup;
	// void (*const sub_9EA6E0)(void *, long, bool);
	// s_cache_file_tag_resource_table_runtime *resource_table;
		// s_tag_resource *resource;
		// void *page_manager;
		// bool keep_in_memory;
			// s_bitmap_definition *bitmap;
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(void *, long, bool)

	void (__thiscall *const sub_9EA6E0)(void *, long, bool) = reinterpret_cast<void (__thiscall *)(void *, long, bool)>(0x9EA6E0);
	s_cache_file_tag_resource_table_runtime *resource_table = *((s_cache_file_tag_resource_table_runtime **)setup->datum_handler + 1);
	if ((setup->control_state_datum->flags >> 5) & 1)
	{
		void *page_manager = *(void **)offset_pointer(thisptr, 0x44);
		s_tag_resource *resource = resource_table->resources[(short)setup->page_handle];
		bool keep_in_memory = true;
		if (resource->parent_tag.group_tag == 'bitm')
		{
			s_bitmap_definition *bitmap = (s_bitmap_definition *)tag_get('bitm', resource->parent_tag.index);
			keep_in_memory = ((short)bitmap->runtime_flags & 0x80) != 0;
		}
		else if (resource->parent_tag.group_tag == 'snd!')
		{
			keep_in_memory = false;
			setup->control_state_datum->flags &= ~0x20;
		}
		sub_9EA6E0(page_manager, setup->control_state_datum->page_handle, !keep_in_memory);
	}
}

static void OnMapLoaded(char const *mapPath) // 0x109238B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoaded@@YAXPBD@Z");
	// `anonymous-namespace'::OnMapLoaded
	// char const *mapPath;

	crash_recovery_helper.map_load_end();
}

static void OnShutdown() // 0x10923900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@@YAXXZ");
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo

	crash_recovery_helper.shutdown();
}

void main_menu_launch_force_hook() // 0x10928C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_menu_launch_force_hook@@YAXXZ");
	// `anonymous-namespace'::main_menu_launch_force_hook
	// procedure flags: nofpo
	// static ...; // 0x10928D8C
	// static ...; // 0x10928D80
	// static ...; // 0x10928D78
	// s_game_options options;
	// void (*const main_game_change)(s_game_options *);
	// void (*const c_map_variant)(s_map_variant *);
	// bool (*const game_options_validate)(s_game_options *);
	// void (*const s_game_options__ctor)(s_game_options *);
	// void (*const main_menu_build_game_options)(s_game_options *);
	// function call : EModResult (EModIndex, char const *, bool)
	// function call : void (*const)(s_game_options *)
	// function call : void (*const)(s_game_options *)
	// function call : bool (*const)(s_game_options *)
	// function call : void (*const)(s_game_options *)

	void (*const main_menu_build_game_options)(s_game_options *) = reinterpret_cast<void (*)(s_game_options *)>(0x568080);
	void (*const main_game_change)(s_game_options *) = reinterpret_cast<void (*)(s_game_options *)>(0x566E70);
	void (__thiscall *const s_game_options__ctor)(s_game_options *) = reinterpret_cast<void (__thiscall *)(s_game_options *)>(0x485420);
	bool (*const game_options_validate)(s_game_options *) = reinterpret_cast<bool (*)(s_game_options *)>(0x532680);
	void (*const c_map_variant)(s_map_variant *) = reinterpret_cast<void (*)(s_map_variant *)>(0x580C60);

	if (!do_load_main_menu_mod_package())
		c_mod_system::GetModManager().SetMod((EModIndex)1, nullptr, true);
	levels_yield_until_enumerate_done();

	s_game_options options;
	s_game_options__ctor(&options);
	main_menu_build_game_options(&options);
	game_options_validate(&options);
	main_game_change(&options);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_cache_file_loaded_state@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_cache_file_loaded_state::s_cache_file_loaded_state() = default; // 0x109218B0

void main_menu_launch_hook() // 0x10928DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_menu_launch_hook@@YAXXZ");
	// `anonymous-namespace'::main_menu_launch_hook
	// procedure flags: nofpo
	// char (*const main_halted_with_errors)();
	// long (*const user_interface_enter_game_shell)();
	// function call : char (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()

	char (*const main_menu_launch_safe_func)() = (char (*const)())0x505860;
	void (*const main_menu_launch_func)() = (void (*const)())0xa84330;

	if (!main_menu_launch_safe_func())
	{
		if (((bool (*const)())0x5314b0)() && ((bool (*const)())0x531e90)())
		{
			main_menu_launch_func();
		}
		else
		{
			main_menu_launch_force_hook();
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1s_cache_file_loaded_state@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_cache_file_loaded_state::~s_cache_file_loaded_state() = default; // 0x10922160

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Ref<IMod> & Ref<IMod>::operator=(Ref<IMod> const &);
template Ref<IMod>::Ref();
template bool c_enum<enum e_hs_type,short>::operator<=(e_hs_type const &) const;
template bool c_enum<enum e_hs_type,short>::operator>=(e_hs_type const &) const;
template bool s_static_array<s_cached_map_file,15>::valid(__int32);
template c_enum<enum e_game_engine_type,long>::c_enum();
template c_enum<enum e_game_mode,long>::c_enum();
template c_flags<enum e_bitmap_runtime_flags,short> & c_flags<enum e_bitmap_runtime_flags,short>::operator|=(__int32 const);
template c_flags<enum e_bitmap_runtime_flags,short>::operator short() const;
template c_flags<enum e_tag_resource_page_flags,unsigned char> c_flags<enum e_tag_resource_page_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_tag_resource_page_flags,unsigned char>::c_flags(unsigned char const &);
template c_flags<enum e_tag_resource_page_flags,unsigned char>::operator bool() const;
template s_cached_map_file & s_static_array<s_cached_map_file,15>::operator[](long);
template s_hs_syntax_node * c_tag_block<s_hs_syntax_node>::begin();
template s_hs_syntax_node * c_tag_block<s_hs_syntax_node>::end();
template s_render_method_texture_constant & c_tag_block<s_render_method_texture_constant>::operator[](__int32);
template s_structure_collision_material * c_tag_block<s_structure_collision_material>::begin();
template s_structure_collision_material * c_tag_block<s_structure_collision_material>::end();

/* ---------- explicit instantiations */
template s_static_array<s_game_player_options,16>::s_static_array();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_static_array<s_cached_map_file,15> &g_cached_map_files = *reinterpret_cast<s_static_array<s_cached_map_file,15> *>(0x240B1E8); }
namespace hades_file_local { s_cache_file_loaded_state loader_state; }
namespace hades_file_local { Ref<IMod> current_mod; }
namespace hades_file_local { s_resource_loaded_state resource_loader_state; }
namespace hades_file_local { namespace hades_file_local_ModSync { char const *const k_mods_mainmenu_virtual_path = "mods\\mainmenu"; } }
namespace hades_file_local { namespace hades_file_local_ModSync { char const *const k_mods_game_virtual_path = "mods\\game"; } }
void (*const security_get_working_memory)(long, void **, long *) = reinterpret_cast<decltype(security_get_working_memory)>(0x508DB0);

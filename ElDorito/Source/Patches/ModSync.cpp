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
bool c_cache_file_tag_resource_runtime_manager__get_page_hook(c_indirect_cache_file_location_atlas *thisptr, void *unused, long index, long a4, s_indirect_cache_file_page *out_location);
void display_dirty_disk();
void main_menu_launch_safe();
void dirty_disk_hook();
c_basic_buffer<void> *cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook(c_basic_buffer<void> *buffer);
bool main_game_initialize_for_new_map_hook(bool a1, s_game_options *options);
void scenario_tags_mark_necessary_bitmaps();
void begin_tracking_resource_hook(void *thisptr, void *unused, tag_resource_tracking_setup *setup);
void OnMapLoaded(char const *mapPath);
void OnShutdown();
void main_menu_launch_force_hook();
void main_menu_launch_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const k_mods_mainmenu_virtual_path; // 0x11197DC0
	extern char const *const k_mods_game_virtual_path; // 0x11197DC4
	extern c_map_load_error_helper error_helper; // 0x12409584
	extern c_map_load_crash_recovery_helper crash_recovery_helper; // 0x12409560
	extern Ref<IMod> current_mod; // 0x1240985C
	extern s_static_array<s_cached_map_file,15> &g_cached_map_files; // 0x113534AC
}
using namespace hades_file_local;
/* ---------- public code */

_inline c_async_completion_flag::c_async_completion_flag() // 0x10921640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_async_completion_flag@@QAE@XZ");
	// c_async_completion_flag *const this;

	compiler_generated();
}

_inline c_game_variant::c_game_variant() // 0x109216A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_game_variant@@QAE@XZ");
	// c_game_variant *const this;

	compiler_generated();
}

_inline c_map_load_crash_recovery_helper::c_map_load_crash_recovery_helper() // 0x109216F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_map_load_crash_recovery_helper@@QAE@XZ");
	// c_map_load_crash_recovery_helper *const this;

	compiler_generated();
}

_inline c_map_load_error_helper::c_map_load_error_helper() // 0x10921770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_map_load_error_helper@@QAE@XZ");
	// c_map_load_error_helper *const this;

	compiler_generated();
}

_inline c_mod_cache_tag_remapper::c_mod_cache_tag_remapper() // 0x109217C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_mod_cache_tag_remapper@@QAE@XZ");
	// c_mod_cache_tag_remapper *const this;

	compiler_generated();
}

_inline s_game_options::s_game_options() // 0x109219A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_game_options@@QAE@XZ");
	// s_game_options *const this;

	compiler_generated();
}

_inline s_game_player_options::s_game_player_options() // 0x10921A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_game_player_options@@QAE@XZ");
	// s_game_player_options *const this;

	compiler_generated();
}

_inline s_player_appearance::s_player_appearance() // 0x10921A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_player_appearance@@QAE@XZ");
	// s_player_appearance *const this;

	compiler_generated();
}

_inline s_player_configuration::s_player_configuration() // 0x10921AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_player_configuration@@QAE@XZ");
	// s_player_configuration *const this;

	compiler_generated();
}

_inline s_player_configuration_from_host::s_player_configuration_from_host() // 0x10921B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_player_configuration_from_host@@QAE@XZ");
	// s_player_configuration_from_host *const this;

	compiler_generated();
}

_inline c_map_load_crash_recovery_helper::~c_map_load_crash_recovery_helper() // 0x10922050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_map_load_crash_recovery_helper@@QAE@XZ");
	// c_map_load_crash_recovery_helper *const this;

	compiler_generated();
}

_inline c_map_load_error_helper::~c_map_load_error_helper() // 0x109220A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_map_load_error_helper@@QAE@XZ");
	// c_map_load_error_helper *const this;

	compiler_generated();
}

_inline c_mod_cache_tag_remapper::~c_mod_cache_tag_remapper() // 0x109220F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_mod_cache_tag_remapper@@QAE@XZ");
	// c_mod_cache_tag_remapper *const this;

	compiler_generated();
}

namespace Patches
{
	namespace ModSync
	{
		_extern void _sub_10922620();
		void ApplyAll() // 0x10922620
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ModSync@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10922620();
		}

		_extern void _sub_10923950();
		void Tick() // 0x10923950
		{
			mangled_x86(MANGLED_TODO, "?Tick@ModSync@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10923950();
		}
	}
}

extern s_cache_tag_instance *_sub_109265E0(long);
s_cache_tag_instance *cache_tag_instance_get(long tag_index) // 0x109265E0
{
	mangled_x86(MANGLED_TODO, "?cache_tag_instance_get@@YAPAUs_cache_tag_instance@@J@Z");
	// long tag_index;
	// long const absolute_index;
	todo("implement");
	s_cache_tag_instance * __result = _sub_109265E0(tag_index);
	return __result;
}

extern char const *_sub_10929D50(long);
char const *tag_get_name(long tag_index) // 0x10929D50
{
	mangled_x86(MANGLED_TODO, "?tag_get_name@@YAPBDJ@Z");
	// long tag_index;
	// s_cache_tag_instance const *instance;
	todo("implement");
	char const * __result = _sub_10929D50(tag_index);
	return __result;
}

_extern long _sub_10929C10(unsigned long, char const *);
long tag_find_by_name(unsigned long group_tag, char const *name) // 0x10929C10
{
	mangled_x86(MANGLED_TODO, "?tag_find_by_name@@YAJKPBD@Z");
	// char const *name;
	{
		// long i;
		{
			// s_cache_tag_instance *instance;
			// long tag_index;
		}
	}
	todo("implement");
	long __result = _sub_10929C10(group_tag, name);
	return __result;
}

/* ---------- private code */

_extern bool _sub_109278B0(long, s_cache_tag_instance *);
bool fixup_mod_tag(long tag_index, s_cache_tag_instance *instance) // 0x109278B0
{
	// `anonymous-namespace'::fixup_mod_tag
	// s_cache_tag_instance *instance;
	// long **tag_reference_fixups;
	// long *dependencies;
	{
		// long j;
		{
			// long *tag_index_pointer;
			// long remapped_tag_index;
		}
	}
	{
		// s_scenario *scenario;
		{
			// c_tag_block<s_hs_syntax_node> &<range>$L0;
			// s_hs_syntax_node *<begin>$L0;
			// s_hs_syntax_node *<end>$L0;
			{
				// s_hs_syntax_node &expr;
				{
					// long remapped_tag_index;
					// long *ref;
				}
			}
		}
	}
	{
		// long i;
		{
			// long dependency_tag_index;
		}
	}
	todo("implement");
	bool __result = _sub_109278B0(tag_index, instance);
	return __result;
}

_extern bool _sub_10925170(long);
bool cache_file_load_tag(long tag_index) // 0x10925170
{
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
	{
		// s_cache_tag_instance const *mod_tag_instance;
	}
	{
		// long i;
	}
	{
		{
			// long dependency_tag_index;
		}
	}
	todo("implement");
	bool __result = _sub_10925170(tag_index);
	return __result;
}

_extern bool _sub_10924670();
bool cache_file_allocate_tags() // 0x10924670
{
	// `anonymous-namespace'::cache_file_allocate_tags
	// procedure flags: nofpo
	// unsigned long const max_table_size;
	// s_cache_file_tag_globals *global_state;
	// long const runtime_tag_count;
	// unsigned long const table_size;
	todo("implement");
	bool __result = _sub_10924670();
	return __result;
}

_extern void _sub_10924960();
void cache_file_compute_and_verify_signature() // 0x10924960
{
	// `anonymous-namespace'::cache_file_compute_and_verify_signature
	// procedure flags: nofpo
	// s_cache_file_secure_memory *(*const cache_file_get_secure_working_memory)();
	// s_cache_file_secure_memory *secure_memory;
	// void (*const cache_file_builder_security_clean_header)(s_cache_file_header *);
	{
		// unsigned char *block;
		// long bytes_remaining;
		{
			// long block_size;
		}
	}
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
	todo("implement");
	_sub_10924960();
}

_extern void _sub_10924D90();
void cache_file_invalidate_signature() // 0x10924D90
{
	// `anonymous-namespace'::cache_file_invalidate_signature
	// procedure flags: nofpo
	// static ...; // 0x10924E4F
	// static ...; // 0x10924E3C
	// static ...; // 0x10924E24
	// static ...; // 0x10924E1C
	// void *secure_memory;
	// long secure_memory_size;
	// function call : void (*const)(long, void **, long *)
	todo("implement");
	_sub_10924D90();
}

_extern bool _sub_10924E90();
bool cache_file_load_allocate_tags() // 0x10924E90
{
	// `anonymous-namespace'::cache_file_load_allocate_tags
	// procedure flags: nofpo
	// long game_globals_tag;
	// bool mainmenu_mod;
	// long scenario_tag_index;
	{
		// long scenario_mod_tag_index;
		// std::shared_ptr<c_cache_file_tag_cache> &mod_cache;
	}
	// function call : long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10924E90();
	return __result;
}

_extern bool _sub_109294C0(char const *);
bool open_mod_package_resource_cache(char const *filepath) // 0x109294C0
{
	// `anonymous-namespace'::open_mod_package_resource_cache
	// char const *filepath;
	// constexpr bool (*const `open_mod_package_resource_cache'::`2'::cache_file_open)(s_cached_map_file *, char const *); // constant == 5945824
	// constexpr bool (*const `open_mod_package_resource_cache'::`2'::cache_file_read_header)(__int32); // constant == 5946320
	// function call : bool (*const)(s_cached_map_file *, char const *)
	// function call : bool (*const)(__int32)
	todo("implement");
	bool __result = _sub_109294C0(filepath);
	return __result;
}

_extern void _sub_10926750();
void close_mod_package_resource_cache() // 0x10926750
{
	// `anonymous-namespace'::close_mod_package_resource_cache
	// procedure flags: nofpo
	// void (*const cached_map_file_close)(long);
	// function call : void (*const)(long)
	todo("implement");
	_sub_10926750();
}

_extern bool _sub_10926D30();
bool do_load_main_menu_mod_package() // 0x10926D30
{
	// `anonymous-namespace'::do_load_main_menu_mod_package
	// procedure flags: nofpo
	// static ...; // 0x10926F4C
	// static ...; // 0x10926F40
	// static ...; // 0x10926F38
	// std::string &MainMenuMod;
	// s_static_string<256> file_path;
	// EModResult result;
	// function call : EModResult (EModIndex, char const *, bool)
	todo("implement");
	bool __result = _sub_10926D30();
	return __result;
}

_extern void _sub_10928790();
void loader_reset() // 0x10928790
{
	// `anonymous-namespace'::loader_reset
	// procedure flags: nofpo
	todo("implement");
	_sub_10928790();
}

_extern bool _sub_10927E90();
bool load_string_id_cache() // 0x10927E90
{
	// `anonymous-namespace'::load_string_id_cache
	// procedure flags: nofpo
	// static ...; // 0x10928146
	// static ...; // 0x1092813C
	// static ...; // 0x10928124
	// static ...; // 0x1092811C
	// IMod *mod;
	// std::shared_ptr<Blam::Cache::StringIDCache> string_id_cache;
	{
		// std::shared_ptr<c_cache_file_interface> mod_cache;
	}
	// function call : IMod *(EModIndex) const
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<Blam::Cache::StringIDCache> () const
	todo("implement");
	bool __result = _sub_10927E90();
	return __result;
}

_extern bool _sub_10928210(long, bool);
bool loader_initialize(long map_id, bool is_mainmenu) // 0x10928210
{
	// `anonymous-namespace'::loader_initialize
	// static ...; // 0x1092865C
	// static ...; // 0x10928654
	// long map_id;
	// bool is_mainmenu;
	// IMod *mod;
	{
		// std::shared_ptr<c_cache_file_interface> mod_cache;
	}
	// function call : IMod *(EModIndex) const
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const
	// function call : c_mod_package *(bool) const
	// function call : char const *() const
	todo("implement");
	bool __result = _sub_10928210(map_id, is_mainmenu);
	return __result;
}

_extern bool _sub_109289F0(char const *);
bool main_load_map_internal_hook(char const *map_path) // 0x109289F0
{
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
	todo("implement");
	bool __result = _sub_109289F0(map_path);
	return __result;
}

_extern void _sub_10926660(char const *, char *);
void canonicalize_map_path_hook(char const *path, char *canonical_path) // 0x10926660
{
	// `anonymous-namespace'::canonicalize_map_path_hook
	// char *canonical_path;
	{
		// char const *filename;
		// char const *directory;
	}
	{
	}
	todo("implement");
	_sub_10926660(path, canonical_path);
}

_extern bool _sub_10929090(EModIndex, IMod *, long, char const *);
bool open_mod_package_map_file(EModIndex index, IMod *mod, long map_file_index, char const *virtual_file_path) // 0x10929090
{
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
	{
		// char *p;
	}
	{
		// __int32 i;
	}
	// function call : c_mod_package *(bool) const
	// function call : EModResult (EModIndex, __int32, bool)
	todo("implement");
	bool __result = _sub_10929090(index, mod, map_file_index, virtual_file_path);
	return __result;
}

_extern bool _sub_10925720(long, char *);
bool cache_file_open_internal_hook(long map_file_index, char *map_file_path) // 0x10925720
{
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
	todo("implement");
	bool __result = _sub_10925720(map_file_index, map_file_path);
	return __result;
}

_extern void _sub_109260E0(s_cache_file_tag_resource_table *);
void cache_file_tag_resource_table_read(s_cache_file_tag_resource_table *out_table) // 0x109260E0
{
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
	{
		// e_cache_file_tag_resource_location location;
		{
			// long map_file_index;
			// unsigned long base_offset;
		}
	}
	{
		// long offset;
		// long location_index;
		{
			// long table_size;
		}
	}
	// function call : __int32 (*const)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)
	// function call : __int32 (*const)(s_file_handle, void *, long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)
	todo("implement");
	_sub_109260E0(out_table);
}

extern s_tag_resource_data *_sub_10925930();
s_tag_resource_data *cache_file_tag_load_resource_table_hook() // 0x10925930
{
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
	{
		// long i;
	}
	{
		// __int32 i;
		{
			// long tag_index;
			// unsigned long *resource_fixups;
			// s_cache_tag_instance *tag_instance;
			{
				// __int32 j;
				{
					// long *entry_ptr;
					{
						// s_tag_resource *pageable;
						// bool zero_size;
						{
							// bool (*const bitmap_group_needs_backing_strorage)(long);
							// unsigned long resource_page_size;
							// long offset;
							// long location_index;
							{
								// unsigned long resource_count;
							}
						}
					}
				}
			}
		}
	}
	// function call : bool (*const)(long)
	todo("implement");
	s_tag_resource_data * __result = _sub_10925930();
	return __result;
}

_extern bool _sub_10924330(c_indirect_cache_file_location_atlas *, void *, long, long, s_indirect_cache_file_page *);
bool c_cache_file_tag_resource_runtime_manager__get_page_hook(c_indirect_cache_file_location_atlas *thisptr, void *unused, long index, long a4, s_indirect_cache_file_page *out_location) // 0x10924330
{
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
	todo("implement");
	bool __result = _sub_10924330(thisptr, unused, index, a4, out_location);
	return __result;
}

_extern void _sub_10926A30();
void display_dirty_disk() // 0x10926A30
{
	// `anonymous-namespace'::display_dirty_disk
	// procedure flags: nofpo
	todo("implement");
	_sub_10926A30();
}

_extern void _sub_10928EB0();
void main_menu_launch_safe() // 0x10928EB0
{
	// `anonymous-namespace'::main_menu_launch_safe
	// procedure flags: nofpo
	// void (*const network_life_cycle_end)();
	// void (*const network_life_cycle_request_leave)(__int32);
	// bool (*const network_life_cycle_get_state)();
	// function call : bool (*const)()
	// function call : void (*const)(__int32)
	// function call : void (*const)()
	// function call : void (*const)()
	todo("implement");
	_sub_10928EB0();
}

_extern void _sub_109267B0();
void dirty_disk_hook() // 0x109267B0
{
	// `anonymous-namespace'::dirty_disk_hook
	// procedure flags: nofpo
	// function call : unsigned long ()
	// function call : IMod *(EModIndex) const
	todo("implement");
	_sub_109267B0();
}

extern c_basic_buffer<void> *_sub_10925F70(c_basic_buffer<void> *);
c_basic_buffer<void> *cache_file_tag_resource_runtime_manager__allocate_memory_buffer_hook(c_basic_buffer<void> *buffer) // 0x10925F70
{
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
	todo("implement");
	c_basic_buffer<void> * __result = _sub_10925F70(buffer);
	return __result;
}

_extern bool _sub_10928950(bool, s_game_options *);
bool main_game_initialize_for_new_map_hook(bool a1, s_game_options *options) // 0x10928950
{
	// `anonymous-namespace'::main_game_initialize_for_new_map_hook
	// s_game_options *options;
	// bool (*const main_game_initialize_for_new_map)(bool, s_game_options *);
	// function call : bool (*const)(bool, s_game_options *)
	todo("implement");
	bool __result = _sub_10928950(a1, options);
	return __result;
}

_extern void _sub_10929660();
void scenario_tags_mark_necessary_bitmaps() // 0x10929660
{
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
	{
		// s_scenario_lightmap_bsp_data *lbsp;
	}
	{
		// s_scenario_structure_bsp *sbsp;
		{
			// c_tag_block<s_structure_collision_material> &<range>$L0;
			// s_structure_collision_material *<begin>$L0;
			// s_structure_collision_material *<end>$L0;
			{
				// s_structure_collision_material const &element;
				{
					// c_render_method *rm;
					{
						// __int32 const *<end>$L1;
						// __int32 const *<begin>$L1;
						// std::initializer_list<int> &<range>$L1;
						{
							// __int32 i;
							{
								// long texture_index;
							}
						}
					}
				}
			}
		}
	}
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10929660();
}

_extern void _sub_10924170(void *, void *, tag_resource_tracking_setup *);
void begin_tracking_resource_hook(void *thisptr, void *unused, tag_resource_tracking_setup *setup) // 0x10924170
{
	// `anonymous-namespace'::begin_tracking_resource_hook
	// tag_resource_tracking_setup *setup;
	// void (*const sub_9EA6E0)(void *, long, bool);
	// s_cache_file_tag_resource_table_runtime *resource_table;
	{
		// s_tag_resource *resource;
		// void *page_manager;
		// bool keep_in_memory;
		{
			// s_bitmap_definition *bitmap;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(void *, long, bool)
	todo("implement");
	_sub_10924170(thisptr, unused, setup);
}

_extern void _sub_109238B0(char const *);
void OnMapLoaded(char const *mapPath) // 0x109238B0
{
	// `anonymous-namespace'::OnMapLoaded
	// char const *mapPath;
	todo("implement");
	_sub_109238B0(mapPath);
}

_extern void _sub_10923900();
void OnShutdown() // 0x10923900
{
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	todo("implement");
	_sub_10923900();
}

_extern void _sub_10928C40();
void main_menu_launch_force_hook() // 0x10928C40
{
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
	todo("implement");
	_sub_10928C40();
}

_inline s_cache_file_loaded_state::s_cache_file_loaded_state() // 0x109218B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_cache_file_loaded_state@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_cache_file_loaded_state::s_cache_file_loaded_state
	// s_cache_file_loaded_state *const this;

	compiler_generated();
}

_extern void _sub_10928DF0();
void main_menu_launch_hook() // 0x10928DF0
{
	// `anonymous-namespace'::main_menu_launch_hook
	// procedure flags: nofpo
	// char (*const main_halted_with_errors)();
	// long (*const user_interface_enter_game_shell)();
	// function call : char (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	todo("implement");
	_sub_10928DF0();
}

_inline s_cache_file_loaded_state::~s_cache_file_loaded_state() // 0x10922160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_cache_file_loaded_state@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_cache_file_loaded_state::~s_cache_file_loaded_state
	// s_cache_file_loaded_state *const this;

	compiler_generated();
}

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

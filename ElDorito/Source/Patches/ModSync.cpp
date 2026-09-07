/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/static_array.inl"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/RefCounting.hpp"
#include "ElDorito.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/map_load_crash_recovery_helper.hpp"
#include "mods/map_load_error_helper.hpp"
#include "mods/mod_cache_tag_remapper.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "mods/tag_resource_memory_size_helper.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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
struct c_async_completion_flag;
struct c_game_variant;
struct c_map_load_error_helper;
struct lambda_1;
struct s_cache_tag_instance;
struct s_cached_map_file;
struct s_datum;
struct s_game_options;
struct s_game_player_options;
struct s_player_appearance;
struct s_player_configuration;
struct s_player_configuration_from_host;
namespace
{
	struct s_cache_file_loaded_state;
	struct s_resource_loaded_state;
	struct c_tag_resource_control_datum;
	struct tag_resource_tracking_setup;
}

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

namespace
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
//class scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1>
//{
//public:
//	void operator()(long) const;
//};
//static_assert(sizeof(scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1>) == 1, "Invalid scenario_tags_mark_necessary_bitmaps::__l2::<lambda_1> size");

namespace
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

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *const k_mods_mainmenu_virtual_path; // 0x11197DC0
	extern char const *const k_mods_game_virtual_path; // 0x11197DC4
	extern c_map_load_error_helper error_helper; // 0x12409584
	extern c_map_load_crash_recovery_helper crash_recovery_helper; // 0x12409560
	extern Ref<IMod> current_mod; // 0x1240985C
	extern s_static_array<s_cached_map_file,15> &g_cached_map_files; // 0x113534AC
}
/* ---------- public code */

extern c_async_completion_flag* _sub_10921640(c_async_completion_flag *const);
_inline c_async_completion_flag::c_async_completion_flag() // 0x10921640
{
	mangled_x86(MANGLED_TODO, "??0c_async_completion_flag@@QAE@XZ");
	// c_async_completion_flag *const this;
	compiler_generated();
	todo("implement");
	_sub_10921640(this);
}

extern c_game_variant* _sub_109216A0(c_game_variant *const);
_inline c_game_variant::c_game_variant() // 0x109216A0
{
	mangled_x86(MANGLED_TODO, "??0c_game_variant@@QAE@XZ");
	// c_game_variant *const this;
	compiler_generated();
	todo("implement");
	_sub_109216A0(this);
}

extern c_map_load_crash_recovery_helper* _sub_109216F0(c_map_load_crash_recovery_helper *const);
_inline c_map_load_crash_recovery_helper::c_map_load_crash_recovery_helper() // 0x109216F0
{
	mangled_x86(MANGLED_TODO, "??0c_map_load_crash_recovery_helper@@QAE@XZ");
	// c_map_load_crash_recovery_helper *const this;
	compiler_generated();
	todo("implement");
	_sub_109216F0(this);
}

extern c_map_load_error_helper* _sub_10921770(c_map_load_error_helper *const);
_inline c_map_load_error_helper::c_map_load_error_helper() // 0x10921770
{
	mangled_x86(MANGLED_TODO, "??0c_map_load_error_helper@@QAE@XZ");
	// c_map_load_error_helper *const this;
	compiler_generated();
	todo("implement");
	_sub_10921770(this);
}

extern c_mod_cache_tag_remapper* _sub_109217C0(c_mod_cache_tag_remapper *const);
_inline c_mod_cache_tag_remapper::c_mod_cache_tag_remapper() // 0x109217C0
{
	mangled_x86(MANGLED_TODO, "??0c_mod_cache_tag_remapper@@QAE@XZ");
	// c_mod_cache_tag_remapper *const this;
	compiler_generated();
	todo("implement");
	_sub_109217C0(this);
}

extern s_game_options* _sub_109219A0(s_game_options *const);
_inline s_game_options::s_game_options() // 0x109219A0
{
	mangled_x86(MANGLED_TODO, "??0s_game_options@@QAE@XZ");
	// s_game_options *const this;
	compiler_generated();
	todo("implement");
	_sub_109219A0(this);
}

extern s_game_player_options* _sub_10921A30(s_game_player_options *const);
_inline s_game_player_options::s_game_player_options() // 0x10921A30
{
	mangled_x86(MANGLED_TODO, "??0s_game_player_options@@QAE@XZ");
	// s_game_player_options *const this;
	compiler_generated();
	todo("implement");
	_sub_10921A30(this);
}

extern s_player_appearance* _sub_10921A90(s_player_appearance *const);
_inline s_player_appearance::s_player_appearance() // 0x10921A90
{
	mangled_x86(MANGLED_TODO, "??0s_player_appearance@@QAE@XZ");
	// s_player_appearance *const this;
	compiler_generated();
	todo("implement");
	_sub_10921A90(this);
}

extern s_player_configuration* _sub_10921AF0(s_player_configuration *const);
_inline s_player_configuration::s_player_configuration() // 0x10921AF0
{
	mangled_x86(MANGLED_TODO, "??0s_player_configuration@@QAE@XZ");
	// s_player_configuration *const this;
	compiler_generated();
	todo("implement");
	_sub_10921AF0(this);
}

extern s_player_configuration_from_host* _sub_10921B50(s_player_configuration_from_host *const);
_inline s_player_configuration_from_host::s_player_configuration_from_host() // 0x10921B50
{
	mangled_x86(MANGLED_TODO, "??0s_player_configuration_from_host@@QAE@XZ");
	// s_player_configuration_from_host *const this;
	compiler_generated();
	todo("implement");
	_sub_10921B50(this);
}

_extern void _sub_10922050(c_map_load_crash_recovery_helper *const);
_inline c_map_load_crash_recovery_helper::~c_map_load_crash_recovery_helper() // 0x10922050
{
	mangled_x86(MANGLED_TODO, "??1c_map_load_crash_recovery_helper@@QAE@XZ");
	// c_map_load_crash_recovery_helper *const this;
	compiler_generated();
	todo("implement");
	_sub_10922050(this);
}

_extern void _sub_109220A0(c_map_load_error_helper *const);
_inline c_map_load_error_helper::~c_map_load_error_helper() // 0x109220A0
{
	mangled_x86(MANGLED_TODO, "??1c_map_load_error_helper@@QAE@XZ");
	// c_map_load_error_helper *const this;
	compiler_generated();
	todo("implement");
	_sub_109220A0(this);
}

_extern void _sub_109220F0(c_mod_cache_tag_remapper *const);
_inline c_mod_cache_tag_remapper::~c_mod_cache_tag_remapper() // 0x109220F0
{
	mangled_x86(MANGLED_TODO, "??1c_mod_cache_tag_remapper@@QAE@XZ");
	// c_mod_cache_tag_remapper *const this;
	compiler_generated();
	todo("implement");
	_sub_109220F0(this);
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

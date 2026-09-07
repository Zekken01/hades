/* ---------- headers */

#include "mods/font_package.hpp"
#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/async/async_definitions.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/multithreading/synchronization/critical_section.hpp"
#include "Blam/multithreading/synchronization/synchronized_int.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/RefCounting.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"

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
#include <limits>
#include <list>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
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
class c_file_open_scope;
class c_file_reference;
class c_mod_package;
class c_synchronized_int32;
struct begin;
struct c_async_completion_flag;
struct c_font_cache_scope_lock;
struct end;
struct s_file_handle;
struct s_file_reference;
struct s_font_loading_state;
struct s_font_loading_task;
struct s_font_package;
struct s_font_package_cache_entry;
struct s_font_package_file_header;
struct s_font_package_font_entry;
struct s_game_options;
struct s_mod_package_section_header;

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

// s_font_package_font_entry is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_font_package_file_header is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_font_package is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_font_package_cache_entry is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_font_loading_state is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_font_loading_task is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// c_font_cache_scope_lock is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern void font_package_do_work(bool blocking, s_font_package_cache_entry *entry);
extern void font_package_cache_flush();
extern void font_package_idle();
extern bool font_package_begin_load_package(char const *filename);
extern bool fonts_begin_loading_internal(bool blocking);
extern void font_package_set_defaults();
extern bool font_load_from_file_blocking(s_font_loading_state *loading_state, unsigned long size, void *buffer, s_font_package_file_header **out_header);
extern bool font_load_from_mod_package_blocking(c_mod_package *mod_package, unsigned long size, void *buffer, s_font_package_file_header **out_header);
extern e_async_completion font_load_callback(void *data);
extern void font_load(s_font_loading_state *loading_state, long font_index, char const *filename, bool blocking);
extern bool font_initialize_for_new_map(s_game_options *options);

extern "C" bool font_get_package_file_handle(s_file_handle *out_handle);
extern "C" bool font_in_emergency_mode();
extern "C" bool validate_fonts(s_font_package_file_header const *header);
extern "C" bool fixup_and_validate_font_package_file(void *buffer);

/* ---------- globals */

extern void *g_font_character_globals; // 0x11352990
extern s_static_array<s_font_package_cache_entry,8> *g_font_package_cache_entries; // 0x11352994
extern c_async_completion_flag *g_font_package_system_ready; // 0x11352998
extern long *g_font_package_salt; // 0x1135299C
extern s_font_loading_state *g_font_loading_state; // 0x113529A0
extern s_font_package_file_header *g_font_load_buffer; // 0x113529A4
extern s_font_package_file_header **g_font_package_file_header; // 0x113529A8
extern EModIndex g_mod_package_index; // 0x123B8900
extern s_static_string<256> g_font_package_file_path; // 0x123B8908

/* ---------- private variables */

/* ---------- public code */

extern c_font_cache_scope_lock* _sub_10888520(c_font_cache_scope_lock *const);
c_font_cache_scope_lock::c_font_cache_scope_lock() // 0x10888520
{
	mangled_x86(MANGLED_TODO, "??0c_font_cache_scope_lock@@QAE@XZ");
	// c_font_cache_scope_lock *const this;
	// void **font_character;
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10888520(this);
}

_extern void _sub_108885D0(c_font_cache_scope_lock *const);
c_font_cache_scope_lock::~c_font_cache_scope_lock() // 0x108885D0
{
	mangled_x86(MANGLED_TODO, "??1c_font_cache_scope_lock@@QAE@XZ");
	// c_font_cache_scope_lock *const this;
	// void **font_character;
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_108885D0(this);
}

_extern void _sub_108893C0(bool, s_font_package_cache_entry *);
void font_package_do_work(bool blocking, s_font_package_cache_entry *entry) // 0x108893C0
{
	mangled_x86(MANGLED_TODO, "?font_package_do_work@@YAX_NPAUs_font_package_cache_entry@@@Z");
	// static ...; // 0x10889660
	// static ...; // 0x10889658
	// bool blocking;
	// s_font_package_cache_entry *entry;
	// long package_index;
	// bool has_completed;
	{
		// s_file_handle file_handle;
		// unsigned long package_offset;
		// long task_id;
	}
	{
		// long read_size;
	}
	// function call : long (*const)(s_file_handle, void *, unsigned long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : bool (*const)(long, long)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)
	// function call : bool (*const)(s_font_package *)
	todo("implement");
	_sub_108893C0(blocking, entry);
}

_extern void _sub_10889280();
void font_package_cache_flush() // 0x10889280
{
	mangled_x86(MANGLED_TODO, "?font_package_cache_flush@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10889378
	// static ...; // 0x1088936C
	// static ...; // 0x10889364
	// c_font_cache_scope_lock lock;
	{
		// s_static_array<s_font_package_cache_entry,8> &<range>$L0;
		// s_font_package_cache_entry *<begin>$L0;
		// s_font_package_cache_entry *<end>$L0;
		{
			// s_font_package_cache_entry &entry;
		}
	}
	todo("implement");
	_sub_10889280();
}

_extern void _sub_10889730();
void font_package_idle() // 0x10889730
{
	mangled_x86(MANGLED_TODO, "?font_package_idle@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10889848
	// static ...; // 0x1088983C
	// static ...; // 0x10889834
	{
		// c_font_cache_scope_lock lock;
		{
			// s_static_array<s_font_package_cache_entry,8> &<range>$L0;
			// s_font_package_cache_entry *<begin>$L0;
			// s_font_package_cache_entry *<end>$L0;
			{
				// s_font_package_cache_entry &entry;
			}
		}
	}
	todo("implement");
	_sub_10889730();
}

_extern bool _sub_10889120(char const *);
bool font_package_begin_load_package(char const *filename) // 0x10889120
{
	mangled_x86(MANGLED_TODO, "?font_package_begin_load_package@@YA_NPBD@Z");
	// static ...; // 0x10889234
	// static ...; // 0x10889228
	// static ...; // 0x10889220
	// char const *filename;
	// c_font_cache_scope_lock lock;
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : void (*const)()
	todo("implement");
	bool __result = _sub_10889120(filename);
	return __result;
}

_extern bool _sub_108898F0(bool);
bool fonts_begin_loading_internal(bool blocking) // 0x108898F0
{
	mangled_x86(MANGLED_TODO, "?fonts_begin_loading_internal@@YA_N_N@Z");
	// bool blocking;
	// bool (*const font_load)(s_font_loading_state *, long, char const *, bool);
	// function call : bool (*const)(s_font_loading_state *, long, char const *, bool)
	todo("implement");
	bool __result = _sub_108898F0(blocking);
	return __result;
}

_extern void _sub_108898A0();
void font_package_set_defaults() // 0x108898A0
{
	mangled_x86(MANGLED_TODO, "?font_package_set_defaults@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_108898A0();
}

_extern bool _sub_10888DC0(s_font_loading_state *, unsigned long, void *, s_font_package_file_header **);
bool font_load_from_file_blocking(s_font_loading_state *loading_state, unsigned long size, void *buffer, s_font_package_file_header **out_header) // 0x10888DC0
{
	mangled_x86(MANGLED_TODO, "?font_load_from_file_blocking@@YA_NPAUs_font_loading_state@@KPAXPAPAUs_font_package_file_header@@@Z");
	// s_font_loading_state *loading_state;
	// unsigned long size;
	// void *buffer;
	// s_font_package_file_header **out_header;
	// unsigned long error;
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	todo("implement");
	bool __result = _sub_10888DC0(loading_state, size, buffer, out_header);
	return __result;
}

_extern bool _sub_10888F50(c_mod_package *, unsigned long, void *, s_font_package_file_header **);
bool font_load_from_mod_package_blocking(c_mod_package *mod_package, unsigned long size, void *buffer, s_font_package_file_header **out_header) // 0x10888F50
{
	mangled_x86(MANGLED_TODO, "?font_load_from_mod_package_blocking@@YA_NPAVc_mod_package@@KPAXPAPAUs_font_package_file_header@@@Z");
	// static ...; // 0x10889094
	// c_mod_package *mod_package;
	// unsigned long size;
	// void *buffer;
	// s_font_package_file_header **out_header;
	// c_file_reference file;
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_10888F50(mod_package, size, buffer, out_header);
	return __result;
}

extern e_async_completion _sub_10888CD0(void *);
e_async_completion font_load_callback(void *data) // 0x10888CD0
{
	mangled_x86(MANGLED_TODO, "?font_load_callback@@YA?AW4e_async_completion@@PAX@Z");
	// static ...; // 0x10888D88
	// static ...; // 0x10888D7C
	// static ...; // 0x10888D74
	// void *data;
	// s_font_loading_task *task_data;
	// s_font_package_file_header *header;
	// s_font_loading_state *loading_state;
	todo("implement");
	e_async_completion __result = _sub_10888CD0(data);
	return __result;
}

_extern void _sub_108888F0(s_font_loading_state *, long, char const *, bool);
void font_load(s_font_loading_state *loading_state, long font_index, char const *filename, bool blocking) // 0x108888F0
{
	mangled_x86(MANGLED_TODO, "?font_load@@YAXPAUs_font_loading_state@@JPBD_N@Z");
	// static ...; // 0x10888BC0
	// static ...; // 0x10888BB8
	// s_font_loading_state *loading_state;
	// long font_index;
	// char const *filename;
	// bool blocking;
	// s_font_loading_task task_data;
	// Ref<IMod> mod;
	{
		// char const *filename;
		// s_mod_package_section_header fonts_section;
		// c_mod_package *mod_package;
	}
	// function call : Ref<IMod> (EModIndex) const
	// function call : char const *() const
	// function call : c_mod_package *(bool) const
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : s_file_reference *(*const)(s_file_reference *, char const *)
	// function call : long (*const)(long, void *, long, void *, c_async_completion_flag *)
	// function call : void (*const)(s_font_loading_state *)
	todo("implement");
	_sub_108888F0(loading_state, font_index, filename, blocking);
}

_extern bool _sub_10888840(s_game_options *);
bool font_initialize_for_new_map(s_game_options *options) // 0x10888840
{
	mangled_x86(MANGLED_TODO, "?font_initialize_for_new_map@@YA_NPAUs_game_options@@@Z");
	// s_game_options *options;
	// function call : void (*const)()
	todo("implement");
	bool __result = _sub_10888840(options);
	return __result;
}

/* ---------- private code */

_extern bool _sub_108887B0(s_file_handle *);
extern "C" bool font_get_package_file_handle(s_file_handle *out_handle) // 0x108887B0
{
	// font_get_package_file_handle
	// s_file_handle *out_handle;
	todo("implement");
	bool __result = _sub_108887B0(out_handle);
	return __result;
}

_extern bool _sub_10888820();
extern "C" bool font_in_emergency_mode() // 0x10888820
{
	// font_in_emergency_mode
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10888820();
	return __result;
}

_extern bool _sub_108899F0(s_font_package_file_header const *);
extern "C" bool validate_fonts(s_font_package_file_header const *header) // 0x108899F0
{
	// validate_fonts
	// s_font_package_file_header const *header;
	{
		// long i;
		{
			// char *font_header;
			// s_font_package_font_entry const *entry;
		}
	}
	// function call : bool (*const)(void *)
	todo("implement");
	bool __result = _sub_108899F0(header);
	return __result;
}

_extern bool _sub_10888710(void *);
extern "C" bool fixup_and_validate_font_package_file(void *buffer) // 0x10888710
{
	// fixup_and_validate_font_package_file
	// void *buffer;
	// s_font_package_file_header *header;
	// bool failed;
	// function call : bool (*const)(s_font_package_file_header *)
	todo("implement");
	bool __result = _sub_10888710(buffer);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_font_package_cache_entry * s_static_array<s_font_package_cache_entry,8>::begin() const;
template s_font_package_cache_entry * s_static_array<s_font_package_cache_entry,8>::end() const;
template void s_static_string<256>::set(char const *);

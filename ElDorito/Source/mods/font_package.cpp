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

extern s_file_reference *(*const file_reference_set_name)(s_file_reference *, char const *);  // hades: added for 0x108888F0
#include "mods/mod_system.hpp"  // hades: added for 0x108888F0

extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x10888DC0
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x10888DC0
extern bool (*const file_set_position)(s_file_reference *, unsigned long, bool);  // hades: added for 0x10888DC0

extern void (*const critical_section_leave)(e_critical_section);  // hades: added for 0x108885D0

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

extern void (*const critical_section_enter)(e_critical_section);  // hades: added for 0x10888520
extern s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool);  // hades: added for 0x10889120

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

c_font_cache_scope_lock::c_font_cache_scope_lock() // 0x10888520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_font_cache_scope_lock@@QAE@XZ");
	// c_font_cache_scope_lock *const this;
	// void **font_character;
	// function call : void (*const)(e_critical_section)

	void **font_character = (void **)tls_get(0xF8);

	m_locked = false;

	if (!*font_character)
	{
		critical_section_enter(_critical_section_font_cache);
		m_locked = true;
		*font_character = g_font_character_globals;
	}
}

c_font_cache_scope_lock::~c_font_cache_scope_lock() // 0x108885D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_font_cache_scope_lock@@QAE@XZ");
	// c_font_cache_scope_lock *const this;
	// void **font_character;
	// function call : void (*const)(e_critical_section)

	void **font_character = (void **)tls_get(0xF8);

	if (*font_character)
	{
		*font_character = nullptr;
		critical_section_leave(_critical_section_font_cache);
		m_locked = false;
	}
}

void font_package_do_work(bool blocking, s_font_package_cache_entry *entry) // 0x108893C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_package_do_work@@YAX_NPAUs_font_package_cache_entry@@@Z");
	// static ...; // 0x10889660
	// static ...; // 0x10889658
	// bool blocking;
	// s_font_package_cache_entry *entry;
	// long package_index;
	// bool has_completed;
		// s_file_handle file_handle;
		// unsigned long package_offset;
		// long task_id;
		// long read_size;
	// function call : long (*const)(s_file_handle, void *, unsigned long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *)
	// function call : bool (*const)(long, long)
	// function call : void (*const)(c_async_completion_flag *, bool, bool)
	// function call : bool (*const)(s_font_package *)

	bool has_completed = ((c_async_completion_flag *)entry->completion_flag)->peek() != 0;
	long package_index = entry->package_index;
	if (package_index == -1)
		return;
	if (entry->task_id == -1 && !has_completed)
	{
		s_file_handle file_handle;
		long task_id = -1;
		unsigned long package_offset = g_font_loading_state->base_file_offset + ((package_index + 1) << 15);
		if (font_get_package_file_handle(&file_handle) && (task_id = ((long (*)(s_file_handle, void *, unsigned long, unsigned long, long, long, c_synchronized_int32 *, c_async_completion_flag *))0x5ADA80)(file_handle, &entry->package, 0x8000, package_offset, 7, 4 * (blocking ? 1 : 0) + 5, ((c_synchronized_int32 *)entry->read_size), ((c_async_completion_flag *)entry->completion_flag)), entry->task_id = task_id, task_id != -1))
			((c_async_completion_flag *)entry->completion_flag)->set_internal_data(2);
		else
		{
			((c_async_completion_flag *)entry->completion_flag)->set(1);
			has_completed = true;
		}
		if (blocking && entry->task_id != -1)
		{
			((bool (*)(long, long))0x5086D0)(entry->task_id, 9);
			((void (*)(c_async_completion_flag *, bool, bool))0x508A40)(((c_async_completion_flag *)entry->completion_flag), false, false);
			has_completed = true;
		}
	}
	if (entry->task_id != -1 && has_completed)
	{
		long read_size = ((c_synchronized_int32 *)entry->read_size)->peek();
		entry->task_id = -1;
		if (read_size == 0x8000 && ((bool (*)(s_font_package *))0x65C880)(&entry->package))
		{
			((c_async_completion_flag *)entry->completion_flag)->set_internal_data(3);
			entry->field_8 = *g_font_package_salt;
		}
		else
		{
			((c_async_completion_flag *)entry->completion_flag)->set_internal_data(0);
			((c_async_completion_flag *)entry->completion_flag)->set(1);
		}
	}
}

void font_package_cache_flush() // 0x10889280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_package_cache_flush@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10889378
	// static ...; // 0x1088936C
	// static ...; // 0x10889364
	// c_font_cache_scope_lock lock;
		// s_static_array<s_font_package_cache_entry,8> &<range>$L0;
		// s_font_package_cache_entry *<begin>$L0;
		// s_font_package_cache_entry *<end>$L0;
			// s_font_package_cache_entry &entry;

	c_font_cache_scope_lock lock;
	for (s_font_package_cache_entry &entry : *g_font_package_cache_entries)
	{
		font_package_do_work(true, &entry);
		entry.package_index = -1;
		entry.status = 0;
	}
}

void font_package_idle() // 0x10889730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_package_idle@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10889848
	// static ...; // 0x1088983C
	// static ...; // 0x10889834
		// c_font_cache_scope_lock lock;
			// s_static_array<s_font_package_cache_entry,8> &<range>$L0;
			// s_font_package_cache_entry *<begin>$L0;
			// s_font_package_cache_entry *<end>$L0;
				// s_font_package_cache_entry &entry;

	if (g_font_package_system_ready->peek() && !font_in_emergency_mode())
	{
		c_font_cache_scope_lock lock;

		++*g_font_package_salt;

		for (s_font_package_cache_entry &entry : *g_font_package_cache_entries)
		{
			font_package_do_work(false, &entry);
		}
	}
}

bool font_package_begin_load_package(char const *filename) // 0x10889120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_package_begin_load_package@@YA_NPBD@Z");
	// static ...; // 0x10889234
	// static ...; // 0x10889228
	// static ...; // 0x10889220
	// char const *filename;
	// c_font_cache_scope_lock lock;
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : void (*const)()

	c_font_cache_scope_lock lock;

	g_font_package_file_path.set(filename);
	file_reference_create_from_path((s_file_reference *)g_font_loading_state->file, g_font_package_file_path.get_string(), false);
	((void (*)())0x509780)();

	return true;
}

bool fonts_begin_loading_internal(bool blocking) // 0x108898F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fonts_begin_loading_internal@@YA_N_N@Z");
	// bool blocking;
	// bool (*const font_load)(s_font_loading_state *, long, char const *, bool);
	// function call : bool (*const)(s_font_loading_state *, long, char const *, bool)

	bool (__cdecl *const F)(s_font_loading_state *, int, const char *, bool) = (bool(__cdecl *const)(s_font_loading_state *, int, const char *, bool))0x509480;

	return F(g_font_loading_state, -1, g_font_package_file_path.get_string(), blocking);
}

void font_package_set_defaults() // 0x108898A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_package_set_defaults@@YAXXZ");
	// procedure flags: nofpo

	g_font_package_file_path.set("font_package.bin");
}

bool font_load_from_file_blocking(s_font_loading_state *loading_state, unsigned long size, void *buffer, s_font_package_file_header **out_header) // 0x10888DC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_load_from_file_blocking@@YA_NPAUs_font_loading_state@@KPAXPAPAUs_font_package_file_header@@@Z");
	// s_font_loading_state *loading_state;
	// unsigned long size;
	// void *buffer;
	// s_font_package_file_header **out_header;
	// unsigned long error;
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)

	unsigned long error;
	if (loading_state->file_opened || file_open((s_file_reference *)loading_state->file, 1, &error))
	{
		loading_state->file_opened = true;
		if (!file_set_position((s_file_reference *)loading_state->file, loading_state->base_file_offset, false))
			return false;
		if (file_read((s_file_reference *)loading_state->file, 0x8000, false, buffer) && fixup_and_validate_font_package_file(buffer))
		{
			*out_header = (s_font_package_file_header *)buffer;
			return true;
		}
	}
	return false;
}

bool font_load_from_mod_package_blocking(c_mod_package *mod_package, unsigned long size, void *buffer, s_font_package_file_header **out_header) // 0x10888F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_load_from_mod_package_blocking@@YA_NPAVc_mod_package@@KPAXPAPAUs_font_package_file_header@@@Z");
	// static ...; // 0x10889094
	// c_mod_package *mod_package;
	// unsigned long size;
	// void *buffer;
	// s_font_package_file_header **out_header;
	// c_file_reference file;
	// c_file_open_scope scope;

	c_file_reference file = mod_package->get_file();
	c_file_open_scope scope(file, 1);
	if (mod_package->read_font_package_blocking(file, 0, 0x8000, buffer) && fixup_and_validate_font_package_file(buffer))
	{
		*out_header = (s_font_package_file_header *)buffer;
		return true;
	}
	return false;
}

e_async_completion font_load_callback(void *data) // 0x10888CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_load_callback@@YA?AW4e_async_completion@@PAX@Z");
	// static ...; // 0x10888D88
	// static ...; // 0x10888D7C
	// static ...; // 0x10888D74
	// void *data;
	// s_font_loading_task *task_data;
	// s_font_package_file_header *header;
	// s_font_loading_state *loading_state;

	s_font_loading_task *task_data = (s_font_loading_task *)data;
	s_font_loading_state *loading_state = task_data->loading_state;
	s_font_package_file_header *header;

	if (font_load_from_file_blocking(loading_state, 0x8000, g_font_load_buffer, &header))
	{
		*g_font_package_file_header = header;

		return _async_completion_done;
	}

	((c_synchronized_int32 *)loading_state->status)->set(1);

	return _async_completion_done;
}

void font_load(s_font_loading_state *loading_state, long font_index, char const *filename, bool blocking) // 0x108888F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_load@@YAXPAUs_font_loading_state@@JPBD_N@Z");
	// static ...; // 0x10888BC0
	// static ...; // 0x10888BB8
	// s_font_loading_state *loading_state;
	// long font_index;
	// char const *filename;
	// bool blocking;
	// s_font_loading_task task_data;
	// Ref<IMod> mod;
		// char const *filename;
		// s_mod_package_section_header fonts_section;
		// c_mod_package *mod_package;
	// function call : Ref<IMod> (EModIndex) const
	// function call : char const *() const
	// function call : c_mod_package *(bool) const
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : s_file_reference *(*const)(s_file_reference *, char const *)
	// function call : long (*const)(long, void *, long, void *, c_async_completion_flag *)
	// function call : void (*const)(s_font_loading_state *)

	loading_state->font_index = font_index;
	loading_state->base_file_offset = 0;
	Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(g_mod_package_index);
	if (mod)
	{
		char const *filename = mod->GetFilename();
		s_mod_package_section_header fonts_section;
		c_mod_package *mod_package = mod->GetPak(true);
		if (mod_package)
		{
			mod_package->get_section_header(_mod_package_section_fonts, &fonts_section);
			if (fonts_section.offset && fonts_section.size >= 0x8000)
			{
				loading_state->base_file_offset = fonts_section.offset;
				file_reference_create_from_path((s_file_reference *)loading_state->file, filename, false);
			}
		}
	}
	if (!loading_state->base_file_offset)
	{
		loading_state->base_file_offset = 0;
		file_reference_create_from_path((s_file_reference *)loading_state->file, "maps\\fonts", true);
		file_reference_set_name((s_file_reference *)loading_state->file, g_font_package_file_path.get_string());
	}
	s_font_loading_task task_data;
	memset(&task_data, 0, sizeof(task_data));
	task_data.loading_state = loading_state;
	loading_state->task_id = ((long (*)(long, void *, long, void *, c_async_completion_flag *))0x5085C0)(4 * (blocking ? 1 : 0) + 5, &task_data, 7, font_load_callback, (c_async_completion_flag *)loading_state->completion_flag);
	if (blocking)
		((void (*)(s_font_loading_state *))0x509140)(loading_state);
}

bool font_initialize_for_new_map(s_game_options *options) // 0x10888840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_initialize_for_new_map@@YA_NPAUs_game_options@@@Z");
	// s_game_options *options;
	// function call : void (*const)()

	g_mod_package_index = kGame;

	if (options->game_mode == _game_mode_mainmenu)
		g_mod_package_index = kMainMenu;

	((void (*)())0x509780)();

	return true;
}

/* ---------- private code */

extern "C" bool font_get_package_file_handle(s_file_handle *out_handle) // 0x108887B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_font_get_package_file_handle");
	// font_get_package_file_handle
	// s_file_handle *out_handle;

	if (g_font_loading_state->file_opened)
	{
		*out_handle = *(s_file_handle *)&((s_file_reference *)g_font_loading_state->file)->handle;
	}

	return out_handle->handle != 0;
}

extern "C" bool font_in_emergency_mode() // 0x10888820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_font_in_emergency_mode");
	// font_in_emergency_mode
	// procedure flags: nofpo

	return *(bool *)0x22b7fae;
}

extern "C" bool validate_fonts(s_font_package_file_header const *header) // 0x108899F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_validate_fonts");
	// validate_fonts
	// s_font_package_file_header const *header;
		// long i;
			// char *font_header;
			// s_font_package_font_entry const *entry;
	// function call : bool (*const)(void *)

	if (header->fonts_count < 0)
	{
		return false;
	}

	for (long i = 0; i < header->fonts_count; i++)
	{
		s_font_package_font_entry const *entry = &header->fonts[i];

		if (entry->offset < 0x118)
		{
			return false;
		}

		if (entry->offset + 348 > header->font_headers_offset + header->font_headers_size)
		{
			return false;
		}

		char *font_header = (char *)header + entry->offset;

		if (!((bool (*)(void *))0x65B620)(font_header))
		{
			return false;
		}
	}

	return true;
}

extern "C" bool fixup_and_validate_font_package_file(void *buffer) // 0x10888710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_fixup_and_validate_font_package_file");
	// fixup_and_validate_font_package_file
	// void *buffer;
	// s_font_package_file_header *header;
	// bool failed;
	// function call : bool (*const)(s_font_package_file_header *)

	s_font_package_file_header *header = (s_font_package_file_header *)buffer;
	bool failed = false;

	if (!((bool(*)(s_font_package_file_header *))0x65BB90)(header))
	{
		return false;
	}

	if (!validate_fonts(header))
	{
		return false;
	}

	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_font_package_cache_entry * s_static_array<s_font_package_cache_entry,8>::begin() const;
template s_font_package_cache_entry * s_static_array<s_font_package_cache_entry,8>::end() const;
template void s_static_string<256>::set(char const *);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
void *g_font_character_globals = reinterpret_cast<void *>(0x244FB90);
s_static_array<s_font_package_cache_entry,8> *g_font_package_cache_entries = reinterpret_cast<s_static_array<s_font_package_cache_entry,8> *>(0x2457BC0);
c_async_completion_flag *g_font_package_system_ready = reinterpret_cast<c_async_completion_flag *>(0x2457BB8);
long *g_font_package_salt = reinterpret_cast<long *>(0x2457BBC);
s_font_loading_state *g_font_loading_state = reinterpret_cast<s_font_loading_state *>(0x22B7FBC);
s_font_package_file_header *g_font_load_buffer = reinterpret_cast<s_font_package_file_header *>(0x22B8108);
s_font_package_file_header **g_font_package_file_header = reinterpret_cast<s_font_package_file_header **>(0x22B8104);
EModIndex g_mod_package_index;

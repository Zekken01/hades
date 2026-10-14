/* ---------- headers */

#include "Blam/tag_files/files.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"

/* ---------- forward declarations */

struct s_file_handle;
struct s_file_reference;
struct s_file_time;
struct s_find_file_data;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void invalidate_file_handle(s_file_handle *handle);
extern bool file_is_open(s_file_reference const *reference);

/* ---------- globals */

extern s_file_reference *(*const file_reference_initialize_header)(s_file_reference *, c_enum<enum e_file_reference_location,short>); // 0x112492E4
extern bool (*const file_close)(s_file_reference *); // 0x1124931C
extern s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool); // 0x112492E8
extern char *(*const file_reference_get_name)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long); // 0x112492F0
extern wchar_t *(*const file_reference_get_name_wide)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, wchar_t *, long); // 0x112492F4
extern bool (*const file_get_size)(s_file_reference *, unsigned long *); // 0x1124930C
extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *); // 0x11249310
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *); // 0x11249324
extern void (*const find_files_start)(s_find_file_data *, unsigned long, s_file_reference *); // 0x1124933C
extern void (*const find_files_end)(s_find_file_data *); // 0x11249340
extern bool (*const find_files_next)(s_find_file_data *, s_file_reference *, s_file_time *); // 0x11249344
extern s_file_reference *(*const file_reference_set_name)(s_file_reference *, char const *); // 0x112492DC
extern unsigned long g_file_reference_error; // 0x124C2C88
extern bool (*const file_set_position)(s_file_reference *, unsigned long, bool); // 0x11249320
extern s_file_reference *(*const file_reference_create_from_path_wide)(s_file_reference *, wchar_t const *, bool); // 0x112492EC
extern bool (*const file_exists)(s_file_reference const *); // 0x11249308
extern bool (*const file_create)(s_file_reference *); // 0x11249314
extern bool (*const file_create_parent_directories_if_not_present)(s_file_reference *); // 0x11249318
extern bool (*const file_delete)(s_file_reference *); // 0x11249328
extern bool (*const file_write)(s_file_reference *, unsigned long, void *); // 0x11249338
extern s_file_reference *(*const file_reference_set_name_wide)(s_file_reference *, wchar_t const *); // 0x112492E0
extern s_file_reference *(*const file_path_add_name)(s_file_reference *, char const *); // 0x112492F8
extern s_file_reference *(*const file_path_add_name_wide)(s_file_reference *, wchar_t const *); // 0x112492FC
extern s_file_reference *(*const file_path_remove_name)(s_file_reference *); // 0x11249300
extern s_file_reference *(*const file_path_remove_name_wide)(s_file_reference *); // 0x11249304
extern bool (*const file_delete_recursive)(s_file_reference *); // 0x1124932C
extern bool (*const file_rename)(s_file_reference *, char const *); // 0x11249330
extern bool (*const file_rename_wide)(s_file_reference *, wchar_t const *); // 0x11249334

/* ---------- private variables */

/* ---------- public code */

void invalidate_file_handle(s_file_handle *handle) // 0x10F00E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?invalidate_file_handle@@YAXPAUs_file_handle@@@Z");
	// s_file_handle *handle;

	handle->handle = 0xFFFFFFFF;
}

bool file_is_open(s_file_reference const *reference) // 0x10F00DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?file_is_open@@YA_NPBUs_file_reference@@@Z");
	// s_file_reference const *reference;

	return reference->handle && reference->handle != -1;
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const file_close)(s_file_reference *) = reinterpret_cast<decltype(file_close)>(0x528B60);
s_file_reference *(*const file_reference_initialize_header)(s_file_reference *, c_enum<enum e_file_reference_location,short>) = reinterpret_cast<decltype(file_reference_initialize_header)>(0x528500);
s_file_reference *(*const file_reference_set_name)(s_file_reference *, char const *) = reinterpret_cast<decltype(file_reference_set_name)>(0x528410);
bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *) = reinterpret_cast<decltype(file_open)>(0x52A220);
bool (*const file_read)(s_file_reference *, unsigned long, bool, void *) = reinterpret_cast<decltype(file_read)>(0x52A7E0);
bool (*const file_set_position)(s_file_reference *, unsigned long, bool) = reinterpret_cast<decltype(file_set_position)>(0x52B060);
s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool) = reinterpret_cast<decltype(file_reference_create_from_path)>(0x528550);
bool (*const file_get_size)(s_file_reference *, unsigned long *) = reinterpret_cast<decltype(file_get_size)>(0x529B00);
bool (*const file_exists)(s_file_reference const *) = reinterpret_cast<decltype(file_exists)>(0x5295F0);
bool (*const file_delete)(s_file_reference *) = reinterpret_cast<decltype(file_delete)>(0x529170);
bool (*const file_rename)(s_file_reference *, char const *) = reinterpret_cast<decltype(file_rename)>(0x52AC80);
bool (*const file_create)(s_file_reference *) = reinterpret_cast<decltype(file_create)>(0x528FB0);
bool (*const file_create_parent_directories_if_not_present)(s_file_reference *) = reinterpret_cast<decltype(file_create_parent_directories_if_not_present)>(0x527FF0);
bool (*const file_write)(s_file_reference *, unsigned long, void *) = reinterpret_cast<decltype(file_write)>(0x52B250);
s_file_reference *(*const file_reference_create_from_path_wide)(s_file_reference *, wchar_t const *, bool) = reinterpret_cast<decltype(file_reference_create_from_path_wide)>(0x5285B0);
bool (*const find_files_next)(s_find_file_data *, s_file_reference *, s_file_time *) = reinterpret_cast<decltype(find_files_next)>(0x52B4A0);
void (*const find_files_end)(s_find_file_data *) = reinterpret_cast<decltype(find_files_end)>(0x52B450);
void (*const find_files_start)(s_find_file_data *, unsigned long, s_file_reference *) = reinterpret_cast<decltype(find_files_start)>(0x52B830);
char *(*const file_reference_get_name)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long) = reinterpret_cast<decltype(file_reference_get_name)>(0x5286A0);
wchar_t *(*const file_reference_get_name_wide)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, wchar_t *, long) = reinterpret_cast<decltype(file_reference_get_name_wide)>(0x5286E0);
unsigned long g_file_reference_error;

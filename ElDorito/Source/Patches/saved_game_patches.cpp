/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/saved_games/content_blf.hpp"
#include "Blam/saved_games/scenario_map_variant_blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"
#include "mods/blf_reader.hpp"
#include "mods/blf_writer.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_system.hpp"  // hades: added for 0x10AC9230
#include "mods/new/IModManager.hpp"  // hades: added for 0x10AC9230
#include "mods/map_variant_loader.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_blf.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
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
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include "mods/map_variant_tag_fixups.hpp"  // hades: added for 0x10AC9930

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
#include <list>
#include <memory>
#include <mutex>
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
class c_blf_reader;
class c_blf_writer;
class c_mod_package;
struct c_async_completion_flag;
struct s_blf_chunk_content_header;
struct s_blf_chunk_end_of_file;
struct s_blf_chunk_header;
struct s_blf_chunk_mapv_tag_names;
struct s_blf_chunk_mod_package_reference;
struct s_blf_chunk_start_of_file;
struct s_file_reference;
struct s_map_variant;
struct s_mod_package_metadata;
struct s_mod_package_reference;
struct s_mod_package_reference_v1;
namespace hades_file_local
{
	class c_gui_selected_item;
	struct _c_gui_map_selected_item;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
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
	class c_gui_selected_item
	{
	public:
		void *vftable; // 0x0
		__int32 field_4; // 0x4
		__int32 type; // 0x8
		__int32 field_C; // 0xC
		__int32 field_10; // 0x10
		char field_14; // 0x14
		char field_15; // 0x15
		char field_16; // 0x16
		char field_17; // 0x17
		unsigned char content_header[376]; // 0x18
	};
}
using namespace hades_file_local;
// static_assert(sizeof(c_gui_selected_item) == 400, "Invalid c_gui_selected_item size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct _c_gui_map_selected_item
	{
		c_gui_selected_item base; // 0x0
		__int32 controller_index; // 0x190
		s_file_reference file_reference; // 0x194
		_c_gui_map_selected_item(_c_gui_map_selected_item &); /* compiler_generated() */
		_c_gui_map_selected_item(_c_gui_map_selected_item const &); /* compiler_generated() */
		_c_gui_map_selected_item(); /* compiler_generated() */
		_c_gui_map_selected_item &operator=(_c_gui_map_selected_item &); /* compiler_generated() */
		_c_gui_map_selected_item &operator=(_c_gui_map_selected_item const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(_c_gui_map_selected_item) == 676, "Invalid _c_gui_map_selected_item size");
}
using namespace hades_file_local;
/* ---------- prototypes */

char const *tag_get_name(long tag_index);  // hades: added for 0x10AC9230
unsigned long tag_get_group_tag(long tag_index);  // hades: added for 0x10AC9230
extern bool (*const file_get_size)(s_file_reference *, unsigned long *);  // hades: added for 0x10AC8BF0
extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x10AC8BF0
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x10AC8BF0
extern bool (*const file_close)(s_file_reference *);  // hades: added for 0x10AC8BF0

extern void saved_game_patches_apply();

long save_map_variant_hook(long controller_index, long content_item_index, long content_type, unsigned char *data, unsigned long size, c_async_completion_flag completion_flag);
char const *map_variant_load_error_string(e_map_variant_load_error error);
bool read_mod_package_metadata(s_file_reference file, short *out_version, s_mod_package_reference *metadata);
bool __fastcall c_gui_map_selected_item__get_map_variant_hook(_c_gui_map_selected_item *thisptr, void *unused, s_map_variant *map_variant);
void __fastcall s_blf_header__setup_hook(s_blf_chunk_header *header, void *unused, unsigned long signature, unsigned long size, short version_major, short version_minor);
void __fastcall s_blf_chunk_start_of_file__ctor_hook(s_blf_chunk_start_of_file *chunk);
void __fastcall s_blf_chunk_end_of_file__ctor_hook(s_blf_chunk_end_of_file *chunk);
void __fastcall s_blf_chunk_content_header__initialize_hook(s_blf_chunk_content_header *chunk);
bool __fastcall c_map_variant__is_valid_hook(s_map_variant *thisptr);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??4s_blf_chunk_end_of_file@@QAEAAU0@$$QAU0@@Z"); no body to assert in
_inline s_blf_chunk_end_of_file &s_blf_chunk_end_of_file::operator=(s_blf_chunk_end_of_file &&__that) = default; // 0x10AC86D0

void saved_game_patches_apply() // 0x10AC9930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?saved_game_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// long const k__mapv_rename_buffer_size;

	Hook(0x6EB794, save_map_variant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6EA4AC, save_map_variant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63640, s_blf_header__setup_hook).Apply();
	Hook(0x62AD0, s_blf_chunk_start_of_file__ctor_hook).Apply();
	Hook(0x629D0, s_blf_chunk_end_of_file__ctor_hook).Apply();
	Hook(0x62CF0, s_blf_chunk_content_header__initialize_hook).Apply();
	long const k__mapv_rename_buffer_size = 0x20000;
	Pointer(0x52762A).Write<long>(k__mapv_rename_buffer_size);
	Pointer(0x52764F).Write<long>(k__mapv_rename_buffer_size);
	Pointer(0x5276AA).Write<long>(k__mapv_rename_buffer_size);
	Pointer(0x527613).Write<long>(k__mapv_rename_buffer_size);
	Hook(0x6A81AD, c_gui_map_selected_item__get_map_variant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	c_map_variant_tag_fixups::initialize();
	Hook(0x1841D0, c_map_variant__is_valid_hook).Apply();
}

/* ---------- private code */

long save_map_variant_hook(long controller_index, long content_item_index, long content_type, unsigned char *data, unsigned long size, c_async_completion_flag completion_flag) // 0x10AC9230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?save_map_variant_hook@@YAJJJJPAEKUc_async_completion_flag@@@Z");
	// `anonymous-namespace'::save_map_variant_hook
	// static ...; // 0x10AC9774
	// static ...; // 0x10AC972C
	// static ...; // 0x10AC9724
	// long controller_index;
	// long content_item_index;
	// long content_type;
	// unsigned char *data;
	// unsigned long size;
	// c_async_completion_flag completion_flag;
	// static std::string `save_map_variant_hook'::`2'::buffer; // 0x12467378
	// unsigned char const *chunk_data;
	// c_blf_writer blf_writer;
	// s_blf_chunk_header chunk_header;
	// unsigned long const blf_size_minus_eof;
	// unsigned long new_blf_size;
	// unsigned long chunk_data_size;
	// IMod *mod;
	// s_map_variant *map_variant;
	// long (*const content_item_write_task_submit)(long, long, long, unsigned char *, unsigned long, c_async_completion_flag);
	// s_blf_chunk_mapv_tag_names *tag_names;
	// c_blf_reader blf_reader;
	// static __int32 `save_map_variant_hook'::`2'::$TSS0; // 0x12467394
		// void *dest_chunk;
		// s_mod_package_metadata const *const mod_metadata;
		// s_blf_chunk_mod_package_reference *ref;
		// c_mod_package const *mod_package;
		// __int32 i;
		// long i;
			// long tag_index;
				// char const *tag_name;
				// unsigned long group_tag;
				// char group_tag_ascii[5];
				// char *dest_tag_name;
				// unsigned __int32 len;
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : long (*const)(long, long, long, unsigned char *, unsigned long, c_async_completion_flag)

	long (*const content_item_write_task_submit)(long, long, long, unsigned char *, unsigned long, c_async_completion_flag) = (long (*)(long, long, long, unsigned char *, unsigned long, c_async_completion_flag))0x527040;
	unsigned long const blf_size_minus_eof = 0xE1D8;
	c_blf_reader blf_reader(data, size);
	if (!blf_reader.begin())
		return -1;
	unsigned long new_blf_size = 0x1E1F5;
	IMod *mod = c_mod_system::GetModManager().GetMod(kGame);
	if (mod)
		new_blf_size += 0x490;
	static std::string buffer;
	buffer.resize(new_blf_size);
	c_blf_writer blf_writer(buffer.size(), &buffer[0]);
	blf_writer.add_chunk<s_blf_chunk_start_of_file>();
	s_blf_chunk_header chunk_header;
	unsigned char const *chunk_data;
	unsigned long chunk_data_size;
	s_map_variant *map_variant = nullptr;
	while (blf_reader.read_next_chunk(&chunk_header, &chunk_data, &chunk_data_size))
	{
		if (chunk_header.signature == '_eof')
			break;
		if (chunk_header.signature == 'mapv')
			map_variant = (s_map_variant *)&chunk_data[4];
		void *dest_chunk = blf_writer.allocate_chunk(chunk_header.size);
		memcpy(dest_chunk, &chunk_data[-12], chunk_header.size);
	}
	if (!map_variant)
		return -1;
	if (mod)
	{
		c_mod_package const *mod_package = mod->GetPak(true);
		s_mod_package_metadata const *const mod_metadata = mod_package->get_metadata();
		s_blf_chunk_mod_package_reference *ref = blf_writer.add_chunk<s_blf_chunk_mod_package_reference>();
		memcpy(&ref->metadata, mod_metadata, sizeof(ref->metadata));
		memcpy(ref->sha1, mod_package->get_header()->sha1, sizeof(ref->sha1));
	}
	s_blf_chunk_mapv_tag_names *tag_names = blf_writer.add_chunk<s_blf_chunk_mapv_tag_names>();
	for (__int32 i = 0; i < 256; i++)
		memset(tag_names->names[i], 0, sizeof(tag_names->names[i]));
	for (long i = 0; i < 256; i++)
	{
		long tag_index = map_variant->object_quotas[i].definition_index;
		if (tag_index != -1)
		{
			char const *tag_name = tag_get_name(tag_index);
			if (!tag_name)
				return -1;
			char *dest_tag_name = tag_names->names[i];
			unsigned __int32 len = strlen(tag_name);
			if (len > 255)
				return -1;
			char group_tag_ascii[5];
			unsigned long group_tag = tag_get_group_tag(tag_index);
			group_tag_ascii[0] = (group_tag >> 24) & 0xFF;
			group_tag_ascii[1] = (group_tag >> 16) & 0xFF;
			group_tag_ascii[2] = (group_tag >> 8) & 0xFF;
			group_tag_ascii[3] = group_tag & 0xFF;
			group_tag_ascii[4] = 0;
			snprintf(dest_tag_name, 256, "%s.%s", tag_name, group_tag_ascii);
		}
	}
	blf_writer.add_chunk<s_blf_chunk_end_of_file>();
	return content_item_write_task_submit(controller_index, content_item_index, content_type, (unsigned char *)&buffer[0], buffer.size(), completion_flag);
}

char const *map_variant_load_error_string(e_map_variant_load_error error) // 0x10AC8B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?map_variant_load_error_string@@YAPBDW4e_map_variant_load_error@@@Z");
	// `anonymous-namespace'::map_variant_load_error_string
	// static ...; // 0x10AC8BB4
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// e_map_variant_load_error error;

	switch (error)
	{
	case _map_variant_load_error_fixup_failed:
		return "Missing tags. Check that any required mods are installed and selected. See dorito.log for details.";
	case _map_variant_load_base_map_not_found:
		return "The scenario required by this variant could not be found.";
	case _map_variant_load_io_error:
		return "The map required could not be read from disk.";
	case _map_variant_load_invalid_format:
		return "Invalid or incompatible format.";
	}

	return "Unknown Error";
}

bool read_mod_package_metadata(s_file_reference file, short *out_version, s_mod_package_reference *metadata) // 0x10AC8BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_mod_package_metadata@@YA_NUs_file_reference@@PAFPAUs_mod_package_reference@@@Z");
	// `anonymous-namespace'::read_mod_package_metadata
	// static ...; // 0x10AC8F4C
	// static ...; // 0x10AC8F3F
	// static ...; // 0x10AC8F34
	// static ...; // 0x10AC8F24
	// static ...; // 0x10AC8EDC
	// static ...; // 0x10AC8ED4
	// s_file_reference file;
	// short *out_version;
	// s_mod_package_reference *metadata;
	// std::string buffer;
	// unsigned char const *chunk_data;
	// unsigned long err;
	// s_blf_chunk_header chunk_header;
	// unsigned long chunk_data_size;
	// bool result;
	// unsigned long file_size;
		// s_mod_package_reference_v1 *v1;
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)

	memset(metadata, 0, sizeof(s_mod_package_reference));
	std::string buffer;
	unsigned long file_size;
	if (!file_get_size(&file, &file_size))
		return false;
	buffer.resize(file_size);
	unsigned long err;
	if (!file_open(&file, 1, &err))
		return false;
	if (!file_read(&file, file_size, false, buffer.data()))
		return false;
	s_blf_chunk_header chunk_header;
	unsigned char const *chunk_data;
	unsigned long chunk_data_size;
	bool result = blf_find_chunk_in_buffer((unsigned char const *)buffer.data(), buffer.size(), 'modp', &chunk_header, &chunk_data, &chunk_data_size);
	if (result)
	{
		*out_version = chunk_header.version_major;
		if (chunk_header.version_major == 1)
		{
			s_mod_package_reference_v1 *v1 = (s_mod_package_reference_v1 *)chunk_data;
			wcsncpy_s(metadata->metadata.name, v1->name, 31);
			strncpy_s(metadata->metadata.author, v1->author, 31);
			memcpy(metadata->sha1, v1->sha1, 20);
		}
		else
		{
			*metadata = *(s_mod_package_reference *)chunk_data;
		}
	}
	file_close(&file);
	return result;
}

bool __fastcall c_gui_map_selected_item__get_map_variant_hook(_c_gui_map_selected_item *thisptr, void *unused, s_map_variant *map_variant) // 0x10AC8760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_map_selected_item__get_map_variant_hook@@YI_NPAU_c_gui_map_selected_item@hades_file_local@@PAXPAUs_map_variant@@@Z");
	// `anonymous-namespace'::c_gui_map_selected_item__get_map_variant_hook
	// static ...; // 0x10AC8A14
	// static ...; // 0x10AC89F0
	// static ...; // 0x10AC89E8
	// _c_gui_map_selected_item *thisptr;
	// void *unused;
	// s_map_variant *map_variant;
	// bool (*const c_gui_map_selected_item__get_map_variant)(_c_gui_map_selected_item *, s_map_variant *);
	// s_static_string<8192> error_message;
	// __int32 height;
		// e_map_variant_load_error error;
			// s_mod_package_reference metdata;
			// short version;

	bool (__fastcall *const c_gui_map_selected_item__get_map_variant)(_c_gui_map_selected_item *, s_map_variant *) = reinterpret_cast<bool (__fastcall *)(_c_gui_map_selected_item *, s_map_variant *)>(0xAD9A30);
	s_static_string<8192> error_message;
	error_message.print("Failed to load map: ");
	__int32 height = 40;
	if (!c_map_variant_loader::load_from_file(thisptr->file_reference.filename, map_variant))
	{
		e_map_variant_load_error error = c_map_variant_loader::get_last_error();
		error_message.append(map_variant_load_error_string(error));
		if (error == _map_variant_load_error_fixup_failed)
		{
			s_mod_package_reference metdata;
			short version;
			if (read_mod_package_metadata(static_cast<s_file_reference const &>(thisptr->file_reference), &version, &metdata))
			{
				height = 45;
				error_message.append_print("|r|n|r|n", metdata.metadata.author);
				error_message.append_print("Mod Name: '%S' v%d.%d|r|n", metdata.metadata.name, metdata.metadata.version_major, metdata.metadata.version_minor);
				error_message.append_print("Mod Author: %s|r|n", metdata.metadata.author);
				if (version >= 2 && strlen(metdata.metadata.url) > 0)
					error_message.append_print("Mod Website: %s|r|n", metdata.metadata.url);
			}
		}
		Web::Ui::ScreenLayer::ShowAlert("Error", error_message.get_string(), (Web::Ui::ScreenLayer::AlertIcon)0, height);
		c_map_variant_loader::load_default(map_variant->map_id, map_variant);
	}
	return c_map_variant_loader::get_last_error() == _map_variant_load_success;
}

void __fastcall s_blf_header__setup_hook(s_blf_chunk_header *header, void *unused, unsigned long signature, unsigned long size, short version_major, short version_minor) // 0x10AC91C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_blf_header__setup_hook@@YIXPAUs_blf_chunk_header@@PAXKKFF@Z");
	// `anonymous-namespace'::s_blf_header__setup_hook
	// short version_minor;

	header->setup(signature, size, version_major, version_minor);
}

void __fastcall s_blf_chunk_start_of_file__ctor_hook(s_blf_chunk_start_of_file *chunk) // 0x10AC9140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_blf_chunk_start_of_file__ctor_hook@@YIXPAUs_blf_chunk_start_of_file@@@Z");
	// `anonymous-namespace'::s_blf_chunk_start_of_file__ctor_hook
	// s_blf_chunk_start_of_file *chunk;

	*chunk = s_blf_chunk_start_of_file();
}

void __fastcall s_blf_chunk_end_of_file__ctor_hook(s_blf_chunk_end_of_file *chunk) // 0x10AC90C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_blf_chunk_end_of_file__ctor_hook@@YIXPAUs_blf_chunk_end_of_file@@@Z");
	// `anonymous-namespace'::s_blf_chunk_end_of_file__ctor_hook
	// s_blf_chunk_end_of_file *chunk;

	*chunk = s_blf_chunk_end_of_file();
}

void __fastcall s_blf_chunk_content_header__initialize_hook(s_blf_chunk_content_header *chunk) // 0x10AC9040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_blf_chunk_content_header__initialize_hook@@YIXPAUs_blf_chunk_content_header@@@Z");
	// `anonymous-namespace'::s_blf_chunk_content_header__initialize_hook
	// s_blf_chunk_content_header *chunk;

	*chunk = s_blf_chunk_content_header();
}

bool __fastcall c_map_variant__is_valid_hook(s_map_variant *thisptr) // 0x10AC8AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__is_valid_hook@@YI_NPAUs_map_variant@@@Z");
	// `anonymous-namespace'::c_map_variant__is_valid_hook
	// s_map_variant *thisptr;

	return thisptr->version == 12;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_blf_authentication_type,char> & c_enum<enum e_blf_authentication_type,char>::operator=(c_enum<enum e_blf_authentication_type,char> const &);

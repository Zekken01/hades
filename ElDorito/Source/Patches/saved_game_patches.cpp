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

extern void saved_game_patches_apply();

long save_map_variant_hook(long controller_index, long content_item_index, long content_type, unsigned char *data, unsigned long size, c_async_completion_flag completion_flag);
char const *map_variant_load_error_string(e_map_variant_load_error error);
bool read_mod_package_metadata(s_file_reference file, short *out_version, s_mod_package_reference *metadata);
bool c_gui_map_selected_item__get_map_variant_hook(_c_gui_map_selected_item *thisptr, void *unused, s_map_variant *map_variant);
void s_blf_header__setup_hook(s_blf_chunk_header *header, void *unused, unsigned long signature, unsigned long size, short version_major, short version_minor);
void s_blf_chunk_start_of_file__ctor_hook(s_blf_chunk_start_of_file *chunk);
void s_blf_chunk_end_of_file__ctor_hook(s_blf_chunk_end_of_file *chunk);
void s_blf_chunk_content_header__initialize_hook(s_blf_chunk_content_header *chunk);
bool c_map_variant__is_valid_hook(s_map_variant *thisptr);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_blf_chunk_end_of_file &_sub_10AC86D0(s_blf_chunk_end_of_file *const, s_blf_chunk_end_of_file &);
_inline s_blf_chunk_end_of_file &s_blf_chunk_end_of_file::operator=(s_blf_chunk_end_of_file &&__that) // 0x10AC86D0
{
	mangled_x86(MANGLED_TODO, "??4s_blf_chunk_end_of_file@@QAEAAU0@$$QAU0@@Z");
	// s_blf_chunk_end_of_file &__that;
	compiler_generated();
	todo("implement");
	s_blf_chunk_end_of_file & __result = _sub_10AC86D0(this, __that);
	return __result;
}

_extern void _sub_10AC9930();
void saved_game_patches_apply() // 0x10AC9930
{
	mangled_x86(MANGLED_TODO, "?saved_game_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// long const k__mapv_rename_buffer_size;
	todo("implement");
	_sub_10AC9930();
}

/* ---------- private code */

_extern long _sub_10AC9230(long, long, long, unsigned char *, unsigned long, c_async_completion_flag);
long save_map_variant_hook(long controller_index, long content_item_index, long content_type, unsigned char *data, unsigned long size, c_async_completion_flag completion_flag) // 0x10AC9230
{
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
	// static std::basic_string<char,std::char_traits<char>,std::allocator<char> > `save_map_variant_hook'::`2'::buffer; // 0x12467378
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
	{
		// void *dest_chunk;
	}
	{
		// s_mod_package_metadata const *const mod_metadata;
		// s_blf_chunk_mod_package_reference *ref;
		// c_mod_package const *mod_package;
	}
	{
		// __int32 i;
	}
	{
		// long i;
		{
			// long tag_index;
			{
				// char const *tag_name;
				// unsigned long group_tag;
				// char group_tag_ascii[5];
				// char *dest_tag_name;
				// unsigned __int32 len;
			}
		}
	}
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : long (*const)(long, long, long, unsigned char *, unsigned long, c_async_completion_flag)
	todo("implement");
	long __result = _sub_10AC9230(controller_index, content_item_index, content_type, data, size, completion_flag);
	return __result;
}

extern char const *_sub_10AC8B50(e_map_variant_load_error);
char const *map_variant_load_error_string(e_map_variant_load_error error) // 0x10AC8B50
{
	// `anonymous-namespace'::map_variant_load_error_string
	// static ...; // 0x10AC8BB4
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// e_map_variant_load_error error;
	todo("implement");
	char const * __result = _sub_10AC8B50(error);
	return __result;
}

_extern bool _sub_10AC8BF0(s_file_reference, short *, s_mod_package_reference *);
bool read_mod_package_metadata(s_file_reference file, short *out_version, s_mod_package_reference *metadata) // 0x10AC8BF0
{
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
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > buffer;
	// unsigned char const *chunk_data;
	// unsigned long err;
	// s_blf_chunk_header chunk_header;
	// unsigned long chunk_data_size;
	// bool result;
	// unsigned long file_size;
	{
		// s_mod_package_reference_v1 *v1;
	}
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)
	todo("implement");
	bool __result = _sub_10AC8BF0(file, out_version, metadata);
	return __result;
}

_extern bool _sub_10AC8760(_c_gui_map_selected_item *, void *, s_map_variant *);
bool c_gui_map_selected_item__get_map_variant_hook(_c_gui_map_selected_item *thisptr, void *unused, s_map_variant *map_variant) // 0x10AC8760
{
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
	{
		// e_map_variant_load_error error;
		{
			// s_mod_package_reference metdata;
			// short version;
		}
	}
	todo("implement");
	bool __result = _sub_10AC8760(thisptr, unused, map_variant);
	return __result;
}

_extern void _sub_10AC91C0(s_blf_chunk_header *, void *, unsigned long, unsigned long, short, short);
void s_blf_header__setup_hook(s_blf_chunk_header *header, void *unused, unsigned long signature, unsigned long size, short version_major, short version_minor) // 0x10AC91C0
{
	// `anonymous-namespace'::s_blf_header__setup_hook
	// short version_minor;
	todo("implement");
	_sub_10AC91C0(header, unused, signature, size, version_major, version_minor);
}

_extern void _sub_10AC9140(s_blf_chunk_start_of_file *);
void s_blf_chunk_start_of_file__ctor_hook(s_blf_chunk_start_of_file *chunk) // 0x10AC9140
{
	// `anonymous-namespace'::s_blf_chunk_start_of_file__ctor_hook
	// s_blf_chunk_start_of_file *chunk;
	todo("implement");
	_sub_10AC9140(chunk);
}

_extern void _sub_10AC90C0(s_blf_chunk_end_of_file *);
void s_blf_chunk_end_of_file__ctor_hook(s_blf_chunk_end_of_file *chunk) // 0x10AC90C0
{
	// `anonymous-namespace'::s_blf_chunk_end_of_file__ctor_hook
	// s_blf_chunk_end_of_file *chunk;
	todo("implement");
	_sub_10AC90C0(chunk);
}

_extern void _sub_10AC9040(s_blf_chunk_content_header *);
void s_blf_chunk_content_header__initialize_hook(s_blf_chunk_content_header *chunk) // 0x10AC9040
{
	// `anonymous-namespace'::s_blf_chunk_content_header__initialize_hook
	// s_blf_chunk_content_header *chunk;
	todo("implement");
	_sub_10AC9040(chunk);
}

_extern bool _sub_10AC8AF0(s_map_variant *);
bool c_map_variant__is_valid_hook(s_map_variant *thisptr) // 0x10AC8AF0
{
	// `anonymous-namespace'::c_map_variant__is_valid_hook
	// s_map_variant *thisptr;
	todo("implement");
	bool __result = _sub_10AC8AF0(thisptr);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_blf_authentication_type,char> & c_enum<enum e_blf_authentication_type,char>::operator=(c_enum<enum e_blf_authentication_type,char> const &);

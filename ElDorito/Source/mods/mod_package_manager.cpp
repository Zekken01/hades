/* ---------- headers */

#include "mods/mod_package_manager.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/mod_database.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Modules/ModuleServer.hpp"
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

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
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_file_reference;
class c_mod_database;
class c_mod_package;
class c_mod_package_manager;
struct begin;
struct end;
struct s_file_reference;
struct s_file_time;
struct s_mod_origin_info;
struct s_mod_package_id;
struct s_mod_package_metadata;

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

/* ---------- prototypes */

extern long long filetime_to_timet(_FILETIME const &ft);

extern "C" bool hash_equals(unsigned char const (&a)[20], unsigned char const (&b)[20]);
extern "C" void get_package_author_uid(c_mod_package const *package, unsigned long long *uid);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_108A56B0(c_mod_package_manager *const);
c_mod_package_manager::~c_mod_package_manager() // 0x108A56B0
{
	mangled_x86(MANGLED_TODO, "??1c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager *const this;
	todo("implement");
	_sub_108A56B0(this);
}

extern c_file_reference &_sub_108A5830(c_file_reference *const, c_file_reference const &);
_inline c_file_reference &c_file_reference::operator=(c_file_reference const &__that) // 0x108A5830
{
	mangled_x86(MANGLED_TODO, "??4c_file_reference@@QAEAAV0@ABV0@@Z");
	// c_file_reference const &__that;
	compiler_generated();
	todo("implement");
	c_file_reference & __result = _sub_108A5830(this, __that);
	return __result;
}

extern c_mod_package_manager::s_entry &_sub_108A5890(c_mod_package_manager::s_entry *const, c_mod_package_manager::s_entry const &);
_inline c_mod_package_manager::s_entry &c_mod_package_manager::s_entry::operator=(c_mod_package_manager::s_entry const &__that) // 0x108A5890
{
	mangled_x86(MANGLED_TODO, "??4s_entry@c_mod_package_manager@@QAEAAU01@ABU01@@Z");
	// c_mod_package_manager::s_entry const &__that;
	{
		// unsigned __int32 $S12;
	}
	{
		// unsigned __int32 $S13;
	}
	{
		// unsigned __int32 $S14;
	}
	{
		// unsigned __int32 $S15;
	}
	{
		// unsigned __int32 $S16;
	}
	compiler_generated();
	todo("implement");
	c_mod_package_manager::s_entry & __result = _sub_108A5890(this, __that);
	return __result;
}

extern s_file_reference &_sub_108A5B60(s_file_reference *const, s_file_reference const &);
_inline s_file_reference &s_file_reference::operator=(s_file_reference const &__that) // 0x108A5B60
{
	mangled_x86(MANGLED_TODO, "??4s_file_reference@@QAEAAU0@ABU0@@Z");
	// s_file_reference const &__that;
	{
		// unsigned __int32 $S11;
	}
	compiler_generated();
	todo("implement");
	s_file_reference & __result = _sub_108A5B60(this, __that);
	return __result;
}

_extern void _sub_108AA150(c_mod_package_manager *const, char const *);
void c_mod_package_manager::initialize(char const *package_directory) // 0x108AA150
{
	mangled_x86(MANGLED_TODO, "?initialize@c_mod_package_manager@@QAEXPBD@Z");
	// static ...; // 0x108AA348
	// static ...; // 0x108AA340
	// c_mod_package_manager *const this;
	// char const *package_directory;
	// std::filesystem::path dir;
	todo("implement");
	_sub_108AA150(this, package_directory);
}

_extern void _sub_108AB190(c_mod_package_manager *const);
void c_mod_package_manager::update() // 0x108AB190
{
	mangled_x86(MANGLED_TODO, "?update@c_mod_package_manager@@QAEXXZ");
	// static ...; // 0x108AB328
	// static ...; // 0x108AB31C
	// static ...; // 0x108AB314
	// c_mod_package_manager *const this;
	// __int32 num;
	{
		// std::unique_lock<std::mutex> lock;
	}
	todo("implement");
	_sub_108AB190(this);
}

_extern bool _sub_108A9740(c_mod_package_manager const *const);
bool c_mod_package_manager::enumeration_in_progress() const // 0x108A9740
{
	mangled_x86(MANGLED_TODO, "?enumeration_in_progress@c_mod_package_manager@@QBE_NXZ");
	// c_mod_package_manager const *const this;
	todo("implement");
	bool __result = _sub_108A9740((c_mod_package_manager const *)this);
	return __result;
}

_extern bool _sub_108A9790(c_mod_package_manager const *const);
bool c_mod_package_manager::enumeration_requested_or_in_progress() const // 0x108A9790
{
	mangled_x86(MANGLED_TODO, "?enumeration_requested_or_in_progress@c_mod_package_manager@@QBE_NXZ");
	// c_mod_package_manager const *const this;
	todo("implement");
	bool __result = _sub_108A9790((c_mod_package_manager const *)this);
	return __result;
}

_extern void _sub_108A7FB0(c_mod_package_manager *const);
void c_mod_package_manager::begin_enumerate() // 0x108A7FB0
{
	mangled_x86(MANGLED_TODO, "?begin_enumerate@c_mod_package_manager@@QAEXXZ");
	// c_mod_package_manager *const this;
	todo("implement");
	_sub_108A7FB0(this);
}

_extern void _sub_108A89D0(c_mod_package_manager *const);
void c_mod_package_manager::enumerate_blocking() // 0x108A89D0
{
	mangled_x86(MANGLED_TODO, "?enumerate_blocking@c_mod_package_manager@@QAEXXZ");
	// c_mod_package_manager *const this;
	todo("implement");
	_sub_108A89D0(this);
}

_extern void _sub_108A88E0(c_mod_package_manager *const);
void c_mod_package_manager::enumerate_async_callback() // 0x108A88E0
{
	mangled_x86(MANGLED_TODO, "?enumerate_async_callback@c_mod_package_manager@@AAEXXZ");
	// static ...; // 0x108A8990
	// static ...; // 0x108A8984
	// static ...; // 0x108A897C
	// c_mod_package_manager *const this;
	// std::unique_lock<std::mutex> lock;
	todo("implement");
	_sub_108A88E0(this);
}

_extern long long _sub_108A98F0(_FILETIME const &);
long long filetime_to_timet(_FILETIME const &ft) // 0x108A98F0
{
	mangled_x86(MANGLED_TODO, "?filetime_to_timet@@YA_JABU_FILETIME@@@Z");
	// static ...; // 0x108A9974
	// static ...; // 0x108A9968
	// static ...; // 0x108A9960
	// _FILETIME const &ft;
	// _ULARGE_INTEGER ull;
	todo("implement");
	long long __result = _sub_108A98F0(ft);
	return __result;
}

_extern void _sub_108A8A20(c_mod_package_manager *const);
void c_mod_package_manager::enumerate_blocking_internal() // 0x108A8A20
{
	mangled_x86(MANGLED_TODO, "?enumerate_blocking_internal@c_mod_package_manager@@AAEXXZ");
	// static ...; // 0x108A949C
	// static ...; // 0x108A9496
	// static ...; // 0x108A948E
	// static ...; // 0x108A9488
	// static ...; // 0x108A9485
	// static ...; // 0x108A947B
	// static ...; // 0x108A946F
	// static ...; // 0x108A946B
	// static ...; // 0x108A9465
	// static ...; // 0x108A9460
	// static ...; // 0x108A9456
	// static ...; // 0x108A944C
	// static ...; // 0x108A93BC
	// static ...; // 0x108A93B4
	// c_mod_package_manager *const this;
	// std::vector<c_mod_package_manager::s_entry,std::allocator<c_mod_package_manager::s_entry> > entries;
	// std::filesystem::directory_iterator endit;
	// std::filesystem::path p;
	// std::unordered_set<s_mod_package_id,std::hash<s_mod_package_id>,std::equal_to<s_mod_package_id>,std::allocator<s_mod_package_id> > found;
	{
		// std::filesystem::directory_iterator it;
		{
			// s_file_time date;
			// c_mod_package::e_error err;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > thin_path;
			// s_mod_package_metadata const *const metadata;
			// c_mod_package_manager::s_entry entry;
			// _FILETIME builtTime;
			// c_mod_database::s_record *db_record;
			// c_mod_package mod_package;
		}
	}
	todo("implement");
	_sub_108A8A20(this);
}

_extern bool _sub_108A9B90(c_mod_package_manager const *const, unsigned char const (&)[20], c_mod_package_manager::s_entry *);
bool c_mod_package_manager::find_package_by_hash(unsigned char const (&hash)[20], c_mod_package_manager::s_entry *out_entry) const // 0x108A9B90
{
	mangled_x86(MANGLED_TODO, "?find_package_by_hash@c_mod_package_manager@@QBE_NAAY0BE@$$CBEPAUs_entry@1@@Z");
	// static ...; // 0x108A9C44
	// c_mod_package_manager const *const this;
	// unsigned char const (&hash)[20];
	// c_mod_package_manager::s_entry *out_entry;
	// std::lock_guard<std::mutex> lock;
	todo("implement");
	bool __result = _sub_108A9B90((c_mod_package_manager const *)this, hash, out_entry);
	return __result;
}

_extern bool _sub_108A9C90(c_mod_package_manager const *const, unsigned char const (&)[20], c_mod_package_manager::s_entry *);
bool c_mod_package_manager::find_package_by_hash_internal(unsigned char const (&hash)[20], c_mod_package_manager::s_entry *out_entry) const // 0x108A9C90
{
	mangled_x86(MANGLED_TODO, "?find_package_by_hash_internal@c_mod_package_manager@@ABE_NAAY0BE@$$CBEPAUs_entry@1@@Z");
	// c_mod_package_manager::s_entry *out_entry;
	{
		// std::vector<c_mod_package_manager::s_entry,std::allocator<c_mod_package_manager::s_entry> > const &<range>$L0;
		// c_mod_package_manager::s_entry const *<begin>$L0;
		// c_mod_package_manager::s_entry const *<end>$L0;
		{
			// c_mod_package_manager::s_entry const &entry;
		}
	}
	todo("implement");
	bool __result = _sub_108A9C90((c_mod_package_manager const *)this, hash, out_entry);
	return __result;
}

_extern bool _sub_108A9AA0(c_mod_package_manager const *const, char const *, c_mod_package_manager::s_entry *);
bool c_mod_package_manager::find_package_by_filename_internal(char const *filename, c_mod_package_manager::s_entry *out_entry) const // 0x108A9AA0
{
	mangled_x86(MANGLED_TODO, "?find_package_by_filename_internal@c_mod_package_manager@@ABE_NPBDPAUs_entry@1@@Z");
	// c_mod_package_manager::s_entry *out_entry;
	{
		// std::vector<c_mod_package_manager::s_entry,std::allocator<c_mod_package_manager::s_entry> > const &<range>$L0;
		// c_mod_package_manager::s_entry const *<begin>$L0;
		// c_mod_package_manager::s_entry const *<end>$L0;
		{
			// c_mod_package_manager::s_entry const &entry;
			{
				// char const *entry_filename;
			}
		}
	}
	todo("implement");
	bool __result = _sub_108A9AA0((c_mod_package_manager const *)this, filename, out_entry);
	return __result;
}

_extern bool _sub_108A99A0(c_mod_package_manager const *const, char const *, c_mod_package_manager::s_entry *);
bool c_mod_package_manager::find_package_by_filename(char const *filename, c_mod_package_manager::s_entry *out_entry) const // 0x108A99A0
{
	mangled_x86(MANGLED_TODO, "?find_package_by_filename@c_mod_package_manager@@QBE_NPBDPAUs_entry@1@@Z");
	// static ...; // 0x108A9A54
	// c_mod_package_manager const *const this;
	// char const *filename;
	// c_mod_package_manager::s_entry *out_entry;
	// std::lock_guard<std::mutex> lock;
	todo("implement");
	bool __result = _sub_108A99A0((c_mod_package_manager const *)this, filename, out_entry);
	return __result;
}

extern c_mod_package_manager::c_threadsafe_iterator _sub_108AA510(c_mod_package_manager *const);
c_mod_package_manager::c_threadsafe_iterator c_mod_package_manager::lock_for_iteration() // 0x108AA510
{
	mangled_x86(MANGLED_TODO, "?lock_for_iteration@c_mod_package_manager@@QAE?AVc_threadsafe_iterator@1@XZ");
	// c_mod_package_manager *const this;
	todo("implement");
	c_mod_package_manager::c_threadsafe_iterator __result = _sub_108AA510(this);
	return __result;
}

extern c_mod_package_manager::c_threadsafe_iterator* _sub_108A4C20(c_mod_package_manager::c_threadsafe_iterator *const, c_mod_package_manager &);
c_mod_package_manager::c_threadsafe_iterator::c_threadsafe_iterator(c_mod_package_manager &manager) : m_modManager(manager) // 0x108A4C20
{
	mangled_x86(MANGLED_TODO, "??0c_threadsafe_iterator@c_mod_package_manager@@QAE@AAV1@@Z");
	// c_mod_package_manager &manager;
	todo("implement");
	_sub_108A4C20(this, manager);
}

extern c_mod_package_manager::s_entry* _sub_108A4CB0(c_mod_package_manager::s_entry *const, c_mod_package_manager::s_entry &);
_inline c_mod_package_manager::s_entry::s_entry(c_mod_package_manager::s_entry &&__that) // 0x108A4CB0
{
	mangled_x86(MANGLED_TODO, "??0s_entry@c_mod_package_manager@@QAE@$$QAU01@@Z");
	// c_mod_package_manager::s_entry &__that;
	compiler_generated();
	todo("implement");
	_sub_108A4CB0(this, __that);
}

extern c_mod_package_manager::s_entry* _sub_108A4F10(c_mod_package_manager::s_entry *const, c_mod_package_manager::s_entry const &);
_inline c_mod_package_manager::s_entry::s_entry(c_mod_package_manager::s_entry const &__that) // 0x108A4F10
{
	mangled_x86(MANGLED_TODO, "??0s_entry@c_mod_package_manager@@QAE@ABU01@@Z");
	// c_mod_package_manager::s_entry const &__that;
	compiler_generated();
	todo("implement");
	_sub_108A4F10(this, __that);
}

_extern bool _sub_108AA7F0(c_mod_package_manager::c_threadsafe_iterator *const);
bool c_mod_package_manager::c_threadsafe_iterator::next() // 0x108AA7F0
{
	mangled_x86(MANGLED_TODO, "?next@c_threadsafe_iterator@c_mod_package_manager@@QAE_NXZ");
	// c_mod_package_manager::c_threadsafe_iterator *const this;
	todo("implement");
	bool __result = _sub_108AA7F0(this);
	return __result;
}

_extern bool _sub_108A83E0(c_mod_package_manager *const, unsigned char const (&)[20]);
bool c_mod_package_manager::delete_package(unsigned char const (&hash)[20]) // 0x108A83E0
{
	mangled_x86(MANGLED_TODO, "?delete_package@c_mod_package_manager@@QAE_NAAY0BE@$$CBE@Z");
	// static ...; // 0x108A85CC
	// static ...; // 0x108A85B4
	// static ...; // 0x108A85AC
// $LN12:
	// c_mod_package_manager *const this;
	// unsigned char const (&hash)[20];
	// std::unique_lock<std::mutex> lock;
	// c_mod_package_manager::s_entry entry;
	{
		// bool removed;
	}
	todo("implement");
	bool __result = _sub_108A83E0(this, hash);
	return __result;
}

_extern bool _sub_108A8660(c_mod_package_manager *const, char const *);
bool c_mod_package_manager::delete_package_by_filename(char const *filename) // 0x108A8660
{
	mangled_x86(MANGLED_TODO, "?delete_package_by_filename@c_mod_package_manager@@QAE_NPBD@Z");
	// static ...; // 0x108A884C
	// static ...; // 0x108A8834
	// static ...; // 0x108A882C
// $LN12:
	// c_mod_package_manager *const this;
	// char const *filename;
	// std::unique_lock<std::mutex> lock;
	// c_mod_package_manager::s_entry entry;
	{
		// bool removed;
	}
	todo("implement");
	bool __result = _sub_108A8660(this, filename);
	return __result;
}

_extern void _sub_108AAA70(c_mod_package_manager *const, s_mod_package_id const &, s_mod_origin_info const &);
void c_mod_package_manager::set_package_origin(s_mod_package_id const &id, s_mod_origin_info const &info) // 0x108AAA70
{
	mangled_x86(MANGLED_TODO, "?set_package_origin@c_mod_package_manager@@QAEXABUs_mod_package_id@@ABUs_mod_origin_info@@@Z");
	// static ...; // 0x108AAB60
	// static ...; // 0x108AAB58
	// c_mod_package_manager *const this;
	// s_mod_package_id const &id;
	// s_mod_origin_info const &info;
	// std::unique_lock<std::mutex> lock;
	// c_mod_database::s_record *record;
	todo("implement");
	_sub_108AAA70(this, id, info);
}

_extern void _sub_108AABD0(c_mod_package_manager *const, s_mod_package_id const &, bool);
void c_mod_package_manager::set_package_signature_verified(s_mod_package_id const &id, bool verified) // 0x108AABD0
{
	mangled_x86(MANGLED_TODO, "?set_package_signature_verified@c_mod_package_manager@@QAEXABUs_mod_package_id@@_N@Z");
	// static ...; // 0x108AACBC
	// static ...; // 0x108AACB4
	// c_mod_package_manager *const this;
	// s_mod_package_id const &id;
	// bool verified;
	// std::unique_lock<std::mutex> lock;
	// c_mod_database::s_record *record;
	todo("implement");
	_sub_108AABD0(this, id, verified);
}

_extern __int32 _sub_108A9E50(c_mod_package_manager const *const);
__int32 c_mod_package_manager::get_enumeration_number() const // 0x108A9E50
{
	mangled_x86(MANGLED_TODO, "?get_enumeration_number@c_mod_package_manager@@QBEHXZ");
	// c_mod_package_manager const *const this;
	todo("implement");
	__int32 __result = _sub_108A9E50((c_mod_package_manager const *)this);
	return __result;
}

_extern __int32 _sub_108A9D60(c_mod_package_manager *const, s_mod_package_id const &);
__int32 c_mod_package_manager::find_package_index_by_hash_internal(s_mod_package_id const &id) // 0x108A9D60
{
	mangled_x86(MANGLED_TODO, "?find_package_index_by_hash_internal@c_mod_package_manager@@QAEHABUs_mod_package_id@@@Z");
	// s_mod_package_id const &id;
	{
		// __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_108A9D60(this, id);
	return __result;
}

_extern void _sub_108AAE60(c_mod_package_manager *const, s_mod_package_id const &);
void c_mod_package_manager::touch_package(s_mod_package_id const &id) // 0x108AAE60
{
	mangled_x86(MANGLED_TODO, "?touch_package@c_mod_package_manager@@QAEXABUs_mod_package_id@@@Z");
	// static ...; // 0x108AAFD8
	// static ...; // 0x108AAFC0
	// static ...; // 0x108AAFB8
	// c_mod_package_manager *const this;
	// s_mod_package_id const &id;
	// std::unique_lock<std::mutex> lock;
	// __int32 index;
	// c_mod_database::s_record *record;
	todo("implement");
	_sub_108AAE60(this, id);
}

_extern void _sub_108AB050(c_mod_package_manager *const, char const *);
void c_mod_package_manager::touch_package(char const *filename) // 0x108AB050
{
	mangled_x86(MANGLED_TODO, "?touch_package@c_mod_package_manager@@QAEXPBD@Z");
	// static ...; // 0x108AB138
	// static ...; // 0x108AB130
	// c_mod_package_manager *const this;
	// char const *filename;
	// c_mod_package_manager::s_entry entry;
	todo("implement");
	_sub_108AB050(this, filename);
}

/* ---------- private code */

_extern bool _sub_108AA040(unsigned char const (&)[20], unsigned char const (&)[20]);
extern "C" bool hash_equals(unsigned char const (&a)[20], unsigned char const (&b)[20]) // 0x108AA040
{
	// hash_equals
	// unsigned char const (&b)[20];
	// unsigned long *ai;
	// unsigned long *bi;
	todo("implement");
	bool __result = _sub_108AA040(a, b);
	return __result;
}

_extern void _sub_108A9EA0(c_mod_package const *, unsigned long long *);
extern "C" void get_package_author_uid(c_mod_package const *package, unsigned long long *uid) // 0x108A9EA0
{
	// get_package_author_uid
	// static ...; // 0x108A9FBF
	// static ...; // 0x108A9FB8
	// static ...; // 0x108A9F94
	// static ...; // 0x108A9F8C
	// c_mod_package const *package;
	// unsigned long long *uid;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > public_key_base64;
	// SHA256state_st sha256;
	// unsigned char public_key_digest[32];
	todo("implement");
	_sub_108A9EA0(package, uid);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_file_reference_location,short> & c_enum<enum e_file_reference_location,short>::operator=(c_enum<enum e_file_reference_location,short> const &);
template c_flags<enum e_file_reference_flags,unsigned short> & c_flags<enum e_file_reference_flags,unsigned short>::operator=(c_flags<enum e_file_reference_flags,unsigned short> const &);

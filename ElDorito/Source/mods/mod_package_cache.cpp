/* ---------- headers */

#include "mods/mod_package_cache.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

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
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_file_open_scope;
class c_file_reference;
class c_mod_package;
struct s_blf_campaign;
struct s_blf_chunk_start_of_file;
struct s_blf_map_information;
struct s_cache_file_header;
struct s_cache_file_segment_header;
struct s_file_reference;
struct s_mod_package_header;
struct s_mod_package_map_file_entry;
struct s_mod_package_metadata;
struct s_mod_package_section_header;
struct s_mod_package_section_table;
struct s_mod_package_tag_cache_entry;
struct s_mod_package_tag_name_entry;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
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

/* ---------- prototypes */

extern bool mod_package_header_valid(s_mod_package_header const *header);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_mod_package* _sub_1089CF00(c_mod_package *const, char const *);
c_mod_package::c_mod_package(char const *file_path) // 0x1089CF00
{
	mangled_x86(MANGLED_TODO, "??0c_mod_package@@QAE@PBD@Z");
	// char const *file_path;
	todo("implement");
	_sub_1089CF00(this, file_path);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_file_reference@@QAE@ABU0@@Z"); no body to assert in
_inline s_file_reference::s_file_reference(s_file_reference const &__that) = default; // 0x1089D0D0

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_package_header@@QAE@XZ"); no body to assert in

c_mod_package::~c_mod_package() // 0x1089D270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_mod_package@@QAE@XZ");
	// c_mod_package *const this;

	dispose();
}

// mangled_x86(MANGLED_DEFAULT, "??0c_file_reference@@QAE@ABV0@@Z"); no body to assert in
_inline c_file_reference::c_file_reference(c_file_reference const &__that) = default; // 0x1089CEA0

void c_mod_package::dispose() // 0x1089D8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dispose@c_mod_package@@QAEXXZ");
	// c_mod_package *const this;

	m_valid = false;
	((c_file_reference *)m_file)->close();
}

_extern bool _sub_108A0080(c_mod_package const *const);
bool c_mod_package::valid() const // 0x108A0080
{
	mangled_x86(MANGLED_TODO, "?valid@c_mod_package@@QBE_NXZ");
	// c_mod_package const *const this;
	todo("implement");
	bool __result = _sub_108A0080((c_mod_package const *)this);
	return __result;
}

char const *c_mod_package::get_file_name() const // 0x1089DBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_file_name@c_mod_package@@QBEPBDXZ");
	// c_mod_package const *const this;

	return ((c_file_reference const *)m_file)->filename;
}

s_mod_package_header const *c_mod_package::get_header() const // 0x1089DC10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_header@c_mod_package@@QBEPBUs_mod_package_header@@XZ");
	// c_mod_package const *const this;

	#line 155 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 161 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	if (!m_valid)
	{
		return nullptr;
	}

	return (s_mod_package_header const *)m_header;
}

s_mod_package_metadata const *c_mod_package::get_metadata() const // 0x1089DD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_metadata@c_mod_package@@QBEPBUs_mod_package_metadata@@XZ");
	// c_mod_package const *const this;

	#line 172 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 179 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	if (!m_valid)
	{
		return nullptr;
	}

	return (s_mod_package_metadata const *)m_metadata;
}

long c_mod_package::get_map_count() const // 0x1089DCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_map_count@c_mod_package@@QBEJXZ");
	// c_mod_package const *const this;

	return m_map_file_count;
}

s_mod_package_map_file_entry const *c_mod_package::get_map_file_entry(long index) const // 0x1089DCD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_map_file_entry@c_mod_package@@QBEPBUs_mod_package_map_file_entry@@J@Z");
	// long index;

	if (!valid_map_file_index(index))
	{
		return nullptr;
	}

	return &((s_mod_package_map_file_entry const *)m_map_files)[index];
}

bool c_mod_package::valid_map_file_index(long map_file_index) const // 0x108A00D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_map_file_index@c_mod_package@@QBE_NJ@Z");
	// long map_file_index;

	return map_file_index >= 0 && map_file_index < m_map_file_count;
}

_extern long _sub_1089D9C0(c_mod_package *const, long, unsigned long *);
long c_mod_package::find_map_file_by_map_id(long map_id, unsigned long *out_size) // 0x1089D9C0
{
	mangled_x86(MANGLED_TODO, "?find_map_file_by_map_id@c_mod_package@@QAEJJPAK@Z");
	// unsigned long *out_size;
	// long map_file_index;
	{
		// long i;
	}
	todo("implement");
	long __result = _sub_1089D9C0(this, map_id, out_size);
	return __result;
}

_extern long _sub_1089DE60(c_mod_package *const, long);
long c_mod_package::get_tag_cache_index_for_map_id(long map_id) // 0x1089DE60
{
	mangled_x86(MANGLED_TODO, "?get_tag_cache_index_for_map_id@c_mod_package@@QAEJJ@Z");
	// long map_id;
	// long map_file_index;
	todo("implement");
	long __result = _sub_1089DE60(this, map_id);
	return __result;
}

_extern bool _sub_1089EA00(c_mod_package *const, c_file_reference &, s_blf_campaign *, bool *);
bool c_mod_package::read_campaign(c_file_reference &file, s_blf_campaign *out_campaign, bool *out_byte_swap) // 0x1089EA00
{
	mangled_x86(MANGLED_TODO, "?read_campaign@c_mod_package@@QAE_NAAVc_file_reference@@PAUs_blf_campaign@@PA_N@Z");
	// static ...; // 0x1089EC10
	// c_mod_package *const this;
	// c_file_reference &file;
	// s_blf_campaign *out_campaign;
	// bool *out_byte_swap;
	// long const k_required_campaign_size;
	// s_mod_package_section_header &section;
	// s_blf_chunk_start_of_file start_of_file;
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_1089EA00(this, file, out_campaign, out_byte_swap);
	return __result;
}

_extern bool _sub_1089F120(c_mod_package *const, c_file_reference &, long, s_cache_file_header *);
bool c_mod_package::read_map_cache_file_header(c_file_reference &file, long map_index, s_cache_file_header *out_header) // 0x1089F120
{
	mangled_x86(MANGLED_TODO, "?read_map_cache_file_header@c_mod_package@@QAE_NAAVc_file_reference@@JPAUs_cache_file_header@@@Z");
	// c_mod_package *const this;
	// c_file_reference &file;
	// long map_index;
	// s_cache_file_header *out_header;
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_1089F120(this, file, map_index, out_header);
	return __result;
}

_extern bool _sub_1089EF10(c_mod_package *const, c_file_reference &, long, s_blf_map_information *);
bool c_mod_package::read_map_blf_map_information(c_file_reference &file, long map_index, s_blf_map_information *out_information) // 0x1089EF10
{
	mangled_x86(MANGLED_TODO, "?read_map_blf_map_information@c_mod_package@@QAE_NAAVc_file_reference@@JPAUs_blf_map_information@@@Z");
	// c_mod_package *const this;
	// c_file_reference &file;
	// long map_index;
	// s_blf_map_information *out_information;
	// constexpr unsigned __int32 const `c_mod_package::read_map_blf_map_information'::`2'::k_blf_map_information_offset; // constant == 13248
	// constexpr unsigned __int32 const `c_mod_package::read_map_blf_map_information'::`2'::k_required_map_size; // constant == 52352
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_1089EF10(this, file, map_index, out_information);
	return __result;
}

_extern bool _sub_108A03B0(c_mod_package *const);
bool c_mod_package::verify_signature() // 0x108A03B0
{
	mangled_x86(MANGLED_TODO, "?verify_signature@c_mod_package@@QAE_NXZ");
	// static ...; // 0x108A051E
	// static ...; // 0x108A051C
	// static ...; // 0x108A0504
	// static ...; // 0x108A04FC
	// c_mod_package *const this;
	// unsigned char const *p;
	// rsa_st *rsa;
	// unsigned char hash[20];
	// __int32 retVal;
	todo("implement");
	bool __result = _sub_108A03B0(this);
	return __result;
}

_extern bool _sub_1089D3D0(c_mod_package *const, unsigned char (&)[20]);
bool c_mod_package::compute_hash(unsigned char (&out_hash)[20]) // 0x1089D3D0
{
	mangled_x86(MANGLED_TODO, "?compute_hash@c_mod_package@@QAE_NAAY0BE@E@Z");
	// static ...; // 0x1089D7D3
	// static ...; // 0x1089D7C9
	// static ...; // 0x1089D7C5
	// static ...; // 0x1089D7B8
	// static ...; // 0x1089D77C
	// static ...; // 0x1089D774
	// c_mod_package *const this;
	// unsigned char (&out_hash)[20];
	// SHAstate_st ctx;
	// unsigned char block_buffer[8192];
	// c_file_reference file;
	// unsigned long long bytes_remaining;
	// unsigned long file_size;
	// c_file_open_scope scope;
	{
		// unsigned long long block_size;
	}
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	todo("implement");
	bool __result = _sub_1089D3D0(this, out_hash);
	return __result;
}

bool c_mod_package::verify_hash(unsigned char const (&hash)[20]) const // 0x108A0240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?verify_hash@c_mod_package@@QBE_NAAY0BE@$$CBE@Z");
	// unsigned char const (&hash)[20];
	// unsigned long const *ul_expected_hash;
	// unsigned long const *ul_input_hash;

	#line 337 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 346 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	unsigned long const *ul_expected_hash = (unsigned long const *)((s_mod_package_header const *)m_header)->sha1;
	unsigned long const *ul_input_hash = (unsigned long const *)hash;

	return ul_expected_hash[0] == ul_input_hash[0]
		&& ul_expected_hash[1] == ul_input_hash[1]
		&& ul_expected_hash[2] == ul_input_hash[2]
		&& ul_expected_hash[3] == ul_input_hash[3]
		&& ul_expected_hash[4] == ul_input_hash[4];
}

bool mod_package_header_valid(s_mod_package_header const *header) // 0x1089E480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?mod_package_header_valid@@YA_NPBUs_mod_package_header@@@Z");
	// s_mod_package_header const *header;

	if (header->signature != 0x6D6F6421)
	{
		return false;
	}

	if (header->version_major != _mod_package_current_major_version)
	{
		return false;
	}

	if (header->section_table.count > k_number_of_mod_package_sections)
	{
		return false;
	}

	return true;
}

bool c_mod_package::read_metadata_section(s_mod_package_metadata *metadata) // 0x1089F610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_metadata_section@c_mod_package@@AAE_NPAUs_mod_package_metadata@@@Z");
	// s_mod_package_metadata *metadata;

	if (!((s_mod_package_section_header *)m_sections)[_mod_package_section_metadata].offset)
	{
		return false;
	}

	return ((c_file_reference *)m_file)->read_from_position(
		((s_mod_package_section_header *)m_sections)[_mod_package_section_metadata].offset,
		metadata);
}

bool c_mod_package::read_tags_section() // 0x1089FF00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_tags_section@c_mod_package@@AAE_NXZ");
	// static ...; // 0x108A0018
	// static ...; // 0x108A000C
	// static ...; // 0x108A0004
	// c_mod_package *const this;
	// unsigned long section_offset;
	// s_mod_package_section_table tag_cache_table;
		// long i;
			// s_mod_package_tag_cache_entry *entry;

	unsigned long section_offset = ((s_mod_package_section_header *)m_sections)[_mod_package_section_tags].offset;
	s_mod_package_section_table tag_cache_table;

	if (!((c_file_reference *)m_file)->read_from_position(section_offset, &tag_cache_table))
	{
		return false;
	}

	m_tag_cache_count = 0;

	for (long i = 0; i < tag_cache_table.count; i++)
	{
		s_mod_package_tag_cache_entry *entry = &((s_mod_package_tag_cache_entry *)m_tag_cache_entries)[m_tag_cache_count];

		if (!((c_file_reference *)m_file)->read(entry))
		{
			return false;
		}

		m_tag_cache_count++;
	}

	return true;
}

bool c_mod_package::read_resources_section(s_cache_file_segment_header *header) // 0x1089F6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_resources_section@c_mod_package@@AAE_NPAUs_cache_file_segment_header@@@Z");
	// s_cache_file_segment_header *header;

	m_resource_cache_offset = ((s_mod_package_section_header *)m_sections)[_mod_package_section_resources].offset;

	return ((c_file_reference *)m_file)->read_from_position(m_resource_cache_offset, header);
}

unsigned long c_mod_package::get_tag_cache_offset(__int32 tag_cache_index) const // 0x1089DF60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_tag_cache_offset@c_mod_package@@QBEKH@Z");
	// __int32 tag_cache_index;

	if (tag_cache_index < 0 || tag_cache_index >= m_tag_cache_count)
	{
		return -1;
	}

	return ((s_mod_package_section_header const *)m_sections)[_mod_package_section_tags].offset
		+ ((s_mod_package_tag_cache_entry const *)m_tag_cache_entries)[tag_cache_index].offset;
}

unsigned long c_mod_package::get_resource_cache_offset() const // 0x1089DDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_resource_cache_offset@c_mod_package@@QBEKXZ");
	// c_mod_package const *const this;

	return m_resource_cache_offset;
}

extern std::shared_ptr<c_cache_file_tag_cache> _sub_1089E770(c_mod_package *const, c_file_reference &, long);
std::shared_ptr<c_cache_file_tag_cache> c_mod_package::open_tag_cache(c_file_reference &file, long index) // 0x1089E770
{
	mangled_x86(MANGLED_TODO, "?open_tag_cache@c_mod_package@@QAE?AV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@AAVc_file_reference@@J@Z");
	// static ...; // 0x1089E958
	// c_mod_package *const this;
	// c_file_reference &file;
	// long index;
	// std::shared_ptr<c_cache_file_tag_cache> tag_cache;
	todo("implement");
	std::shared_ptr<c_cache_file_tag_cache> __result = _sub_1089E770(this, file, index);
	return __result;
}

extern std::shared_ptr<Blam::Cache::StringIDCache> _sub_1089E4E0(c_mod_package *const, c_file_reference &);
std::shared_ptr<Blam::Cache::StringIDCache> c_mod_package::open_string_id_cache(c_file_reference &file) // 0x1089E4E0
{
	mangled_x86(MANGLED_TODO, "?open_string_id_cache@c_mod_package@@QAE?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@AAVc_file_reference@@@Z");
	// static ...; // 0x1089E6D4
	// static ...; // 0x1089E6BC
	// static ...; // 0x1089E6B4
	// c_mod_package *const this;
	// c_file_reference &file;
	// s_mod_package_section_header string_id_section;
	// std::shared_ptr<Blam::Cache::StringIDCache> cache;
	todo("implement");
	std::shared_ptr<Blam::Cache::StringIDCache> __result = _sub_1089E4E0(this, file);
	return __result;
}

bool c_mod_package::read_section_headers() // 0x1089F8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_section_headers@c_mod_package@@AAE_NXZ");
	// c_mod_package *const this;

	return ((c_file_reference *)m_file)->read_from_position(
		((s_mod_package_header *)m_header)->section_table.offset,
		8 * ((s_mod_package_header *)m_header)->section_table.count,
		m_sections);
}

bool c_mod_package::read_map_files_section() // 0x1089F4A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_map_files_section@c_mod_package@@AAE_NXZ");
	// static ...; // 0x1089F5B8
	// static ...; // 0x1089F5AC
	// static ...; // 0x1089F5A4
	// c_mod_package *const this;
	// s_mod_package_section_table map_file_table;
	// unsigned long table_size;
	// s_mod_package_section_header &section;

	s_mod_package_section_table map_file_table;
	s_mod_package_section_header &section = ((s_mod_package_section_header *)m_sections)[_mod_package_section_map_files];

	if (!section.offset)
	{
		return true;
	}

	if (section.size < 8)
	{
		return false;
	}

	if (!((c_file_reference *)m_file)->read_from_position(section.offset, &map_file_table))
	{
		return false;
	}

	if (map_file_table.count > k_mod_package_map_count)
	{
		return false;
	}

	unsigned long table_size = 16 * map_file_table.count;

	if (!((c_file_reference *)m_file)->read_from_position(map_file_table.offset + section.offset, table_size, m_map_files))
	{
		return false;
	}

	m_map_file_count = map_file_table.count;

	return true;
}

_extern bool _sub_1089F380(c_mod_package *const, c_file_reference &, long, unsigned long, void *);
bool c_mod_package::read_map_file_into_buffer(c_file_reference &file, long map_file_index, unsigned long buffer_size, void *buffer) // 0x1089F380
{
	mangled_x86(MANGLED_TODO, "?read_map_file_into_buffer@c_mod_package@@QAE_NAAVc_file_reference@@JKPAX@Z");
	// void *buffer;
	todo("implement");
	bool __result = _sub_1089F380(this, file, map_file_index, buffer_size, buffer);
	return __result;
}

_extern bool _sub_1089ECE0(c_mod_package *const, c_file_reference &, unsigned long, unsigned long, void *);
bool c_mod_package::read_font_package_blocking(c_file_reference &file, unsigned long offset, unsigned long size, void *buffer) // 0x1089ECE0
{
	mangled_x86(MANGLED_TODO, "?read_font_package_blocking@c_mod_package@@QAE_NAAVc_file_reference@@KKPAX@Z");
	// c_file_reference &file;
	// unsigned long offset;
	// unsigned long size;
	// void *buffer;
	// s_mod_package_section_header *section;
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_1089ECE0(this, file, offset, size, buffer);
	return __result;
}

extern std::unordered_map<int,std::string> _sub_1089F960(c_mod_package *const, c_file_reference &, __int32);
std::unordered_map<int,std::string> c_mod_package::read_tag_names(c_file_reference &file, __int32 tag_cache_index) // 0x1089F960
{
	mangled_x86(MANGLED_TODO, "?read_tag_names@c_mod_package@@QAE?AV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@std@@AAVc_file_reference@@H@Z");
	// static ...; // 0x1089FDB2
	// static ...; // 0x1089FD9E
	// static ...; // 0x1089FD8F
	// static ...; // 0x1089FD80
	// static ...; // 0x1089FD38
	// static ...; // 0x1089FD30
	// c_mod_package *const this;
	// c_file_reference &file;
	// __int32 tag_cache_index;
	// std::unordered_map<int,std::string> tag_names;
	// unsigned long offset;
	// s_mod_package_generic_table_entry tag_name_file_entry;
	// s_mod_package_generic_section_entry tag_name_table;
	// s_mod_package_section_table tag_name_file_table;
	// c_file_open_scope scope;
	{
		// long i;
		{
			// s_mod_package_tag_name_entry tag_name_entry;
		}
	}
	todo("implement");
	std::unordered_map<int,std::string> __result = _sub_1089F960(this, file, tag_cache_index);
	return __result;
}

c_file_reference c_mod_package::get_file() const // 0x1089DAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_file@c_mod_package@@QBE?AVc_file_reference@@XZ");
	// static ...; // 0x1089DB9C
	// static ...; // 0x1089DB90
	// static ...; // 0x1089DB88
	// c_mod_package const *const this;
	// c_file_reference copy;

	c_file_reference copy(((c_file_reference const *)m_file)->filename);

	return copy;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_file_reference_flags,unsigned short>::c_flags(c_flags<enum e_file_reference_flags,unsigned short> const &);
template c_flags<enum e_file_reference_flags,unsigned short>::c_flags(unsigned short const &);
template c_flags<enum e_mod_package_modifier_flags,long>::operator long() const;

/* ---------- explicit instantiations */
template bool c_file_reference::read_from_position<s_cache_file_header>(unsigned long, s_cache_file_header *);
template bool c_file_reference::read_from_position<s_mod_package_metadata>(unsigned long, s_mod_package_metadata *);
template bool c_file_reference::read<s_blf_campaign>(s_blf_campaign *);
template bool c_file_reference::read<s_blf_map_information>(s_blf_map_information *);
template bool c_file_reference::read<s_mod_package_header>(s_mod_package_header *);
template bool c_file_reference::read<s_mod_package_tag_name_entry>(s_mod_package_tag_name_entry *);
template bool c_file_reference::read_from_position<s_cache_file_segment_header>(unsigned long, s_cache_file_segment_header *);
template bool c_file_reference::read_from_position<s_mod_package_generic_section_entry>(unsigned long, s_mod_package_generic_section_entry *);
template bool c_file_reference::read_from_position<s_mod_package_generic_table_entry>(unsigned long, s_mod_package_generic_table_entry *);
template bool c_file_reference::read_from_position<s_mod_package_section_table>(unsigned long, s_mod_package_section_table *);
template bool c_file_reference::read<s_blf_chunk_start_of_file>(s_blf_chunk_start_of_file *);
template bool c_file_reference::read<s_mod_package_tag_cache_entry>(s_mod_package_tag_cache_entry *);

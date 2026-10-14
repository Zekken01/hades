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

#include <openssl/sha.h>  // hades: added for 0x1089D3D0
extern bool (*const file_get_size)(s_file_reference *, unsigned long *);  // hades: added for 0x1089D3D0

extern bool mod_package_header_valid(s_mod_package_header const *header);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_mod_package::c_mod_package(char const *file_path) : m_valid(false), m_campaign_file_count(0), m_tags_section_offset(0), m_resource_cache_offset(0), m_file(file_path), m_metadata(), m_resource_cache_header{}, m_tag_cache_count(0), m_map_file_count(0) /* hades-mem-init:  */ // 0x1089CF00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_mod_package@@QAE@PBD@Z");
	// char const *file_path;
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
	m_file.close();
}

bool c_mod_package::valid() const // 0x108A0080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid@c_mod_package@@QBE_NXZ");
	// c_mod_package const *const this;

	return m_valid == true;
}

char const *c_mod_package::get_file_name() const // 0x1089DBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_file_name@c_mod_package@@QBEPBDXZ");
	// c_mod_package const *const this;

	return m_file.filename;
}

s_mod_package_header const *c_mod_package::get_header() const // 0x1089DC10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_header@c_mod_package@@QBEPBUs_mod_package_header@@XZ");
	// c_mod_package const *const this;

	#line 152 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 158 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	if (!m_valid)
	{
		return nullptr;
	}

	return &m_header;
}

s_mod_package_metadata const *c_mod_package::get_metadata() const // 0x1089DD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_metadata@c_mod_package@@QBEPBUs_mod_package_metadata@@XZ");
	// c_mod_package const *const this;

	#line 169 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 175 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	if (!m_valid)
	{
		return nullptr;
	}

	return &m_metadata;
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

long c_mod_package::find_map_file_by_map_id(long map_id, unsigned long *out_size) // 0x1089D9C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_map_file_by_map_id@c_mod_package@@QAEJJPAK@Z");
	// unsigned long *out_size;
	// long map_file_index;
		// long i;

	#line 215 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 223 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	long map_file_index = -1;
	for (long i = 0; i < m_map_file_count; i++)
	{
		if (((s_mod_package_map_file_entry *)m_map_files)[i].map_id == map_id)
		{
			if (out_size)
			{
				*out_size = ((s_mod_package_map_file_entry *)m_map_files)[i].size;
			}

			map_file_index = i;
			break;
		}
	}

	return map_file_index;
}

long c_mod_package::get_tag_cache_index_for_map_id(long map_id) // 0x1089DE60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_tag_cache_index_for_map_id@c_mod_package@@QAEJJ@Z");
	// long map_id;
	// long map_file_index;

	#line 244 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 251 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	if (m_tag_cache_count < 1)
	{
		return -1;
	}

	if (m_map_file_count < 1 || m_tag_cache_count == 1)
	{
		return 0;
	}

	long map_file_index = find_map_file_by_map_id(map_id, nullptr);
	if (!valid_map_file_index(map_file_index))
	{
		return -1;
	}

	return ((s_mod_package_map_file_entry *)m_map_files)[map_file_index].tag_cache_index;
}

bool c_mod_package::read_campaign(c_file_reference &file, s_blf_campaign *out_campaign, bool *out_byte_swap) // 0x1089EA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_campaign@c_mod_package@@QAE_NAAVc_file_reference@@PAUs_blf_campaign@@PA_N@Z");
	// static ...; // 0x1089EC10
	// c_mod_package *const this;
	// c_file_reference &file;
	// s_blf_campaign *out_campaign;
	// bool *out_byte_swap;
	// long const k_required_campaign_size;
	// s_mod_package_section_header &section;
	// s_blf_chunk_start_of_file start_of_file;
	// c_file_open_scope scope;

	long const k_required_campaign_size = 0x1348;
	#line 275 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
	#line 276 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		if (!(out_campaign)) { display_assert("out_campaign", __FILE__, __LINE__, true); system_exit(-1); }
	#line 277 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		if (!(out_byte_swap)) { display_assert("out_byte_swap", __FILE__, __LINE__, true); system_exit(-1); }
		#line 292 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	s_mod_package_section_header &section = m_sections[_mod_package_section_campaign_files];
	if (!section.offset)
		return true;
	if (section.size < sizeof(s_blf_chunk_start_of_file))
		return false;
	c_file_open_scope scope(file, 1);
	if (!file.set_position(section.offset, false))
		return false;
	s_blf_chunk_start_of_file start_of_file;
	if (!file.read(&start_of_file))
		return false;
	*out_byte_swap = start_of_file.byte_order_marker != -2;
	return file.read(out_campaign);
}

bool c_mod_package::read_map_cache_file_header(c_file_reference &file, long map_index, s_cache_file_header *out_header) // 0x1089F120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_map_cache_file_header@c_mod_package@@QAE_NAAVc_file_reference@@JPAUs_cache_file_header@@@Z");
	// c_mod_package *const this;
	// c_file_reference &file;
	// long map_index;
	// s_cache_file_header *out_header;
	// c_file_open_scope scope;

	#line 309 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		if (!(valid())) { display_assert("valid()", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(out_header)) { display_assert("out_header", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(valid_map_file_index(map_index))) { display_assert("valid_map_file_index(map_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 321 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	if (!valid_map_file_index(map_index))
		return false;
	if (m_map_files[map_index].size < sizeof(s_cache_file_header))
		return false;

	c_file_open_scope scope(file, 1);
	if (!file.read_from_position(m_map_files[map_index].offset + m_sections[_mod_package_section_map_files].offset, out_header))
		return false;
	return true;
}

bool c_mod_package::read_map_blf_map_information(c_file_reference &file, long map_index, s_blf_map_information *out_information) // 0x1089EF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_map_blf_map_information@c_mod_package@@QAE_NAAVc_file_reference@@JPAUs_blf_map_information@@@Z");
	// c_mod_package *const this;
	// c_file_reference &file;
	// long map_index;
	// s_blf_map_information *out_information;
	// constexpr unsigned __int32 const `c_mod_package::read_map_blf_map_information'::`2'::k_blf_map_information_offset; // constant == 13248
	// constexpr unsigned __int32 const `c_mod_package::read_map_blf_map_information'::`2'::k_required_map_size; // constant == 52352
	// c_file_open_scope scope;

	static constexpr unsigned __int32 const k_blf_map_information_offset = 0x33C0;
	static constexpr unsigned __int32 const k_required_map_size = 0xCC80;
	#line 337 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 348 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	if (!valid() || !out_information)
		return false;
	if (m_map_files[map_index].size < k_required_map_size)
		return false;

	c_file_open_scope scope(file, 1);
	if (!file.set_position(m_map_files[map_index].offset + m_sections[_mod_package_section_map_files].offset + k_blf_map_information_offset, false))
		return false;
	if (!file.read(out_information))
		return false;
	return true;
}

bool c_mod_package::verify_signature() // 0x108A03B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?verify_signature@c_mod_package@@QAE_NXZ");
	// static ...; // 0x108A051E
	// static ...; // 0x108A051C
	// static ...; // 0x108A0504
	// static ...; // 0x108A04FC
	// c_mod_package *const this;
	// unsigned char const *p;
	// rsa_st *rsa;
	// unsigned char hash[20];
	// __int32 retVal;

	#line 363 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 377 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	if (!(static_cast<long>(m_header.modifier_flags) & 0x10))
		return false;
	unsigned char hash[20];
	if (!compute_hash(hash))
		return false;
	if (!verify_hash(hash))
		return false;
	unsigned char const *p = m_header.rsa_public_key;
	rsa_st *rsa = d2i_RSA_PUBKEY(nullptr, &p, sizeof(m_header.rsa_public_key));
	if (!rsa)
		return false;
	__int32 retVal = RSA_verify(NID_sha1, hash, sizeof(hash), m_header.rsa_signature, sizeof(m_header.rsa_signature), rsa);
	RSA_free(rsa);
	return retVal == 1;
}

bool c_mod_package::compute_hash(unsigned char (&out_hash)[20]) // 0x1089D3D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?compute_hash@c_mod_package@@QAE_NAAY0BE@E@Z");
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
		// unsigned long long block_size;
	// function call : bool (*const)(s_file_reference *, unsigned long *)

	#line 395 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 416 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	c_file_reference file = get_file();
	c_file_open_scope scope(file, 1);
	unsigned long file_size;
	if (!file_get_size(&file, &file_size) || file_size < 0x458)
		return false;
	if (!file.set_position(0x458, false))
		return false;
	SHAstate_st ctx;
	SHA1_Init(&ctx);
	if (!SHA1_Init(&ctx))
		return false;
	unsigned char block_buffer[8192];
	unsigned long long bytes_remaining = file_size - 0x458;
	do
	{
		unsigned long long block_size = bytes_remaining;
		if (bytes_remaining > sizeof(block_buffer))
			block_size = sizeof(block_buffer);
		if (!file.read(block_size, false, block_buffer))
			return false;
		if (!SHA1_Update(&ctx, block_buffer, block_size))
			return false;
		bytes_remaining -= block_size;
	} while (bytes_remaining > 0);
	if (!SHA1_Final(out_hash, &ctx))
		return false;
	return true;
}

bool c_mod_package::verify_hash(unsigned char const (&hash)[20]) const // 0x108A0240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?verify_hash@c_mod_package@@QBE_NAAY0BE@$$CBE@Z");
	// unsigned char const (&hash)[20];
	// unsigned long const *ul_expected_hash;
	// unsigned long const *ul_input_hash;

	#line 447 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 455 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	unsigned long const *ul_expected_hash = (unsigned long const *)m_header.sha1;
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

	return m_file.read_from_position(
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

	if (!m_file.read_from_position(section_offset, &tag_cache_table))
	{
		return false;
	}

	m_tag_cache_count = 0;

	for (long i = 0; i < tag_cache_table.count; i++)
	{
		s_mod_package_tag_cache_entry *entry = &((s_mod_package_tag_cache_entry *)m_tag_cache_entries)[m_tag_cache_count];

		if (!m_file.read(entry))
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

	return m_file.read_from_position(m_resource_cache_offset, header);
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

std::shared_ptr<c_cache_file_tag_cache> c_mod_package::open_tag_cache(c_file_reference &file, long index) // 0x1089E770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open_tag_cache@c_mod_package@@QAE?AV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@AAVc_file_reference@@J@Z");
	// static ...; // 0x1089E958
	// c_mod_package *const this;
	// c_file_reference &file;
	// long index;
	// std::shared_ptr<c_cache_file_tag_cache> tag_cache;

	#line 575 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 585 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	std::shared_ptr<c_cache_file_tag_cache> tag_cache = std::make_shared<c_cache_file_tag_cache>(&file, m_tag_cache_entries[index].offset + m_sections[_mod_package_section_tags].offset, c_tag_name_dictionary(read_tag_names(file, index)));
	if (!tag_cache->initialize())
		return nullptr;
	return tag_cache;
}

std::shared_ptr<Blam::Cache::StringIDCache> c_mod_package::open_string_id_cache(c_file_reference &file) // 0x1089E4E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open_string_id_cache@c_mod_package@@QAE?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@AAVc_file_reference@@@Z");
	// static ...; // 0x1089E6D4
	// static ...; // 0x1089E6BC
	// static ...; // 0x1089E6B4
	// c_mod_package *const this;
	// c_file_reference &file;
	// s_mod_package_section_header string_id_section;
	// std::shared_ptr<Blam::Cache::StringIDCache> cache;

	#line 593 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(m_valid);
		#line 605 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
	s_mod_package_section_header string_id_section;
	if (!get_section_header(_mod_package_section_string_ids, &string_id_section))
		return nullptr;
	std::shared_ptr<Blam::Cache::StringIDCache> cache = std::make_shared<Blam::Cache::StringIDCache>();
	if (!cache->Load(file.filename, string_id_section.offset))
		return nullptr;
	return cache;
}

bool c_mod_package::read_section_headers() // 0x1089F8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_section_headers@c_mod_package@@AAE_NXZ");
	// c_mod_package *const this;

	return m_file.read_from_position(
		m_header.section_table.offset,
		8 * m_header.section_table.count,
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

	if (!m_file.read_from_position(section.offset, &map_file_table))
	{
		return false;
	}

	if (map_file_table.count > k_mod_package_map_count)
	{
		return false;
	}

	unsigned long table_size = 16 * map_file_table.count;

	if (!m_file.read_from_position(map_file_table.offset + section.offset, table_size, m_map_files))
	{
		return false;
	}

	m_map_file_count = map_file_table.count;

	return true;
}

bool c_mod_package::read_map_file_into_buffer(c_file_reference &file, long map_file_index, unsigned long buffer_size, void *buffer) // 0x1089F380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_map_file_into_buffer@c_mod_package@@QAE_NAAVc_file_reference@@JKPAX@Z");
	// void *buffer;

	if (!valid_map_file_index(map_file_index))
	{
		#line 675 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
			assert(!"invalid map file index");
			#line 681 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		return false;
	}

	if (m_map_files[map_file_index].size > buffer_size)
	{
		#line 681 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
			assert(!"insufficient buffer size");
			#line 689 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		return false;
	}

	return read_section_data(file, _mod_package_section_map_files, m_map_files[map_file_index].offset, m_map_files[map_file_index].size, buffer);
}

bool c_mod_package::read_font_package_blocking(c_file_reference &file, unsigned long offset, unsigned long size, void *buffer) // 0x1089ECE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_font_package_blocking@c_mod_package@@QAE_NAAVc_file_reference@@KKPAX@Z");
	// c_file_reference &file;
	// unsigned long offset;
	// unsigned long size;
	// void *buffer;
	// s_mod_package_section_header *section;
	// c_file_open_scope scope;

	c_file_open_scope scope(file, 1);
	s_mod_package_section_header *section = &m_sections[_mod_package_section_map_files];
	if (!section->offset || section->size < size)
		return false;
	return read_section_data(file, _mod_package_section_fonts, offset, size, buffer);
}

std::unordered_map<int,std::string> c_mod_package::read_tag_names(c_file_reference &file, __int32 tag_cache_index) // 0x1089F960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_tag_names@c_mod_package@@QAE?AV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@std@@AAVc_file_reference@@H@Z");
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
		// long i;
			// s_mod_package_tag_name_entry tag_name_entry;

	c_file_open_scope scope(file, 1);
	std::unordered_map<int,std::string> tag_names;
	if (tag_cache_index < 0 || tag_cache_index >= m_tag_cache_count)
		return {};
	if (m_sections[_mod_package_section_tag_names].offset == 0)
		return {};
	s_mod_package_section_table tag_name_file_table;
	if (!file.read_from_position(m_sections[_mod_package_section_tag_names].offset, &tag_name_file_table))
		return {};
	if (tag_cache_index >= tag_name_file_table.count || tag_name_file_table.offset == 0)
		return {};
	unsigned long offset = tag_name_file_table.offset + m_sections[_mod_package_section_tag_names].offset + tag_cache_index * sizeof(s_mod_package_generic_table_entry);
	s_mod_package_generic_table_entry tag_name_file_entry;
	if (!file.read_from_position(offset, &tag_name_file_entry))
		return {};
	s_mod_package_generic_section_entry tag_name_table;
	if (!file.read_from_position(tag_name_file_entry.offset + m_sections[_mod_package_section_tag_names].offset, &tag_name_table))
		return {};
	for (long i = 0; i < tag_name_table.count; i++)
	{
		s_mod_package_tag_name_entry tag_name_entry;
		if (!file.read(&tag_name_entry))
			return {};
		tag_names.insert({ tag_name_entry.tag_index, tag_name_entry.name });
	}
	return tag_names;
}

c_file_reference c_mod_package::get_file() const // 0x1089DAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_file@c_mod_package@@QBE?AVc_file_reference@@XZ");
	// static ...; // 0x1089DB9C
	// static ...; // 0x1089DB90
	// static ...; // 0x1089DB88
	// c_mod_package const *const this;
	// c_file_reference copy;

	c_file_reference copy(m_file.filename);

	return copy;
}

bool c_mod_package::initialize(c_mod_package::e_error *out_error) // 0x1089DFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_mod_package@@QAE_NPAW4e_error@1@@Z");

	c_mod_package::e_error error = initialize_internal();
	if (out_error)
	{
		*out_error = error;
	}

	return error == _error_none;
}

c_mod_package::e_error c_mod_package::initialize_internal() // 0x1089E060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_internal@c_mod_package@@AAE?AW4e_error@1@XZ");

	if (!m_file.exists())
	{
		return _error_not_found;
	}

	c_file_open_scope scope(m_file, 1);
	if (!m_file.is_open())
	{
		return _error_access_denied;
	}

	if (!m_file.set_position(0, false) || !m_file.read(&m_header))
	{
		return _error_bad_format;
	}

	if (!mod_package_header_valid(&m_header))
	{
		return _error_bad_format;
	}

	if (!read_section_headers())
	{
		return _error_bad_format;
	}

	if (!read_metadata_section(&m_metadata))
	{
		return _error_bad_format;
	}

	if (!read_tags_section())
	{
		return _error_bad_format;
	}

	if (!read_resources_section(&m_resource_cache_header))
	{
		return _error_bad_format;
	}

	if (!read_map_files_section())
	{
		return _error_bad_format;
	}

	m_valid = true;
	return _error_none;
}

bool c_mod_package::get_section_header(e_mod_package_sections section, s_mod_package_section_header *header) // 0x1089DE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_section_header@c_mod_package@@QAE_NW4e_mod_package_sections@@PAUs_mod_package_section_header@@@Z");

	*header = ((s_mod_package_section_header *)m_sections)[section];
	return true;
}

bool c_mod_package::read_section_data(c_file_reference &file, e_mod_package_sections section, unsigned long offset, unsigned long size, void *buffer) // 0x1089F740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_section_data@c_mod_package@@QAE_NAAVc_file_reference@@W4e_mod_package_sections@@KKPAX@Z");

	c_file_open_scope scope(file, 1);
	if (!valid_section_offset(section, offset + size))
	{
		#line 856 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
			assert(!"invalid section offset");
			#line 860 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		return false;
	}

	return file.read_from_position(((s_mod_package_section_header *)m_sections)[section].offset + offset, size, buffer);
}

bool c_mod_package::valid_section(e_mod_package_sections section) const // 0x108A0130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_section@c_mod_package@@QBE_NW4e_mod_package_sections@@@Z");

	return section >= 0 && section < k_number_of_mod_package_sections;
}

bool c_mod_package::valid_section_offset(e_mod_package_sections section, unsigned long offset) const // 0x108A0180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_section_offset@c_mod_package@@QBE_NW4e_mod_package_sections@@K@Z");

	#line 875 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_cache.cpp"
		assert(valid_section(section));
		#line 880 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_cache.cpp"

	return offset <= ((s_mod_package_section_header const *)m_sections)[section].size;
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

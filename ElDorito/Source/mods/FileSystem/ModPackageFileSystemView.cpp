/* ---------- headers */

#include "mods/FileSystem/ModPackageFileSystemView.hpp"
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
#include "Forge/Magnets.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/tag_name_dictionary.hpp"
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
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CModPackageFileSystemView;
struct begin;
struct end;
struct s_mod_package_file_entry;
struct s_mod_package_header;
struct s_mod_package_section_header;
struct s_mod_package_section_table;

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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

CModPackageFileSystemView::CModPackageFileSystemView(std::string const &filePath) : m_baseOffset(0), m_filePath(filePath) /* hades-mem-init:  */ // 0x10880470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CModPackageFileSystemView@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &filePath;

	Initialize();
}

bool CModPackageFileSystemView::GetFileEntry(std::string const &virtualPath, CModPackageFileSystemView::SFileEntry *outEntry) // 0x10881150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileEntry@CModPackageFileSystemView@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUSFileEntry@1@@Z");
	// static ...; // 0x10881298
	// CModPackageFileSystemView *const this;
	// std::string const &virtualPath;
	// CModPackageFileSystemView::SFileEntry *outEntry;
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > > it;

	if (auto it = m_files.find(virtualPath); it != std::end(m_files))
	{
		*outEntry = it->second;
		return true;
	}
	return false;
}

std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> CModPackageFileSystemView::GetFileList() // 0x10881310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileList@CModPackageFileSystemView@@QAE?AV?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@@std@@@2@@std@@XZ");
	// CModPackageFileSystemView *const this;

	return m_files;
}

void CModPackageFileSystemView::Initialize() // 0x10881390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CModPackageFileSystemView@@AAEXXZ");
	// static ...; // 0x10881458
	// static ...; // 0x1088144C
	// static ...; // 0x10881444
	// CModPackageFileSystemView *const this;
	// std::ifstream stream;

	std::ifstream stream(m_filePath, std::ios::binary);
	ReadFileTable(stream);
}

bool CModPackageFileSystemView::ReadFileTable(std::istream &stream) // 0x108814A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReadFileTable@CModPackageFileSystemView@@AAE_NAAV?$basic_istream@DU?$char_traits@D@std@@@std@@@Z");
	// static ...; // 0x10881937
	// static ...; // 0x1088192D
	// static ...; // 0x10881922
	// static ...; // 0x10881918
	// static ...; // 0x108818DC
	// static ...; // 0x108818D4
	// CModPackageFileSystemView *const this;
	// std::istream &stream;
	// long long sectionSize;
	// s_mod_package_section_header sectionHeaders[10];
	// s_mod_package_header packageHeader;
	// s_mod_package_section_header const &section;
	// s_mod_package_section_table fileTable;
		// __int32 i;
			// CModPackageFileSystemView::SFileEntry fileEntry;
			// s_mod_package_file_entry tableEntry;
				// char &<range>$L0[256];
				// char *<begin>$L0;
				// char *<end>$L0;
					// char &c;

	m_files.clear();
	s_mod_package_header packageHeader = {};
	if (!stream.read((char *)&packageHeader, sizeof(packageHeader)))
		return false;
	if (!mod_package_header_valid(&packageHeader))
		return false;
	s_mod_package_section_header sectionHeaders[10] = {};
	stream.seekg(packageHeader.section_table.offset);
	if (!stream.read((char *)sectionHeaders, sizeof(sectionHeaders)))
		return false;
	s_mod_package_section_header const &section = sectionHeaders[_mod_package_section_files];
	if (!section.offset || section.size < 1)
		return true;
	m_baseOffset = section.offset;
	long long sectionSize = section.size;
	s_mod_package_section_table fileTable = {};
	stream.seekg(section.offset);
	if (!stream.read((char *)&fileTable, sizeof(fileTable)))
		return false;
	stream.seekg((long long)fileTable.offset + section.offset);
	for (__int32 i = 0; i < fileTable.count; i++)
	{
		s_mod_package_file_entry tableEntry;
		if (!stream.read((char *)&tableEntry, sizeof(tableEntry)))
			continue;
		if ((long long)tableEntry.offset + tableEntry.size > sectionSize)
			continue;
		CModPackageFileSystemView::SFileEntry fileEntry;
		fileEntry.offset = tableEntry.offset;
		fileEntry.size = tableEntry.size;
		for (char &c : tableEntry.path)
			if (c == '\\')
				c = '/';
		m_files.insert(std::make_pair(tableEntry.path, fileEntry));
	}
	return true;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_mod_package_map_flags,long>::c_flags();
template c_flags<enum e_mod_package_modifier_flags,long>::c_flags();

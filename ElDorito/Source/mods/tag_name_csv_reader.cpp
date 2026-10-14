/* ---------- headers */

#include "mods/tag_name_csv_reader.hpp"
#include "hades/hades.h"

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
#include <ios>
#include <iosfwd>
#include <istream>
#include <limits>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class c_tag_names_csv_file_reader;
struct s_tag_name_entry;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_tag_names_csv_file_reader::c_tag_names_csv_file_reader(char const *filename) // 0x108C1850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_tag_names_csv_file_reader@@QAE@PBD@Z");
	// char const *filename;

	m_filestream = std::ifstream(filename);
}

bool c_tag_names_csv_file_reader::read_next(s_tag_name_entry *entry) // 0x108C1C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_next@c_tag_names_csv_file_reader@@QAE_NPAUs_tag_name_entry@@@Z");
	// static ...; // 0x108C1DA4
	// static ...; // 0x108C1D9C
	// c_tag_names_csv_file_reader *const this;
	// s_tag_name_entry *entry;
	// std::string line;

	std::string line;
	if (!std::getline(m_filestream, line))
		return false;
	return parse_line(line, entry);
}

bool c_tag_names_csv_file_reader::parse_line(std::string const &line, s_tag_name_entry *entry) // 0x108C1960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?parse_line@c_tag_names_csv_file_reader@@AAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_tag_name_entry@@@Z");
	// static ...; // 0x108C1BD0
	// static ...; // 0x108C1BCC
	// static ...; // 0x108C1B9C
	// static ...; // 0x108C1B94
	// c_tag_names_csv_file_reader *const this;
	// std::string const &line;
	// s_tag_name_entry *entry;
	// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > it;
	// unsigned __int32 separator_pos;
	// std::string index_part;
	// std::string name_part;
	// unsigned __int32 idx;
	// unsigned __int32 name_length;

	auto it = std::begin(line);
	unsigned __int32 separator_pos = line.find(',');
	if (separator_pos == std::string::npos)
		return false;
	std::string index_part = line.substr(0, separator_pos);
	unsigned __int32 name_length = std::min<unsigned __int32>(255, std::distance(std::begin(line), std::end(line)) - separator_pos - 1);
	std::string name_part = line.substr(separator_pos + 1, name_length);
	unsigned __int32 idx;
	entry->index = std::stoul(index_part, &idx, 16);
	std::copy(std::begin(name_part), std::end(name_part), entry->name);
	entry->name[name_length] = 0;
	return true;
}

/* ---------- private code */

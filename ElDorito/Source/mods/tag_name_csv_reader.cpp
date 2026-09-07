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

extern c_tag_names_csv_file_reader* _sub_108C1850(c_tag_names_csv_file_reader *const, char const *);
c_tag_names_csv_file_reader::c_tag_names_csv_file_reader(char const *filename) // 0x108C1850
{
	mangled_x86(MANGLED_TODO, "??0c_tag_names_csv_file_reader@@QAE@PBD@Z");
	// char const *filename;
	todo("implement");
	_sub_108C1850(this, filename);
}

_extern bool _sub_108C1C90(c_tag_names_csv_file_reader *const, s_tag_name_entry *);
bool c_tag_names_csv_file_reader::read_next(s_tag_name_entry *entry) // 0x108C1C90
{
	mangled_x86(MANGLED_TODO, "?read_next@c_tag_names_csv_file_reader@@QAE_NPAUs_tag_name_entry@@@Z");
	// static ...; // 0x108C1DA4
	// static ...; // 0x108C1D9C
	// c_tag_names_csv_file_reader *const this;
	// s_tag_name_entry *entry;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > line;
	todo("implement");
	bool __result = _sub_108C1C90(this, entry);
	return __result;
}

_extern bool _sub_108C1960(c_tag_names_csv_file_reader *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, s_tag_name_entry *);
bool c_tag_names_csv_file_reader::parse_line(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &line, s_tag_name_entry *entry) // 0x108C1960
{
	mangled_x86(MANGLED_TODO, "?parse_line@c_tag_names_csv_file_reader@@AAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_tag_name_entry@@@Z");
	// static ...; // 0x108C1BD0
	// static ...; // 0x108C1BCC
	// static ...; // 0x108C1B9C
	// static ...; // 0x108C1B94
	// c_tag_names_csv_file_reader *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &line;
	// s_tag_name_entry *entry;
	// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > it;
	// unsigned __int32 separator_pos;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > index_part;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name_part;
	// unsigned __int32 idx;
	// unsigned __int32 name_length;
	todo("implement");
	bool __result = _sub_108C1960(this, line, entry);
	return __result;
}

/* ---------- private code */

#ifndef __MODS_TAG_NAME_CSV_READER_HPP__
#define __MODS_TAG_NAME_CSV_READER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <fstream>
#include <memory>
#include <string>

/* ---------- forward declarations */

class c_tag_names_csv_file_reader;
struct s_tag_name_entry;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_tag_name_entry
{
	long index; // 0x0
	char name[256]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_tag_name_entry) == 260, "Invalid s_tag_name_entry size");

class c_tag_names_csv_file_reader
{
public:
	c_tag_names_csv_file_reader(c_tag_names_csv_file_reader &); /* compiler_generated() */
	c_tag_names_csv_file_reader(char const *filename);
	bool read_next(s_tag_name_entry *entry);
private:
	std::basic_ifstream<char,std::char_traits<char> > m_filestream; // 0x0
	bool parse_line(std::string const &line, s_tag_name_entry *entry);
public:
	_inline ~c_tag_names_csv_file_reader(); /* compiler_generated() */
	c_tag_names_csv_file_reader &operator=(c_tag_names_csv_file_reader &); /* compiler_generated() */
};
static_assert(sizeof(c_tag_names_csv_file_reader) == 184, "Invalid c_tag_names_csv_file_reader size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_TAG_NAME_CSV_READER_HPP__

#ifndef __MODS_MOD_PACKAGE_MANAGER_HPP__
#define __MODS_MOD_PACKAGE_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/HttpFileDownload.hpp"
#include "mods/mod_database.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "Utils/StlUtil.hpp"

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

class c_file_reference;
class c_mod_database;
class c_mod_package_manager;
struct s_mod_origin_info;
struct s_mod_package_id;

/* ---------- constants */

/* ---------- definitions */

class c_mod_package_manager
{
public:
	public:
	struct mod_type
	{
		bool mainmenu : 1; // 0x0
		bool multiplayer : 1; // 0x0
		bool campaign : 1; // 0x0
		bool firefight : 1; // 0x0
		bool character : 1; // 0x0
		_inline mod_type(); /* compiler_generated() */
	};
	static_assert(sizeof(mod_type) == 1, "Invalid mod_type size");
	struct s_entry
	{
		c_file_reference file; // 0x0
		unsigned __int32 file_size; // 0x110
		short version_major; // 0x114
		short version_minor; // 0x116
		bool verified; // 0x118
		unsigned char hash[20]; // 0x119
		unsigned char __pad0[1]; // 0x12D
		wchar_t name[32]; // 0x12E
		char author[32]; // 0x16E
		char description[512]; // 0x18E
		char website[512]; // 0x38E
		unsigned char __pad1[2]; // 0x58E
		unsigned long long author_uid; // 0x590
		long long dateAdded; // 0x598
		long long lastUsed; // 0x5A0
		long long dateBuilt; // 0x5A8
		mod_type modtype; // 0x5B0
		unsigned char __pad2[3]; // 0x5B1
		s_mod_origin_info origin; // 0x5B4
		_inline s_entry(s_entry &&__that); /* compiler_generated() */
		_inline s_entry(s_entry const &__that); /* compiler_generated() */
		_inline s_entry(); /* compiler_generated() */
		_inline ~s_entry(); /* compiler_generated() */
		s_entry &operator=(s_entry &); /* compiler_generated() */
		_inline s_entry &operator=(s_entry const &__that); /* compiler_generated() */
		unsigned char __pad3[4]; // 0x624
	};
	static_assert(sizeof(s_entry) == 1576, "Invalid s_entry size");
#pragma pack(push, 4)
	class c_threadsafe_iterator
	{
	public:
		c_threadsafe_iterator(c_threadsafe_iterator &); /* compiler_generated() */
		c_threadsafe_iterator(c_mod_package_manager &manager);
		_inline s_entry const *get() const;
		bool next();
		_inline s_entry const *operator->() const;
	private:
		c_mod_package_manager &m_modManager; // 0x0
		std::unique_lock<std::mutex> m_lock; // 0x4
		long m_index; // 0xC
		s_entry *m_entry; // 0x10
	public:
		_inline ~c_threadsafe_iterator(); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(c_threadsafe_iterator) == 20, "Invalid c_threadsafe_iterator size");
	public:
	CEventSink<> enumerated; // 0x0
private:
	std::mutex m_mutex; // 0x14
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_package_directory; // 0x44
	std::vector<s_entry,std::allocator<s_entry> > m_entries; // 0x60
	std::atomic<bool> m_enumeration_requested; // 0x70
	std::atomic<bool> m_enumeraton_in_progress; // 0x71
	unsigned char __pad0[2]; // 0x72
	c_mod_database *m_database; // 0x74
	std::atomic<int> m_enumeration_number; // 0x78
	__int32 m_previous_enumeration_number; // 0x7C
public:
	c_mod_package_manager(c_mod_package_manager &);
	c_mod_package_manager(c_mod_package_manager const &);
	_inline c_mod_package_manager();
	~c_mod_package_manager();
	c_mod_package_manager &operator=(c_mod_package_manager &);
	c_mod_package_manager &operator=(c_mod_package_manager const &);
	void initialize(char const *package_directory);
	void update();
	bool enumeration_in_progress() const;
	bool enumeration_requested_or_in_progress() const;
	void begin_enumerate();
	void enumerate_blocking();
	bool find_package_by_hash(unsigned char const (&hash)[20], s_entry *out_entry) const;
	bool find_package_by_filename(char const *filename, s_entry *out_entry) const;
	bool delete_package(unsigned char const (&hash)[20]);
	bool delete_package_by_filename(char const *filename);
	void set_package_origin(s_mod_package_id const &id, s_mod_origin_info const &info);
	void set_package_signature_verified(s_mod_package_id const &id, bool verified);
	__int32 find_package_index_by_hash_internal(s_mod_package_id const &id);
	void touch_package(char const *filename);
	void touch_package(s_mod_package_id const &id);
	__int32 get_enumeration_number() const;
	c_threadsafe_iterator lock_for_iteration();
private:
	void enumerate_blocking_internal();
	void enumerate_async_callback();
	bool find_package_by_hash_internal(unsigned char const (&hash)[20], s_entry *out_entry) const;
	bool find_package_by_filename_internal(char const *filename, s_entry *out_entry) const;
};
static_assert(sizeof(c_mod_package_manager) == 128, "Invalid c_mod_package_manager size");

/* ---------- prototypes */

extern long long filetime_to_timet(_FILETIME const &ft);

/* ---------- globals */

/* ---------- public code */

extern c_mod_package_manager* _sub_108B6A60(c_mod_package_manager *const);
_inline c_mod_package_manager::c_mod_package_manager() // 0x108B6A60
{
	mangled_x86(MANGLED_TODO, "??0c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager *const this;
	todo("implement");
	_sub_108B6A60(this);
}

extern c_mod_package_manager::s_entry const *_sub_10A182C0(c_mod_package_manager::c_threadsafe_iterator const *const);
_inline c_mod_package_manager::s_entry const *c_mod_package_manager::c_threadsafe_iterator::get() const // 0x10A182C0
{
	mangled_x86(MANGLED_TODO, "?get@c_threadsafe_iterator@c_mod_package_manager@@QBEPBUs_entry@2@XZ");
	// c_mod_package_manager::c_threadsafe_iterator const *const this;
	todo("implement");
	c_mod_package_manager::s_entry const * __result = _sub_10A182C0((c_mod_package_manager::c_threadsafe_iterator const *)this);
	return __result;
}

extern c_mod_package_manager::s_entry const *_sub_10A074B0(c_mod_package_manager::c_threadsafe_iterator const *const);
_inline c_mod_package_manager::s_entry const *c_mod_package_manager::c_threadsafe_iterator::operator->() const // 0x10A074B0
{
	mangled_x86(MANGLED_TODO, "??Cc_threadsafe_iterator@c_mod_package_manager@@QBEPBUs_entry@1@XZ");
	// c_mod_package_manager::c_threadsafe_iterator const *const this;
	todo("implement");
	c_mod_package_manager::s_entry const * __result = _sub_10A074B0((c_mod_package_manager::c_threadsafe_iterator const *)this);
	return __result;
}

/* ---------- private code */

#endif // __MODS_MOD_PACKAGE_MANAGER_HPP__

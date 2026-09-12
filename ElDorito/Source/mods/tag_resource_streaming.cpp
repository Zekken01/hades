/* ---------- headers */

#include "mods/tag_resource_streaming.hpp"
#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/async/async_definitions.hpp"
#include "Blam/cache/cache_file_tag_resources.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/memory/bit_vector.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_tag_optimization.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct c_async_completion_flag;
struct s_cache_file_resource_shared_file;
struct s_cache_file_tag_resource_table_runtime;
struct s_indirect_cache_file_page;
struct s_tag_resource;
namespace hades_file_local
{
	class c_tag_resource_stream_task;
}
using namespace hades_file_local;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class c_tag_resource_stream_task
	{
	public:
	private:
		public:
		struct s_packet
		{
			char buffer[65535]; // 0x0
			unsigned char __pad0[1]; // 0xFFFF
			long index; // 0x10000
			unsigned long length; // 0x10004
			unsigned long bytes_read; // 0x10008
			_OVERLAPPED overlapped; // 0x1000C
			bool is_filled() const;
			s_packet(); /* compiler_generated() */
		};
		static_assert(sizeof(s_packet) == 65568, "Invalid s_packet size");
		struct s_lz_block_header
		{
			unsigned long uncompressed_size; // 0x0
			unsigned long compressed_size; // 0x4
		};
		static_assert(sizeof(s_lz_block_header) == 8, "Invalid s_lz_block_header size");
		public:
		static long (*const decompress_block)(void *, void *, long);
		typedef c_block_allocator<1048568,8> block_allocator;
	public:
		void initialize(void *, unsigned long, unsigned long, unsigned long, void *, unsigned long, c_async_completion_flag *);
		void dispose();
		long next_free_packet_index();
		bool update();
		void abort(e_tag_resource_stream_abort_reason);
		static e_async_completion async_callback(c_tag_resource_stream_task *);
	private:
		bool m_initialized; // 0x0
		bool m_aborted; // 0x1
		unsigned char __pad0[2]; // 0x2
		long m_failure_reason; // 0x4
		char *m_destination_buffer; // 0x8
		unsigned long m_destination_buffer_size; // 0xC
		char *m_block_buffer; // 0x10
		unsigned long m_block_buffer_size; // 0x14
		unsigned long m_block_pos; // 0x18
		long m_inflight_packets; // 0x1C
		long m_next_in_block_index; // 0x20
		long m_next_out_block_index; // 0x24
		unsigned long m_compressed_size; // 0x28
		unsigned long m_uncompressed_size; // 0x2C
		unsigned long m_file_offset; // 0x30
		void *m_file_handle; // 0x34
		_OVERLAPPED m_overlapped; // 0x38
		unsigned long m_total_bytes_read; // 0x4C
		unsigned long m_total_bytes_processed; // 0x50
		unsigned long m_total_bytes_decompressed; // 0x54
		char *m_dest_ptr; // 0x58
		c_async_completion_flag *m_completion_flag; // 0x5C
		static s_packet m_packets[32];
		static c_static_bit_vector<32> m_used_packets;
	public:
		c_tag_resource_stream_task(); /* compiler_generated() */
	};
	static_assert(sizeof(c_tag_resource_stream_task) == 96, "Invalid c_tag_resource_stream_task size");

}
using namespace hades_file_local;
/* ---------- prototypes */

extern long tag_resource_stream_async(long resource_handle, void *buffer, long buffer_size, c_async_completion_flag *completed);

/* ---------- globals */

/* ---------- private variables */

c_static_bit_vector<32> c_tag_resource_stream_task::m_used_packets; // 0x118F4E80

/* ---------- public code */

_extern long _sub_10854430(long, void *, long, c_async_completion_flag *);
long tag_resource_stream_async(long resource_handle, void *buffer, long buffer_size, c_async_completion_flag *completed) // 0x10854430
{
	mangled_x86(MANGLED_TODO, "?tag_resource_stream_async@@YAJJPAXJPAUc_async_completion_flag@@@Z");
	// static ...; // 0x108545D4
	// long resource_handle;
	// void *buffer;
	// long buffer_size;
	// c_async_completion_flag *completed;
	// s_cache_file_tag_resource_table_runtime *resource_table;
	// s_cache_file_resource_shared_file *(*const get_shared_file_handle)(void *, e_cache_file_tag_resource_location);
	// bool (*const get_page)(void *, __int32, __int32, s_indirect_cache_file_page *);
	// s_tag_resource *resource;
	// void *page_atlas;
	// e_cache_file_tag_resource_location resource_location;
	// s_indirect_cache_file_page page;
	// s_cache_file_resource_shared_file *shared_file;
	// c_tag_resource_stream_task task;
	// void *resource_runtime_manager;
	// short resource_index;
	// function call : s_cache_file_resource_shared_file *(*const)(void *, e_cache_file_tag_resource_location)
	// function call : bool (*const)(void *, __int32, __int32, s_indirect_cache_file_page *)
	todo("implement");
	long __result = _sub_10854430(resource_handle, buffer, buffer_size, completed);
	return __result;
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0c_tag_resource_stream_task@hades_file_local@@QAE@XZ"); no body to assert in
_inline c_tag_resource_stream_task::c_tag_resource_stream_task() = default; // 0x10853DB0

_extern bool _sub_10854290(c_tag_resource_stream_task::s_packet const *const);
_inline bool c_tag_resource_stream_task::s_packet::is_filled() const // 0x10854290
{
	// `anonymous-namespace'::c_tag_resource_stream_task::s_packet::is_filled
	// c_tag_resource_stream_task::s_packet const *const this;
	todo("implement");
	bool __result = _sub_10854290((c_tag_resource_stream_task::s_packet const *)this);
	return __result;
}

_inline void c_tag_resource_stream_task::initialize(void *file_handle, unsigned long file_offset, unsigned long compressed_size, unsigned long uncompressed_size, void *buffer, unsigned long buffer_size, c_async_completion_flag *completion_flag) // 0x108541A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_tag_resource_stream_task@hades_file_local@@QAEXPAXKKK0KPAUc_async_completion_flag@@@Z");
	// `anonymous-namespace'::c_tag_resource_stream_task::initialize
	// c_async_completion_flag *completion_flag;

	m_file_handle = file_handle;
	m_file_offset = file_offset;
	m_compressed_size = compressed_size;
	m_uncompressed_size = uncompressed_size;
	m_destination_buffer = (char *)buffer;
	m_destination_buffer_size = buffer_size;
	m_initialized = true;
	m_inflight_packets = 0;
	m_next_in_block_index = 0;
	m_next_out_block_index = 0;
	m_block_pos = 0;
	m_total_bytes_decompressed = 0;
	m_total_bytes_processed = 0;
	m_total_bytes_read = 0;
	m_dest_ptr = (char *)buffer;
	m_block_buffer = nullptr;
	m_completion_flag = completion_flag;
}

_extern void _sub_10854030(c_tag_resource_stream_task *const);
_inline void c_tag_resource_stream_task::dispose() // 0x10854030
{
	// `anonymous-namespace'::c_tag_resource_stream_task::dispose
	// c_tag_resource_stream_task *const this;
	todo("implement");
	_sub_10854030(this);
}

_extern long _sub_108542F0(c_tag_resource_stream_task *const);
_inline long c_tag_resource_stream_task::next_free_packet_index() // 0x108542F0
{
	// `anonymous-namespace'::c_tag_resource_stream_task::next_free_packet_index
	// c_tag_resource_stream_task *const this;
	{
		// __int32 j;
	}
	todo("implement");
	long __result = _sub_108542F0(this);
	return __result;
}

_extern bool _sub_108547F0(c_tag_resource_stream_task *const);
_inline bool c_tag_resource_stream_task::update() // 0x108547F0
{
	// `anonymous-namespace'::c_tag_resource_stream_task::update
	// c_tag_resource_stream_task *const this;
	{
		// c_tag_resource_stream_task::s_lz_block_header *block_header;
		{
			// long packet_index;
			// __int32 bRet;
			// unsigned long err;
		}
		{
			// __int32 j;
			{
				// long input_length;
				// char *input_buffer;
			}
		}
		{
			// long overflow;
		}
	}
	// function call : __int32 (void *, void *, unsigned long, unsigned long *, _OVERLAPPED *)
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : long (*const)(void *, void *, long)
	todo("implement");
	bool __result = _sub_108547F0(this);
	return __result;
}

_inline void c_tag_resource_stream_task::abort(e_tag_resource_stream_abort_reason reason) // 0x10853E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?abort@c_tag_resource_stream_task@hades_file_local@@QAEXW4e_tag_resource_stream_abort_reason@@@Z");
	// `anonymous-namespace'::c_tag_resource_stream_task::abort
	// e_tag_resource_stream_abort_reason reason;

	m_completion_flag->set_internal_data(reason);
	m_aborted = true;
}

_inline e_async_completion c_tag_resource_stream_task::async_callback(c_tag_resource_stream_task *task) // 0x10853FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?async_callback@c_tag_resource_stream_task@hades_file_local@@SA?AW4e_async_completion@@PAV12@@Z");
	// `anonymous-namespace'::c_tag_resource_stream_task::async_callback
	// c_tag_resource_stream_task *task;

	if (!task->update())
	{
		return (e_async_completion)0;
	}

	task->dispose();
	return (e_async_completion)1;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_static_bit_vector<32>::test(long);
template bool c_static_bit_vector<32>::valid_bit(long);
template void c_static_bit_vector<32>::set(long);
template void c_static_bit_vector<32>::unset(long);

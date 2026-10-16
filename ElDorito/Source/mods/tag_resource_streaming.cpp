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
			// s_packet(); /* compiler_generated(): left implicit, as the original's was */
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
		_OVERLAPPED m_overlapped = {}; // 0x38
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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols where it has them.
	static auto const lz4_decompress_fast = reinterpret_cast<long (*)(void *, void *, long)>(0xF34960);  // no symbol; named from what it does
}
#line 118

template<typename t_task_data> static long const async_task_add_ex(long priority, t_task_data *data, long category, e_async_completion (*callback)(t_task_data *), c_async_completion_flag *completion_flag) { if (!(sizeof(t_task_data) <= 554)) { display_assert("sizeof(t_task_data) <= 554", "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\async\\async.hpp", 23, true); system_exit(-1); } return ((long (*)(long, void *, long, void *, c_async_completion_flag *))0x5085C0)(priority, data, category, (void *)callback, completion_flag); }  // hades: added for 0x10854430

extern long tag_resource_stream_async(long resource_handle, void *buffer, long buffer_size, c_async_completion_flag *completed);

/* ---------- globals */

/* ---------- private variables */

c_static_bit_vector<32> c_tag_resource_stream_task::m_used_packets; // 0x118F4E80

/* ---------- public code */

long tag_resource_stream_async(long resource_handle, void *buffer, long buffer_size, c_async_completion_flag *completed) // 0x10854430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_resource_stream_async@@YAJJPAXJPAUc_async_completion_flag@@@Z");

	bool (__thiscall *const get_page)(void *, __int32, __int32, s_indirect_cache_file_page *) = *reinterpret_cast<bool (__thiscall **)(void *, __int32, __int32, s_indirect_cache_file_page *)>(0x1658634);
	s_cache_file_resource_shared_file *(__thiscall *const get_shared_file_handle)(void *, e_cache_file_tag_resource_location) = reinterpret_cast<s_cache_file_resource_shared_file *(__thiscall *)(void *, e_cache_file_tag_resource_location)>(0x561520);
	void *resource_runtime_manager = *reinterpret_cast<void **>(0x23916C8);
	void *page_atlas = offset_pointer(resource_runtime_manager, 0x14);
	s_cache_file_tag_resource_table_runtime *resource_table = *static_cast<s_cache_file_tag_resource_table_runtime **>(offset_pointer(resource_runtime_manager, 0x24));
	short resource_index = (short)resource_handle;
	if (resource_index < 0 || resource_index >= resource_table->count)
		return -1;
	s_tag_resource *resource = resource_table->resources[resource_index];
	e_cache_file_tag_resource_location resource_location = tag_resource_get_location(resource);
	if (resource_location == _cache_file_tag_resource_location_invalid)
		return -1;
	s_indirect_cache_file_page page;
	s_cache_file_resource_shared_file *shared_file = get_shared_file_handle(resource_runtime_manager, resource_location);
	if (!shared_file || !get_page(page_atlas, resource_handle & 0xFFFF, 0, &page))
		return -1;
	c_tag_resource_stream_task task;
	task.initialize(shared_file->file_handle, page.offset, resource->compressed_block_size, resource->uncompressed_block_size, buffer, buffer_size, completed);
	completed->set(0);
	completed->set_internal_data(0);
	return async_task_add_ex(10, &task, 8, c_tag_resource_stream_task::async_callback, completed);
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0c_tag_resource_stream_task@hades_file_local@@QAE@XZ"); no body to assert in
_inline c_tag_resource_stream_task::c_tag_resource_stream_task() = default; // 0x10853DB0

_inline bool c_tag_resource_stream_task::s_packet::is_filled() const // 0x10854290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_filled@s_packet@c_tag_resource_stream_task@hades_file_local@@QBE_NXZ");

	return overlapped.InternalHigh >= length;
}

_inline void c_tag_resource_stream_task::initialize(void *file_handle, unsigned long file_offset, unsigned long compressed_size, unsigned long uncompressed_size, void *buffer, unsigned long buffer_size, c_async_completion_flag *completion_flag) // 0x108541A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_tag_resource_stream_task@hades_file_local@@QAEXPAXKKK0KPAUc_async_completion_flag@@@Z");

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

_inline void c_tag_resource_stream_task::dispose() // 0x10854030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dispose@c_tag_resource_stream_task@hades_file_local@@QAEXXZ");

	block_allocator::get().free(m_block_buffer);
}

_inline long c_tag_resource_stream_task::next_free_packet_index() // 0x108542F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next_free_packet_index@c_tag_resource_stream_task@hades_file_local@@QAEJXZ");

	for (long i = 0; i < 32; i++)
	{
		if (!m_used_packets.test(i))
		{
			return i;
		}
	}

	return -1;
}

_inline bool c_tag_resource_stream_task::update() // 0x108547F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_tag_resource_stream_task@hades_file_local@@QAE_NXZ");

	(void)((!!(m_initialized)) || (_wassert(L"m_initialized", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\tag_resource_streaming.cpp", 147), 0));
	if (m_total_bytes_decompressed < m_uncompressed_size)
	{
		if (m_total_bytes_read < m_compressed_size && m_inflight_packets <= 2)
		{
			long packet_index = next_free_packet_index();
			if (packet_index == -1)
				return false;
			m_used_packets.set(packet_index);
			m_packets[packet_index].overlapped = {};
			m_packets[packet_index].overlapped.Offset = m_file_offset + m_total_bytes_read;
			m_packets[packet_index].length = std::min<int>(m_compressed_size - m_total_bytes_read, 0xFFFF);
			m_packets[packet_index].index = m_next_in_block_index;
			__int32 bRet = ReadFile(m_file_handle, m_packets[packet_index].buffer, m_packets[packet_index].length, &m_packets[packet_index].bytes_read, &m_packets[packet_index].overlapped);
			unsigned long err = GetLastError();
			if (!bRet && GetLastError() != ERROR_IO_PENDING)
			{
				abort(_tag_resource_stream_abort_file_read_error);
				return true;
			}
			m_total_bytes_read += m_packets[packet_index].length;
			m_next_in_block_index++;
			m_inflight_packets++;
		}
		for (__int32 j = 0; j < 32; j++)
		{
			if (m_used_packets.test(j) && m_packets[j].is_filled() && m_packets[j].index == m_next_out_block_index)
			{
				m_used_packets.unset(j);
				m_next_out_block_index++;
				m_inflight_packets--;
				long input_length = m_packets[j].length;
				char *input_buffer = m_packets[j].buffer;
				if (!m_block_buffer)
				{
					m_block_buffer_size = 0xFFFF8;
					m_block_buffer = (char *)block_allocator::get().allocate();
					if (!m_block_buffer)
						return false;
				}
				(void)((!!(m_block_pos + input_length < m_block_buffer_size)) || (_wassert(L"m_block_pos + input_length < m_block_buffer_size", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\tag_resource_streaming.cpp", 202), 0));
				memcpy(m_block_buffer + m_block_pos, input_buffer, input_length);
				m_block_pos += input_length;
			}
		}
		s_lz_block_header *block_header = (s_lz_block_header *)m_block_buffer;
		if (m_block_pos >= block_header->compressed_size + 8)
		{
			if (eldorado::lz4_decompress_fast(m_block_buffer + 8, m_dest_ptr, block_header->uncompressed_size) < 0 && m_block_buffer)
			{
				abort(_tag_resource_stream_abort_decompression_error);
				return true;
			}
			m_dest_ptr += block_header->uncompressed_size;
			m_total_bytes_decompressed += block_header->uncompressed_size;
			m_total_bytes_processed += block_header->compressed_size;
			long overflow = m_block_pos - (block_header->compressed_size + 8);
			if (overflow < 0 && m_block_buffer)
			{
				abort(_tag_resource_stream_abort_decompression_error);
				return true;
			}
			memcpy(m_block_buffer, &m_block_buffer[m_block_pos - overflow], overflow);
			m_block_pos = overflow;
		}
	}
	else
	{
		return true;
	}
	return false;
}

_inline void c_tag_resource_stream_task::abort(e_tag_resource_stream_abort_reason reason) // 0x10853E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?abort@c_tag_resource_stream_task@hades_file_local@@QAEXW4e_tag_resource_stream_abort_reason@@@Z");

	m_completion_flag->set_internal_data(reason);
	m_aborted = true;
}

_inline e_async_completion c_tag_resource_stream_task::async_callback(c_tag_resource_stream_task *task) // 0x10853FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?async_callback@c_tag_resource_stream_task@hades_file_local@@SA?AW4e_async_completion@@PAV12@@Z");

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

/* ---------- explicit instantiations */
template void c_block_allocator<1048568,8>::free(void *);

/* ---------- data definitions */
namespace hades_file_local { c_tag_resource_stream_task::s_packet c_tag_resource_stream_task::m_packets[32]; }

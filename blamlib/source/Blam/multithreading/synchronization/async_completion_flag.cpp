/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"

/* ---------- forward declarations */

struct c_async_completion_flag;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

long c_async_completion_flag::peek() const // 0x10F0C190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?peek@c_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;

	return m_status.peek();
}

void c_async_completion_flag::set(long value) // 0x10F0C1F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_async_completion_flag@@QAEXJ@Z");
	// long value;

	m_status.set(value);
}

void c_async_completion_flag::set_internal_data(long value) // 0x10F0C260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_internal_data@c_async_completion_flag@@QAEXJ@Z");
	// long value;

	m_internal_data.set(value);
}

long c_async_completion_flag::get_internal_data() const // 0x10F0C0B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_internal_data@c_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;

	return m_internal_data.peek();
}

bool c_async_completion_flag::is_done() const // 0x10F0C110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_done@c_async_completion_flag@@QBE_NXZ");
	// c_async_completion_flag const *const this;

	return m_status.peek() == 1;
}

c_async_completion_flag &c_async_completion_flag::operator=(c_async_completion_flag const &other) // 0x10F0BFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??4c_async_completion_flag@@QAEAAU0@ABU0@@Z");
	// c_async_completion_flag const &other;

	m_status = other.peek();
	m_internal_data = other.get_internal_data();

	return *this;
}

c_async_completion_flag::operator long() const // 0x10F0C050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??Bc_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;

	return m_status.peek();
}

/* ---------- private code */

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
	return m_status.peek();
}

void c_async_completion_flag::set(long value) // 0x10F0C1F0
{
	m_status.set(value);
}

void c_async_completion_flag::set_internal_data(long value) // 0x10F0C260
{
	m_internal_data.set(value);
}

long c_async_completion_flag::get_internal_data() const // 0x10F0C0B0
{
	return m_internal_data.peek();
}

bool c_async_completion_flag::is_done() const // 0x10F0C110
{
	return m_status.peek() == 1;
}

c_async_completion_flag &c_async_completion_flag::operator=(c_async_completion_flag const &other) // 0x10F0BFA0
{
	m_status = other.peek();
	m_internal_data = other.get_internal_data();

	return *this;
}

c_async_completion_flag::operator long() const // 0x10F0C050
{
	return m_status.peek();
}

/* ---------- private code */

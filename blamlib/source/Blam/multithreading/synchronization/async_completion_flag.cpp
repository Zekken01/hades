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

_extern long _sub_10F0C190(c_async_completion_flag const *const);
long c_async_completion_flag::peek() const // 0x10F0C190
{
	mangled_x86(MANGLED_TODO, "?peek@c_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;
	todo("implement");
	long __result = _sub_10F0C190((c_async_completion_flag const *)this);
	return __result;
}

_extern void _sub_10F0C1F0(c_async_completion_flag *const, long);
void c_async_completion_flag::set(long value) // 0x10F0C1F0
{
	mangled_x86(MANGLED_TODO, "?set@c_async_completion_flag@@QAEXJ@Z");
	// long value;
	todo("implement");
	_sub_10F0C1F0(this, value);
}

_extern void _sub_10F0C260(c_async_completion_flag *const, long);
void c_async_completion_flag::set_internal_data(long value) // 0x10F0C260
{
	mangled_x86(MANGLED_TODO, "?set_internal_data@c_async_completion_flag@@QAEXJ@Z");
	// long value;
	todo("implement");
	_sub_10F0C260(this, value);
}

_extern long _sub_10F0C0B0(c_async_completion_flag const *const);
long c_async_completion_flag::get_internal_data() const // 0x10F0C0B0
{
	mangled_x86(MANGLED_TODO, "?get_internal_data@c_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;
	todo("implement");
	long __result = _sub_10F0C0B0((c_async_completion_flag const *)this);
	return __result;
}

_extern bool _sub_10F0C110(c_async_completion_flag const *const);
bool c_async_completion_flag::is_done() const // 0x10F0C110
{
	mangled_x86(MANGLED_TODO, "?is_done@c_async_completion_flag@@QBE_NXZ");
	// c_async_completion_flag const *const this;
	todo("implement");
	bool __result = _sub_10F0C110((c_async_completion_flag const *)this);
	return __result;
}

extern c_async_completion_flag &_sub_10F0BFA0(c_async_completion_flag *const, c_async_completion_flag const &);
c_async_completion_flag &c_async_completion_flag::operator=(c_async_completion_flag const &other) // 0x10F0BFA0
{
	mangled_x86(MANGLED_TODO, "??4c_async_completion_flag@@QAEAAU0@ABU0@@Z");
	// c_async_completion_flag const &other;
	todo("implement");
	c_async_completion_flag & __result = _sub_10F0BFA0(this, other);
	return __result;
}

_extern long _sub_10F0C050(c_async_completion_flag const *const);
c_async_completion_flag::operator long() const // 0x10F0C050
{
	mangled_x86(MANGLED_TODO, "??Bc_async_completion_flag@@QBEJXZ");
	// c_async_completion_flag const *const this;
	todo("implement");
	long __result = _sub_10F0C050((c_async_completion_flag const *)this);
	return __result;
}

/* ---------- private code */

#pragma once
#ifndef __HADES_RECOVERED_EARLY_TEMPLATES_H__
#define __HADES_RECOVERED_EARLY_TEMPLATES_H__

// Split out of hades/recovered_templates.h by
// Docs/Scripts/split_early_templates.py -- do not edit.
//
// These templates reference nothing from hades/recovered_types.h, and
// recovered_types.h has members whose real type is one of them. Declaring them
// FIRST is what lets `build_recovered_types.py` spell those members instead of
// falling back to `unsigned char name[N]`. Their member definitions stay in
// recovered_templates.h, which still comes after.

#include "hades/static_assert.h"
#include "hades/mangled_assert.h"
#include "hades/reverse_engineering.h"

// CEventSink's callback list is a std::function and its counter a std::atomic;
// recovered_types.h pulls those in for itself, but this header now comes first.
#include <atomic>
#include <functional>
#include <vector>

/* ---------- c_enum (183 instantiations) */

template<typename t_type, typename t_storage_type>
class c_enum
{
private:
	t_storage_type m_value; // 0x0
public:
	_inline c_enum(c_enum const &other);
	_inline c_enum(t_type const &value);
	_inline c_enum(t_storage_type const &value);
	_inline c_enum();
	bool operator==(c_enum const &) const;
	_inline bool operator==(t_type const &other) const;
	_inline bool operator==(t_storage_type const &other) const;
	bool operator!=(c_enum const &) const;
	_inline bool operator!=(t_type const &other) const;
	_inline bool operator!=(t_storage_type const &other) const;
	bool operator<(c_enum const &) const;
	bool operator<(t_type const &) const;
	bool operator<(t_storage_type const &) const;
	bool operator>(c_enum const &) const;
	bool operator>(t_type const &) const;
	bool operator>(t_storage_type const &) const;
	bool operator<=(c_enum const &) const;
	_inline bool operator<=(t_type const &other) const;
	bool operator<=(t_storage_type const &) const;
	bool operator>=(c_enum const &) const;
	_inline bool operator>=(t_type const &other) const;
	bool operator>=(t_storage_type const &) const;
	c_enum operator~() const;
	c_enum operator|(c_enum const &) const;
	c_enum operator|(t_type const &) const;
	c_enum operator|(__int32 const) const;
	c_enum &operator|=(c_enum const &);
	c_enum &operator|=(t_type const &);
	c_enum &operator|=(__int32 const);
	c_enum operator&(c_enum const &) const;
	c_enum operator&(t_type const &) const;
	_inline c_enum operator&(__int32 const other) const;
	c_enum &operator&=(c_enum const &);
	c_enum &operator&=(t_type const &);
	c_enum &operator&=(__int32 const);
	c_enum operator+(c_enum const &) const;
	c_enum operator+(t_type const &) const;
	c_enum operator+(t_storage_type const &) const;
	c_enum &operator+=(c_enum const &);
	c_enum &operator+=(t_type const &);
	c_enum &operator+=(t_storage_type const &);
	c_enum operator-(c_enum const &) const;
	_inline c_enum operator-(t_type const &other) const;
	c_enum operator-(t_storage_type const &) const;
	c_enum operator-() const;
	c_enum &operator-=(c_enum const &);
	c_enum &operator-=(t_type const &);
	c_enum &operator-=(t_storage_type const &);
	c_enum operator*(c_enum const &) const;
	c_enum operator*(t_type const &) const;
	c_enum operator*(t_storage_type const &) const;
	c_enum &operator*=(c_enum const &);
	c_enum &operator*=(t_type const &);
	c_enum &operator*=(t_storage_type const &);
	c_enum operator/(c_enum const &) const;
	c_enum operator/(t_type const &) const;
	c_enum operator/(t_storage_type const &) const;
	c_enum &operator/=(c_enum const &);
	c_enum &operator/=(t_type const &);
	c_enum &operator/=(t_storage_type const &);
	_inline c_enum &operator=(c_enum const &other);
	_inline c_enum &operator=(t_type const &other);
	_inline c_enum &operator=(t_storage_type const &other);
	_inline operator bool() const;
	_inline operator t_type() const;
	_inline operator t_storage_type() const;
};

/* ---------- c_flags (146 instantiations) */

template<typename t_type, typename t_storage_type>
class c_flags
{
private:
	t_storage_type m_value; // 0x0
public:
	_inline c_flags(c_flags const &other);
	c_flags(t_type const &);
	_inline c_flags(t_storage_type const &value);
	_inline c_flags();
	bool operator==(c_flags const &) const;
	_inline bool operator==(t_type const &other) const;
	_inline bool operator==(t_storage_type const &other) const;
	bool operator!=(c_flags const &) const;
	bool operator!=(t_type const &) const;
	_inline bool operator!=(t_storage_type const &other) const;
	bool operator<(c_flags const &) const;
	_inline bool operator<(t_type const &other) const;
	bool operator<(t_storage_type const &) const;
	bool operator>(c_flags const &) const;
	bool operator>(t_type const &) const;
	bool operator>(t_storage_type const &) const;
	bool operator<=(c_flags const &) const;
	bool operator<=(t_type const &) const;
	bool operator<=(t_storage_type const &) const;
	bool operator>=(c_flags const &) const;
	_inline bool operator>=(t_type const &other) const;
	bool operator>=(t_storage_type const &) const;
	c_flags operator~() const;
	c_flags operator|(c_flags const &) const;
	c_flags operator|(t_type const &) const;
	_inline c_flags operator|(__int32 const other) const;
	c_flags &operator|=(c_flags const &);
	c_flags &operator|=(t_type const &);
	_inline c_flags &operator|=(__int32 const other);
	c_flags operator&(c_flags const &) const;
	_inline c_flags operator&(t_type const &other) const;
	_inline c_flags operator&(__int32 const other) const;
	c_flags &operator&=(c_flags const &);
	c_flags &operator&=(t_type const &);
	_inline c_flags &operator&=(__int32 const other);
	c_flags operator+(c_flags const &) const;
	c_flags operator+(t_type const &) const;
	c_flags operator+(t_storage_type const &) const;
	c_flags &operator+=(c_flags const &);
	c_flags &operator+=(t_type const &);
	c_flags &operator+=(t_storage_type const &);
	c_flags operator-(c_flags const &) const;
	c_flags operator-(t_type const &) const;
	c_flags operator-(t_storage_type const &) const;
	c_flags operator-() const;
	c_flags &operator-=(c_flags const &);
	c_flags &operator-=(t_type const &);
	c_flags &operator-=(t_storage_type const &);
	c_flags operator*(c_flags const &) const;
	c_flags operator*(t_type const &) const;
	c_flags operator*(t_storage_type const &) const;
	c_flags &operator*=(c_flags const &);
	c_flags &operator*=(t_type const &);
	c_flags &operator*=(t_storage_type const &);
	c_flags operator/(c_flags const &) const;
	c_flags operator/(t_type const &) const;
	c_flags operator/(t_storage_type const &) const;
	c_flags &operator/=(c_flags const &);
	c_flags &operator/=(t_type const &);
	c_flags &operator/=(t_storage_type const &);
	_inline c_flags &operator=(c_flags const &other);
	c_flags &operator=(t_type const &);
	_inline c_flags &operator=(t_storage_type const &other);
	_inline operator bool() const;
	operator t_type() const;
	_inline operator t_storage_type() const;
	_inline bool test(t_type bit) const;
	_inline void set(t_type bit, bool value);
};

/* ---------- s_static_array (41 instantiations) */

template<typename t_type, long k_count>
struct s_static_array
{
public:
	_inline t_type const &operator[](long index) const;
	_inline t_type &operator[](long index);
	void set_all(t_type const &);
	_inline void set_memory(unsigned char value);
	_inline long get_count();
	static _inline bool valid(__int32 index);
	_inline t_type *begin() const;
	// s_static_array(s_static_array &) = default; /* compiler_generated() */
	_inline t_type *end() const;
	// s_static_array(s_static_array const &) = default; /* compiler_generated() */
	_inline t_type *get_elements();
	// hades: `= default` rather than a declaration with no definition. A
	// declared-only constructor makes every defaulted constructor of a class
	// holding one emit a call to it, which the original does not have -
	// c_network_session_parameter_base's lost its match that way.
	// hades: no declared constructors at all, so it stays an aggregate (H7).
	t_type m_elements[k_count]; // 0x0
	s_static_array &operator=(s_static_array &) = default; /* compiler_generated() */
	s_static_array &operator=(s_static_array const &) = default; /* compiler_generated() */
};

/* ---------- CEventSink (6 instantiations) */

template<typename... t_args>
class CEventSink
{
public:
	struct SCallbackEntry
	{
		std::function<void __cdecl(t_args...)> callback; // 0x0
		int id; // 0x28
		// hades: no declared special members, so it stays an aggregate - Subscribe
		// builds its entry with aggregate initialization, and the move constructor
		// and destructor are the implicit ones.
	};
	typedef std::function<void __cdecl(t_args...)> TCallback;
	_inline __int32 Subscribe(std::function<void __cdecl(t_args...)> const &callable);
	void Unsubscribe(__int32);
	_inline void PostEvent(t_args... args);
	void Reset();
private:
	std::atomic<int> m_nextId; // 0x0
	std::vector<CEventSink::SCallbackEntry> m_callbacks; // 0x4
public:
	CEventSink() = default; /* compiler_generated() */  // hades: implicit (noexcept, no EH in its users)
	_inline ~CEventSink() = default; /* compiler_generated() */
};

/* ---------- hkArray (1 instantiations) */

template<typename t_arg0>
class hkArray
{
public:
	t_arg0 *m_data; // 0x0
	__int32 m_size; // 0x4
	__int32 m_capacityAndFlags; // 0x8
	_inline t_arg0 &operator[](__int32 i);
	t_arg0 const &operator[](__int32) const;
};

#endif // __HADES_RECOVERED_EARLY_TEMPLATES_H__

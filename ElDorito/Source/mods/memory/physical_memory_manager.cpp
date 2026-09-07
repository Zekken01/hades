/* ---------- headers */

#include "mods/memory/physical_memory_manager.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Forge/ForgeUndo.hpp"
#include "mods/memory/virtual_page_memory_allocator.hpp"

/* ---------- forward declarations */

struct c_physical_memory_manager;
struct c_virtual_page_memory_allocator;
namespace
{
	struct s_physical_memory_stage;
	class c_physical_memory_stack;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_physical_memory_stage
	{
		unsigned long marker; // 0x0
		unsigned long current_size; // 0x4
	};
}
// static_assert(sizeof(s_physical_memory_stage) == 8, "Invalid s_physical_memory_stage size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace
{
	class c_physical_memory_stack
	{
	public:
		bool initialize(unsigned long);
		void push(e_physical_memory_stage);
		void pop(e_physical_memory_stage);
		void *allocate(e_physical_memory_stage, unsigned long, long, unsigned long *);
		unsigned long get_stage_used_size(e_physical_memory_stage);
		unsigned long get_used_size() const;
		unsigned long get_total_size() const;
		void *get_base_address();
		void *get_current_address();
		e_physical_memory_stage get_current_stage() const;
	private:
		bool m_initialized; // 0x0
		unsigned char __pad0[3]; // 0x1
		long m_current_stage; // 0x4
		s_physical_memory_stage m_stages[3]; // 0x8
		c_virtual_page_memory_allocator m_allocator; // 0x20
	public:
		c_physical_memory_stack(); /* compiler_generated() */
	};
	static_assert(sizeof(c_physical_memory_stack) == 48, "Invalid c_physical_memory_stack size");
}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_virtual_page_memory_allocator* _sub_108BDA90(c_virtual_page_memory_allocator *const);
_inline c_virtual_page_memory_allocator::c_virtual_page_memory_allocator() // 0x108BDA90
{
	mangled_x86(MANGLED_TODO, "??0c_virtual_page_memory_allocator@@QAE@XZ");
	// c_virtual_page_memory_allocator *const this;
	compiler_generated();
	todo("implement");
	_sub_108BDA90(this);
}

_extern bool _sub_108BE090(unsigned long);
bool c_physical_memory_manager::initialize(unsigned long total_memory_size) // 0x108BE090
{
	mangled_x86(MANGLED_TODO, "?initialize@c_physical_memory_manager@@SA_NK@Z");
	// unsigned long total_memory_size;
	todo("implement");
	bool __result = _sub_108BE090(total_memory_size);
	return __result;
}

_extern void _sub_108BE370(e_physical_memory_stage);
void c_physical_memory_manager::push(e_physical_memory_stage stage) // 0x108BE370
{
	mangled_x86(MANGLED_TODO, "?push@c_physical_memory_manager@@SAXW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;
	todo("implement");
	_sub_108BE370(stage);
}

_extern void _sub_108BE1A0(e_physical_memory_stage);
void c_physical_memory_manager::pop(e_physical_memory_stage stage) // 0x108BE1A0
{
	mangled_x86(MANGLED_TODO, "?pop@c_physical_memory_manager@@SAXW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;
	todo("implement");
	_sub_108BE1A0(stage);
}

_extern void *_sub_108BDAE0(e_physical_memory_stage, char const *, unsigned long, long, unsigned long *);
void *c_physical_memory_manager::allocate(e_physical_memory_stage stage, char const *name, unsigned long size, long alignment_bits, unsigned long *out_allocated_size) // 0x108BDAE0
{
	mangled_x86(MANGLED_TODO, "?allocate@c_physical_memory_manager@@SAPAXW4e_physical_memory_stage@@PBDKJPAK@Z");
	// unsigned long *out_allocated_size;
	todo("implement");
	void * __result = _sub_108BDAE0(stage, name, size, alignment_bits, out_allocated_size);
	return __result;
}

_extern void *_sub_108BDCB0();
void *c_physical_memory_manager::get_base_address() // 0x108BDCB0
{
	mangled_x86(MANGLED_TODO, "?get_base_address@c_physical_memory_manager@@SAPAXXZ");
	// procedure flags: nofpo
	todo("implement");
	void * __result = _sub_108BDCB0();
	return __result;
}

_extern void *_sub_108BDD80();
void *c_physical_memory_manager::get_current_address() // 0x108BDD80
{
	mangled_x86(MANGLED_TODO, "?get_current_address@c_physical_memory_manager@@SAPAXXZ");
	// procedure flags: nofpo
	todo("implement");
	void * __result = _sub_108BDD80();
	return __result;
}

_extern unsigned long _sub_108BDE70(e_physical_memory_stage);
unsigned long c_physical_memory_manager::get_stage_used_size(e_physical_memory_stage stage) // 0x108BDE70
{
	mangled_x86(MANGLED_TODO, "?get_stage_used_size@c_physical_memory_manager@@SAKW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;
	todo("implement");
	unsigned long __result = _sub_108BDE70(stage);
	return __result;
}

_extern unsigned long _sub_108BDFC0();
unsigned long c_physical_memory_manager::get_used_size() // 0x108BDFC0
{
	mangled_x86(MANGLED_TODO, "?get_used_size@c_physical_memory_manager@@SAKXZ");
	// procedure flags: nofpo
	todo("implement");
	unsigned long __result = _sub_108BDFC0();
	return __result;
}

_extern unsigned long _sub_108BDEF0();
unsigned long c_physical_memory_manager::get_total_size() // 0x108BDEF0
{
	mangled_x86(MANGLED_TODO, "?get_total_size@c_physical_memory_manager@@SAKXZ");
	// procedure flags: nofpo
	todo("implement");
	unsigned long __result = _sub_108BDEF0();
	return __result;
}

_extern void _sub_108BE2F0();
void c_physical_memory_manager::prepare_for_new_map() // 0x108BE2F0
{
	mangled_x86(MANGLED_TODO, "?prepare_for_new_map@c_physical_memory_manager@@SAXXZ");
	// procedure flags: nofpo
	{
		// unsigned long i;
	}
	todo("implement");
	_sub_108BE2F0();
}

/* ---------- private code */

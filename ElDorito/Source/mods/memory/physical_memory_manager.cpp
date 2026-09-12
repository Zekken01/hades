/* ---------- headers */

#include "mods/memory/physical_memory_manager.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Forge/ForgeUndo.hpp"
#include "mods/memory/virtual_page_memory_allocator.hpp"

/* ---------- forward declarations */

struct c_physical_memory_manager;
struct c_virtual_page_memory_allocator;
namespace hades_file_local
{
	struct s_physical_memory_stage;
	class c_physical_memory_stack;
}
using namespace hades_file_local;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_physical_memory_stage
	{
		unsigned long marker; // 0x0
		unsigned long current_size; // 0x4
	};
}
using namespace hades_file_local;
// static_assert(sizeof(s_physical_memory_stage) == 8, "Invalid s_physical_memory_stage size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern c_physical_memory_stack memory_stack; // 0x12408008
}
using namespace hades_file_local;
/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0c_virtual_page_memory_allocator@@QAE@XZ"); no body to assert in
_inline c_virtual_page_memory_allocator::c_virtual_page_memory_allocator() = default; // 0x108BDA90

bool c_physical_memory_manager::initialize(unsigned long total_memory_size) // 0x108BE090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_physical_memory_manager@@SA_NK@Z");
	// unsigned long total_memory_size;

	return memory_stack.initialize(total_memory_size);
}

void c_physical_memory_manager::push(e_physical_memory_stage stage) // 0x108BE370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?push@c_physical_memory_manager@@SAXW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;

	memory_stack.push(stage);
}

void c_physical_memory_manager::pop(e_physical_memory_stage stage) // 0x108BE1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?pop@c_physical_memory_manager@@SAXW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;

	memory_stack.pop(stage);
}

void *c_physical_memory_manager::allocate(e_physical_memory_stage stage, char const *name, unsigned long size, long alignment_bits, unsigned long *out_allocated_size) // 0x108BDAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?allocate@c_physical_memory_manager@@SAPAXW4e_physical_memory_stage@@PBDKJPAK@Z");
	// unsigned long *out_allocated_size;

	return memory_stack.allocate(stage, size, alignment_bits, out_allocated_size);
}

void *c_physical_memory_manager::get_base_address() // 0x108BDCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_base_address@c_physical_memory_manager@@SAPAXXZ");
	// procedure flags: nofpo

	return memory_stack.get_base_address();
}

void *c_physical_memory_manager::get_current_address() // 0x108BDD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_address@c_physical_memory_manager@@SAPAXXZ");
	// procedure flags: nofpo

	return memory_stack.get_current_address();
}

unsigned long c_physical_memory_manager::get_stage_used_size(e_physical_memory_stage stage) // 0x108BDE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_stage_used_size@c_physical_memory_manager@@SAKW4e_physical_memory_stage@@@Z");
	// e_physical_memory_stage stage;

	return memory_stack.get_stage_used_size(stage);
}

unsigned long c_physical_memory_manager::get_used_size() // 0x108BDFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_used_size@c_physical_memory_manager@@SAKXZ");
	// procedure flags: nofpo

	return memory_stack.get_used_size();
}

unsigned long c_physical_memory_manager::get_total_size() // 0x108BDEF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_total_size@c_physical_memory_manager@@SAKXZ");
	// procedure flags: nofpo

	return memory_stack.get_total_size();
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

// mangled_x86(MANGLED_DEFAULT, "??0c_physical_memory_stack@hades_file_local@@QAE@XZ"); no body to assert in
_inline c_physical_memory_stack::c_physical_memory_stack() = default; // 0x108BDA20

_inline unsigned long c_physical_memory_stack::get_stage_used_size(e_physical_memory_stage stage) // 0x108BDEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_stage_used_size@c_physical_memory_stack@hades_file_local@@QAEKW4e_physical_memory_stage@@@Z");
	// `anonymous-namespace'::c_physical_memory_stack::get_stage_used_size
	// e_physical_memory_stage stage;

	return m_stages[stage].current_size;
}

_inline unsigned long c_physical_memory_stack::get_used_size() const // 0x108BE010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_used_size@c_physical_memory_stack@hades_file_local@@QBEKXZ");
	// `anonymous-namespace'::c_physical_memory_stack::get_used_size
	// c_physical_memory_stack const *const this;

	return m_allocator.get_used_size();
}

_inline unsigned long c_physical_memory_stack::get_total_size() const // 0x108BDF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_total_size@c_physical_memory_stack@hades_file_local@@QBEKXZ");
	// `anonymous-namespace'::c_physical_memory_stack::get_total_size
	// c_physical_memory_stack const *const this;

	return m_allocator.get_total_size();
}

_inline void *c_physical_memory_stack::get_base_address() // 0x108BDD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_base_address@c_physical_memory_stack@hades_file_local@@QAEPAXXZ");
	// `anonymous-namespace'::c_physical_memory_stack::get_base_address
	// c_physical_memory_stack *const this;

	return m_allocator.get_base_address();
}

_inline void *c_physical_memory_stack::get_current_address() // 0x108BDDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_address@c_physical_memory_stack@hades_file_local@@QAEPAXXZ");
	// `anonymous-namespace'::c_physical_memory_stack::get_current_address
	// c_physical_memory_stack *const this;

	return (char *)m_allocator.get_base_address() + m_allocator.get_used_size();
}

_inline e_physical_memory_stage c_physical_memory_stack::get_current_stage() const // 0x108BDE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_stage@c_physical_memory_stack@hades_file_local@@QBE?AW4e_physical_memory_stage@@XZ");
	// `anonymous-namespace'::c_physical_memory_stack::get_current_stage
	// c_physical_memory_stack const *const this;

	return static_cast<e_physical_memory_stage>(m_current_stage);
}

_extern void _sub_108BE3C0(c_physical_memory_stack *const, e_physical_memory_stage);
void c_physical_memory_stack::push(e_physical_memory_stage stage) // 0x108BE3C0
{
	// `anonymous-namespace'::c_physical_memory_stack::push
	// e_physical_memory_stage stage;
	todo("implement");
	_sub_108BE3C0(this, stage);
}

_extern void _sub_108BE1F0(c_physical_memory_stack *const, e_physical_memory_stage);
void c_physical_memory_stack::pop(e_physical_memory_stage stage) // 0x108BE1F0
{
	// `anonymous-namespace'::c_physical_memory_stack::pop
	// e_physical_memory_stage stage;
	todo("implement");
	_sub_108BE1F0(this, stage);
}

_extern bool _sub_108BE0E0(c_physical_memory_stack *const, unsigned long);
bool c_physical_memory_stack::initialize(unsigned long m_total_size) // 0x108BE0E0
{
	// `anonymous-namespace'::c_physical_memory_stack::initialize
	// unsigned long m_total_size;
	{
		// __int32 i;
	}
	todo("implement");
	bool __result = _sub_108BE0E0(this, m_total_size);
	return __result;
}

_extern void *_sub_108BDB40(c_physical_memory_stack *const, e_physical_memory_stage, unsigned long, long, unsigned long *);
void *c_physical_memory_stack::allocate(e_physical_memory_stage stage, unsigned long size, long alignment_bits, unsigned long *out_allocated_size) // 0x108BDB40
{
	// `anonymous-namespace'::c_physical_memory_stack::allocate
	// e_physical_memory_stage stage;
	// unsigned long size;
	// long alignment_bits;
	// unsigned long *out_allocated_size;
	// void *memory;
	// unsigned long allocated_size;
	todo("implement");
	void * __result = _sub_108BDB40(this, stage, size, alignment_bits, out_allocated_size);
	return __result;
}

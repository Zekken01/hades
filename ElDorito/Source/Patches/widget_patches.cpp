/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/widgets/muffin.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_data_array;
struct s_muffin_datum;
struct tls_data;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void widget_patches_apply();

void muffins_update(float time_delta);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_107C41A0();
void widget_patches_apply() // 0x107C41A0
{
	mangled_x86(MANGLED_TODO, "?widget_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_107C41A0();
}

/* ---------- private code */

_extern void _sub_107C3FF0(float);
void muffins_update(float time_delta) // 0x107C3FF0
{
	// `anonymous-namespace'::muffins_update
	// float time_delta;
	// long (*const data_next_index)(s_data_array *, long);
	// char *muffin_array;
	// tls_data *tls;
	// void (*const sub_BC6D80)(long);
	// void (*const sub_BC6920)(long);
	{
		// unsigned short i;
		{
			// s_muffin_datum *muffin;
		}
	}
	// function call : long (*const)(s_data_array *, long)
	// function call : long (*const)(s_data_array *, long)
	// function call : float (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_107C3FF0(time_delta);
}

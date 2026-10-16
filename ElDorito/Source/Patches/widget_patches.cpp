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

extern float (*const game_tick_length)();  // hades: added for 0x107C3FF0

extern void widget_patches_apply();

void muffins_update(float time_delta);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void widget_patches_apply() // 0x107C41A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?widget_patches_apply@@YAXXZ");

	Hook(0x7C76B0, muffins_update).Apply();
}

/* ---------- private code */

void muffins_update(float time_delta) // 0x107C3FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?muffins_update@@YAXM@Z");

	long (*const data_next_index)(s_data_array *, long) = reinterpret_cast<long (*)(s_data_array *, long)>(0x55B130);
	void (*const sub_BC6D80)(long) = reinterpret_cast<void (*)(long)>(0xBC6D80);
	void (*const sub_BC6920)(long) = reinterpret_cast<void (*)(long)>(0xBC6920);
	tls_data *tls = (tls_data *)tls_get(0);
	char *muffin_array = (char *)tls->muffin->address;
	for (unsigned short i = data_next_index(tls->muffin, -1); i != 0xFFFF; i = data_next_index(tls->muffin, i))
	{
		s_muffin_datum *muffin = (s_muffin_datum *)&muffin_array[i * sizeof(s_muffin_datum)];
		muffin->seconds_since_last_update += time_delta;
		if (muffin->seconds_since_last_update >= game_tick_length())
		{
			sub_BC6D80(i);
			muffin->seconds_since_last_update = 0.0f;
			sub_BC6920(i);
		}
	}
}

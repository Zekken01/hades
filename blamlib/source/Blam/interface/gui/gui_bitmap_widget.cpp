/* ---------- headers */

#include "Blam/interface/gui/gui_bitmap_widget.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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

/* ---------- forward declarations */

class c_gui_bitmap_widget;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern short _sub_10F1C4F0(c_gui_bitmap_widget *const);
short c_gui_bitmap_widget::get_sprite_frame_count() // 0x10F1C4F0
{
	mangled_x86(MANGLED_TODO, "?get_sprite_frame_count@c_gui_bitmap_widget@@QAEFXZ");
	// c_gui_bitmap_widget *const this;
	// function call : short (*)(c_gui_bitmap_widget *)
	todo("implement");
	short __result = _sub_10F1C4F0(this);
	return __result;
}

_extern void _sub_10F1C560(c_gui_bitmap_widget *const, long);
void c_gui_bitmap_widget::set_sprite_frame_index(long frame_index) // 0x10F1C560
{
	mangled_x86(MANGLED_TODO, "?set_sprite_frame_index@c_gui_bitmap_widget@@QAEXJ@Z");
	// long frame_index;
	todo("implement");
	_sub_10F1C560(this, frame_index);
}

/* ---------- private code */

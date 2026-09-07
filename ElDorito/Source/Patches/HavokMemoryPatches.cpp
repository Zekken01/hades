/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct c_font_cache_mt_safe;
struct c_rasterizer_draw_string;
struct real_argb_color;
struct short_rectangle2d;
namespace
{
	struct CHavokStatsOutputHandler;
	struct CHavokStatsStringOutputHandler;
	struct CHavokStatsDisplayOutputHandler;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace HavokMemory {}
	using namespace Patches::HavokMemory;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct CHavokStatsOutputHandler
	{
		virtual void OutputLine(real_argb_color const *, char const *) = 0;
		CHavokStatsOutputHandler(CHavokStatsOutputHandler &); /* compiler_generated() */
		CHavokStatsOutputHandler(CHavokStatsOutputHandler const &); /* compiler_generated() */
		CHavokStatsOutputHandler(); /* compiler_generated() */
		CHavokStatsOutputHandler &operator=(CHavokStatsOutputHandler &); /* compiler_generated() */
		CHavokStatsOutputHandler &operator=(CHavokStatsOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(CHavokStatsOutputHandler) == 4, "Invalid CHavokStatsOutputHandler size");

	struct CHavokStatsStringOutputHandler :
		public CHavokStatsOutputHandler
	{
		virtual void OutputLine(real_argb_color const *, char const *);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetString() const;
	private:
		unsigned char __pad0[4]; // 0x4
		std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > m_buffer; // 0x8
	public:
		CHavokStatsStringOutputHandler(CHavokStatsStringOutputHandler &); /* compiler_generated() */
		CHavokStatsStringOutputHandler(); /* compiler_generated() */
		~CHavokStatsStringOutputHandler(); /* compiler_generated() */
		CHavokStatsStringOutputHandler &operator=(CHavokStatsStringOutputHandler &); /* compiler_generated() */
	};
	static_assert(sizeof(CHavokStatsStringOutputHandler) == 184, "Invalid CHavokStatsStringOutputHandler size");

	struct CHavokStatsDisplayOutputHandler :
		public CHavokStatsOutputHandler
	{
		static real_argb_color const kDefaultColor;
		CHavokStatsDisplayOutputHandler(CHavokStatsDisplayOutputHandler &); /* compiler_generated() */
		CHavokStatsDisplayOutputHandler(CHavokStatsDisplayOutputHandler const &); /* compiler_generated() */
		CHavokStatsDisplayOutputHandler();
		virtual void OutputLine(real_argb_color const *, char const *);
	private:
		short_rectangle2d m_displayBounds; // 0x4
		c_font_cache_mt_safe m_fontCache; // 0xC
		c_rasterizer_draw_string m_drawString; // 0x14
		__int32 m_yOffset; // 0x83C
	public:
		~CHavokStatsDisplayOutputHandler(); /* compiler_generated() */
		CHavokStatsDisplayOutputHandler &operator=(CHavokStatsDisplayOutputHandler &); /* compiler_generated() */
		CHavokStatsDisplayOutputHandler &operator=(CHavokStatsDisplayOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(CHavokStatsDisplayOutputHandler) == 2112, "Invalid CHavokStatsDisplayOutputHandler size");
}
/* ---------- prototypes */

extern void ExpandRuntimePool();
namespace Patches
{
	namespace HavokMemory
	{
		extern void ApplyAll();
		extern void RenderDebug();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern unsigned char g_runtimePoolMemory[9014800]; // 0x1195B5E8
}
/* ---------- public code */

_extern void _sub_1085F150();
void ExpandRuntimePool() // 0x1085F150
{
	mangled_x86(MANGLED_TODO, "?ExpandRuntimePool@@YAXXZ");
	// procedure flags: nofpo
	// __int32 additionalPageMemorySize;
	// __int32 additionPages;
	todo("implement");
	_sub_1085F150();
}

namespace Patches
{
	namespace HavokMemory
	{
		_extern void _sub_1085E750();
		void ApplyAll() // 0x1085E750
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@HavokMemory@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1085E750();
		}

		_extern void _sub_1085F970();
		void RenderDebug() // 0x1085F970
		{
			mangled_x86(MANGLED_TODO, "?RenderDebug@HavokMemory@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x1085FA64
			// static ...; // 0x1085FA58
			// static ...; // 0x1085FA50
			{
				// CHavokStatsDisplayOutputHandler outputHandler;
			}
			// function call : bool (*const)()
			// function call : void (*const)(CHavokStatsOutputHandler *)
			todo("implement");
			_sub_1085F970();
		}
	}
}

/* ---------- private code */

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
namespace hades_file_local
{
	struct CHavokStatsOutputHandler;
	struct CHavokStatsStringOutputHandler;
	struct CHavokStatsDisplayOutputHandler;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
		std::string GetString() const;
	private:
		unsigned char __pad0[4]; // 0x4
		std::stringstream m_buffer; // 0x8
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
using namespace hades_file_local;
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

void *havok_memory_init_runtime_pool_hook(void *buff);
void *havok_memory_init_overflow_pool_hook(void *pool, void *buff, __int32 buff_size);
__int32 havok_display_stats_printf_hook(CHavokStatsOutputHandler *output_handler, real_argb_color const *color, char const *format, ...);
void havok_out_of_memory_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned char g_runtimePoolMemory[9014800]; // 0x1195B5E8
}
using namespace hades_file_local;
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

_extern void *_sub_1085FCB0(void *);
void *havok_memory_init_runtime_pool_hook(void *buff) // 0x1085FCB0
{
	// `anonymous-namespace'::havok_memory_init_runtime_pool_hook
	// void *buff;
	// function call : void *(*)(void *)
	todo("implement");
	void * __result = _sub_1085FCB0(buff);
	return __result;
}

_extern void *_sub_1085FC40(void *, void *, __int32);
void *havok_memory_init_overflow_pool_hook(void *pool, void *buff, __int32 buff_size) // 0x1085FC40
{
	// `anonymous-namespace'::havok_memory_init_overflow_pool_hook
	// __int32 buff_size;
	// function call : void *(*)(void *, void *, __int32)
	todo("implement");
	void * __result = _sub_1085FC40(pool, buff, buff_size);
	return __result;
}

_extern void _sub_1085F900(CHavokStatsStringOutputHandler *const, real_argb_color const *, char const *);
_inline void CHavokStatsStringOutputHandler::OutputLine(real_argb_color const *color, char const *line) // 0x1085F900
{
	// `anonymous-namespace'::CHavokStatsStringOutputHandler::OutputLine
	// char const *line;
	todo("implement");
	_sub_1085F900(this, color, line);
}

extern std::string _sub_1085F630(CHavokStatsStringOutputHandler const *const);
_inline std::string CHavokStatsStringOutputHandler::GetString() const // 0x1085F630
{
	// `anonymous-namespace'::CHavokStatsStringOutputHandler::GetString
	// CHavokStatsStringOutputHandler const *const this;
	todo("implement");
	std::string __result = _sub_1085F630((CHavokStatsStringOutputHandler const *)this);
	return __result;
}

extern CHavokStatsDisplayOutputHandler* _sub_1085E4F0(CHavokStatsDisplayOutputHandler *const);
_inline CHavokStatsDisplayOutputHandler::CHavokStatsDisplayOutputHandler() // 0x1085E4F0
{
	// `anonymous-namespace'::CHavokStatsDisplayOutputHandler::CHavokStatsDisplayOutputHandler
	// CHavokStatsDisplayOutputHandler *const this;
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_1085E4F0(this);
}

_inline CHavokStatsOutputHandler::CHavokStatsOutputHandler() // 0x1085E5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CHavokStatsOutputHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CHavokStatsOutputHandler::CHavokStatsOutputHandler
	// CHavokStatsOutputHandler *const this;

	compiler_generated();
}

_inline CHavokStatsStringOutputHandler::CHavokStatsStringOutputHandler() // 0x1085E620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CHavokStatsStringOutputHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CHavokStatsStringOutputHandler::CHavokStatsStringOutputHandler
	// CHavokStatsStringOutputHandler *const this;

	compiler_generated();
}

_inline CHavokStatsDisplayOutputHandler::~CHavokStatsDisplayOutputHandler() // 0x1085E6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CHavokStatsDisplayOutputHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CHavokStatsDisplayOutputHandler::~CHavokStatsDisplayOutputHandler
	// CHavokStatsDisplayOutputHandler *const this;

	compiler_generated();
}

_inline CHavokStatsStringOutputHandler::~CHavokStatsStringOutputHandler() // 0x1085E700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CHavokStatsStringOutputHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CHavokStatsStringOutputHandler::~CHavokStatsStringOutputHandler
	// CHavokStatsStringOutputHandler *const this;

	compiler_generated();
}

_extern void _sub_1085F6C0(CHavokStatsDisplayOutputHandler *const, real_argb_color const *, char const *);
_inline void CHavokStatsDisplayOutputHandler::OutputLine(real_argb_color const *color, char const *line) // 0x1085F6C0
{
	// `anonymous-namespace'::CHavokStatsDisplayOutputHandler::OutputLine
	// static ...; // 0x1085F868
	// CHavokStatsDisplayOutputHandler *const this;
	// real_argb_color const *color;
	// char const *line;
	// short_rectangle2d bounds;
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_1085F6C0(this, color, line);
}

_extern __int32 _sub_1085FB20(CHavokStatsOutputHandler *, real_argb_color const *, char const *, ...);
__int32 havok_display_stats_printf_hook(CHavokStatsOutputHandler *output_handler, real_argb_color const *color, char const *format, ...) // 0x1085FB20
{
	// `anonymous-namespace'::havok_display_stats_printf_hook
	// CHavokStatsOutputHandler *output_handler;
	// real_argb_color const *color;
	// char const *format;
	// __int32 n;
	// char buff[8192];
	// char *va;
	// function call : void (real_argb_color const *, char const *)
	todo("implement");
	__int32 __result = _sub_1085FB20(output_handler, color, format);
	return __result;
}

_extern void _sub_1085FD10();
void havok_out_of_memory_hook() // 0x1085FD10
{
	// `anonymous-namespace'::havok_out_of_memory_hook
	// procedure flags: nofpo
	// static ...; // 0x1085FE24
	// static ...; // 0x1085FE18
	// static ...; // 0x1085FE10
	// CHavokStatsStringOutputHandler buff;
	// function call : void (*const)(CHavokStatsOutputHandler *)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	_sub_1085FD10();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<float>(float const) const;

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Modules/ModuleDebug.hpp"
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
		~CHavokStatsStringOutputHandler() = default; /* compiler_generated() */
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
		~CHavokStatsDisplayOutputHandler() = default; /* compiler_generated() */
		CHavokStatsDisplayOutputHandler &operator=(CHavokStatsDisplayOutputHandler &); /* compiler_generated() */
		CHavokStatsDisplayOutputHandler &operator=(CHavokStatsDisplayOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(CHavokStatsDisplayOutputHandler) == 2112, "Invalid CHavokStatsDisplayOutputHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const havok_display_stats = reinterpret_cast<void (*)(CHavokStatsOutputHandler *)>(0x5C4FC0);
	static auto const interface_get_current_display_settings = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
}

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

void ExpandRuntimePool() // 0x1085F150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ExpandRuntimePool@@YAXXZ");

	__int32 additionPages = 0x28A;
	__int32 additionalPageMemorySize = additionPages * 0x2000;
	*(uint32_t *)0x9F775E += additionalPageMemorySize;
	*(uint32_t *)0x9F7764 += additionalPageMemorySize;
	*(uint32_t *)0x9F75CA += additionalPageMemorySize;
	*(uint32_t *)0x9F75D0 += additionalPageMemorySize;
	*(uint32_t *)0x9F7805 += additionalPageMemorySize;
	*(uint32_t *)0x9F6EB4 += additionalPageMemorySize;
	*(uint32_t *)0x9F6EBA += additionalPageMemorySize;
	*(uint32_t *)0x9F6F1C += additionalPageMemorySize;
	*(uint32_t *)0x9F6F41 += additionalPageMemorySize;
	*(uint32_t *)0x9F6F48 += additionalPageMemorySize;
	*(uint32_t *)0x9F6F52 += additionalPageMemorySize;
	*(uint32_t *)0x9F6E89 += additionalPageMemorySize;
	*(uint32_t *)0x9F741A += additionalPageMemorySize;
	*(uint32_t *)0x9F7445 += additionalPageMemorySize;
	*(uint32_t *)0x9F744B += additionalPageMemorySize;
	*(uint32_t *)0x9F748F += additionalPageMemorySize;
	*(uint32_t *)0x9F74AB += additionalPageMemorySize;
	*(uint32_t *)0x9F74B2 += additionalPageMemorySize;
	*(uint32_t *)0x9F74BC += additionalPageMemorySize;
	*(uint32_t *)0x9F6E1A += additionalPageMemorySize;
	*(uint32_t *)0x9F6E4B += additionalPageMemorySize;
	*(uint32_t *)0x9F6E51 += additionalPageMemorySize;
	*(uint32_t *)0x9F6E5F += additionalPageMemorySize;
	*(uint32_t *)0x9F6E69 += additionalPageMemorySize;
	*(uint32_t *)0x9F7379 += additionalPageMemorySize;
	*(uint32_t *)0x9F73A2 += additionalPageMemorySize;
	*(uint32_t *)0x9F73D8 += additionalPageMemorySize;
	*(uint32_t *)0x9F73EF += additionalPageMemorySize;
	*(uint32_t *)0x9F73F9 += additionalPageMemorySize;
	*(uint32_t *)0x9F73AB += additionalPageMemorySize;
	*(uint32_t *)0x9F718D += additionalPageMemorySize;
	*(uint32_t *)0x9F71CA += additionalPageMemorySize;
	*(uint32_t *)0x9F71D0 += additionalPageMemorySize;
	*(uint32_t *)0x9F71E3 += additionalPageMemorySize;
	*(uint32_t *)0x9F724B += additionalPageMemorySize;
	*(uint32_t *)0x9F7252 += additionalPageMemorySize;
	*(uint32_t *)0x9F7283 += additionalPageMemorySize;
	*(uint32_t *)0x9F729C += additionalPageMemorySize;
	*(uint32_t *)0x9F72A2 += additionalPageMemorySize;
	*(uint32_t *)0x9F72C5 += additionalPageMemorySize;
	*(uint32_t *)0x9F72D9 += additionalPageMemorySize;
	*(uint32_t *)0x9F72FC += additionalPageMemorySize;
	*(uint32_t *)0x9F7303 += additionalPageMemorySize;
	*(uint32_t *)0x9F7329 += additionalPageMemorySize;
	*(uint32_t *)0x9F6D85 += additionalPageMemorySize;
	*(uint32_t *)0x9F6D8B += additionalPageMemorySize;
	*(uint32_t *)0x9F6D9F += additionalPageMemorySize;
	*(uint32_t *)0x9F6DA9 += additionalPageMemorySize;
	*(uint32_t *)0x9F6D67 += additionalPageMemorySize;
	*(uint32_t *)0x9F6A06 += additionalPageMemorySize;
	*(uint32_t *)0x9F6A24 += additionalPageMemorySize;
	*(uint32_t *)0x9F6A4F += additionalPageMemorySize;
	*(uint32_t *)0x9F6A59 += additionalPageMemorySize;
	*(uint32_t *)0x9F6A6A += additionalPageMemorySize;
	*(uint32_t *)0x9F76BC += additionalPageMemorySize;
	*(uint32_t *)0x9F76C4 += additionalPageMemorySize;
	*(uint32_t *)0x9F76DB += additionalPageMemorySize;
	*(uint32_t *)0x9F772B += additionalPageMemorySize;
	*(uint32_t *)0x9F71D7 = 0x44C;
	*(uint32_t *)0x9F72B0 = 0x44C;
	*(uint32_t *)0x9F75C4 = 0x44C;
	*(uint32_t *)0x9F75BD = 0x898E10;
	Pointer(0x1690A8C).Write<float>(1100.0f);
}

namespace Patches
{
	namespace HavokMemory
	{
		void ApplyAll() // 0x1085E750
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@HavokMemory@Patches@@YAXXZ");

			Hook(0x35D38B, havok_memory_init_runtime_pool_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35D4D0, havok_memory_init_overflow_pool_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1C5520, havok_display_stats_printf_hook).Apply();
			Hook(0x35C6BA, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35C77A, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35C98E, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35CD92, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35D057, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x35D23A, havok_out_of_memory_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x5F844A, { 0xEB }).Apply();
			ExpandRuntimePool();
		}

		void RenderDebug() // 0x1085F970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RenderDebug@HavokMemory@Patches@@YAXXZ");

			if (!Modules::ModuleDebug::Instance().VarHavokStats->ValueInt)
				return;
			if (((bool(*)())0x5C45BB)())
			{
				CHavokStatsDisplayOutputHandler outputHandler;
				((void(*)(CHavokStatsOutputHandler *))0x5C4FC0)(&outputHandler);
			}
		}
	}
}

/* ---------- private code */

void *havok_memory_init_runtime_pool_hook(void *buff) // 0x1085FCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_memory_init_runtime_pool_hook@@YAPAXPAX@Z");

	return ((void *(__cdecl *)(void *))0x9f7790)(g_runtimePoolMemory);
}

void *havok_memory_init_overflow_pool_hook(void *pool, void *buff, __int32 buff_size) // 0x1085FC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_memory_init_overflow_pool_hook@@YAPAXPAX0H@Z");

	return ((void *(__cdecl *)(void *, void *, __int32))0x9f8480)(pool, (char *)buff - 0x384E10, 0x384E10);
}

_inline void CHavokStatsStringOutputHandler::OutputLine(real_argb_color const *color, char const *line) // 0x1085F900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OutputLine@CHavokStatsStringOutputHandler@hades_file_local@@UAEXPBUreal_argb_color@@PBD@Z");

	m_buffer << line << "\r\n";
}

_inline std::string CHavokStatsStringOutputHandler::GetString() const // 0x1085F630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetString@CHavokStatsStringOutputHandler@hades_file_local@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	return m_buffer.str();
}

_inline CHavokStatsDisplayOutputHandler::CHavokStatsDisplayOutputHandler() // 0x1085E4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CHavokStatsDisplayOutputHandler@hades_file_local@@QAE@XZ");

	m_yOffset = 0;
	eldorado::interface_get_current_display_settings(nullptr, nullptr, nullptr, &m_displayBounds);
}

// mangled_x86(MANGLED_DEFAULT, "??0CHavokStatsOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline CHavokStatsOutputHandler::CHavokStatsOutputHandler() = default; // 0x1085E5F0

// mangled_x86(MANGLED_DEFAULT, "??0CHavokStatsStringOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline CHavokStatsStringOutputHandler::CHavokStatsStringOutputHandler() = default; // 0x1085E620

// mangled_x86(MANGLED_DEFAULT, "??1CHavokStatsDisplayOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
// hades: ~CHavokStatsDisplayOutputHandler() is defaulted in the class (implicit: no vftable store) // 0x1085E6A0

// mangled_x86(MANGLED_DEFAULT, "??1CHavokStatsStringOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
// hades: ~CHavokStatsStringOutputHandler() is defaulted in the class (implicit: no vftable store) // 0x1085E700

_inline void CHavokStatsDisplayOutputHandler::OutputLine(real_argb_color const *color, char const *line) // 0x1085F6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OutputLine@CHavokStatsDisplayOutputHandler@hades_file_local@@UAEXPBUreal_argb_color@@PBD@Z");

	if (!color)
	{ static real_argb_color const white = { 1.0f, 1.0f, 1.0f, 1.0f }; color = &white; } // 0x11191FD8
	short_rectangle2d bounds;
	eldorado::interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
	m_drawString.set_font(0);
	m_drawString.set_justification(0);
	m_drawString.set_color(*color);
	m_drawString.set_shadow_color({ 0.0f, 0.0f, 0.0f, 1.0f });
	bounds.y0 += m_yOffset;
	m_yOffset += m_drawString.get_line_height();
	m_drawString.set_bounds(bounds);
	m_drawString.draw(&m_fontCache, line);
}

__int32 havok_display_stats_printf_hook(CHavokStatsOutputHandler *output_handler, real_argb_color const *color, char const *format, ...) // 0x1085FB20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_display_stats_printf_hook@@YAHPAUCHavokStatsOutputHandler@hades_file_local@@PBUreal_argb_color@@PBDZZ");

	if (output_handler == (CHavokStatsOutputHandler *)1)
		return -1;

	char buff[8192];
	va_list va;

	va_start(va, format);
	__int32 n = vsprintf_s(buff, format, va);
	va_end(va);

	output_handler->OutputLine(color, buff);
	return n;
}

void havok_out_of_memory_hook() // 0x1085FD10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_out_of_memory_hook@@YAXXZ");

	CHavokStatsStringOutputHandler buff;
	eldorado::havok_display_stats(&buff);
	MessageBoxA(nullptr, buff.GetString().c_str(), "Havok out of memory!!!", 0x10);
	__debugbreak();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<float>(float const) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { unsigned char g_runtimePoolMemory[9014800]; }

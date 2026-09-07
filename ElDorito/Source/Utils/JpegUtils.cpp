/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace
{
	struct jpeg_memory_mgr;
	struct jpeg_compress_struct;
	struct jpeg_destination_mgr;
	struct stdvector_destination_mgr;
}

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct jpeg_memory_mgr
	{
		void *(*alloc_small)(void *, __int32, unsigned __int32); // 0x0
		void *(*alloc_large)(void *, __int32, unsigned __int32); // 0x4
	};
	static_assert(sizeof(jpeg_memory_mgr) == 8, "Invalid jpeg_memory_mgr size");

	struct jpeg_compress_struct
	{
		void *err; // 0x0
		jpeg_memory_mgr *mem; // 0x4
		char field_0[16]; // 0x8
		void *dest; // 0x18
		__int32 image_width; // 0x1C
		__int32 image_height; // 0x20
		__int32 input_components; // 0x24
		__int32 in_color_space; // 0x28
		char field_30[164]; // 0x2C
		__int32 next_scanline; // 0xD0
		char field_D4[148]; // 0xD4
	};
	static_assert(sizeof(jpeg_compress_struct) == 360, "Invalid jpeg_compress_struct size");

	struct jpeg_destination_mgr
	{
		unsigned char *next_output_byte; // 0x0
		unsigned __int32 free_in_buffer; // 0x4
		void (*init_destination)(jpeg_compress_struct *); // 0x8
		bool (*empty_output_buffer)(jpeg_compress_struct *); // 0xC
		void (*term_destination)(jpeg_compress_struct *); // 0x10
	};
	static_assert(sizeof(jpeg_destination_mgr) == 20, "Invalid jpeg_destination_mgr size");

	struct stdvector_destination_mgr
	{
		jpeg_destination_mgr pub; // 0x0
		std::vector<unsigned char,std::allocator<unsigned char> > *vec; // 0x14
		stdvector_destination_mgr(); /* compiler_generated() */
	};
	static_assert(sizeof(stdvector_destination_mgr) == 24, "Invalid stdvector_destination_mgr size");
}
/* ---------- prototypes */

namespace Utils
{
	namespace Jpeg
	{
		extern void CompressBuf(std::vector<unsigned char,std::allocator<unsigned char> > &dest, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height);
		extern void CompressFile(std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > destFilename, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Jpeg
	{
		_extern void _sub_10753AD0(std::vector<unsigned char,std::allocator<unsigned char> > &, __int32, unsigned char const *, __int32, __int32);
		void CompressBuf(std::vector<unsigned char,std::allocator<unsigned char> > &dest, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height) // 0x10753AD0
		{
			mangled_x86(MANGLED_TODO, "?CompressBuf@Jpeg@Utils@@YAXAAV?$vector@EV?$allocator@E@std@@@std@@HPBEHH@Z");
			// static ...; // 0x10753DD0
			// static ...; // 0x10753DC8
			// std::vector<unsigned char,std::allocator<unsigned char> > &dest;
			// __int32 quality;
			// unsigned char const *srcBits;
			// __int32 width;
			// __int32 height;
			// unsigned char *row;
			// char err_mgr[132];
			// std::unique_ptr<unsigned char [0],std::default_delete<unsigned char [0]> > row_buf;
			// jpeg_compress_struct cinfo;
			{
				// unsigned char const *src;
				// unsigned char *dest;
				{
					// __int32 i;
				}
			}
			// function call : void *(*const)(void *)
			// function call : __int32 (*const)(void *, __int32, unsigned __int32)
			// function call : void (*const)(void *)
			// function call : void (*const)(void *, __int32, bool)
			// function call : void (*const)(void *, bool)
			// function call : void (*const)(void *, unsigned char const *const *, unsigned __int32)
			// function call : void (*const)(void *)
			// function call : void (*const)(void *)
			todo("implement");
			_sub_10753AD0(dest, quality, srcBits, width, height);
		}

		_extern void _sub_10753EF0(std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> >, __int32, unsigned char const *, __int32, __int32);
		void CompressFile(std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > destFilename, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height) // 0x10753EF0
		{
			mangled_x86(MANGLED_TODO, "?CompressFile@Jpeg@Utils@@YAXV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@HPBEHH@Z");
			// __int32 height;
			todo("implement");
			_sub_10753EF0(destFilename, quality, srcBits, width, height);
		}
	}
}

/* ---------- private code */

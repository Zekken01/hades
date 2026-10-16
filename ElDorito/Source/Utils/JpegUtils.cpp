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

namespace hades_file_local
{
	struct jpeg_memory_mgr;
	struct jpeg_compress_struct;
	struct jpeg_destination_mgr;
	struct stdvector_destination_mgr;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
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
		std::vector<unsigned char> *vec; // 0x14
		stdvector_destination_mgr(); /* compiler_generated() */
	};
	static_assert(sizeof(stdvector_destination_mgr) == 24, "Invalid stdvector_destination_mgr size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const jpeg_CreateCompress = reinterpret_cast<__int32 (*)(void *, __int32, unsigned __int32)>(0xD4C520);
	static auto const jpeg_destroy_compress = reinterpret_cast<void (*)(void *)>(0xD4C5F0);
	static auto const jpeg_finish_compress = reinterpret_cast<void (*)(void *)>(0xD4C680);
	static auto const jpeg_set_defaults = reinterpret_cast<void (*)(void *)>(0xD4D3E0);
	static auto const jpeg_set_quality = reinterpret_cast<void (*)(void *, __int32, bool)>(0xD4CC90);
	static auto const jpeg_start_compress = reinterpret_cast<void (*)(void *, bool)>(0xD4D4E0);
	static auto const jpeg_std_error = reinterpret_cast<void *(*)(void *)>(0xD4C4D0);
	static auto const jpeg_write_scanlines = reinterpret_cast<void (*)(void *, unsigned char const *const *, unsigned __int32)>(0xD4D560);
}
#line 90

namespace Utils
{
	namespace Jpeg
	{
		extern void CompressBuf(std::vector<unsigned char> &dest, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height);
		extern void CompressFile(std::wstring destFilename, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height);
	}
}

void init_stdvector_destination(jpeg_compress_struct *__formal);
bool empty_stdvector_output_buffer(jpeg_compress_struct *cinfo);
void term_stdvector_destination(jpeg_compress_struct *cinfo);
void jpeg_stdvector_dest(jpeg_compress_struct *cinfo, std::vector<unsigned char> &vec);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Jpeg
	{
		void CompressBuf(std::vector<unsigned char> &dest, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height) // 0x10753AD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CompressBuf@Jpeg@Utils@@YAXAAV?$vector@EV?$allocator@E@std@@@std@@HPBEHH@Z");

			char err_mgr[132];
			jpeg_compress_struct cinfo;
			cinfo.err = eldorado::jpeg_std_error(err_mgr);
			eldorado::jpeg_CreateCompress(&cinfo, 62, 360);
			jpeg_stdvector_dest(&cinfo, dest);
			cinfo.image_width = width;
			cinfo.image_height = height;
			cinfo.input_components = 3;
			cinfo.in_color_space = 2;
			eldorado::jpeg_set_defaults(&cinfo);
			eldorado::jpeg_set_quality(&cinfo, quality, true);
			eldorado::jpeg_start_compress(&cinfo, true);
			std::unique_ptr<unsigned char[]> row_buf = std::make_unique<unsigned char[]>(width * 3);
			unsigned char *row = row_buf.get();
			if (!row)
			{
				dest.resize(0);
				return;
			}
			while (cinfo.next_scanline < cinfo.image_height)
			{
				unsigned char const *src = srcBits + cinfo.next_scanline * cinfo.image_width * 4;
				unsigned char *dest = row;
				for (__int32 i = 0; i < width; i++)
				{
					dest[0] = src[2];
					dest[1] = src[1];
					dest[2] = src[0];
					dest += 3;
					src += 4;
				}
				eldorado::jpeg_write_scanlines(&cinfo, &row, 1);
			}
			eldorado::jpeg_finish_compress(&cinfo);
			eldorado::jpeg_destroy_compress(&cinfo);
		}

#line 178
		void CompressFile(std::wstring destFilename, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height) // 0x10753EF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CompressFile@Jpeg@Utils@@YAXV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@HPBEHH@Z");
#line 182

			#line 180 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\JpegUtils.cpp"
			assert(!"not implemented");
			#line 186 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Utils\\JpegUtils.cpp"
		}
	}
}

/* ---------- private code */

void init_stdvector_destination(jpeg_compress_struct *__formal) // 0x10754710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?init_stdvector_destination@@YAXPAUjpeg_compress_struct@hades_file_local@@@Z");
}

bool empty_stdvector_output_buffer(jpeg_compress_struct *cinfo) // 0x10754630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?empty_stdvector_output_buffer@@YA_NPAUjpeg_compress_struct@hades_file_local@@@Z");

	stdvector_destination_mgr *dest = (stdvector_destination_mgr *)cinfo->dest;
	unsigned int currentSize = dest->vec->size();
	dest->vec->resize(2 * currentSize);
	dest->pub.next_output_byte = &dest->vec->data()[currentSize];
	dest->pub.free_in_buffer = currentSize;
	return true;
}

void term_stdvector_destination(jpeg_compress_struct *cinfo) // 0x10754950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?term_stdvector_destination@@YAXPAUjpeg_compress_struct@hades_file_local@@@Z");

	stdvector_destination_mgr *dest = (stdvector_destination_mgr *)cinfo->dest;
	size_t newSize = dest->vec->capacity() - dest->pub.free_in_buffer;
	dest->vec->resize(newSize);
}

void jpeg_stdvector_dest(jpeg_compress_struct *cinfo, std::vector<unsigned char> &vec) // 0x10754730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?jpeg_stdvector_dest@@YAXPAUjpeg_compress_struct@hades_file_local@@AAV?$vector@EV?$allocator@E@std@@@std@@@Z");

	if (cinfo->dest == nullptr)
	{
		cinfo->dest = (*(void *(__cdecl **)(jpeg_compress_struct *, int, unsigned int))cinfo->mem)(cinfo, 0, sizeof(stdvector_destination_mgr));
	}

	stdvector_destination_mgr *dest = (stdvector_destination_mgr *)cinfo->dest;
	*(void (__cdecl **)())((unsigned char *)dest + 0x8) = (void (__cdecl *)())init_stdvector_destination;
	*(void (__cdecl **)())((unsigned char *)dest + 0xc) = (void (__cdecl *)())empty_stdvector_output_buffer;
	*(void (__cdecl **)())((unsigned char *)dest + 0x10) = (void (__cdecl *)())term_stdvector_destination;
	dest->vec = &vec;
	dest->vec->resize(0x1000);
	*(unsigned char **)dest = dest->vec->data();
	*(unsigned int *)((unsigned char *)dest + 0x4) = dest->vec->size();
}

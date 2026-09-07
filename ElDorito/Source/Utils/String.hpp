#ifndef __UTILS_STRING_HPP__
#define __UTILS_STRING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace String
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > Base64Encode(unsigned char const *bytes_to_encode, unsigned __int32 in_len);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > Base64Decode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &encoded_string);
		extern unsigned __int32 calcDecodeLength(char const *b64input);
		extern __int32 Base64DecodeBinary(char *b64message, unsigned char *buffer, unsigned __int32 *length);
		extern void RemoveCharsFromString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, char *charsToRemove);
		extern void HexStringToBytes(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &in, void *const data, unsigned __int32 length);
		extern void BytesToHexString(void const *data, unsigned __int32 const dataLength, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest);
		extern void ReplaceCharacters(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, char find, char replaceWith);
		extern bool ReplaceString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &replace, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &with);
		extern std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > WidenString(std::basic_string_view<char,std::char_traits<char> > string);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > ThinString(std::basic_string_view<wchar_t,std::char_traits<wchar_t> > wide_string);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > ToLower(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > TitleCase(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str);
		extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > SplitString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &stringToSplit, char delim);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > &TrimInline(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &string);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > Trim(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string, bool fromEnd);
		extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Wrap(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string, unsigned __int32 lineLength);

		extern _inline unsigned __int32 GetLineFromOffset(std::basic_string_view<char,std::char_traits<char> > source, unsigned __int32 offset);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	namespace String
	{
		_extern unsigned __int32 _sub_107464B0(std::basic_string_view<char,std::char_traits<char> >, unsigned __int32);
		_inline unsigned __int32 GetLineFromOffset(std::basic_string_view<char,std::char_traits<char> > source, unsigned __int32 offset) // 0x107464B0
		{
			mangled_x86(MANGLED_TODO, "?GetLineFromOffset@String@Utils@@YAIV?$basic_string_view@DU?$char_traits@D@std@@@std@@I@Z");
			// unsigned __int32 offset;
			// unsigned __int32 lineNumber;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			unsigned __int32 __result = _sub_107464B0(source, offset);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __UTILS_STRING_HPP__

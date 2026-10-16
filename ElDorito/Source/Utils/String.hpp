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
		extern std::string Base64Encode(unsigned char const *bytes_to_encode, unsigned __int32 in_len);
		extern std::string Base64Decode(std::string const &encoded_string);
		extern unsigned __int32 calcDecodeLength(char const *b64input);
		extern __int32 Base64DecodeBinary(char *b64message, unsigned char *buffer, unsigned __int32 *length);
		extern void RemoveCharsFromString(std::string &str, char *charsToRemove);
		extern void HexStringToBytes(std::string const &in, void *const data, unsigned __int32 length);
		extern void BytesToHexString(void const *data, unsigned __int32 const dataLength, std::string &dest);
		extern void ReplaceCharacters(std::string &str, char find, char replaceWith);
		extern bool ReplaceString(std::string &str, std::string const &replace, std::string const &with);
		extern std::wstring WidenString(std::string_view string);
		extern std::string ThinString(std::wstring_view wide_string);
		extern std::string ToLower(std::string const &str);
		extern std::string TitleCase(std::string const &str);
		extern std::vector<std::string> SplitString(std::string const &stringToSplit, char delim);
		extern std::string &TrimInline(std::string &string);
		extern std::string Trim(std::string const &string, bool fromEnd);
		extern std::vector<std::string> Wrap(std::string const &string, unsigned __int32 lineLength);

		extern _inline unsigned __int32 GetLineFromOffset(std::string_view source, unsigned __int32 offset);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	namespace String
	{
		inline unsigned __int32 GetLineFromOffset(std::string_view source, unsigned __int32 offset) // 0x107464B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLineFromOffset@String@Utils@@YAIV?$basic_string_view@DU?$char_traits@D@std@@@std@@I@Z");

			unsigned __int32 lineNumber = 1;
			for (unsigned __int32 i = 0; i < source.length() && i < offset; i++)
			{
				if (source[i] == '\n')
					lineNumber++;
			}
			return lineNumber;
		}
	}
}

namespace Utils
{
	namespace String
	{
		template<typename t_char> void StrzCopy(t_char *dest, int dest_size, t_char const *src) // 0x10A8C420
		{

			(void)((!!(src)) || (_wassert(L"src", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\String.hpp", 44), 0));  // hades: the original pushes the line as a constant
			int i = 0;
			if (src)
			{
				while (i < dest_size - 1 && *src)
					dest[i++] = *src++;
			}
			memset(&dest[i], 0, (dest_size - i) * sizeof(t_char));
		}
	}
}

/* ---------- private code */

#endif // __UTILS_STRING_HPP__

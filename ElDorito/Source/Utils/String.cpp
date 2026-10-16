/* ---------- headers */

#include "Utils/String.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <Windows.h>
#include <boost/range/detail/implementation_help.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iomanip>
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
#include <string_view>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

typedef void bio_info_cb(bio_st *, __int32, char const *, __int32, long, long);

/* ---------- prototypes */

namespace Utils { namespace String { _inline bool is_base64(unsigned char c); } }  // hades: added for 0x10C5D900  // hades: added for 0x10C5D900

namespace Utils { namespace String { _inline std::string &ltrim(std::string &s); _inline std::string &rtrim(std::string &s); } }  // hades: added for 0x10C5F4A0  // hades: added for 0x10C5F4A0

namespace Utils
{
	namespace String
	{
		extern std::string Base64Encode(unsigned char const *bytes_to_encode, unsigned __int32 in_len);
		std::string &trim(std::string &s);  // hades: added for 0x10C5F630
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
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace Utils
{
	namespace String
	{
		std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // 0x1247EC68
	}
}

/* ---------- public code */


namespace Utils
{
	namespace String
	{
		std::string Base64Encode(unsigned char const *bytes_to_encode, unsigned __int32 in_len) // 0x10C5DF30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Base64Encode@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBEI@Z");

			std::string ret;
			__int32 i = 0;
			__int32 j = 0;
			unsigned char char_array_3[3];
			unsigned char char_array_4[4];
			while (in_len--)
			{
				char_array_3[i++] = *(bytes_to_encode++);
				if (i == 3)
				{
					char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
					char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
					char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
					char_array_4[3] = char_array_3[2] & 0x3f;
					for (i = 0; i < 4; i++)
						ret += ((std::string const &)base64_chars)[char_array_4[i]];
					i = 0;
				}
			}
			if (i)
			{
				for (j = i; j < 3; j++)
					char_array_3[j] = '\0';
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;
				for (j = 0; j < i + 1; j++)
					ret += ((std::string const &)base64_chars)[char_array_4[j]];
				while (i++ < 3)
					ret += '=';
			}
			return ret;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string Base64Decode(std::string const &encoded_string) // 0x10C5D900
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Base64Decode@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");

			__int32 in_len = encoded_string.size();
			__int32 i = 0;
			__int32 j = 0;
			__int32 in_ = 0;
			unsigned char char_array_4[4], char_array_3[3];
			std::string ret;
			while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
			{
				char_array_4[i++] = encoded_string[in_];
				in_++;
				if (i == 4)
				{
					for (i = 0; i < 4; i++)
						char_array_4[i] = ((std::string const &)base64_chars)[base64_chars.find(char_array_4[i])];
					char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
					char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
					char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
					for (i = 0; i < 3; i++)
						ret += char_array_3[i];
					i = 0;
				}
			}
			if (i)
			{
				for (j = i; j < 4; j++)
					char_array_4[j] = 0;
				for (j = 0; j < 4; j++)
					char_array_4[j] = ((std::string const &)base64_chars)[base64_chars.find(char_array_4[j])];
				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
				for (j = 0; j < i - 1; j++)
					ret += char_array_3[j];
			}
			return ret;
		}

		unsigned __int32 calcDecodeLength(char const *b64input) // 0x10C5FE70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?calcDecodeLength@String@Utils@@YAIPBD@Z");

			size_t len = strlen(b64input);
			size_t padding = 0;
			if (b64input[len - 1] == '=' && b64input[len - 2] == '=')
			{
				padding = 2;
			}
			else if (b64input[len - 1] == '=')
			{
				padding = 1;
			}
			return (len * 3) / 4 - padding;
		}

		__int32 Base64DecodeBinary(char *b64message, unsigned char *buffer, unsigned __int32 *length) // 0x10C5DE10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Base64DecodeBinary@String@Utils@@YAHPADPAEPAI@Z");

			int decodeLen = Utils::String::calcDecodeLength(b64message);
			BIO *bio, *b64;

			if (buffer == nullptr)
			{
				*length = decodeLen;
				return 1;
			}

			bio = BIO_new_mem_buf(b64message, -1);
			b64 = BIO_new(BIO_f_base64());
			bio = BIO_push(b64, bio);
			BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
			*length = BIO_read(bio, buffer, strlen(b64message));
			if (*length != decodeLen)
				return 2;

			BIO_free_all(bio);
			return 0;
		}

		void RemoveCharsFromString(std::string &str, char *charsToRemove) // 0x10C5E930
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveCharsFromString@String@Utils@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAD@Z");

			for (unsigned __int32 i = 0, j = strlen(charsToRemove); i < j; i++)
				str.erase(std::remove(str.begin(), str.end(), charsToRemove[i]), str.end());
		}

		void HexStringToBytes(std::string const &in, void *const data, unsigned __int32 length) // 0x10C5E630
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HexStringToBytes@String@Utils@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAXI@Z");

			unsigned char *byteData = (unsigned char *)data;
			if (in.length() < length * 2)
			{
				memset(data, 0, length);
				return;
			}
			std::stringstream hexStringStream;
			hexStringStream >> std::hex;
			for (unsigned __int32 strIndex = 0, dataIndex = 0; strIndex < length * 2; dataIndex++)
			{
				char const tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };
				hexStringStream.clear();
				hexStringStream.str(tmpStr);
				__int32 tmpValue = 0;
				hexStringStream >> tmpValue;
				byteData[dataIndex] = (unsigned char)tmpValue;
			}
		}

		void BytesToHexString(void const *data, unsigned __int32 const dataLength, std::string &dest) // 0x10C5E400
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BytesToHexString@String@Utils@@YAXPBXIAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			unsigned char const *byteData = (unsigned char const *)data;
			std::stringstream hexStringStream;
			hexStringStream << std::hex << std::setfill('0');
			for (unsigned __int32 index = 0; index < dataLength; index++)
				hexStringStream << std::setw(2) << (__int32)byteData[index];
			dest = hexStringStream.str();
		}

		void ReplaceCharacters(std::string &str, char find, char replaceWith) // 0x10C5EB30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReplaceCharacters@String@Utils@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@DD@Z");

			for (unsigned __int32 i = 0; i < str.length(); i++)
			{
				if (str[i] == find)
					str[i] = replaceWith;
			}
		}

		bool ReplaceString(std::string &str, std::string const &replace, std::string const &with) // 0x10C5EBD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReplaceString@String@Utils@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@1@Z");

			unsigned __int32 start_pos = str.find(replace, 0);
			bool found = false;
			while (start_pos != std::string::npos)
			{
				str.replace(start_pos, replace.length(), with);
				start_pos += with.length();
				found = true;
				start_pos = str.find(replace, start_pos);
			}
			return found;
		}
	}
}


namespace Utils
{
	namespace String
	{
#line 371
		std::wstring WidenString(std::string_view string) // 0x10C5F680
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?WidenString@String@Utils@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@V?$basic_string_view@DU?$char_traits@D@std@@@4@@Z");
#line 383

			__int32 const len = (__int32)string.size();
			if (len == 0)
				return L"";
			__int32 n = MultiByteToWideChar(CP_UTF8, 0, string.data(), len, nullptr, 0);
			if (n <= 0)
			{
				#line 380 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\String.cpp"
					assert(false);
					#line 393 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Utils\\String.cpp"
				return L"";
			}
			std::wstring result(n, 0);
			n = MultiByteToWideChar(CP_UTF8, 0, string.data(), len, result.data(), n);
			if (n <= 0)
			{
				#line 388 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\String.cpp"
					assert(false);
					#line 402 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Utils\\String.cpp"
				return L"";
			}
			return result;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string ThinString(std::wstring_view wide_string) // 0x10C5EE80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ThinString@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$basic_string_view@_WU?$char_traits@_W@std@@@4@@Z");
#line 426

			__int32 const len = (__int32)wide_string.size();
			if (len == 0)
				return "";
			__int32 n = WideCharToMultiByte(CP_UTF8, 0, wide_string.data(), len, nullptr, 0, nullptr, nullptr);
			if (n <= 0)
			{
				#line 423 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\String.cpp"
					assert(false);
					#line 436 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Utils\\String.cpp"
				return "";
			}
			std::string result(n, 0);
			n = WideCharToMultiByte(CP_UTF8, 0, wide_string.data(), len, result.data(), n, nullptr, nullptr);
			if (n <= 0)
			{
				#line 431 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Utils\\String.cpp"
					assert(false);
					#line 445 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Utils\\String.cpp"
				return "";
			}
			return result;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string ToLower(std::string const &str) // 0x10C5F300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ToLower@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");

			std::string retValue = str;
			std::transform(retValue.begin(), retValue.end(), retValue.begin(), tolower);
			return retValue;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string TitleCase(std::string const &str) // 0x10C5F140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TitleCase@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");

			std::string retValue = str;
			unsigned __int32 len = str.length();
			for (unsigned __int32 i = 0; i < len; i++)
			{
				if (str[i] == ' ' && i + 1 < len - 1)
					retValue[i + 1] = toupper(str[i + 1]);
			}
			if (len > 1)
				retValue[0] = toupper(retValue[0]);
			return retValue;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::vector<std::string> SplitString(std::string const &stringToSplit, char delim) // 0x10C5EC80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SplitString@String@Utils@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@D@Z");

			std::vector<std::string> retValue;
			std::stringstream ss(stringToSplit);
			std::string item;
			while (std::getline(ss, item, delim))
				retValue.push_back(item);
			return retValue;
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string &TrimInline(std::string &string) // 0x10C5F630
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TrimInline@String@Utils@@YAAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");

			return trim(string);
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::string Trim(std::string const &string, bool fromEnd) // 0x10C5F4A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Trim@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@_N@Z");

			std::string retValue = string;
			if (fromEnd)
			{
				return rtrim(retValue);
			}
			else
			{
				return ltrim(retValue);
			}
		}
	}
}


namespace Utils
{
	namespace String
	{
		std::vector<std::string> Wrap(std::string const &string, unsigned __int32 lineLength) // 0x10C5F940
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Wrap@String@Utils@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@I@Z");

			std::stringstream sstream;
			sstream << string;
			std::vector<std::string> lines;
			while (sstream.good())
			{
				std::string currentLine;
				std::getline(sstream, currentLine);
				lines.push_back(currentLine);
			}
			std::vector<std::string> retValue;
			for (unsigned __int32 i = 0; i < lines.size(); i++)
			{
				std::string currentLine = lines[i];
				while (currentLine.length() > lineLength)
				{
					__int32 wordEnd = lineLength;
					while (wordEnd > 0 && !isspace(currentLine[wordEnd]))
						wordEnd--;
					if (wordEnd <= 0)
						wordEnd = lineLength;
					retValue.push_back(currentLine.substr(0, wordEnd));
					currentLine = currentLine.substr(wordEnd);
				}
				retValue.push_back(currentLine);
			}
			return retValue;
		}
	}
}

/* ---------- private code */

namespace Utils
{
	namespace String
	{
		_inline bool is_base64(unsigned char c) // 0x10C5FF20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?is_base64@String@Utils@@YA_NE@Z");

			return isalnum(c) || c == '+' || c == '/';
		}
	}
}


namespace Utils
{
	namespace String
	{
		_inline std::string &ltrim(std::string &s) // 0x10C5FFB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ltrim@String@Utils@@YAAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");

			boost::algorithm::trim_left(s);
			return s;
		}
	}
}


namespace Utils
{
	namespace String
	{
		_inline std::string &rtrim(std::string &s) // 0x10C60080
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?rtrim@String@Utils@@YAAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");

			boost::algorithm::trim_right(s);
			return s;
		}
	}
}


namespace Utils
{
	namespace String
	{
		_inline std::string &trim(std::string &s) // 0x10C60150
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?trim@String@Utils@@YAAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");

			return ltrim(rtrim(s));
		}
	}
}

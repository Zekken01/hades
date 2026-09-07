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
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace Utils
{
	namespace String
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > base64_chars; // 0x1247EC68
	}
}

/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5DF30(unsigned char const *, unsigned __int32);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Base64Encode(unsigned char const *bytes_to_encode, unsigned __int32 in_len) // 0x10C5DF30
		{
			mangled_x86(MANGLED_TODO, "?Base64Encode@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBEI@Z");
			// static ...; // 0x10C5E2ED
			// static ...; // 0x10C5E2E0
			// static ...; // 0x10C5E2BC
			// static ...; // 0x10C5E2B4
			// unsigned char const *bytes_to_encode;
			// unsigned __int32 in_len;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > ret;
			// __int32 i;
			// __int32 j;
			// unsigned char char_array_4[4];
			// unsigned char char_array_3[3];
			todo("implement");
			std::string __result = _sub_10C5DF30(bytes_to_encode, in_len);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5D900(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Base64Decode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &encoded_string) // 0x10C5D900
		{
			mangled_x86(MANGLED_TODO, "?Base64Decode@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
			// static ...; // 0x10C5DCFD
			// static ...; // 0x10C5DCF0
			// static ...; // 0x10C5DCEC
			// static ...; // 0x10C5DCC8
			// static ...; // 0x10C5DCC0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &encoded_string;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > ret;
			// __int32 i;
			// __int32 j;
			// unsigned char char_array_4[4];
			// __int32 in_;
			// __int32 in_len;
			// unsigned char char_array_3[3];
			todo("implement");
			std::string __result = _sub_10C5D900(encoded_string);
			return __result;
		}

		_extern unsigned __int32 _sub_10C5FE70(char const *);
		unsigned __int32 calcDecodeLength(char const *b64input) // 0x10C5FE70
		{
			mangled_x86(MANGLED_TODO, "?calcDecodeLength@String@Utils@@YAIPBD@Z");
			// char const *b64input;
			// unsigned __int32 padding;
			// unsigned __int32 len;
			todo("implement");
			unsigned __int32 __result = _sub_10C5FE70(b64input);
			return __result;
		}

		_extern __int32 _sub_10C5DE10(char *, unsigned char *, unsigned __int32 *);
		__int32 Base64DecodeBinary(char *b64message, unsigned char *buffer, unsigned __int32 *length) // 0x10C5DE10
		{
			mangled_x86(MANGLED_TODO, "?Base64DecodeBinary@String@Utils@@YAHPADPAEPAI@Z");
			// unsigned __int32 *length;
			// __int32 decodeLen;
			// bio_st *bio;
			// bio_st *b64;
			todo("implement");
			__int32 __result = _sub_10C5DE10(b64message, buffer, length);
			return __result;
		}

		_extern void _sub_10C5E930(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, char *);
		void RemoveCharsFromString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, char *charsToRemove) // 0x10C5E930
		{
			mangled_x86(MANGLED_TODO, "?RemoveCharsFromString@String@Utils@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAD@Z");
			// char *charsToRemove;
			{
				// unsigned __int32 i;
				// unsigned __int32 j;
			}
			todo("implement");
			_sub_10C5E930(str, charsToRemove);
		}

		_extern void _sub_10C5E630(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, void *const, unsigned __int32);
		void HexStringToBytes(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &in, void *const data, unsigned __int32 length) // 0x10C5E630
		{
			mangled_x86(MANGLED_TODO, "?HexStringToBytes@String@Utils@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAXI@Z");
			// static ...; // 0x10C5E86C
			// static ...; // 0x10C5E848
			// static ...; // 0x10C5E840
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &in;
			// void *const data;
			// unsigned __int32 length;
			// unsigned char *byteData;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > hexStringStream;
			{
				// unsigned __int32 dataIndex;
				// unsigned __int32 strIndex;
				{
					// __int32 tmpValue;
					// char const tmpStr[3];
				}
			}
			todo("implement");
			_sub_10C5E630(in, data, length);
		}

		_extern void _sub_10C5E400(void const *, unsigned __int32 const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		void BytesToHexString(void const *data, unsigned __int32 const dataLength, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest) // 0x10C5E400
		{
			mangled_x86(MANGLED_TODO, "?BytesToHexString@String@Utils@@YAXPBXIAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C5E59C
			// void const *data;
			// unsigned __int32 const dataLength;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest;
			// unsigned char const *byteData;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > hexStringStream;
			{
				// unsigned __int32 index;
			}
			todo("implement");
			_sub_10C5E400(data, dataLength, dest);
		}

		_extern void _sub_10C5EB30(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, char, char);
		void ReplaceCharacters(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, char find, char replaceWith) // 0x10C5EB30
		{
			mangled_x86(MANGLED_TODO, "?ReplaceCharacters@String@Utils@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@DD@Z");
			// char replaceWith;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			_sub_10C5EB30(str, find, replaceWith);
		}

		_extern bool _sub_10C5EBD0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool ReplaceString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &str, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &replace, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &with) // 0x10C5EBD0
		{
			mangled_x86(MANGLED_TODO, "?ReplaceString@String@Utils@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@1@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &with;
			// unsigned __int32 start_pos;
			// bool found;
			todo("implement");
			bool __result = _sub_10C5EBD0(str, replace, with);
			return __result;
		}
	}
}

extern std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _sub_10C5F680(std::basic_string_view<char,std::char_traits<char> >);
namespace Utils
{
	namespace String
	{
		std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > WidenString(std::basic_string_view<char,std::char_traits<char> > string) // 0x10C5F680
		{
			mangled_x86(MANGLED_TODO, "?WidenString@String@Utils@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@V?$basic_string_view@DU?$char_traits@D@std@@@4@@Z");
			// static ...; // 0x10C5F8A4
			// static ...; // 0x10C5F898
			// static ...; // 0x10C5F890
			// std::basic_string_view<char,std::char_traits<char> > string;
			// __int32 n;
			// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > result;
			// __int32 const len;
			// function call : __int32 (unsigned __int32, unsigned long, char const *, __int32, wchar_t *, __int32)
			// function call : __int32 (unsigned __int32, unsigned long, char const *, __int32, wchar_t *, __int32)
			todo("implement");
			std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > __result = _sub_10C5F680(string);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5EE80(std::basic_string_view<wchar_t,std::char_traits<wchar_t> >);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ThinString(std::basic_string_view<wchar_t,std::char_traits<wchar_t> > wide_string) // 0x10C5EE80
		{
			mangled_x86(MANGLED_TODO, "?ThinString@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$basic_string_view@_WU?$char_traits@_W@std@@@4@@Z");
			// static ...; // 0x10C5F0AC
			// static ...; // 0x10C5F0A0
			// static ...; // 0x10C5F098
			// std::basic_string_view<wchar_t,std::char_traits<wchar_t> > wide_string;
			// __int32 n;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > result;
			// __int32 const len;
			// function call : __int32 (unsigned __int32, unsigned long, wchar_t const *, __int32, char *, __int32, char const *, __int32 *)
			// function call : __int32 (unsigned __int32, unsigned long, wchar_t const *, __int32, char *, __int32, char const *, __int32 *)
			todo("implement");
			std::string __result = _sub_10C5EE80(wide_string);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5F300(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ToLower(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str) // 0x10C5F300
		{
			mangled_x86(MANGLED_TODO, "?ToLower@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
			// static ...; // 0x10C5F438
			// static ...; // 0x10C5F42C
			// static ...; // 0x10C5F424
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > retValue;
			todo("implement");
			std::string __result = _sub_10C5F300(str);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5F140(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > TitleCase(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str) // 0x10C5F140
		{
			mangled_x86(MANGLED_TODO, "?TitleCase@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
			// static ...; // 0x10C5F29C
			// static ...; // 0x10C5F290
			// static ...; // 0x10C5F288
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > retValue;
			// unsigned __int32 len;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			std::string __result = _sub_10C5F140(str);
			return __result;
		}
	}
}

extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10C5EC80(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, char);
namespace Utils
{
	namespace String
	{
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > SplitString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &stringToSplit, char delim) // 0x10C5EC80
		{
			mangled_x86(MANGLED_TODO, "?SplitString@String@Utils@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@D@Z");
			// static ...; // 0x10C5EE09
			// static ...; // 0x10C5EE04
			// static ...; // 0x10C5EDE0
			// static ...; // 0x10C5EDD8
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &stringToSplit;
			// char delim;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > item;
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > retValue;
			todo("implement");
			std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10C5EC80(stringToSplit, delim);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > &_sub_10C5F630(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > &TrimInline(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &string) // 0x10C5F630
		{
			mangled_x86(MANGLED_TODO, "?TrimInline@String@Utils@@YAAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &string;
			todo("implement");
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > & __result = _sub_10C5F630(string);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C5F4A0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, bool);
namespace Utils
{
	namespace String
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Trim(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string, bool fromEnd) // 0x10C5F4A0
		{
			mangled_x86(MANGLED_TODO, "?Trim@String@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@_N@Z");
			// static ...; // 0x10C5F5C8
			// static ...; // 0x10C5F5C0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string;
			// bool fromEnd;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > retValue;
			todo("implement");
			std::string __result = _sub_10C5F4A0(string, fromEnd);
			return __result;
		}
	}
}

extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10C5F940(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned __int32);
namespace Utils
{
	namespace String
	{
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Wrap(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string, unsigned __int32 lineLength) // 0x10C5F940
		{
			mangled_x86(MANGLED_TODO, "?Wrap@String@Utils@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@I@Z");
			// static ...; // 0x10C5FC9D
			// static ...; // 0x10C5FC91
			// static ...; // 0x10C5FC88
			// static ...; // 0x10C5FC7C
			// static ...; // 0x10C5FC40
			// static ...; // 0x10C5FC38
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &string;
			// unsigned __int32 lineLength;
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > retValue;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > sstream;
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > lines;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > currentLine;
			}
			{
				// unsigned __int32 i;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > currentLine;
					{
						// __int32 wordEnd;
					}
				}
			}
			todo("implement");
			std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10C5F940(string, lineLength);
			return __result;
		}
	}
}

/* ---------- private code */

namespace Utils
{
	namespace String
	{
		_extern bool _sub_10C5FF20(unsigned char);
		_inline bool is_base64(unsigned char c) // 0x10C5FF20
		{
			// Utils::String::is_base64
			// unsigned char c;
			todo("implement");
			bool __result = _sub_10C5FF20(c);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > &_sub_10C5FFB0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
namespace Utils
{
	namespace String
	{
		_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > &ltrim(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s) // 0x10C5FFB0
		{
			// Utils::String::ltrim
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s;
			todo("implement");
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > & __result = _sub_10C5FFB0(s);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > &_sub_10C60080(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
namespace Utils
{
	namespace String
	{
		_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > &rtrim(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s) // 0x10C60080
		{
			// Utils::String::rtrim
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s;
			todo("implement");
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > & __result = _sub_10C60080(s);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > &_sub_10C60150(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
namespace Utils
{
	namespace String
	{
		_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > &trim(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s) // 0x10C60150
		{
			// Utils::String::trim
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &s;
			todo("implement");
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > & __result = _sub_10C60150(s);
			return __result;
		}
	}
}

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

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

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

typedef __int32 pem_password_cb(char *, __int32, __int32, void *);

/* ---------- prototypes */

namespace Utils
{
	namespace Cryptography
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > ReformatKey(bool isPrivateKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > key);
		extern bool PrivateEncrypt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted);
		extern bool PublicEncrypt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > publicKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetEncryptedTimestamp(std::basic_string<char,std::char_traits<char>,std::allocator<char> > unformattedkey, bool isPrivate);
		extern bool CreateRSASignature(std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &signature);
		extern bool VerifyRSASignature(std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > signature, void *data, unsigned __int32 dataSize);
		extern bool GenerateRSAKeyPair(__int32 numBits, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &privKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &pubKey);
		extern bool Hash32(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned __int32 *out);
		extern bool RandomBytes(__int32 num, unsigned char *out);
		extern bool RandomString(__int32 length, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &chars, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out);
		extern bool RandomPassword(__int32 length, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out);

		__int32 genrsa_cb(__int32 p, __int32 n, bn_gencb_st *cb);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace Utils
{
	namespace Cryptography
	{
		extern char const *const PasswordChars; // 0x111BA740
	}
}

/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C550A0(bool, std::string);
namespace Utils
{
	namespace Cryptography
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ReformatKey(bool isPrivateKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > key) // 0x10C550A0
		{
			mangled_x86(MANGLED_TODO, "?ReformatKey@Cryptography@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_NV34@@Z");
			// static ...; // 0x10C552FF
			// static ...; // 0x10C552FC
			// static ...; // 0x10C552D8
			// static ...; // 0x10C552D0
			// bool isPrivateKey;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > key;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > returnKey;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
			// unsigned __int32 pos;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > keyType;
			{
				// __int32 toCopy;
			}
			todo("implement");
			std::string __result = _sub_10C550A0(isPrivateKey, key);
			return __result;
		}

		_extern bool _sub_10C54830(std::string, void *, unsigned __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool PrivateEncrypt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted) // 0x10C54830
		{
			mangled_x86(MANGLED_TODO, "?PrivateEncrypt@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted;
			// bio_st *privKeyBuff;
			// rsa_st *rsa;
			// unsigned char buf[4098];
			// __int32 retVal;
			todo("implement");
			bool __result = _sub_10C54830(privateKey, data, dataSize, encrypted);
			return __result;
		}

		_extern bool _sub_10C54AC0(std::string, void *, unsigned __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool PublicEncrypt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > publicKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted) // 0x10C54AC0
		{
			mangled_x86(MANGLED_TODO, "?PublicEncrypt@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > publicKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &encrypted;
			// bio_st *pubKeyBuff;
			// rsa_st *rsa;
			// unsigned char buf[4098];
			// __int32 retVal;
			todo("implement");
			bool __result = _sub_10C54AC0(publicKey, data, dataSize, encrypted);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C54460(std::string, bool);
namespace Utils
{
	namespace Cryptography
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetEncryptedTimestamp(std::basic_string<char,std::char_traits<char>,std::allocator<char> > unformattedkey, bool isPrivate) // 0x10C54460
		{
			mangled_x86(MANGLED_TODO, "?GetEncryptedTimestamp@Cryptography@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@_N@Z");
			// static ...; // 0x10C54600
			// static ...; // 0x10C545FC
			// static ...; // 0x10C545D8
			// static ...; // 0x10C545D0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > unformattedkey;
			// bool isPrivate;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > encryptedString;
			// char buf[42];
			// tm *now_tm;
			// long long now;
			todo("implement");
			std::string __result = _sub_10C54460(unformattedkey, isPrivate);
			return __result;
		}

		_extern bool _sub_10C53EA0(std::string, void *, unsigned __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool CreateRSASignature(std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey, void *data, unsigned __int32 dataSize, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &signature) // 0x10C53EA0
		{
			mangled_x86(MANGLED_TODO, "?CreateRSASignature@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// static ...; // 0x10C540E4
			// static ...; // 0x10C540DC
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > privateKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &signature;
			// unsigned __int32 siglen;
			// void *sigret;
			// bio_st *privKeyBuff;
			// rsa_st *rsa;
			// unsigned char hash[32];
			// __int32 retVal;
			// SHA256state_st sha;
			todo("implement");
			bool __result = _sub_10C53EA0(privateKey, data, dataSize, signature);
			return __result;
		}

		_extern bool _sub_10C553B0(std::string, std::string, void *, unsigned __int32);
		bool VerifyRSASignature(std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > signature, void *data, unsigned __int32 dataSize) // 0x10C553B0
		{
			mangled_x86(MANGLED_TODO, "?VerifyRSASignature@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAXI@Z");
			// static ...; // 0x10C55684
			// static ...; // 0x10C5567C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > signature;
			// void *data;
			// unsigned __int32 dataSize;
			// unsigned char *sigBuf;
			// unsigned __int32 length;
			// bio_st *pubKeyBuff;
			// rsa_st *rsa;
			// unsigned char hash[32];
			// __int32 retVal;
			// SHA256state_st sha;
			todo("implement");
			bool __result = _sub_10C553B0(pubKey, signature, data, dataSize);
			return __result;
		}

		_extern bool _sub_10C541C0(__int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool GenerateRSAKeyPair(__int32 numBits, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &privKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &pubKey) // 0x10C541C0
		{
			mangled_x86(MANGLED_TODO, "?GenerateRSAKeyPair@Cryptography@Utils@@YA_NHAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// static ...; // 0x10C543C0
			// static ...; // 0x10C5439C
			// static ...; // 0x10C54394
			// __int32 numBits;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &privKey;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &pubKey;
			// bio_st *bio_err;
			// bio_st *pubKeyBuff;
			// bio_st *privKeyBuff;
			// char *privKeyData;
			// rsa_st *rsa;
			// bn_gencb_st cb;
			// char *pubKeyData;
			// long privKeySize;
			// long pubKeySize;
			// bignum_st *bn;
			{
				// bn_gencb_st *tmp_gencb;
			}
			todo("implement");
			bool __result = _sub_10C541C0(numBits, privKey, pubKey);
			return __result;
		}

		_extern bool _sub_10C54690(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned __int32 *);
		bool Hash32(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned __int32 *out) // 0x10C54690
		{
			mangled_x86(MANGLED_TODO, "?Hash32@Cryptography@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAI@Z");
			// static ...; // 0x10C547C8
			// static ...; // 0x10C547B0
			// static ...; // 0x10C547A8
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
			// unsigned __int32 *out;
			// unsigned char digest[20];
			// SHAstate_st context;
			todo("implement");
			bool __result = _sub_10C54690(str, out);
			return __result;
		}

		_extern bool _sub_10C54D70(__int32, unsigned char *);
		bool RandomBytes(__int32 num, unsigned char *out) // 0x10C54D70
		{
			mangled_x86(MANGLED_TODO, "?RandomBytes@Cryptography@Utils@@YA_NHPAE@Z");
			// unsigned char *out;
			// unsigned long provider;
			// function call : __int32 (unsigned long, unsigned long, unsigned char *)
			todo("implement");
			bool __result = _sub_10C54D70(num, out);
			return __result;
		}

		_extern bool _sub_10C54EF0(__int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool RandomString(__int32 length, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &chars, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out) // 0x10C54EF0
		{
			mangled_x86(MANGLED_TODO, "?RandomString@Cryptography@Utils@@YA_NHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
			// static ...; // 0x10C5502C
			// __int32 length;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &chars;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out;
			// std::unique_ptr<unsigned char [0],std::default_delete<unsigned char [0]> > bytes;
			{
				// __int32 i;
				{
					// unsigned __int32 charIndex;
				}
			}
			todo("implement");
			bool __result = _sub_10C54EF0(length, chars, out);
			return __result;
		}

		_extern bool _sub_10C54E10(__int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool RandomPassword(__int32 length, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out) // 0x10C54E10
		{
			mangled_x86(MANGLED_TODO, "?RandomPassword@Cryptography@Utils@@YA_NHAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &out;
			todo("implement");
			bool __result = _sub_10C54E10(length, out);
			return __result;
		}
	}
}

/* ---------- private code */

namespace Utils
{
	namespace Cryptography
	{
		_extern __int32 _sub_10C55780(__int32, __int32, bn_gencb_st *);
		__int32 genrsa_cb(__int32 p, __int32 n, bn_gencb_st *cb) // 0x10C55780
		{
			// Utils::Cryptography::genrsa_cb
			// static ...; // 0x10C5581C
			// __int32 p;
			// __int32 n;
			// bn_gencb_st *cb;
			// char c;
			todo("implement");
			__int32 __result = _sub_10C55780(p, n, cb);
			return __result;
		}
	}
}

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <openssl/rsa.h>  // hades: added for 0x10C541C0, 0x10C54830  // hades: added for 0x10C53EA0
#include <openssl/pem.h>  // hades: added for 0x10C541C0, 0x10C54830  // hades: added for 0x10C53EA0

#include <openssl/rsa.h>  // hades: added for 0x10C541C0, 0x10C54830  // hades: added for 0x10C541C0
#include <openssl/pem.h>  // hades: added for 0x10C541C0, 0x10C54830  // hades: added for 0x10C541C0

#include <openssl/sha.h>  // hades: added for 0x10C54690  // hades: added for 0x10C54690

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
		extern std::string ReformatKey(bool isPrivateKey, std::string key);
		extern bool PrivateEncrypt(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &encrypted);
		extern bool PublicEncrypt(std::string publicKey, void *data, unsigned __int32 dataSize, std::string &encrypted);
		extern std::string GetEncryptedTimestamp(std::string unformattedkey, bool isPrivate);
		extern bool CreateRSASignature(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &signature);
		extern bool VerifyRSASignature(std::string pubKey, std::string signature, void *data, unsigned __int32 dataSize);
		extern bool GenerateRSAKeyPair(__int32 numBits, std::string &privKey, std::string &pubKey);
		extern bool Hash32(std::string const &str, unsigned __int32 *out);
		extern bool RandomBytes(__int32 num, unsigned char *out);
		extern bool RandomString(__int32 length, std::string const &chars, std::string &out);
		extern bool RandomPassword(__int32 length, std::string &out);

		__int32 genrsa_cb(__int32 p, __int32 n, bn_gencb_st *cb);
	}
}

unsigned long AcquireProvider();

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


namespace Utils
{
	namespace Cryptography
	{
		std::string ReformatKey(bool isPrivateKey, std::string key) // 0x10C550A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReformatKey@Cryptography@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_NV34@@Z");
			// static ...; // 0x10C552FF
			// static ...; // 0x10C552FC
			// static ...; // 0x10C552D8
			// static ...; // 0x10C552D0
			// bool isPrivateKey;
			// std::string key;
			// std::string returnKey;
			// std::stringstream ss;
			// unsigned __int32 pos;
			// std::string keyType;
				// __int32 toCopy;

			unsigned __int32 pos = 0;
			std::string returnKey;
			while (pos < key.length())
			{
				__int32 toCopy = key.length() - pos;
				if (toCopy > 64)
					toCopy = 64;
				returnKey += key.substr(pos, toCopy);
				returnKey += "\n";
				pos += toCopy;
			}
			std::string keyType = isPrivateKey ? "RSA PRIVATE KEY" : "PUBLIC KEY";
			std::stringstream ss;
			ss << "-----BEGIN " << keyType << "-----\n" << returnKey << "-----END " << keyType << "-----\n";
			return ss.str();
		}

		bool PrivateEncrypt(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &encrypted) // 0x10C54830
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PrivateEncrypt@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// std::string privateKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::string &encrypted;
			// bio_st *privKeyBuff;
			// rsa_st *rsa;
			// unsigned char buf[4098];
			// __int32 retVal;

			bio_st *privKeyBuff = BIO_new_mem_buf(privateKey.c_str(), privateKey.length());
			if (!privKeyBuff)
				return false;
			rsa_st *rsa = PEM_read_bio_RSAPrivateKey(privKeyBuff, nullptr, nullptr, nullptr);
			if (!rsa)
				return false;
			unsigned char buf[4098];
			memset(buf, 0, sizeof(buf));
			__int32 retVal = RSA_private_encrypt(dataSize, (unsigned char *)data, buf, rsa, RSA_PKCS1_PADDING);
			RSA_free(rsa);
			BIO_free_all(privKeyBuff);
			if (retVal == -1)
				return false;
			encrypted = Utils::String::Base64Encode(buf, retVal);
			return true;
		}

		bool PublicEncrypt(std::string publicKey, void *data, unsigned __int32 dataSize, std::string &encrypted) // 0x10C54AC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PublicEncrypt@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// std::string publicKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::string &encrypted;
			// bio_st *pubKeyBuff;
			// rsa_st *rsa;
			// unsigned char buf[4098];
			// __int32 retVal;

			bio_st *pubKeyBuff = BIO_new_mem_buf(publicKey.c_str(), publicKey.length());
			if (!pubKeyBuff)
			{
				BIO_free(pubKeyBuff);
				return false;
			}
			rsa_st *rsa = PEM_read_bio_RSA_PUBKEY(pubKeyBuff, nullptr, nullptr, nullptr);
			if (!rsa)
			{
				RSA_free(rsa);
				return false;
			}
			unsigned char buf[4098];
			memset(buf, 0, sizeof(buf));
			__int32 retVal = RSA_public_encrypt(dataSize, (unsigned char *)data, buf, rsa, RSA_PKCS1_PADDING);
			RSA_free(rsa);
			BIO_free_all(pubKeyBuff);
			if (retVal == -1)
				return false;
			encrypted = Utils::String::Base64Encode(buf, retVal);
			return true;
		}
	}
}


namespace Utils
{
	namespace Cryptography
	{
		std::string GetEncryptedTimestamp(std::string unformattedkey, bool isPrivate) // 0x10C54460
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetEncryptedTimestamp@Cryptography@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@_N@Z");
			// static ...; // 0x10C54600
			// static ...; // 0x10C545FC
			// static ...; // 0x10C545D8
			// static ...; // 0x10C545D0
			// std::string unformattedkey;
			// bool isPrivate;
			// std::string encryptedString;
			// char buf[42];
			// tm *now_tm;
			// long long now;

			std::string encryptedString;
			long long now = time(nullptr);
			tm *now_tm = gmtime(&now);
			char buf[42];
			strftime(buf, 42, "%Y%m%d %X", now_tm);
			PublicEncrypt(ReformatKey(isPrivate, unformattedkey), buf, strlen(buf), encryptedString);
			return encryptedString;
		}

		bool CreateRSASignature(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &signature) // 0x10C53EA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CreateRSASignature@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAXIAAV34@@Z");
			// static ...; // 0x10C540E4
			// static ...; // 0x10C540DC
			// std::string privateKey;
			// void *data;
			// unsigned __int32 dataSize;
			// std::string &signature;
			// unsigned __int32 siglen;
			// void *sigret;
			// bio_st *privKeyBuff;
			// rsa_st *rsa;
			// unsigned char hash[32];
			// __int32 retVal;
			// SHA256state_st sha;

			bio_st *privKeyBuff = BIO_new_mem_buf(privateKey.c_str(), privateKey.length());
			if (!privKeyBuff)
				return false;
			rsa_st *rsa = PEM_read_bio_RSAPrivateKey(privKeyBuff, nullptr, nullptr, nullptr);
			if (!rsa)
				return false;
			unsigned char hash[32];
			SHA256state_st sha;
			SHA256_Init(&sha);
			SHA256_Update(&sha, data, dataSize);
			SHA256_Final(hash, &sha);
			void *sigret = malloc(RSA_size(rsa));
			unsigned __int32 siglen = 0;
			__int32 retVal = RSA_sign(NID_sha256, hash, sizeof(hash), (unsigned char *)sigret, &siglen, rsa);
			RSA_free(rsa);
			BIO_free_all(privKeyBuff);
			if (retVal != 1)
				return false;
			signature = Utils::String::Base64Encode((unsigned char *)sigret, siglen);
			return true;
		}

		bool VerifyRSASignature(std::string pubKey, std::string signature, void *data, unsigned __int32 dataSize) // 0x10C553B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?VerifyRSASignature@Cryptography@Utils@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0PAXI@Z");
			// static ...; // 0x10C55684
			// static ...; // 0x10C5567C
			// std::string pubKey;
			// std::string signature;
			// void *data;
			// unsigned __int32 dataSize;
			// unsigned char *sigBuf;
			// unsigned __int32 length;
			// bio_st *pubKeyBuff;
			// rsa_st *rsa;
			// unsigned char hash[32];
			// __int32 retVal;
			// SHA256state_st sha;

			bio_st *pubKeyBuff = BIO_new_mem_buf(pubKey.c_str(), pubKey.length());
			if (!pubKeyBuff)
				return false;
			rsa_st *rsa = PEM_read_bio_RSA_PUBKEY(pubKeyBuff, nullptr, nullptr, nullptr);
			if (!rsa)
				return false;
			unsigned char hash[32];
			SHA256state_st sha;
			SHA256_Init(&sha);
			SHA256_Update(&sha, data, dataSize);
			SHA256_Final(hash, &sha);
			unsigned __int32 length = 0;
			if (Utils::String::Base64DecodeBinary((char *)signature.c_str(), nullptr, &length) != 1 || length == 0)
				return false;
			unsigned char *sigBuf = (unsigned char *)malloc(length);
			if (Utils::String::Base64DecodeBinary((char *)signature.c_str(), sigBuf, &length))
				return false;
			__int32 retVal = RSA_verify(NID_sha256, hash, sizeof(hash), sigBuf, length, rsa);
			free(sigBuf);
			RSA_free(rsa);
			BIO_free_all(pubKeyBuff);
			return retVal == 1;
		}

		bool GenerateRSAKeyPair(__int32 numBits, std::string &privKey, std::string &pubKey) // 0x10C541C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateRSAKeyPair@Cryptography@Utils@@YA_NHAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// static ...; // 0x10C543C0
			// static ...; // 0x10C5439C
			// static ...; // 0x10C54394
			// __int32 numBits;
			// std::string &privKey;
			// std::string &pubKey;
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
				// bn_gencb_st *tmp_gencb;

			rsa_st *rsa = RSA_new();
			bignum_st *bn = BN_new();
			bn_gencb_st cb;
			bio_st *bio_err = nullptr;
			BN_GENCB_set(&cb, genrsa_cb, bio_err);
			BN_set_word(bn, RSA_F4);
			RSA_generate_key_ex(rsa, numBits, bn, &cb);
			bio_st *privKeyBuff = BIO_new(BIO_s_mem());
			bio_st *pubKeyBuff = BIO_new(BIO_s_mem());
			PEM_write_bio_RSAPrivateKey(privKeyBuff, rsa, nullptr, nullptr, 0, nullptr, nullptr);
			PEM_write_bio_RSA_PUBKEY(pubKeyBuff, rsa);
			char *privKeyData;
			char *pubKeyData;
			long privKeySize = BIO_get_mem_data(privKeyBuff, &privKeyData);
			long pubKeySize = BIO_get_mem_data(pubKeyBuff, &pubKeyData);
			privKey = std::string(privKeyData, privKeySize);
			pubKey = std::string(pubKeyData, pubKeySize);
			BIO_free_all(privKeyBuff);
			BIO_free_all(pubKeyBuff);
			BN_free(bn);
			RSA_free(rsa);
			return true;
		}

		bool Hash32(std::string const &str, unsigned __int32 *out) // 0x10C54690
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Hash32@Cryptography@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAI@Z");
			// static ...; // 0x10C547C8
			// static ...; // 0x10C547B0
			// static ...; // 0x10C547A8
			// std::string const &str;
			// unsigned __int32 *out;
			// unsigned char digest[20];
			// SHAstate_st context;

			unsigned char digest[20];
			SHA_CTX context;
			if (!SHA1_Init(&context))
				return false;
			if (!SHA1_Update(&context, str.c_str(), str.length()))
				return false;
			if (!SHA1_Final(digest, &context))
				return false;
			*out = digest[0] << 24 | digest[1] << 16 | digest[2] << 8 | digest[3];
			return true;
		}

		bool RandomBytes(__int32 num, unsigned char *out) // 0x10C54D70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RandomBytes@Cryptography@Utils@@YA_NHPAE@Z");
			// unsigned char *out;
			// unsigned long provider;
			// function call : __int32 (unsigned long, unsigned long, unsigned char *)

			HCRYPTPROV provider = AcquireProvider();
			if (!provider)
				return false;
			return CryptGenRandom(provider, num, out) == TRUE;
		}

		bool RandomString(__int32 length, std::string const &chars, std::string &out) // 0x10C54EF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RandomString@Cryptography@Utils@@YA_NHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
			// static ...; // 0x10C5502C
			// __int32 length;
			// std::string const &chars;
			// std::string &out;
			// std::unique_ptr<unsigned char [0]> bytes;
				// __int32 i;
					// unsigned __int32 charIndex;

			std::unique_ptr<unsigned char []> bytes = std::make_unique<unsigned char []>(length);
			if (!RandomBytes(length, &bytes[0]))
				return false;
			out.reserve(length);
			for (__int32 i = 0; i < length; i++)
			{
				unsigned __int32 charIndex = bytes[i] * chars.length() >> 8;
				out += chars[charIndex];
			}
			return true;
		}

		bool RandomPassword(__int32 length, std::string &out) // 0x10C54E10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RandomPassword@Cryptography@Utils@@YA_NHAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string &out;

			return RandomString(length, PasswordChars, out);
		}
	}
}

/* ---------- private code */

namespace Utils
{
	namespace Cryptography
	{
		__int32 genrsa_cb(__int32 p, __int32 n, bn_gencb_st *cb) // 0x10C55780
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?genrsa_cb@Cryptography@Utils@@YAHHHPAUbn_gencb_st@@@Z");
			// Utils::Cryptography::genrsa_cb
			// static ...; // 0x10C5581C
			// __int32 p;
			// __int32 n;
			// bn_gencb_st *cb;
			// char c;

			char c = '*';

			if (p == 0)
				c = '.';
			if (p == 1)
				c = '+';
			if (p == 2)
				c = '*';
			if (p == 3)
				c = '\n';
			BIO_write((BIO*)cb->arg, &c, 1);
			(void)BIO_flush((BIO*)cb->arg);

			return 1;
		}
	}
}

unsigned long AcquireProvider() // 0x10C53E20
{
	// `anonymous-namespace'::AcquireProvider
	// procedure flags: nofpo
	// static unsigned long `AcquireProvider'::`2'::handle; // 0x1247EC64
	// function call : __int32 (unsigned long *, char const *, char const *, unsigned long, unsigned long)

	static HCRYPTPROV handle;
	if (handle || CryptAcquireContextA(&handle, nullptr, nullptr, 1, 0xF0000040))
	{
		return handle;
	}

	return 0;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Utils { namespace Cryptography { char const *const PasswordChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*"; } }

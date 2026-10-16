/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomizationExtension.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
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

struct s_player_configuration;
namespace Blam
{
	class BitStream;
}
namespace Modules
{
	class ModulePlayer;
}
namespace hades_file_local
{
	class UidExtension;
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
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Network {}
	using namespace Patches::Network;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class UidExtension :
		public Patches::Network::PlayerPropertiesExtension<unsigned __int64>
	{
	protected:
		virtual void BuildData(__int32, unsigned long long *);
		virtual void ApplyData(__int32, s_player_configuration *, unsigned long long const &);
		virtual void Serialize(Blam::BitStream *, unsigned long long const &);
		virtual void Deserialize(Blam::BitStream *, unsigned long long *);
	public:
		UidExtension(UidExtension &); /* compiler_generated() */
		UidExtension(UidExtension const &); /* compiler_generated() */
		UidExtension() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~UidExtension() = default; /* compiler_generated() */
		UidExtension &operator=(UidExtension &); /* compiler_generated() */
		UidExtension &operator=(UidExtension const &); /* compiler_generated() */
	};
	static_assert(sizeof(UidExtension) == 4, "Invalid UidExtension size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Utils { namespace Cryptography { std::string ReformatKey(bool isPrivateKey, std::string key); } }  // hades: added for 0x10AB49F0  // hades: added for 0x10AB49F0

namespace Utils::Cryptography { bool GenerateRSAKeyPair(__int32 numBits, std::string &privKey, std::string &pubKey); }  // hades: added for 0x10AB42D0

namespace Patches
{
	namespace PlayerUid
	{
		extern void ApplyAll();
		extern unsigned long long Get();
		extern std::string GetFormattedPrivKey();
		extern bool ParseUid(std::string const &str, unsigned long long *out);
	}
}

void EnsureValidUid();
unsigned long long GetPlayerUidHook(__int32 unused);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	Pointer UidValidPtr = Pointer::Base(0x15AB728); // 0x12467320
	extern "C" { Pointer UidPtr = Pointer::Base(0x15AB730); } // 0x12467324
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace PlayerUid
	{
		void ApplyAll() // 0x10AB3CF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@PlayerUid@Patches@@YAXXZ");

			Hook(0x67E005, GetPlayerUidHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x67D810, { 0x30, 0xC0, 0xC3 }).Apply();
			Patches::Network::PlayerPropertiesExtender::Instance().Add(std::make_shared<UidExtension>());
		}

		unsigned long long Get() // 0x10AB4960
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Get@PlayerUid@Patches@@YA_KXZ");

			EnsureValidUid();
			return UidPtr.Read<unsigned long long>();
		}
	}
}


namespace Patches
{
	namespace PlayerUid
	{
		std::string GetFormattedPrivKey() // 0x10AB49F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFormattedPrivKey@PlayerUid@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

			EnsureValidUid();
			return Utils::Cryptography::ReformatKey(true, Modules::ModulePlayer::Instance().VarPlayerPrivKey->ValueString);
		}

		bool ParseUid(std::string const &str, unsigned long long *out) // 0x10AB4AE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseUid@PlayerUid@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PA_K@Z");

			try
			{
				unsigned __int32 end;
				*out = std::stoull(str, &end, 16);
				return end == str.length();
			}
			catch (...)
			{
				return false;
			}
		}
	}
}

/* ---------- private code */

_inline void UidExtension::BuildData(__int32 playerIndex, unsigned long long *out) // 0x10AB4190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildData@UidExtension@hades_file_local@@MAEXHPA_K@Z");

	*out = Patches::PlayerUid::Get();
}

_inline void UidExtension::ApplyData(__int32 playerIndex, s_player_configuration *properties, unsigned long long const &data) // 0x10AB40D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyData@UidExtension@hades_file_local@@MAEXHPAUs_player_configuration@@AB_K@Z");

	properties->host.player_uid = data;
}

_inline void UidExtension::Serialize(Blam::BitStream *stream, unsigned long long const &data) // 0x10AB4CC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@UidExtension@hades_file_local@@MAEXPAVBitStream@Blam@@AB_K@Z");

	stream->WriteUnsigned<unsigned long long>(data, 64);
}

_inline void UidExtension::Deserialize(Blam::BitStream *stream, unsigned long long *out) // 0x10AB4270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@UidExtension@hades_file_local@@MAEXPAVBitStream@Blam@@PA_K@Z");

	*out = stream->ReadUnsigned<unsigned __int64>(64);
}

// mangled_x86(MANGLED_DEFAULT, "??0UidExtension@hades_file_local@@QAE@XZ"); no body to assert in
// _inline UidExtension::UidExtension() = default; // 0x10AB39F0  // hades: defaulted on its declaration


void EnsureValidUid() // 0x10AB42D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnsureValidUid@@YAXXZ");

	if (UidValidPtr.Read<bool>())
		return;
	Modules::ModulePlayer &playerVars = Modules::ModulePlayer::Instance();
	std::string pubKey = playerVars.VarPlayerPubKey->ValueString;
	unsigned long long uid;
	if (pubKey.length() <= 0)
	{
		Console::WriteLine("Generating player keypair, this may take a moment...");
		std::string privKey;
		Utils::Cryptography::GenerateRSAKeyPair(4096, privKey, pubKey);
		Utils::String::ReplaceString(privKey, "\n", "");
		Utils::String::ReplaceString(privKey, "-----BEGIN RSA PRIVATE KEY-----", "");
		Utils::String::ReplaceString(privKey, "-----END RSA PRIVATE KEY-----", "");
		Utils::String::ReplaceString(pubKey, "\n", "");
		Utils::String::ReplaceString(pubKey, "-----BEGIN PUBLIC KEY-----", "");
		Utils::String::ReplaceString(pubKey, "-----END PUBLIC KEY-----", "");
		Modules::CommandMap::Instance().SetVariable(playerVars.VarPlayerPrivKey, privKey, true);
		Modules::CommandMap::Instance().SetVariable(playerVars.VarPlayerPubKey, pubKey, true);
		Console::WriteLine("Done!");
		Modules::CommandMap::Instance().ExecuteCommand("WriteConfig");
	}
	unsigned char hash[32];
	SHA256state_st sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, pubKey.c_str(), pubKey.length());
	SHA256_Final(hash, &sha256);
	memcpy(&uid, hash, sizeof(uid));
	UidPtr.WriteFast<unsigned long long>(uid);
	UidValidPtr.Write<bool>(true);
}

unsigned long long GetPlayerUidHook(__int32 unused) // 0x10AB4AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerUidHook@@YA_KH@Z");

	return Patches::PlayerUid::Get();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template unsigned __int32 Patches::Network::PlayerPropertiesExtension<unsigned __int64>::GetDataSize() const;
template unsigned long long Blam::BitStream::ReadUnsigned<unsigned __int64>(__int32);
template void Patches::Network::PlayerPropertiesExtension<unsigned __int64>::ApplyData(__int32, s_player_configuration *, void const *);
template void Patches::Network::PlayerPropertiesExtension<unsigned __int64>::BuildData(__int32, void *);
template void Patches::Network::PlayerPropertiesExtension<unsigned __int64>::Deserialize(Blam::BitStream *, void *);
template void Patches::Network::PlayerPropertiesExtension<unsigned __int64>::Serialize(Blam::BitStream *, void const *);
template void Pointer::WriteFast<unsigned __int64>(unsigned long long const) const;

/* ---------- explicit instantiations */
template unsigned long long & Pointer::Read<unsigned __int64>() const;
template Patches::Network::PlayerPropertiesExtension<unsigned __int64>::PlayerPropertiesExtension();

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
		UidExtension(); /* compiler_generated() */
		virtual ~UidExtension(); /* compiler_generated() */
		UidExtension &operator=(UidExtension &); /* compiler_generated() */
		UidExtension &operator=(UidExtension const &); /* compiler_generated() */
	};
	static_assert(sizeof(UidExtension) == 4, "Invalid UidExtension size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace PlayerUid
	{
		extern void ApplyAll();
		extern unsigned long long Get();
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetFormattedPrivKey();
		extern bool ParseUid(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned long long *out);
	}
}

void EnsureValidUid();
unsigned long long GetPlayerUidHook(__int32 unused);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern Pointer UidValidPtr; // 0x12467320
	extern Pointer UidPtr; // 0x12467324
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace PlayerUid
	{
		_extern void _sub_10AB3CF0();
		void ApplyAll() // 0x10AB3CF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@PlayerUid@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AB3CF0();
		}

		_extern unsigned long long _sub_10AB4960();
		unsigned long long Get() // 0x10AB4960
		{
			mangled_x86(MANGLED_TODO, "?Get@PlayerUid@Patches@@YA_KXZ");
			// procedure flags: nofpo
			todo("implement");
			unsigned long long __result = _sub_10AB4960();
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10AB49F0();
namespace Patches
{
	namespace PlayerUid
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetFormattedPrivKey() // 0x10AB49F0
		{
			mangled_x86(MANGLED_TODO, "?GetFormattedPrivKey@PlayerUid@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10AB49F0();
			return __result;
		}

		_extern bool _sub_10AB4AE0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned long long *);
		bool ParseUid(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned long long *out) // 0x10AB4AE0
		{
			mangled_x86(MANGLED_TODO, "?ParseUid@PlayerUid@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PA_K@Z");
			// static ...; // 0x10AB4BE4
			// static ...; // 0x10AB4BDC
		// $LN9:
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
			// unsigned long long *out;
			{
				// unsigned __int32 end;
			}
			todo("implement");
			bool __result = _sub_10AB4AE0(str, out);
			return __result;
		}
	}
}

/* ---------- private code */

_extern void _sub_10AB4190(UidExtension *const, __int32, unsigned long long *);
_inline void UidExtension::BuildData(__int32 playerIndex, unsigned long long *out) // 0x10AB4190
{
	// `anonymous-namespace'::UidExtension::BuildData
	// unsigned long long *out;
	todo("implement");
	_sub_10AB4190(this, playerIndex, out);
}

_extern void _sub_10AB40D0(UidExtension *const, __int32, s_player_configuration *, unsigned long long const &);
_inline void UidExtension::ApplyData(__int32 playerIndex, s_player_configuration *properties, unsigned long long const &data) // 0x10AB40D0
{
	// `anonymous-namespace'::UidExtension::ApplyData
	// unsigned long long const &data;
	todo("implement");
	_sub_10AB40D0(this, playerIndex, properties, data);
}

_extern void _sub_10AB4CC0(UidExtension *const, Blam::BitStream *, unsigned long long const &);
_inline void UidExtension::Serialize(Blam::BitStream *stream, unsigned long long const &data) // 0x10AB4CC0
{
	// `anonymous-namespace'::UidExtension::Serialize
	// unsigned long long const &data;
	todo("implement");
	_sub_10AB4CC0(this, stream, data);
}

_extern void _sub_10AB4270(UidExtension *const, Blam::BitStream *, unsigned long long *);
_inline void UidExtension::Deserialize(Blam::BitStream *stream, unsigned long long *out) // 0x10AB4270
{
	// `anonymous-namespace'::UidExtension::Deserialize
	// unsigned long long *out;
	todo("implement");
	_sub_10AB4270(this, stream, out);
}

extern UidExtension* _sub_10AB39F0(UidExtension *const);
_inline UidExtension::UidExtension() // 0x10AB39F0
{
	// `anonymous-namespace'::UidExtension::UidExtension
	// UidExtension *const this;
	compiler_generated();
	todo("implement");
	_sub_10AB39F0(this);
}

_extern void _sub_10AB3B50(UidExtension *const);
_inline UidExtension::~UidExtension() // 0x10AB3B50
{
	// `anonymous-namespace'::UidExtension::~UidExtension
	// UidExtension *const this;
	compiler_generated();
	todo("implement");
	_sub_10AB3B50(this);
}

_extern void _sub_10AB42D0();
void EnsureValidUid() // 0x10AB42D0
{
	// `anonymous-namespace'::EnsureValidUid
	// procedure flags: nofpo
	// static ...; // 0x10AB4804
	// static ...; // 0x10AB4800
	// static ...; // 0x10AB47F8
	// static ...; // 0x10AB47F3
	// static ...; // 0x10AB47EC
	// static ...; // 0x10AB47B0
	// static ...; // 0x10AB47A8
	// Modules::ModulePlayer &playerVars;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey;
	// unsigned long long uid;
	// SHA256state_st sha256;
	// unsigned char hash[32];
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > privKey;
	}
	todo("implement");
	_sub_10AB42D0();
}

_extern unsigned long long _sub_10AB4AA0(__int32);
unsigned long long GetPlayerUidHook(__int32 unused) // 0x10AB4AA0
{
	// `anonymous-namespace'::GetPlayerUidHook
	// __int32 unused;
	todo("implement");
	unsigned long long __result = _sub_10AB4AA0(unused);
	return __result;
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

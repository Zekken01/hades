/* ---------- headers */

#include "Player/PlayerServiceRecord.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "ElDorito.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
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
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;
class c_network_session;
struct s_network_session_player;
namespace Player
{
	namespace ServiceRecord
	{
		struct PlayerTopMedals;
		struct ServiceRecord;
		struct ServiceRecordPlayer;
	}
}
namespace Utils
{
	class DewritoReader;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace ServiceRecord {}
	using namespace Player::ServiceRecord;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void GetServiceRecordEndpoint();
bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex);
std::wstring processNumber(__int32 num);
void clearCachedServiceRecords();

/* ---------- globals */

namespace Utils
{
	Utils::DewritoReader *Utils::Singleton<Utils::DewritoReader>::m_instance; // 0x113861C4
}

/* ---------- private variables */

namespace hades_file_local
{
	extern ::Player::ServiceRecord::ServiceRecord ServiceRecords[16]; // 0x113861C8
	extern ::Player::ServiceRecord::ServiceRecordPlayer currentDesiredRecord; // 0x11387948
	extern bool threadActive; // 0x11387994
	extern std::string serviceRecordEndpoint; // 0x11387978
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	namespace ServiceRecord
	{
		_extern unsigned long _sub_106C73A0(void *);
		unsigned long __stdcall GetServiceRecord_Thread(void *lpParam) // 0x106C73A0
		{
			mangled_x86(MANGLED_TODO, "?GetServiceRecord_Thread@ServiceRecord@Player@@YGKPAX@Z");
			// static ...; // 0x106C8AFF
			// static ...; // 0x106C8AFD
			// static ...; // 0x106C8AF6
			// static ...; // 0x106C8AF2
			// static ...; // 0x106C8AEE
			// static ...; // 0x106C8AE7
			// static ...; // 0x106C8ADC
			// static ...; // 0x106C8AD3
			// static ...; // 0x106C8ACE
			// static ...; // 0x106C8AC9
			// static ...; // 0x106C8AC5
			// static ...; // 0x106C8ABA
			// static ...; // 0x106C8AB4
			// static ...; // 0x106C8A18
			// static ...; // 0x106C8A10
		// $LN64:
			// void *lpParam;
			// char uid[17];
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// Player::ServiceRecord::ServiceRecord record;
			// HttpRequest req;
			// Player::ServiceRecord::ServiceRecordPlayer playerRecord;
			{
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::string sendObject;
				// std::wstring expected;
				// std::string resp;
				{
					// __int32 id;
				}
				{
					// char const *name;
				}
				{
					// unsigned long long uid;
					// char const *uid_str;
				}
				{
					// __int32 exp;
				}
				{
					// __int32 skill;
				}
				{
					// __int32 total_games;
				}
				{
					// __int32 total_wins;
				}
				{
					// __int32 total_kills;
				}
				{
					// __int32 total_deaths;
				}
				{
					// __int32 total_medals;
				}
				{
					// __int32 best_streak;
				}
				{
					// __int32 ranked_matches;
				}
				{
					// __int32 social_matches;
				}
				{
					// __int32 custom_games;
				}
				{
					// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > top_medals;
					{
						// __int32 x;
						{
							// Player::ServiceRecord::PlayerTopMedals medal;
						}
					}
				}
			}
			todo("implement");
			unsigned long __result = _sub_106C73A0(lpParam);
			return __result;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerTopMedals@ServiceRecord@Player@@QAE@ABU012@@Z"); no body to assert in
		_inline PlayerTopMedals::PlayerTopMedals(::Player::ServiceRecord::PlayerTopMedals const &__that) = default; // 0x106C5D30

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerTopMedals@ServiceRecord@Player@@QAE@XZ"); no body to assert in
		_inline PlayerTopMedals::PlayerTopMedals() = default; // 0x106C5DC0

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecord@0Player@@QAE@ABU001@@Z"); no body to assert in
		_inline ServiceRecord::ServiceRecord(::Player::ServiceRecord::ServiceRecord const &__that) = default; // 0x106C5E40

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecord@0Player@@QAE@XZ"); no body to assert in
		_inline ServiceRecord::ServiceRecord() = default; // 0x106C6000

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecordPlayer@ServiceRecord@Player@@QAE@XZ"); no body to assert in
		_inline ServiceRecordPlayer::ServiceRecordPlayer() = default; // 0x106C6170
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1HttpRequest@@QAE@XZ"); no body to assert in
_inline HttpRequest::~HttpRequest() = default; // 0x106C63A0

namespace Player
{
	namespace ServiceRecord
	{
		// mangled_x86(MANGLED_DEFAULT, "??1PlayerTopMedals@ServiceRecord@Player@@QAE@XZ"); no body to assert in
		_inline PlayerTopMedals::~PlayerTopMedals() = default; // 0x106C6410

		// mangled_x86(MANGLED_DEFAULT, "??1ServiceRecord@0Player@@QAE@XZ"); no body to assert in
		_inline ServiceRecord::~ServiceRecord() = default; // 0x106C6460

		// mangled_x86(MANGLED_DEFAULT, "??4PlayerTopMedals@ServiceRecord@Player@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		_inline ::Player::ServiceRecord::PlayerTopMedals &PlayerTopMedals::operator=(::Player::ServiceRecord::PlayerTopMedals &&__that) = default; // 0x106C6610

		// mangled_x86(MANGLED_DEFAULT, "??4PlayerTopMedals@ServiceRecord@Player@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline ::Player::ServiceRecord::PlayerTopMedals &PlayerTopMedals::operator=(::Player::ServiceRecord::PlayerTopMedals const &__that) = default; // 0x106C6690

		// mangled_x86(MANGLED_DEFAULT, "??4ServiceRecord@0Player@@QAEAAU001@$$QAU001@@Z"); no body to assert in
		_inline ::Player::ServiceRecord::ServiceRecord &ServiceRecord::operator=(::Player::ServiceRecord::ServiceRecord &&__that) = default; // 0x106C6710

		// mangled_x86(MANGLED_DEFAULT, "??4ServiceRecord@0Player@@QAEAAU001@ABU001@@Z"); no body to assert in
		_inline ::Player::ServiceRecord::ServiceRecord &ServiceRecord::operator=(::Player::ServiceRecord::ServiceRecord const &__that) = default; // 0x106C6890

		extern ServiceRecord _sub_106CA2C0(__int32);
		::Player::ServiceRecord::ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex) // 0x106CA2C0
		{
			mangled_x86(MANGLED_TODO, "?getCachedServiceRecord@ServiceRecord@Player@@YA?AU112@H@Z");
			// __int32 networkPlayerIndex;
			todo("implement");
			::Player::ServiceRecord::ServiceRecord __result = _sub_106CA2C0(networkPlayerIndex);
			return __result;
		}

		void clearCache() // 0x106CA000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?clearCache@ServiceRecord@Player@@YAXXZ");
			// procedure flags: nofpo

			clearCachedServiceRecords();
		}

		_extern void _sub_106CAB50(__int32);
		void requestPlayerServiceRecord(__int32 networkPlayerIndex) // 0x106CAB50
		{
			mangled_x86(MANGLED_TODO, "?requestPlayerServiceRecord@ServiceRecord@Player@@YAXH@Z");
			// static ...; // 0x106CAD27
			// static ...; // 0x106CAD20
			// static ...; // 0x106CAD08
			// static ...; // 0x106CAD00
			// __int32 networkPlayerIndex;
			// s_network_session_player *networkPlayer;
			// c_network_session *session;
			{
				// Player::ServiceRecord::ServiceRecordPlayer player;
				// void *thread;
			}
			// function call : bool (*const)(c_network_session **)
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
			todo("implement");
			_sub_106CAB50(networkPlayerIndex);
		}
	}
}

/* ---------- private code */

_extern void _sub_106C7200();
void GetServiceRecordEndpoint() // 0x106C7200
{
	// `anonymous-namespace'::GetServiceRecordEndpoint
	// procedure flags: nofpo
	// static ...; // 0x106C733C
	// static ...; // 0x106C7330
	// static ...; // 0x106C7328
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
	{
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;
	}
	todo("implement");
	_sub_106C7200();
}

bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex) // 0x106C9A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ValidNetworkPlayerIndex@@YA_NH@Z");
	// `anonymous-namespace'::ValidNetworkPlayerIndex
	// __int32 networkPlayerIndex;

	return networkPlayerIndex >= 0 && networkPlayerIndex < 16;
}

extern std::wstring _sub_106CA7E0(__int32);
std::wstring processNumber(__int32 num) // 0x106CA7E0
{
	// `anonymous-namespace'::processNumber
	// static ...; // 0x106CAA18
	// static ...; // 0x106CAA0C
	// static ...; // 0x106CAA04
	// __int32 num;
	// std::ostringstream oss;
	{
		// double numInK;
	}
	{
		// double numInM;
	}
	todo("implement");
	std::wstring __result = _sub_106CA7E0(num);
	return __result;
}

_extern void _sub_106CA040();
void clearCachedServiceRecords() // 0x106CA040
{
	// `anonymous-namespace'::clearCachedServiceRecords
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	_sub_106CA040();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Utils::DewritoReader & Utils::Singleton<Utils::DewritoReader>::Instance();

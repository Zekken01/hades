/* ---------- headers */

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
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_player_datum;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	namespace PlayerNetworkUtil
	{
		extern s_player_datum *get_player_from_session_index(__int32 player_session_index);
		extern long get_player_datum_index_from_session_index(__int32 player_session_index);
		extern long get_session_player_index_from_player_datum_index(long player_datum_index);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_player_datum *_sub_106D7FD0(__int32);
namespace Player
{
	namespace PlayerNetworkUtil
	{
		s_player_datum *get_player_from_session_index(__int32 player_session_index) // 0x106D7FD0
		{
			mangled_x86(MANGLED_TODO, "?get_player_from_session_index@PlayerNetworkUtil@Player@@YAPAUs_player_datum@@H@Z");
			// static ...; // 0x106D80F1
			// static ...; // 0x106D80E8
			// static ...; // 0x106D80D0
			// static ...; // 0x106D80C8
			// __int32 player_session_index;
			// Blam::Network::Session *session;
			{
				// __int32 peer_index;
				{
					// c_data_array<s_player_datum> &<range>$L0;
					// c_data_iterator<s_player_datum> <begin>$L0;
					// c_data_iterator<s_player_datum> <end>$L0;
					{
						// s_player_datum &player;
					}
				}
			}
			todo("implement");
			s_player_datum * __result = _sub_106D7FD0(player_session_index);
			return __result;
		}

		_extern long _sub_106D7E80(__int32);
		long get_player_datum_index_from_session_index(__int32 player_session_index) // 0x106D7E80
		{
			mangled_x86(MANGLED_TODO, "?get_player_datum_index_from_session_index@PlayerNetworkUtil@Player@@YAJH@Z");
			// static ...; // 0x106D7F84
			// static ...; // 0x106D7F78
			// static ...; // 0x106D7F70
			// __int32 player_session_index;
			// Blam::Network::Session *session;
			{
				// c_data_array<s_player_datum> *players;
				// __int32 peer_index;
				{
					// c_data_iterator<s_player_datum> it;
				}
			}
			todo("implement");
			long __result = _sub_106D7E80(player_session_index);
			return __result;
		}

		long get_session_player_index_from_player_datum_index(long player_datum_index) // 0x106D8150
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_player_index_from_player_datum_index@PlayerNetworkUtil@Player@@YAJJ@Z");
			// long player_datum_index;
			// Blam::Network::Session *session;
				// s_player_datum *player;

			if (player_datum_index == -1)
				return -1;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				s_player_datum *player = player_get(player_datum_index);
				if (player)
					return session->MembershipInfo.GetPeerPlayer(player->machine_index);
			}
			return -1;
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_player_datum & c_data_iterator<s_player_datum>::operator*();

/* ---------- headers */

#include "Server/Voting/VotingJson.hpp"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Server/Voting/VotingUtil.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/en.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
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
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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

struct begin;
struct end;
namespace Server
{
	namespace Voting
	{
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct PlaylistItem;
		struct SMapListItem;
		struct VotingJson;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern bool LoadVotingJson(std::string const &filename, Server::Voting::VotingJson &voting);
		extern bool LoadPlaylistItem(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::PlaylistItem &item, std::vector<Server::Voting::HaloType> const &types);
		extern bool LoadHaloMap(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject, std::string const &modPack, Server::Voting::HaloMap &map);
		extern bool LoadHaloType(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::HaloType &ht);

		unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x11388C30
			extern std::string const DefaultTypeNames[8]; // 0x11388D10
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_extern bool _sub_10747C00(std::string const &, Server::Voting::VotingJson &);
		bool LoadVotingJson(std::string const &filename, Server::Voting::VotingJson &voting) // 0x10747C00
		{
			mangled_x86(MANGLED_TODO, "?LoadVotingJson@Voting@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUVotingJson@12@@Z");
			// static ...; // 0x107483F0
			// static ...; // 0x107483E7
			// static ...; // 0x107483E3
			// static ...; // 0x107483DB
			// static ...; // 0x107483D6
			// static ...; // 0x107483D3
			// static ...; // 0x107483CE
			// static ...; // 0x107483C9
			// static ...; // 0x107483C0
			// static ...; // 0x10748348
			// static ...; // 0x10748340
			// std::string const &filename;
			// Server::Voting::VotingJson &voting;
			// std::ifstream in;
			// std::string contents;
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
			{
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L0;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject;
					{
						// Server::Voting::HaloMap haloMap;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L1;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L1;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L1;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &typeObject;
					{
						// Server::Voting::HaloType ht;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L2;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L2;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L2;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &itemObject;
					{
						// Server::Voting::PlaylistItem item;
					}
				}
			}
			{
				// std::string errorMsg;
			}
			todo("implement");
			bool __result = _sub_10747C00(filename, voting);
			return __result;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline PlaylistItem::PlaylistItem(Server::Voting::PlaylistItem &&__that) = default; // 0x107459E0

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline PlaylistItem::PlaylistItem(Server::Voting::PlaylistItem const &__that) = default; // 0x10745AE0

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@XZ"); no body to assert in
		_inline PlaylistItem::PlaylistItem() = default; // 0x10745BF0

		// mangled_x86(MANGLED_DEFAULT, "??0SMapListItem@Voting@Server@@QAE@XZ"); no body to assert in
		_inline SMapListItem::SMapListItem() = default; // 0x10745CB0

		// mangled_x86(MANGLED_DEFAULT, "??1SMapListItem@Voting@Server@@QAE@XZ"); no body to assert in
		_inline SMapListItem::~SMapListItem() = default; // 0x10745DE0

		// mangled_x86(MANGLED_DEFAULT, "??4CharacterOverride@HaloType@Voting@Server@@QAEAAU0123@$$QAU0123@@Z"); no body to assert in
		_inline Server::Voting::HaloType::CharacterOverride &HaloType::CharacterOverride::operator=(Server::Voting::HaloType::CharacterOverride &&__that) = default; // 0x10745E40

		_extern bool _sub_107477D0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, Server::Voting::PlaylistItem &, std::vector<Server::Voting::HaloType> const &);
		bool LoadPlaylistItem(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::PlaylistItem &item, std::vector<Server::Voting::HaloType> const &types) // 0x107477D0
		{
			mangled_x86(MANGLED_TODO, "?LoadPlaylistItem@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@AAUPlaylistItem@12@ABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@@Z");
			// static ...; // 0x10747B0D
			// static ...; // 0x10747B04
			// static ...; // 0x10747AD4
			// static ...; // 0x10747ACC
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c;
			// Server::Voting::PlaylistItem &item;
			// std::vector<Server::Voting::HaloType> const &types;
			// std::string modPack;
			{
				// std::string errorMsg;
			}
			{
				// unsigned __int32 typeIndex;
			}
			{
				// Server::Voting::HaloType ht;
			}
			{
			}
			todo("implement");
			bool __result = _sub_107477D0(c, item, types);
			return __result;
		}

		_extern bool _sub_10746890(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string const &, Server::Voting::HaloMap &);
		bool LoadHaloMap(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject, std::string const &modPack, Server::Voting::HaloMap &map) // 0x10746890
		{
			mangled_x86(MANGLED_TODO, "?LoadHaloMap@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUHaloMap@12@@Z");
			// static ...; // 0x10746C34
			// static ...; // 0x10746C2C
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject;
			// std::string const &modPack;
			// Server::Voting::HaloMap &map;
			// std::string displayName;
			// Server::Voting::SMapListItem mapInfo;
			todo("implement");
			bool __result = _sub_10746890(mapObject, modPack, map);
			return __result;
		}

		_extern bool _sub_10746D60(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, Server::Voting::HaloType &);
		bool LoadHaloType(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::HaloType &ht) // 0x10746D60
		{
			mangled_x86(MANGLED_TODO, "?LoadHaloType@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@AAUHaloType@12@@Z");
			// static ...; // 0x107475A2
			// static ...; // 0x1074759D
			// static ...; // 0x1074759A
			// static ...; // 0x10747595
			// static ...; // 0x10747590
			// static ...; // 0x10747584
			// static ...; // 0x10747530
			// static ...; // 0x10747528
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c;
			// Server::Voting::HaloType &ht;
			// std::string typeDisplayName;
			// Server::Voting::AllowedPlayerCount playerCount;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &commands;
				{
					// unsigned __int32 i;
				}
			}
			{
				{
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &smaps;
				{
					{
						// Server::Voting::HaloMap haloMap;
					}
				}
			}
			{
				// rapidjson::GenericObject<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &overridesArr;
				{
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
					{
						// rapidjson::GenericArray<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &overrideObj;
						// std::string const &teamDesignator;
					}
				}
			}
			todo("implement");
			bool __result = _sub_10746D60(c, ht);
			return __result;
		}
	}
}

/* ---------- private code */

namespace Server
{
	namespace Voting
	{
		_extern unsigned __int32 _sub_10746060(std::vector<Server::Voting::HaloType> const &, std::string const &);
		unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name) // 0x10746060
		{
			// Server::Voting::FindTypeByName
			// std::string const &name;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			unsigned __int32 __result = _sub_10746060(types, name);
			return __result;
		}
	}
}

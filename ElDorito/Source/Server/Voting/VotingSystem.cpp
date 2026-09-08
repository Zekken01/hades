/* ---------- headers */

#include "Server/Voting/VotingSystem.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Server/Voting/AbstractVotingSystem.hpp"
#include "Server/Voting/VotingJson.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
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
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <random>
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
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
		class VotingSystem;
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
		struct SMapListItem;
		struct VotingJson;
		struct VotingMessage;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

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
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern double getRandom(double fMin, double fMax);
		extern __int32 getVotesNeededToInstantSkip();
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
			extern std::string const DefaultTypes[8]; // 0x1246B710
			extern std::string const DefaultTypeNames[8]; // 0x1246B7F0
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		extern VotingSystem* _sub_10C4D570(Server::Voting::VotingSystem *const);
		VotingSystem::VotingSystem() // 0x10C4D570
		{
			mangled_x86(MANGLED_TODO, "??0VotingSystem@Voting@Server@@QAE@XZ");
			// Server::Voting::VotingSystem *const this;
			todo("implement");
			_sub_10C4D570(this);
		}

		void VotingSystem::Init() // 0x10C4EBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
		}

		_extern bool _sub_10C51440(Server::Voting::VotingSystem *const);
		bool VotingSystem::isEnabled() // 0x10C51440
		{
			mangled_x86(MANGLED_TODO, "?isEnabled@VotingSystem@Voting@Server@@UAE_NXZ");
			// Server::Voting::VotingSystem *const this;
			todo("implement");
			bool __result = _sub_10C51440(this);
			return __result;
		}

		_extern void _sub_10C4F230(Server::Voting::VotingSystem *const);
		void VotingSystem::Reset() // 0x10C4F230
		{
			mangled_x86(MANGLED_TODO, "?Reset@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
			todo("implement");
			_sub_10C4F230(this);
		}

		_extern void _sub_10C4F1B0(Server::Voting::VotingSystem *const);
		void VotingSystem::NewVote() // 0x10C4F1B0
		{
			mangled_x86(MANGLED_TODO, "?NewVote@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10C4F1B0(this);
		}

		_extern void _sub_10C4DAB0(Server::Voting::VotingSystem *const);
		void VotingSystem::EndVote() // 0x10C4DAB0
		{
			mangled_x86(MANGLED_TODO, "?EndVote@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4DB44
			// static ...; // 0x10C4DB38
			// static ...; // 0x10C4DB30
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			todo("implement");
			_sub_10C4DAB0(this);
		}

		_extern void _sub_10C4EE90(Server::Voting::VotingSystem *const, Server::Voting::VotingMessage const &, std::string);
		void VotingSystem::LogVote(Server::Voting::VotingMessage const &message, std::string name) // 0x10C4EE90
		{
			mangled_x86(MANGLED_TODO, "?LogVote@VotingSystem@Voting@Server@@UAEXABUVotingMessage@23@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C4F0E8
			// static ...; // 0x10C4F0E0
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage const &message;
			// std::string name;
			// unsigned __int32 vote;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > it;
			// function call : void ()
			todo("implement");
			_sub_10C4EE90(this, message, name);
		}

		_extern void _sub_10C4F300(Server::Voting::VotingSystem *const);
		void VotingSystem::SendVoteCountsToEveryone() // 0x10C4F300
		{
			mangled_x86(MANGLED_TODO, "?SendVoteCountsToEveryone@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4F5B2
			// static ...; // 0x10C4F5A7
			// static ...; // 0x10C4F597
			// static ...; // 0x10C4F58C
			// static ...; // 0x10C4F55C
			// static ...; // 0x10C4F554
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			// __int32 optionIndex;
			{
				// unsigned long Timerlength;
				// Server::Voting::VotingMessage newmessageTimer;
				// __int32 time;
				// long long elapsed;
				// Server::Voting::VotingMessage newmessage;
				// long long curTime1;
				// long long elapsed2;
			}
			{
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
				{
					// Server::Voting::MapAndType &option;
				}
			}
			todo("implement");
			_sub_10C4F300(this);
		}

		_extern void _sub_10C514C0(Server::Voting::VotingSystem *const);
		void VotingSystem::loadDefaultMapsAndTypes() // 0x10C514C0
		{
			mangled_x86(MANGLED_TODO, "?loadDefaultMapsAndTypes@VotingSystem@Voting@Server@@EAEXXZ");
			// static ...; // 0x10C51859
			// static ...; // 0x10C51855
			// static ...; // 0x10C51850
			// static ...; // 0x10C5182C
			// static ...; // 0x10C51824
			// Server::Voting::VotingSystem *const this;
			// __int32 index;
			{
				// std::vector<Server::Voting::SMapListItem> const &<range>$L0;
				// Server::Voting::SMapListItem const *<begin>$L0;
				// Server::Voting::SMapListItem const *<end>$L0;
				{
					// Server::Voting::SMapListItem const &m;
					{
						// Server::Voting::AllowedPlayerCount playerCount;
						// Server::Voting::HaloMap map;
					}
				}
			}
			{
				// std::string const *<end>$L1;
				// std::string const *<begin>$L1;
				// std::string const &<range>$L1[8];
				{
					// std::string const &t;
					{
						// Server::Voting::HaloType type;
					}
				}
			}
			todo("implement");
			_sub_10C514C0(this);
		}

		_extern double _sub_10C512A0(double, double);
		double getRandom(double fMin, double fMax) // 0x10C512A0
		{
			mangled_x86(MANGLED_TODO, "?getRandom@Voting@Server@@YANNN@Z");
			// static ...; // 0x10C5137C
			// static ...; // 0x10C51364
			// static ...; // 0x10C5135C
			// double fMin;
			// double fMax;
			// std::uniform_real_distribution<double> dist;
			// std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253> rng;
			todo("implement");
			double __result = _sub_10C512A0(fMin, fMax);
			return __result;
		}

		extern MapAndType _sub_10C4E190(Server::Voting::VotingSystem *const);
		Server::Voting::MapAndType VotingSystem::GenerateVotingOption() // 0x10C4E190
		{
			mangled_x86(MANGLED_TODO, "?GenerateVotingOption@VotingSystem@Voting@Server@@EAE?AUMapAndType@23@XZ");
			// static ...; // 0x10C4E6AD
			// static ...; // 0x10C4E6A9
			// static ...; // 0x10C4E69C
			// static ...; // 0x10C4E678
			// static ...; // 0x10C4E670
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::HaloType gametype;
			// float gametype_sum_of_weights;
			// float pGametype;
			// float maps_sum_of_weights;
			// Server::Voting::HaloMap map;
			// __int32 playerCount;
			// std::vector<Server::Voting::HaloMap> mapsToSearch;
			// float pMap;
			{
				// unsigned __int32 i;
			}
			{
			}
			{
			}
			{
			}
			todo("implement");
			Server::Voting::MapAndType __result = _sub_10C4E190(this);
			return __result;
		}

		_extern bool _sub_10C4F670(Server::Voting::AbstractVotingSystem *const);
		bool AbstractVotingSystem::ShouldSendVotingOptions() // 0x10C4F670
		{
			mangled_x86(MANGLED_TODO, "?ShouldSendVotingOptions@AbstractVotingSystem@Voting@Server@@UAE_NXZ");
			// Server::Voting::AbstractVotingSystem *const this;
			todo("implement");
			bool __result = _sub_10C4F670(this);
			return __result;
		}

		extern VotingMessage _sub_10C4E800(Server::Voting::VotingSystem *const, bool);
		Server::Voting::VotingMessage VotingSystem::GenerateVotingOptionsMessage(bool updateTime) // 0x10C4E800
		{
			mangled_x86(MANGLED_TODO, "?GenerateVotingOptionsMessage@VotingSystem@Voting@Server@@UAE?AUVotingMessage@23@_N@Z");
			// static ...; // 0x10C4EAEC
			// static ...; // 0x10C4EAE4
			// static ...; // 0x10C4EAC0
			// static ...; // 0x10C4EAB8
			// Server::Voting::VotingSystem *const this;
			// bool updateTime;
			// __int32 i;
			// Server::Voting::VotingMessage newmessage;
			// long long curTime;
			{
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
				{
					// Server::Voting::MapAndType const &option;
					{
						// std::string modHash;
					}
				}
			}
			todo("implement");
			Server::Voting::VotingMessage __result = _sub_10C4E800(this, updateTime);
			return __result;
		}
	}
}

extern std::vector<Server::Voting::MapAndType> _sub_10C50E80(Server::Voting::VotingSystem *const);
namespace Server
{
	namespace Voting
	{
		std::vector<Server::Voting::MapAndType> VotingSystem::countQuickVotes() // 0x10C50E80
		{
			mangled_x86(MANGLED_TODO, "?countQuickVotes@VotingSystem@Voting@Server@@AAE?AV?$vector@UMapAndType@Voting@Server@@V?$allocator@UMapAndType@Voting@Server@@@std@@@std@@XZ");
			// static ...; // 0x10C51018
			// static ...; // 0x10C5100D
			// static ...; // 0x10C51004
			// static ...; // 0x10C50FE0
			// static ...; // 0x10C50FD8
			// Server::Voting::VotingSystem *const this;
			// std::vector<Server::Voting::MapAndType> tmp;
			{
				// std::map<std::string,int> &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::pair<std::string const ,int> const &vote;
				}
			}
			todo("implement");
			std::vector<Server::Voting::MapAndType> __result = _sub_10C50E80(this);
			return __result;
		}

		_extern void _sub_10C51090(Server::Voting::VotingSystem *const);
		void VotingSystem::countVotes() // 0x10C51090
		{
			mangled_x86(MANGLED_TODO, "?countVotes@VotingSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x10C511B1
			// static ...; // 0x10C511A8
			// static ...; // 0x10C51190
			// static ...; // 0x10C51188
			// Server::Voting::VotingSystem *const this;
			{
				// std::map<std::string,int> &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::pair<std::string const ,int> const &vote;
				}
			}
			todo("implement");
			_sub_10C51090(this);
		}

		_extern void _sub_10C4DB80(Server::Voting::VotingSystem *const);
		void VotingSystem::FindWinner() // 0x10C4DB80
		{
			mangled_x86(MANGLED_TODO, "?FindWinner@VotingSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x10C4E041
			// static ...; // 0x10C4E036
			// static ...; // 0x10C4E02C
			// static ...; // 0x10C4E008
			// static ...; // 0x10C4E000
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			// __int32 optionIndex;
			// std::vector<Server::Voting::MapAndType> finalVotingOptions;
			// Server::Voting::VotingMessage voteTally;
			{
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
				{
					// Server::Voting::MapAndType &option;
				}
			}
			{
				// std::string *<end>$L1;
				// std::string *<begin>$L1;
				// std::vector<std::string> &<range>$L1;
				{
					// std::string const &command;
				}
			}
			todo("implement");
			_sub_10C4DB80(this);
		}

		_extern void _sub_10C4F6F0(Server::Voting::VotingSystem *const);
		void VotingSystem::StartVoting() // 0x10C4F6F0
		{
			mangled_x86(MANGLED_TODO, "?StartVoting@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4FD3B
			// static ...; // 0x10C4FD33
			// static ...; // 0x10C4FD2C
			// static ...; // 0x10C4FD24
			// static ...; // 0x10C4FCF4
			// static ...; // 0x10C4FCEC
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage message;
			{
				// unsigned __int32 i;
				{
					// bool votingOptionsContains;
					// __int32 votingDuplicatesSeen;
					// Server::Voting::MapAndType Option;
				}
			}
			{
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
				{
					// std::string const &command;
				}
			}
			{
				// Server::Voting::MapAndType rematch;
			}
			{
				// Server::Voting::MapAndType revote;
			}
			// function call : bool (std::string)
			// function call : void ()
			// function call : Server::Voting::MapAndType ()
			// function call : Server::Voting::MapAndType ()
			// function call : Server::Voting::VotingMessage (bool)
			todo("implement");
			_sub_10C4F6F0(this);
		}

		_extern __int32 _sub_10C513C0();
		__int32 getVotesNeededToInstantSkip() // 0x10C513C0
		{
			mangled_x86(MANGLED_TODO, "?getVotesNeededToInstantSkip@Voting@Server@@YAHXZ");
			// procedure flags: nofpo
			todo("implement");
			__int32 __result = _sub_10C513C0();
			return __result;
		}

		_extern void _sub_10C4FEE0(Server::Voting::VotingSystem *const);
		void VotingSystem::Tick() // 0x10C4FEE0
		{
			mangled_x86(MANGLED_TODO, "?Tick@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C5050E
			// static ...; // 0x10C50503
			// static ...; // 0x10C504F8
			// static ...; // 0x10C504D4
			// static ...; // 0x10C504CC
			// Server::Voting::VotingSystem *const this;
			// long long elapsed;
			// long long curTime1;
			{
				// long long enumerationElapsed;
				{
					// Server::Voting::VotingMessage newmessage;
				}
			}
			{
				// long long elapsed2;
			}
			{
				// __int32 playerCount;
				{
					// std::vector<Server::Voting::MapAndType> voteCounts;
					// Server::Voting::MapAndType const &winningOption;
				}
			}
			// function call : void ()
			// function call : void ()
			// function call : bool (*const)()
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10C4FEE0(this);
		}

		_extern void _sub_10C51970(Server::Voting::VotingSystem *const);
		void VotingSystem::onExit() // 0x10C51970
		{
			mangled_x86(MANGLED_TODO, "?onExit@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
			{
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
				{
					// std::string const &command;
				}
			}
			todo("implement");
			_sub_10C51970(this);
		}

		_extern bool _sub_10C4EBE0(Server::Voting::VotingSystem *const, std::string);
		bool VotingSystem::LoadJson(std::string filename) // 0x10C4EBE0
		{
			mangled_x86(MANGLED_TODO, "?LoadJson@VotingSystem@Voting@Server@@EAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C4EDE8
			// static ...; // 0x10C4EDE0
			// Server::Voting::VotingSystem *const this;
			// std::string filename;
			// Server::Voting::VotingJson voting;
			{
				// std::vector<Server::Voting::HaloMap> &<range>$L0;
				// Server::Voting::HaloMap *<begin>$L0;
				// Server::Voting::HaloMap *<end>$L0;
				{
					// Server::Voting::HaloMap &map;
				}
			}
			todo("implement");
			bool __result = _sub_10C4EBE0(this, filename);
			return __result;
		}
	}
}

/* ---------- private code */

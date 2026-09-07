/* ---------- headers */

#include "Server/Voting/VetoSystem.hpp"
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
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
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
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
		class VetoSystem;
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
		struct PlaylistItem;
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
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x11388A10
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x11388AF0
		}
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		extern VetoSystem* _sub_1073A8D0(Server::Voting::VetoSystem *const);
		VetoSystem::VetoSystem() // 0x1073A8D0
		{
			mangled_x86(MANGLED_TODO, "??0VetoSystem@Voting@Server@@QAE@XZ");
			// Server::Voting::VetoSystem *const this;
			todo("implement");
			_sub_1073A8D0(this);
		}

		extern VotingJson* _sub_1073AA30(Server::Voting::VotingJson *const);
		_inline VotingJson::VotingJson() // 0x1073AA30
		{
			mangled_x86(MANGLED_TODO, "??0VotingJson@Voting@Server@@QAE@XZ");
			// Server::Voting::VotingJson *const this;
			compiler_generated();
			todo("implement");
			_sub_1073AA30(this);
		}

		_extern void _sub_1073D950(Server::Voting::VetoSystem *const);
		void VetoSystem::Init() // 0x1073D950
		{
			mangled_x86(MANGLED_TODO, "?Init@VetoSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VetoSystem *const this;
			todo("implement");
			_sub_1073D950(this);
		}

		_extern void _sub_1073E4C0(Server::Voting::VetoSystem *const);
		void VetoSystem::SendVoteCountsToEveryone() // 0x1073E4C0
		{
			mangled_x86(MANGLED_TODO, "?SendVoteCountsToEveryone@VetoSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x1073E59C
			// static ...; // 0x1073E590
			// static ...; // 0x1073E588
			// Server::Voting::VetoSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			// function call : __int32 ()
			todo("implement");
			_sub_1073E4C0(this);
		}

		_extern void _sub_1073B780(Server::Voting::PlaylistItem *const);
		_inline PlaylistItem::~PlaylistItem() // 0x1073B780
		{
			mangled_x86(MANGLED_TODO, "??1PlaylistItem@Voting@Server@@QAE@XZ");
			// Server::Voting::PlaylistItem *const this;
			compiler_generated();
			todo("implement");
			_sub_1073B780(this);
		}

		_extern void _sub_1073B7F0(Server::Voting::VetoSystem *const);
		_inline VetoSystem::~VetoSystem() // 0x1073B7F0
		{
			mangled_x86(MANGLED_TODO, "??1VetoSystem@Voting@Server@@UAE@XZ");
			// Server::Voting::VetoSystem *const this;
			compiler_generated();
			todo("implement");
			_sub_1073B7F0(this);
		}

		_extern void _sub_1073B890(Server::Voting::VotingJson *const);
		_inline VotingJson::~VotingJson() // 0x1073B890
		{
			mangled_x86(MANGLED_TODO, "??1VotingJson@Voting@Server@@QAE@XZ");
			// Server::Voting::VotingJson *const this;
			compiler_generated();
			todo("implement");
			_sub_1073B890(this);
		}

		extern MapAndType _sub_1073CF30(Server::Voting::VetoSystem *const);
		Server::Voting::MapAndType VetoSystem::GenerateVotingOption() // 0x1073CF30
		{
			mangled_x86(MANGLED_TODO, "?GenerateVotingOption@VetoSystem@Voting@Server@@EAE?AUMapAndType@23@XZ");
			// static ...; // 0x1073D3B0
			// static ...; // 0x1073D3A4
			// static ...; // 0x1073D39C
			// Server::Voting::VetoSystem *const this;
			// __int32 playerCount;
			// Server::Voting::MapAndType m;
			{
				// float sum_of_weights;
				// __int32 optionIndex;
				// float p;
				{
					// unsigned __int32 i;
				}
				{
				}
			}
			todo("implement");
			Server::Voting::MapAndType __result = _sub_1073CF30(this);
			return __result;
		}

		extern HaloMap &_sub_1073BDA0(Server::Voting::HaloMap *const, Server::Voting::HaloMap &);
		_inline Server::Voting::HaloMap &HaloMap::operator=(Server::Voting::HaloMap &&__that) // 0x1073BDA0
		{
			mangled_x86(MANGLED_TODO, "??4HaloMap@Voting@Server@@QAEAAU012@$$QAU012@@Z");
			// Server::Voting::HaloMap &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::HaloMap & __result = _sub_1073BDA0(this, __that);
			return __result;
		}

		extern HaloMap &_sub_1073BE80(Server::Voting::HaloMap *const, Server::Voting::HaloMap const &);
		_inline Server::Voting::HaloMap &HaloMap::operator=(Server::Voting::HaloMap const &__that) // 0x1073BE80
		{
			mangled_x86(MANGLED_TODO, "??4HaloMap@Voting@Server@@QAEAAU012@ABU012@@Z");
			// Server::Voting::HaloMap const &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::HaloMap & __result = _sub_1073BE80(this, __that);
			return __result;
		}

		extern HaloType &_sub_1073BF60(Server::Voting::HaloType *const, Server::Voting::HaloType &);
		_inline Server::Voting::HaloType &HaloType::operator=(Server::Voting::HaloType &&__that) // 0x1073BF60
		{
			mangled_x86(MANGLED_TODO, "??4HaloType@Voting@Server@@QAEAAU012@$$QAU012@@Z");
			// Server::Voting::HaloType &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::HaloType & __result = _sub_1073BF60(this, __that);
			return __result;
		}

		extern HaloType &_sub_1073C0E0(Server::Voting::HaloType *const, Server::Voting::HaloType const &);
		_inline Server::Voting::HaloType &HaloType::operator=(Server::Voting::HaloType const &__that) // 0x1073C0E0
		{
			mangled_x86(MANGLED_TODO, "??4HaloType@Voting@Server@@QAEAAU012@ABU012@@Z");
			// Server::Voting::HaloType const &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::HaloType & __result = _sub_1073C0E0(this, __that);
			return __result;
		}

		extern MapAndType &_sub_1073C260(Server::Voting::MapAndType *const, Server::Voting::MapAndType &);
		_inline Server::Voting::MapAndType &MapAndType::operator=(Server::Voting::MapAndType &&__that) // 0x1073C260
		{
			mangled_x86(MANGLED_TODO, "??4MapAndType@Voting@Server@@QAEAAU012@$$QAU012@@Z");
			// Server::Voting::MapAndType &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::MapAndType & __result = _sub_1073C260(this, __that);
			return __result;
		}

		extern MapAndType &_sub_1073C350(Server::Voting::MapAndType *const, Server::Voting::MapAndType const &);
		_inline Server::Voting::MapAndType &MapAndType::operator=(Server::Voting::MapAndType const &__that) // 0x1073C350
		{
			mangled_x86(MANGLED_TODO, "??4MapAndType@Voting@Server@@QAEAAU012@ABU012@@Z");
			// Server::Voting::MapAndType const &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::MapAndType & __result = _sub_1073C350(this, __that);
			return __result;
		}

		extern VotingMessage _sub_1073D4E0(Server::Voting::VetoSystem *const, bool);
		Server::Voting::VotingMessage VetoSystem::GenerateVotingOptionsMessage(bool updateTime) // 0x1073D4E0
		{
			mangled_x86(MANGLED_TODO, "?GenerateVotingOptionsMessage@VetoSystem@Voting@Server@@UAE?AUVotingMessage@23@_N@Z");
			// static ...; // 0x1073D854
			// static ...; // 0x1073D84C
			// static ...; // 0x1073D828
			// static ...; // 0x1073D820
			// Server::Voting::VetoSystem *const this;
			// bool updateTime;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modHash;
			// Server::Voting::VotingMessage newmessage;
			// long long curTime;
			// function call : __int32 ()
			todo("implement");
			Server::Voting::VotingMessage __result = _sub_1073D4E0(this, updateTime);
			return __result;
		}

		extern AbstractVotingSystem* _sub_10739F90(Server::Voting::AbstractVotingSystem *const);
		_inline AbstractVotingSystem::AbstractVotingSystem() : finalTally(todo_result<Server::Voting::VotingMessage>()) // 0x10739F90
		{
			mangled_x86(MANGLED_TODO, "??0AbstractVotingSystem@Voting@Server@@QAE@XZ");
			// Server::Voting::AbstractVotingSystem *const this;
			compiler_generated();
			todo("implement");
			_sub_10739F90(this);
		}

		extern MapAndType* _sub_1073A550(Server::Voting::MapAndType *const, Server::Voting::MapAndType &);
		_inline MapAndType::MapAndType(Server::Voting::MapAndType &&__that) // 0x1073A550
		{
			mangled_x86(MANGLED_TODO, "??0MapAndType@Voting@Server@@QAE@$$QAU012@@Z");
			// Server::Voting::MapAndType &__that;
			compiler_generated();
			todo("implement");
			_sub_1073A550(this, __that);
		}

		_extern void _sub_10742160(Server::Voting::VetoSystem *const);
		void VetoSystem::countVotes() // 0x10742160
		{
			mangled_x86(MANGLED_TODO, "?countVotes@VetoSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x10742249
			// static ...; // 0x10742240
			// static ...; // 0x10742228
			// static ...; // 0x10742220
			// Server::Voting::VetoSystem *const this;
			{
				// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> > > &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> const &vote;
				}
			}
			todo("implement");
			_sub_10742160(this);
		}

		_extern bool _sub_10742780(Server::Voting::VetoSystem *const);
		bool VetoSystem::isEnabled() // 0x10742780
		{
			mangled_x86(MANGLED_TODO, "?isEnabled@VetoSystem@Voting@Server@@UAE_NXZ");
			// Server::Voting::VetoSystem *const this;
			todo("implement");
			bool __result = _sub_10742780(this);
			return __result;
		}

		_extern void _sub_1073E3C0(Server::Voting::VetoSystem *const);
		void VetoSystem::Reset() // 0x1073E3C0
		{
			mangled_x86(MANGLED_TODO, "?Reset@VetoSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VetoSystem *const this;
			todo("implement");
			_sub_1073E3C0(this);
		}

		_extern void _sub_1073EC30(Server::Voting::VetoSystem *const);
		void VetoSystem::StartVoting() // 0x1073EC30
		{
			mangled_x86(MANGLED_TODO, "?StartVoting@VetoSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VetoSystem *const this;
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &command;
				}
			}
			// function call : Server::Voting::MapAndType ()
			todo("implement");
			_sub_1073EC30(this);
		}

		_extern void _sub_1073CE60(Server::Voting::VetoSystem *const);
		void VetoSystem::FindWinner() // 0x1073CE60
		{
			mangled_x86(MANGLED_TODO, "?FindWinner@VetoSystem@Voting@Server@@AAEXXZ");
			// Server::Voting::VetoSystem *const this;
			// function call : __int32 ()
			todo("implement");
			_sub_1073CE60(this);
		}

		_extern void _sub_1073E5E0(Server::Voting::VetoSystem *const);
		void VetoSystem::SetGameAndMap() // 0x1073E5E0
		{
			mangled_x86(MANGLED_TODO, "?SetGameAndMap@VetoSystem@Voting@Server@@AAEXXZ");
			// Server::Voting::VetoSystem *const this;
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &command;
				}
			}
			todo("implement");
			_sub_1073E5E0(this);
		}

		_extern void _sub_1073EA30(Server::Voting::VetoSystem *const);
		void VetoSystem::SetStartTimer() // 0x1073EA30
		{
			mangled_x86(MANGLED_TODO, "?SetStartTimer@VetoSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x1073EAF0
			// static ...; // 0x1073EAE4
			// static ...; // 0x1073EADC
			// Server::Voting::VetoSystem *const this;
			// Server::Voting::VotingMessage message;
			// function call : Server::Voting::VotingMessage (bool)
			todo("implement");
			_sub_1073EA30(this);
		}

		_extern void _sub_1073EB30(Server::Voting::VetoSystem *const);
		void VetoSystem::SetVoteStartedTime() // 0x1073EB30
		{
			mangled_x86(MANGLED_TODO, "?SetVoteStartedTime@VetoSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x1073EBEC
			// static ...; // 0x1073EBE0
			// static ...; // 0x1073EBD8
			// Server::Voting::VetoSystem *const this;
			// Server::Voting::VotingMessage message;
			// function call : Server::Voting::VotingMessage (bool)
			todo("implement");
			_sub_1073EB30(this);
		}

		_extern void _sub_10742FE0(Server::Voting::VetoSystem *const);
		void VetoSystem::onExit() // 0x10742FE0
		{
			mangled_x86(MANGLED_TODO, "?onExit@VetoSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VetoSystem *const this;
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &command;
				}
			}
			todo("implement");
			_sub_10742FE0(this);
		}

		_extern bool _sub_1073D970(Server::Voting::VetoSystem *const, std::string);
		bool VetoSystem::LoadJson(std::basic_string<char,std::char_traits<char>,std::allocator<char> > filename) // 0x1073D970
		{
			mangled_x86(MANGLED_TODO, "?LoadJson@VetoSystem@Voting@Server@@EAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1073DDF7
			// static ...; // 0x1073DDF4
			// static ...; // 0x1073DDD0
			// static ...; // 0x1073DDC8
			// Server::Voting::VetoSystem *const this;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > filename;
			// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > gameTypes;
			// Server::Voting::VotingJson voting;
			{
				// std::vector<Server::Voting::PlaylistItem,std::allocator<Server::Voting::PlaylistItem> > &<range>$L0;
				// Server::Voting::PlaylistItem *<begin>$L0;
				// Server::Voting::PlaylistItem *<end>$L0;
				{
					// Server::Voting::PlaylistItem const &playlistItem;
					{
						// Server::Voting::HaloType ht;
						{
							// unsigned __int32 typeIndex;
						}
					}
				}
			}
			todo("implement");
			bool __result = _sub_1073D970(this, filename);
			return __result;
		}

		_extern void _sub_1073EE10(Server::Voting::VetoSystem *const);
		void VetoSystem::Tick() // 0x1073EE10
		{
			mangled_x86(MANGLED_TODO, "?Tick@VetoSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x1073F250
			// static ...; // 0x1073F244
			// static ...; // 0x1073F23C
			// Server::Voting::VetoSystem *const this;
			// long VoteTime;
			// long long elapsed;
			// long long curTime1;
			// Blam::Network::Session *session;
			{
				// long long elapsed;
			}
			// function call : void ()
			// function call : void ()
			// function call : bool (*const)()
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_1073EE10(this);
		}

		_extern void _sub_1073DF30(Server::Voting::VetoSystem *const, Server::Voting::VotingMessage const &, std::string);
		void VetoSystem::LogVote(Server::Voting::VotingMessage const &message, std::basic_string<char,std::char_traits<char>,std::allocator<char> > name) // 0x1073DF30
		{
			mangled_x86(MANGLED_TODO, "?LogVote@VetoSystem@Voting@Server@@UAEXABUVotingMessage@23@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1073E1B0
			// static ...; // 0x1073E1A8
			// Server::Voting::VetoSystem *const this;
			// Server::Voting::VotingMessage const &message;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
			// unsigned __int32 vote;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> > > > it;
			// Blam::Network::Session *session;
			// function call : void ()
			todo("implement");
			_sub_1073DF30(this, message, name);
		}

		_extern void _sub_1073E280(Server::Voting::VetoSystem *const);
		void VetoSystem::NewVote() // 0x1073E280
		{
			mangled_x86(MANGLED_TODO, "?NewVote@VetoSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VetoSystem *const this;
			// function call : void ()
			// function call : Server::Voting::MapAndType ()
			todo("implement");
			_sub_1073E280(this);
		}

		_extern void _sub_1073CD90(Server::Voting::VetoSystem *const);
		void VetoSystem::EndVote() // 0x1073CD90
		{
			mangled_x86(MANGLED_TODO, "?EndVote@VetoSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x1073CE24
			// static ...; // 0x1073CE18
			// static ...; // 0x1073CE10
			// Server::Voting::VetoSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			todo("implement");
			_sub_1073CD90(this);
		}

		_extern void _sub_10742800(Server::Voting::VetoSystem *const);
		void VetoSystem::loadDefaultMapsAndTypes() // 0x10742800
		{
			mangled_x86(MANGLED_TODO, "?loadDefaultMapsAndTypes@VetoSystem@Voting@Server@@EAEXXZ");
			// static ...; // 0x10742D23
			// static ...; // 0x10742D1A
			// static ...; // 0x10742D0E
			// static ...; // 0x10742D0A
			// static ...; // 0x10742D05
			// static ...; // 0x10742CFC
			// static ...; // 0x10742CB4
			// static ...; // 0x10742CAC
			// Server::Voting::VetoSystem *const this;
			// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > gameTypes;
			// __int32 index;
			// std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > haloMaps;
			{
				// std::vector<Server::Voting::SMapListItem,std::allocator<Server::Voting::SMapListItem> > const &<range>$L0;
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
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L1;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L1;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &<range>$L1[8];
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &t;
					{
						// Server::Voting::HaloType type;
					}
				}
			}
			{
				// __int32 i;
				{
					// Server::Voting::HaloType gametype;
					// Server::Voting::HaloMap &map;
				}
			}
			todo("implement");
			_sub_10742800(this);
		}
	}
}

/* ---------- private code */

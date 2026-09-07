/* ---------- headers */

#include "Server/Voting/HaloTypeInheritance.hpp"
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
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"

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
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ratio>
#include <stdexcept>
#include <stop_token>
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
		struct HaloTypeInheritance;
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
namespace Blam {}
using namespace ::Blam;

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
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x113887F0
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x113888D0
		}
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_extern void _sub_10733A40(std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > &, std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &);
		void HaloTypeInheritance::MergeMaps(std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > &maps, std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &newMaps) // 0x10733A40
		{
			mangled_x86(MANGLED_TODO, "?MergeMaps@HaloTypeInheritance@Voting@Server@@SAXAAV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@std@@ABV45@@Z");
			// std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &newMaps;
			{
				// std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &<range>$L0;
				// Server::Voting::HaloMap const *<begin>$L0;
				// Server::Voting::HaloMap const *<end>$L0;
				{
					// Server::Voting::HaloMap const &map;
				}
			}
			todo("implement");
			_sub_10733A40(maps, newMaps);
		}

		_extern bool _sub_10733360(Server::Voting::HaloType &, Server::Voting::HaloType const &, std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &);
		bool HaloTypeInheritance::BuildHaloType(Server::Voting::HaloType &newType, Server::Voting::HaloType const &currentType, std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &types) // 0x10733360
		{
			mangled_x86(MANGLED_TODO, "?BuildHaloType@HaloTypeInheritance@Voting@Server@@SA_NAAUHaloType@23@ABU423@ABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@@Z");
			// static ...; // 0x107336EC
			// static ...; // 0x107336E4
			// Server::Voting::HaloType &newType;
			// Server::Voting::HaloType const &currentType;
			// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &types;
			{
				// unsigned __int32 baseTypeIndex;
			}
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &cmd;
				}
			}
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L1;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L1;
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &<range>$L1;
				{
				}
			}
			{
				// std::_Default_sentinel <end>$L2;
				// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Server::Voting::HaloType::CharacterOverride,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Server::Voting::HaloType::CharacterOverride> > > const &<range>$L2;
				// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Server::Voting::HaloType::CharacterOverride> > >,std::_Iterator_base0> <begin>$L2;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &k;
					// Server::Voting::HaloType::CharacterOverride const &v;
				}
			}
			{
				// std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &<range>$L3;
				// Server::Voting::HaloMap const *<begin>$L3;
				// Server::Voting::HaloMap const *<end>$L3;
				{
					// Server::Voting::HaloMap const &map;
				}
			}
			todo("implement");
			bool __result = _sub_10733360(newType, currentType, types);
			return __result;
		}

		extern AllowedPlayerCount* _sub_107327F0(Server::Voting::AllowedPlayerCount *const);
		_inline AllowedPlayerCount::AllowedPlayerCount() // 0x107327F0
		{
			mangled_x86(MANGLED_TODO, "??0AllowedPlayerCount@Voting@Server@@QAE@XZ");
			// Server::Voting::AllowedPlayerCount *const this;
			compiler_generated();
			todo("implement");
			_sub_107327F0(this);
		}

		extern HaloType::CharacterOverride* _sub_10732830(Server::Voting::HaloType::CharacterOverride *const);
		_inline HaloType::CharacterOverride::CharacterOverride() // 0x10732830
		{
			mangled_x86(MANGLED_TODO, "??0CharacterOverride@HaloType@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloType::CharacterOverride *const this;
			compiler_generated();
			todo("implement");
			_sub_10732830(this);
		}

		extern HaloMap* _sub_10732890(Server::Voting::HaloMap *const, Server::Voting::HaloMap &);
		_inline HaloMap::HaloMap(Server::Voting::HaloMap &&__that) // 0x10732890
		{
			mangled_x86(MANGLED_TODO, "??0HaloMap@Voting@Server@@QAE@$$QAU012@@Z");
			// Server::Voting::HaloMap &__that;
			compiler_generated();
			todo("implement");
			_sub_10732890(this, __that);
		}

		_extern void _sub_10733810(std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > &, std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &);
		void HaloTypeInheritance::BuildHaloTypes(std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > &newTypes, std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &allTypes) // 0x10733810
		{
			mangled_x86(MANGLED_TODO, "?BuildHaloTypes@HaloTypeInheritance@Voting@Server@@SAXAAV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@ABV45@@Z");
			// static ...; // 0x107339AC
			// static ...; // 0x107339A4
			// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > &newTypes;
			// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &allTypes;
			{
				// std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &<range>$L0;
				// Server::Voting::HaloType const *<begin>$L0;
				// Server::Voting::HaloType const *<end>$L0;
				{
					// Server::Voting::HaloType const &ht;
					{
						// Server::Voting::HaloType newHaloType;
					}
				}
			}
			todo("implement");
			_sub_10733810(newTypes, allTypes);
		}

		extern HaloType* _sub_107329A0(Server::Voting::HaloType *const, Server::Voting::HaloType &);
		_inline HaloType::HaloType(Server::Voting::HaloType &&__that) // 0x107329A0
		{
			mangled_x86(MANGLED_TODO, "??0HaloType@Voting@Server@@QAE@$$QAU012@@Z");
			// Server::Voting::HaloType &__that;
			compiler_generated();
			todo("implement");
			_sub_107329A0(this, __that);
		}

		extern HaloType::CharacterOverride &_sub_10732F60(Server::Voting::HaloType::CharacterOverride *const, Server::Voting::HaloType::CharacterOverride const &);
		_inline Server::Voting::HaloType::CharacterOverride &HaloType::CharacterOverride::operator=(Server::Voting::HaloType::CharacterOverride const &__that) // 0x10732F60
		{
			mangled_x86(MANGLED_TODO, "??4CharacterOverride@HaloType@Voting@Server@@QAEAAU0123@ABU0123@@Z");
			// Server::Voting::HaloType::CharacterOverride const &__that;
			compiler_generated();
			todo("implement");
			Server::Voting::HaloType::CharacterOverride & __result = _sub_10732F60(this, __that);
			return __result;
		}
	}
}

/* ---------- private code */

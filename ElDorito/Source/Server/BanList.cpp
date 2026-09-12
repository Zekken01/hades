/* ---------- headers */

#include "Server/BanList.hpp"
#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Prefab.hpp"
#include "Modules/ModuleServer.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
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
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Server
{
	class BanList;
	class TempBanList;
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
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	extern Server::BanList LoadDefaultBanList();
	extern void SaveDefaultBanList(Server::BanList const &list);
}

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x1246757C
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace Server
{
	_extern void _sub_10AFAF10(Server::TempBanList *const, std::string const);
	void TempBanList::AddIp(std::string const ip) // 0x10AFAF10
	{
		mangled_x86(MANGLED_TODO, "?AddIp@TempBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10AFB108
		// static ...; // 0x10AFB100
		// Server::TempBanList *const this;
		// std::string ip;
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > it;
		todo("implement");
		_sub_10AFAF10(this, ip);
	}

	void TempBanList::decrementDuration() // 0x10AFC1B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?decrementDuration@TempBanList@Server@@QAEXXZ");
		// static ...; // 0x10AFC338
		// static ...; // 0x10AFC32C
		// static ...; // 0x10AFC324
		// Server::TempBanList *const this;
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > it;

		auto it = ipAddresses.begin();
		while (it != ipAddresses.end())
		{
			if (it->second < 2)
			{
				//remove this Ip if its duration has finished.
				it = ipAddresses.erase(it);
			}
			else
			{
				it->second--;
				++it;
			}
		}
	}

	extern BanList* _sub_10AFA740(Server::BanList *const, std::string const &);
	BanList::BanList(std::string const &path) // 0x10AFA740
	{
		mangled_x86(MANGLED_TODO, "??0BanList@Server@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10AFA82C
		// static ...; // 0x10AFA824
		// Server::BanList *const this;
		// std::string const &path;
		// std::ifstream stream;
		todo("implement");
		_sub_10AFA740(this, path);
	}

	_extern void _sub_10AFB320(Server::BanList *const, std::istream &);
	void BanList::Read(std::istream &stream) // 0x10AFB320
	{
		mangled_x86(MANGLED_TODO, "?Read@BanList@Server@@AAEXAAV?$basic_istream@DU?$char_traits@D@std@@@std@@@Z");
		// static ...; // 0x10AFB604
		// static ...; // 0x10AFB600
		// static ...; // 0x10AFB5DC
		// static ...; // 0x10AFB5D4
		// Server::BanList *const this;
		// std::istream &stream;
		{
			// std::string line;
			// std::vector<std::string> components;
			// unsigned __int32 commentStart;
			{
				// unsigned long long uid;
			}
		}
		todo("implement");
		_sub_10AFB320(this, stream);
	}

	_extern void _sub_10AFB6E0(Server::BanList const *const, std::ostream &);
	void BanList::Save(std::ostream &stream) const // 0x10AFB6E0
	{
		mangled_x86(MANGLED_TODO, "?Save@BanList@Server@@QBEXAAV?$basic_ostream@DU?$char_traits@D@std@@@std@@@Z");
		// static ...; // 0x10AFBAF8
		// static ...; // 0x10AFBAF3
		// static ...; // 0x10AFBAE8
		// static ...; // 0x10AFBADF
		// static ...; // 0x10AFBADC
		// static ...; // 0x10AFBAD1
		// static ...; // 0x10AFBAC8
		// static ...; // 0x10AFBA68
		// static ...; // 0x10AFBA60
		// Server::BanList const *const this;
		// std::ostream &stream;
		{
			// std::unordered_set<std::string> const &<range>$L0;
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L0;
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L0;
			{
				// std::string name;
			}
		}
		{
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L1;
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L1;
			// std::unordered_set<std::string> const &<range>$L1;
			{
				// std::string ip;
			}
		}
		{
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<unsigned __int64> >,std::_Iterator_base0> <end>$L2;
			// std::unordered_set<unsigned __int64> const &<range>$L2;
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<unsigned __int64> >,std::_Iterator_base0> <begin>$L2;
			{
				// unsigned long long uid;
			}
		}
		todo("implement");
		_sub_10AFB6E0((Server::BanList const *)this, stream);
	}

	_extern void _sub_10AFBC20(Server::BanList const *const, std::string const &);
	void BanList::Save(std::string const &path) const // 0x10AFBC20
	{
		mangled_x86(MANGLED_TODO, "?Save@BanList@Server@@QBEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10AFBCDC
		// static ...; // 0x10AFBCD4
		// Server::BanList const *const this;
		// std::string const &path;
		// std::ofstream stream;
		todo("implement");
		_sub_10AFBC20((Server::BanList const *)this, path);
	}

	Server::BanList LoadDefaultBanList() // 0x10AFB1A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultBanList@Server@@YA?AVBanList@1@XZ");
		// procedure flags: nofpo
		// static ...; // 0x10AFB2C8
		// static ...; // 0x10AFB2BC
		// static ...; // 0x10AFB2B4
		// std::ifstream file;

		std::ifstream file(DefaultBanListPath);
		if (file)
			return BanList(file);
		return BanList();
	}

	_extern void _sub_10AFBD30(Server::BanList const &);
	void SaveDefaultBanList(Server::BanList const &list) // 0x10AFBD30
	{
		mangled_x86(MANGLED_TODO, "?SaveDefaultBanList@Server@@YAXABVBanList@1@@Z");
		// Server::BanList const &list;
		todo("implement");
		_sub_10AFBD30(list);
	}
}

/* ---------- private code */

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

namespace Patches { namespace PlayerUid { bool ParseUid(std::string const &str, unsigned long long *out); } }  // hades: added for 0x10AFB320  // hades: added for 0x10AFB320

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
		// extern std::string DefaultBanListPath; // 0x1246757C  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace Server
{
	void TempBanList::AddIp(std::string const ip) // 0x10AFAF10
	{
		auto it = ipAddresses.find(ip);
		if (it != ipAddresses.end())
			it->second += Utils::Singleton<Modules::ModuleServer>::Instance().VarTempBanDuration->ValueInt;
		else
			ipAddresses.insert(std::make_pair(ip, Utils::Singleton<Modules::ModuleServer>::Instance().VarTempBanDuration->ValueInt));
	}

	void TempBanList::decrementDuration() // 0x10AFC1B0
	{
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

	BanList::BanList(std::string const &path) // 0x10AFA740
	{
		std::ifstream stream(path);
		Read(stream);
	}

	void BanList::Read(std::istream &stream) // 0x10AFB320
	{
		while (true)
		{
			std::string line;
			std::getline(stream, line);
			if (stream.fail())
				break;
			unsigned __int32 commentStart = line.find('#');
			if (commentStart != std::string::npos)
				line = line.substr(0, commentStart);
			line = Utils::String::Trim(Utils::String::Trim(line, false), true);
			std::vector<std::string> components = Utils::String::SplitString(line, ' ');
			if (components.size() < 2)
				continue;
			if (components[0] == "ip")
				AddIp(components[1]);
			else if (components[0] == "uid")
			{
				unsigned long long uid;
				if (Patches::PlayerUid::ParseUid(components[1], &uid))
					AddUid(uid);
			}
			else if (components[0] == "name")
				AddName(components[1]);
		}
	}

	void BanList::Save(std::ostream &stream) const // 0x10AFB6E0
	{
		stream << "# ElDewrito server ban list\n";
		stream << "# Players matching the filters in this file will not be allowed to connect to your server.\n\n";
		stream << "# Name bans\n";
		stream << "# Format: name XXXX\n";
		for (auto name : names)
			stream << "name " << name << '\n';
		stream << "\n# IPv4 address bans\n";
		stream << "# Format: ip XXX.XXX.XXX.XXX\n";
		for (auto ip : ipAddresses)
			stream << "ip " << ip << '\n';
		stream << "\n# UID bans\n";
		stream << "# Format: uid XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
		for (auto uid : uids)
			stream << "uid " << std::hex << std::setw(16) << std::setfill('0') << uid << std::dec << '\n';
	}

	void BanList::Save(std::string const &path) const // 0x10AFBC20
	{
		std::ofstream stream(path, std::ios::trunc);
		Save(stream);
	}

	Server::BanList LoadDefaultBanList() // 0x10AFB1A0
	{
		std::ifstream file(DefaultBanListPath);
		if (file)
			return BanList(file);
		return BanList();
	}

	void SaveDefaultBanList(Server::BanList const &list) // 0x10AFBD30
	{
		list.Save(DefaultBanListPath);
	}
}

/* ---------- private code */

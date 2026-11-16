#ifndef __SERVER_BANLIST_HPP__
#define __SERVER_BANLIST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Prefab.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"

#include "Server/StatsServerBanList.hpp"  // hades: added for 0x10A98300

#include <functional>
#include <istream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>
#include <utility>

/* ---------- forward declarations */

namespace Server
{
	class BanList;
	class TempBanList;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Server
{
	class TempBanList :
		public Utils::Singleton<Server::TempBanList>
	{
	public:
		_inline TempBanList();
		void AddIp(std::string const ip);
		_inline bool ContainsIp(std::string ip);
		_inline bool RemoveIp(std::string const &ip);
		void decrementDuration();
		_inline void ClearList();
		_inline std::map<std::string,int> TempBannedList();
	private:
		std::map<std::string,int> ipAddresses; // 0x0
	public:
		~TempBanList() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Server::TempBanList) == 12, "Invalid Server::TempBanList size");

namespace Server
{
	class BanList
	{
	public:
		public:
		enum BanType
		{
			ePerm = 42, // 0x002A '*'
			eTemp = 43, // 0x002B '+'
			eNone = 44, // 0x002C ','
		};
		public:
		BanList(Server::BanList &); /* compiler_generated() */
		BanList(Server::BanList const &); /* compiler_generated() */
		BanList(std::string const &path);
		_inline BanList(std::istream &stream);
		_inline BanList();
		_inline void AddIp(std::string const &ip);
		_inline bool ContainsIp(std::string const &ip) const;
		_inline bool RemoveIp(std::string const &ip);
		_inline void AddUid(unsigned long long uid);
		_inline bool ContainsUid(unsigned long long uid);
		_inline bool RemoveUid(unsigned long long uid);
		_inline void AddName(std::string const &name);
		_inline bool ContainsName(std::string const &name);
		_inline bool RemoveName(std::string const &name);
		void Save(std::string const &path) const;
		void Save(std::ostream &stream) const;
		_inline BanType IsBanned(std::string const &ip);
	private:
		void Read(std::istream &stream);
		std::unordered_set<std::string> ipAddresses; // 0x0
		std::unordered_set<unsigned __int64> uids; // 0x28
		std::unordered_set<std::string> names; // 0x50
	public:
		_inline ~BanList(); /* compiler_generated() */
		Server::BanList &operator=(Server::BanList &); /* compiler_generated() */
		Server::BanList &operator=(Server::BanList const &); /* compiler_generated() */
	};
	static_assert(sizeof(Server::BanList) == 120, "Invalid Server::BanList size");
}

/* ---------- prototypes */

namespace Server
{
	extern Server::BanList LoadDefaultBanList();
	extern void SaveDefaultBanList(Server::BanList const &list);
}

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	inline TempBanList::TempBanList() // 0x10728080
	{
	}

	inline bool TempBanList::ContainsIp(std::string ip) // 0x10A94290
	{
		return ipAddresses.find(ip) != ipAddresses.end();
	}

	inline bool TempBanList::RemoveIp(std::string const &ip) // 0x10A13F30
	{
		return ipAddresses.erase(ip) == 1;
	}

	inline void TempBanList::ClearList() // 0x10728340
	{
		ipAddresses.clear();
	}
}


namespace Server
{
	inline std::map<std::string,int> TempBanList::TempBannedList() // 0x10A141C0
	{
		return ipAddresses;
	}

	inline BanList::BanList() // 0x10AFA880
	{
	}

	inline BanList::BanList(std::istream &stream) // 0x10AFA670
	{
		Read(stream);
	}

	inline void BanList::AddIp(std::string const &ip) // 0x10A07830
	{
		ipAddresses.insert(ip);
	}

	inline bool BanList::ContainsIp(std::string const &ip) const // 0x10A93FE0
	{
		return ipAddresses.find(ip) != ipAddresses.end();
	}

	inline bool BanList::RemoveIp(std::string const &ip) // 0x10A13EA0
	{
		return ipAddresses.erase(ip) == 1;
	}

	inline void BanList::AddUid(unsigned long long uid) // 0x10A07930
	{
		uids.insert(uid);
	}

	inline bool BanList::ContainsUid(unsigned long long uid) // 0x10A94840
	{
		return !(uids.find(uid) == uids.end());
	}

	inline bool BanList::RemoveUid(unsigned long long uid) // 0x10A14050
	{
		return uids.erase(uid) == 1;
	}

	inline void BanList::AddName(std::string const &name) // 0x10A078B0
	{
		names.insert(name);
	}

	inline bool BanList::ContainsName(std::string const &name) // 0x10A94410
	{
		return names.find(name) != names.end();
	}

	inline bool BanList::RemoveName(std::string const &name) // 0x10A13FC0
	{
		return names.erase(name) == 1;
	}

	inline Server::BanList::BanType BanList::IsBanned(std::string const &ip) // 0x10A98300
	{
		if (ContainsIp(ip) || Utils::Singleton<StatsServersBanList>::Instance().ContainsIp(ip))
			return ePerm;
		else if (Utils::Singleton<TempBanList>::Instance().ContainsIp(ip))
			return eTemp;
		else
			return eNone;
	}
}

/* ---------- private code */

// hades: one copy per including file, each with its own initialiser and atexit destructor.
namespace Server
{
	static std::string DefaultBanListPath = "data/server/banlist.txt";
}

#endif // __SERVER_BANLIST_HPP__

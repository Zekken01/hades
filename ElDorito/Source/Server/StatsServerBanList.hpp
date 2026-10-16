#ifndef __SERVER_STATSSERVERBANLIST_HPP__
#define __SERVER_STATSSERVERBANLIST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/StlUtil.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Server
{
	class StatsServersBanList;
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	class StatsServersBanList :
		public Utils::Singleton<Server::StatsServersBanList>
	{
	public:
		public:
		struct Subnet
		{
			unsigned long Network; // 0x0
			unsigned long Mask; // 0x4
		};
		static_assert(sizeof(Subnet) == 8, "Invalid Subnet size");
		public:
		_inline StatsServersBanList();
		_inline void AddIp(std::string const ip);
		_inline void AddSubnet(unsigned long network, unsigned long mask);
		_inline void AddName(std::string const name);
		_inline void AddUID(std::string const uid);
		_inline bool ContainsIp(std::string ip);
		_inline bool ContainsSubnet(std::string ip);
		_inline bool ContainsName(std::string name);
		_inline bool ContainsUID(std::string uid);
		bool RemoveIp(std::string const &);
		_inline void ClearList();
	private:
		std::vector<Subnet> subnets; // 0x0
		std::unordered_set<std::string> ipAddresses; // 0x10
		std::unordered_set<std::string> uids; // 0x38
		std::unordered_set<std::string> names; // 0x60
	public:
		~StatsServersBanList() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Server::StatsServersBanList) == 136, "Invalid Server::StatsServersBanList size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	inline StatsServersBanList::StatsServersBanList() // 0x10A8F940
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0StatsServersBanList@Server@@QAE@XZ");
	}

	inline void StatsServersBanList::AddIp(std::string const ip) // 0x10B17F70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddIp@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		ipAddresses.insert(ip);
	}

	inline void StatsServersBanList::AddSubnet(unsigned long network, unsigned long mask) // 0x10B18110
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddSubnet@StatsServersBanList@Server@@QAEXKK@Z");

		subnets.push_back({ network, mask });
	}

	inline void StatsServersBanList::AddName(std::string const name) // 0x10B18040
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddName@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		names.insert(name);
	}

	inline void StatsServersBanList::AddUID(std::string const uid) // 0x10B18190
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddUID@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		uids.insert(uid);
	}

	inline bool StatsServersBanList::ContainsIp(std::string ip) // 0x10A94110
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ContainsIp@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		return ipAddresses.find(ip) != ipAddresses.end();
	}

	inline bool StatsServersBanList::ContainsSubnet(std::string ip) // 0x10B18AB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ContainsSubnet@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		unsigned long addr = inet_addr(ip.c_str());
		for (Server::StatsServersBanList::Subnet const &subnet : subnets)
		{
			if (((addr ^ subnet.Network) & subnet.Mask) == 0)
				return true;
		}
		return false;
	}

	inline bool StatsServersBanList::ContainsName(std::string name) // 0x10A94540
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ContainsName@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		return names.find(name) != names.end();
	}

	inline bool StatsServersBanList::ContainsUID(std::string uid) // 0x10A946C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ContainsUID@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		return uids.find(uid) != uids.end();
	}

	inline void StatsServersBanList::ClearList() // 0x10B18A30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ClearList@StatsServersBanList@Server@@QAEXXZ");

		subnets.clear();
		ipAddresses.clear();
		uids.clear();
		names.clear();
	}
}

/* ---------- private code */

#endif // __SERVER_STATSSERVERBANLIST_HPP__

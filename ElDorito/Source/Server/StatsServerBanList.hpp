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
		~StatsServersBanList(); /* compiler_generated() */
	};
	static_assert(sizeof(Server::StatsServersBanList) == 136, "Invalid Server::StatsServersBanList size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	_inline StatsServersBanList::StatsServersBanList() // 0x10A8F940
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0StatsServersBanList@Server@@QAE@XZ");
		// Server::StatsServersBanList *const this;
	}

	_extern void _sub_10B17F70(Server::StatsServersBanList *const, std::string const);
	_inline void StatsServersBanList::AddIp(std::string const ip) // 0x10B17F70
	{
		mangled_x86(MANGLED_TODO, "?AddIp@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string ip;
		todo("implement");
		_sub_10B17F70(this, ip);
	}

	_extern void _sub_10B18110(Server::StatsServersBanList *const, unsigned long, unsigned long);
	_inline void StatsServersBanList::AddSubnet(unsigned long network, unsigned long mask) // 0x10B18110
	{
		mangled_x86(MANGLED_TODO, "?AddSubnet@StatsServersBanList@Server@@QAEXKK@Z");
		// unsigned long mask;
		todo("implement");
		_sub_10B18110(this, network, mask);
	}

	_extern void _sub_10B18040(Server::StatsServersBanList *const, std::string const);
	_inline void StatsServersBanList::AddName(std::string const name) // 0x10B18040
	{
		mangled_x86(MANGLED_TODO, "?AddName@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_10B18040(this, name);
	}

	_extern void _sub_10B18190(Server::StatsServersBanList *const, std::string const);
	_inline void StatsServersBanList::AddUID(std::string const uid) // 0x10B18190
	{
		mangled_x86(MANGLED_TODO, "?AddUID@StatsServersBanList@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string uid;
		todo("implement");
		_sub_10B18190(this, uid);
	}

	_extern bool _sub_10A94110(Server::StatsServersBanList *const, std::string);
	_inline bool StatsServersBanList::ContainsIp(std::string ip) // 0x10A94110
	{
		mangled_x86(MANGLED_TODO, "?ContainsIp@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string ip;
		todo("implement");
		bool __result = _sub_10A94110(this, ip);
		return __result;
	}

	_extern bool _sub_10B18AB0(Server::StatsServersBanList *const, std::string);
	_inline bool StatsServersBanList::ContainsSubnet(std::string ip) // 0x10B18AB0
	{
		mangled_x86(MANGLED_TODO, "?ContainsSubnet@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string ip;
		// unsigned long addr;
		{
			// std::vector<Server::StatsServersBanList::Subnet> &<range>$L0;
			// Server::StatsServersBanList::Subnet *<begin>$L0;
			// Server::StatsServersBanList::Subnet *<end>$L0;
			{
				// Server::StatsServersBanList::Subnet const &subnet;
			}
		}
		todo("implement");
		bool __result = _sub_10B18AB0(this, ip);
		return __result;
	}

	_extern bool _sub_10A94540(Server::StatsServersBanList *const, std::string);
	_inline bool StatsServersBanList::ContainsName(std::string name) // 0x10A94540
	{
		mangled_x86(MANGLED_TODO, "?ContainsName@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		bool __result = _sub_10A94540(this, name);
		return __result;
	}

	_extern bool _sub_10A946C0(Server::StatsServersBanList *const, std::string);
	_inline bool StatsServersBanList::ContainsUID(std::string uid) // 0x10A946C0
	{
		mangled_x86(MANGLED_TODO, "?ContainsUID@StatsServersBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string uid;
		todo("implement");
		bool __result = _sub_10A946C0(this, uid);
		return __result;
	}

	_inline void StatsServersBanList::ClearList() // 0x10B18A30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ClearList@StatsServersBanList@Server@@QAEXXZ");
		// Server::StatsServersBanList *const this;

		subnets.clear();
		ipAddresses.clear();
		uids.clear();
		names.clear();
	}
}

/* ---------- private code */

#endif // __SERVER_STATSSERVERBANLIST_HPP__

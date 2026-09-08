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
		_inline std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<std::string const ,int> > > TempBannedList();
	private:
		std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<std::string const ,int> > > ipAddresses; // 0x0
	public:
		~TempBanList(); /* compiler_generated() */
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
		_inline BanList(std::basic_istream<char,std::char_traits<char> > &stream);
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
		void Save(std::basic_ostream<char,std::char_traits<char> > &stream) const;
		_inline BanType IsBanned(std::string const &ip);
	private:
		void Read(std::basic_istream<char,std::char_traits<char> > &stream);
		std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > ipAddresses; // 0x0
		std::unordered_set<unsigned __int64,std::hash<unsigned __int64>,std::equal_to<unsigned __int64>,std::allocator<unsigned __int64> > uids; // 0x28
		std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > names; // 0x50
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
	extern TempBanList* _sub_10728080(Server::TempBanList *const);
	_inline TempBanList::TempBanList() // 0x10728080
	{
		mangled_x86(MANGLED_TODO, "??0TempBanList@Server@@QAE@XZ");
		// Server::TempBanList *const this;
		todo("implement");
		_sub_10728080(this);
	}

	_extern bool _sub_10A94290(Server::TempBanList *const, std::string);
	_inline bool TempBanList::ContainsIp(std::string ip) // 0x10A94290
	{
		mangled_x86(MANGLED_TODO, "?ContainsIp@TempBanList@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string ip;
		todo("implement");
		bool __result = _sub_10A94290(this, ip);
		return __result;
	}

	_extern bool _sub_10A13F30(Server::TempBanList *const, std::string const &);
	_inline bool TempBanList::RemoveIp(std::string const &ip) // 0x10A13F30
	{
		mangled_x86(MANGLED_TODO, "?RemoveIp@TempBanList@Server@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ip;
		todo("implement");
		bool __result = _sub_10A13F30(this, ip);
		return __result;
	}

	_extern void _sub_10728340(Server::TempBanList *const);
	_inline void TempBanList::ClearList() // 0x10728340
	{
		mangled_x86(MANGLED_TODO, "?ClearList@TempBanList@Server@@QAEXXZ");
		// Server::TempBanList *const this;
		todo("implement");
		_sub_10728340(this);
	}
}

extern std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<std::string const ,int> > > _sub_10A141C0(Server::TempBanList *const);
namespace Server
{
	_inline std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<std::string const ,int> > > TempBanList::TempBannedList() // 0x10A141C0
	{
		mangled_x86(MANGLED_TODO, "?TempBannedList@TempBanList@Server@@QAE?AV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HU?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@std@@@2@@std@@XZ");
		// Server::TempBanList *const this;
		todo("implement");
		std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<std::string const ,int> > > __result = _sub_10A141C0(this);
		return __result;
	}

	extern BanList* _sub_10AFA880(Server::BanList *const);
	_inline BanList::BanList() // 0x10AFA880
	{
		mangled_x86(MANGLED_TODO, "??0BanList@Server@@QAE@XZ");
		// Server::BanList *const this;
		todo("implement");
		_sub_10AFA880(this);
	}

	extern BanList* _sub_10AFA670(Server::BanList *const, std::basic_istream<char,std::char_traits<char> > &);
	_inline BanList::BanList(std::basic_istream<char,std::char_traits<char> > &stream) // 0x10AFA670
	{
		mangled_x86(MANGLED_TODO, "??0BanList@Server@@QAE@AAV?$basic_istream@DU?$char_traits@D@std@@@std@@@Z");
		// std::basic_istream<char,std::char_traits<char> > &stream;
		todo("implement");
		_sub_10AFA670(this, stream);
	}

	_extern void _sub_10A07830(Server::BanList *const, std::string const &);
	_inline void BanList::AddIp(std::string const &ip) // 0x10A07830
	{
		mangled_x86(MANGLED_TODO, "?AddIp@BanList@Server@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ip;
		todo("implement");
		_sub_10A07830(this, ip);
	}

	_extern bool _sub_10A93FE0(Server::BanList const *const, std::string const &);
	_inline bool BanList::ContainsIp(std::string const &ip) const // 0x10A93FE0
	{
		mangled_x86(MANGLED_TODO, "?ContainsIp@BanList@Server@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ip;
		todo("implement");
		bool __result = _sub_10A93FE0((Server::BanList const *)this, ip);
		return __result;
	}

	_extern bool _sub_10A13EA0(Server::BanList *const, std::string const &);
	_inline bool BanList::RemoveIp(std::string const &ip) // 0x10A13EA0
	{
		mangled_x86(MANGLED_TODO, "?RemoveIp@BanList@Server@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ip;
		todo("implement");
		bool __result = _sub_10A13EA0(this, ip);
		return __result;
	}

	_extern void _sub_10A07930(Server::BanList *const, unsigned long long);
	_inline void BanList::AddUid(unsigned long long uid) // 0x10A07930
	{
		mangled_x86(MANGLED_TODO, "?AddUid@BanList@Server@@QAEX_K@Z");
		// unsigned long long uid;
		todo("implement");
		_sub_10A07930(this, uid);
	}

	_extern bool _sub_10A94840(Server::BanList *const, unsigned long long);
	_inline bool BanList::ContainsUid(unsigned long long uid) // 0x10A94840
	{
		mangled_x86(MANGLED_TODO, "?ContainsUid@BanList@Server@@QAE_N_K@Z");
		// unsigned long long uid;
		todo("implement");
		bool __result = _sub_10A94840(this, uid);
		return __result;
	}

	_extern bool _sub_10A14050(Server::BanList *const, unsigned long long);
	_inline bool BanList::RemoveUid(unsigned long long uid) // 0x10A14050
	{
		mangled_x86(MANGLED_TODO, "?RemoveUid@BanList@Server@@QAE_N_K@Z");
		// unsigned long long uid;
		todo("implement");
		bool __result = _sub_10A14050(this, uid);
		return __result;
	}

	_extern void _sub_10A078B0(Server::BanList *const, std::string const &);
	_inline void BanList::AddName(std::string const &name) // 0x10A078B0
	{
		mangled_x86(MANGLED_TODO, "?AddName@BanList@Server@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &name;
		todo("implement");
		_sub_10A078B0(this, name);
	}

	_extern bool _sub_10A94410(Server::BanList *const, std::string const &);
	_inline bool BanList::ContainsName(std::string const &name) // 0x10A94410
	{
		mangled_x86(MANGLED_TODO, "?ContainsName@BanList@Server@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &name;
		todo("implement");
		bool __result = _sub_10A94410(this, name);
		return __result;
	}

	_extern bool _sub_10A13FC0(Server::BanList *const, std::string const &);
	_inline bool BanList::RemoveName(std::string const &name) // 0x10A13FC0
	{
		mangled_x86(MANGLED_TODO, "?RemoveName@BanList@Server@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &name;
		todo("implement");
		bool __result = _sub_10A13FC0(this, name);
		return __result;
	}

	extern BanList::BanType _sub_10A98300(Server::BanList *const, std::string const &);
	_inline Server::BanList::BanType BanList::IsBanned(std::string const &ip) // 0x10A98300
	{
		mangled_x86(MANGLED_TODO, "?IsBanned@BanList@Server@@QAE?AW4BanType@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ip;
		todo("implement");
		Server::BanList::BanType __result = _sub_10A98300(this, ip);
		return __result;
	}
}

/* ---------- private code */

#endif // __SERVER_BANLIST_HPP__

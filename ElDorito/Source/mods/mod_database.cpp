/* ---------- headers */

#include "mods/mod_database.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "Modules/ModuleServer.hpp"
#undef GetObject  // hades: the original resolves rapidjson's GetObject members, so the Windows macro must not rename them
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/istreamwrapper.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/ostreamwrapper.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_mod_database;
struct begin;
struct end;
struct lambda_1;
struct s_mod_origin_info;
struct s_mod_package_id;

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

//class c_mod_database::purge_all_not_in_set::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(c_mod_database::purge_all_not_in_set::__l2::<lambda_1> &);
//	<lambda_1>(std::unordered_set<s_mod_package_id> &);
//private:
//	std::unordered_set<s_mod_package_id> &set; // 0x0
//public:
//	c_mod_database::purge_all_not_in_set::__l2::<lambda_1> &operator=(c_mod_database::purge_all_not_in_set::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(c_mod_database::purge_all_not_in_set::__l2::<lambda_1>) == 4, "Invalid c_mod_database::purge_all_not_in_set::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_mod_database::~c_mod_database() // 0x1084DB20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_mod_database@@QAE@XZ");

	if (m_dirty)
		save();
}

// mangled_x86(MANGLED_DEFAULT, "??1s_record@c_mod_database@@QAE@XZ"); no body to assert in
// c_mod_database::s_record::~s_record() is implicit; 0x1084DBD0

// mangled_x86(MANGLED_DEFAULT, "??4s_mod_origin_info@@QAEAAU0@ABU0@@Z"); no body to assert in
// s_mod_origin_info &s_mod_origin_info::operator=(s_mod_origin_info const &__that) is implicit; 0x1084DE80

// mangled_x86(MANGLED_DEFAULT, "??4s_record@c_mod_database@@QAEAAU01@ABU01@@Z"); no body to assert in
// c_mod_database::s_record &c_mod_database::s_record::operator=(c_mod_database::s_record const &__that) is implicit; 0x1084DF20

bool c_mod_database::try_get_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x10853630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_get_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");

	if (auto it = m_records.find(id); it != m_records.end())
	{
		*record = &it->second;
		return true;
	}
	return false;
}

bool c_mod_database::get_or_create_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x10852200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_or_create_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");

	return try_get_record(id, record) || create_record(id, record);
}

bool c_mod_database::create_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x108517C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");

	if (auto it = m_records.find(id); it == m_records.end())
	{
		s_record new_record{};
		time(&new_record.date_added);
		auto result = m_records.emplace(std::make_pair(id, new_record));
		if (result.second)
		{
			*record = &result.first->second;
			m_dirty = true;
			return true;
		}
	}
	return false;
}

bool c_mod_database::delete_record(s_mod_package_id const &id) // 0x10851D60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?delete_record@c_mod_database@@QAE_NABUs_mod_package_id@@@Z");

	if (auto it = m_records.find(id); it != m_records.end())
	{
		m_records.erase(it);
		m_dirty = true;
		return true;
	}
	return false;
}

bool c_mod_database::update_record(s_mod_package_id const &id, c_mod_database::s_record const &record) // 0x108537A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_record@c_mod_database@@QAE_NABUs_mod_package_id@@ABUs_record@1@@Z");

	if (auto it = m_records.find(id); it != m_records.end())
	{
		it->second = record;
		m_dirty = true;
		return true;
	}
	return false;
}

bool c_mod_database::create(std::string const &filename) // 0x108516B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	if (std::filesystem::exists(filename))
		return false;
	m_filename = filename;
	return save();
}

bool c_mod_database::load_or_create(std::string const &filename) // 0x10852AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_or_create@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	return load(filename) || create(filename);
}

bool c_mod_database::load(std::string const &filename) // 0x108522A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	m_filename = filename;
	if (!std::filesystem::exists(filename))
		return false;
	std::ifstream ifs(m_filename);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);
	if (d.GetParseError() != rapidjson::kParseErrorNone)
		return false;
	auto records_member = d.FindMember("records");
	if (records_member == d.MemberEnd() || !records_member->value.IsObject())
		return false;
	std::unordered_map<s_mod_package_id,s_record> tmp;
	for (auto &key : records_member->value.GetObject())
	{
		char const *hash = key.name.GetString();
		auto value = key.value.GetObject();
		s_record record;
		record.date_added = value["timestamp"].GetUint();
		if (value.HasMember("last_used"))
			record.date_last_used = value["last_used"].GetUint();
		if (value.HasMember("verified"))
			record.signature_verified = value["verified"].GetBool();
		record.mod_name.assign(value["mod_name"].GetString());
		record.origin.server_name.assign(value["server_name"].GetString());
		record.origin.server_host.assign(value["server_host"].GetString());
		record.origin.server_ip.assign(value["server_ip"].GetString());
		record.origin.url.assign(value["url"].GetString());
		tmp.insert(std::make_pair(s_mod_package_id::from_string(hash), std::move(record)));
	}
	m_records = std::move(tmp);
	return true;
}

bool c_mod_database::save() // 0x108530E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?save@c_mod_database@@QAE_NXZ");

	std::ofstream ofs(m_filename);
	rapidjson::OStreamWrapper osw(ofs);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	writer.StartObject();
	writer.Key("version");
	writer.Uint(1);
	writer.Key("records");
	writer.StartObject();
	for (auto &record : m_records)
	{
		std::string key = record.first.to_string();
		writer.Key(key.c_str());
		writer.StartObject();
		writer.Key("timestamp");
		writer.Uint(record.second.date_added);
		writer.Key("last_used");
		writer.Uint(record.second.date_last_used);
		writer.Key("verified");
		writer.Bool(record.second.signature_verified);
		writer.Key("mod_name");
		writer.String(record.second.mod_name.c_str());
		writer.Key("server_name");
		writer.String(record.second.origin.server_name.c_str());
		writer.Key("server_host");
		writer.String(record.second.origin.server_host.c_str());
		writer.Key("server_ip");
		writer.String(record.second.origin.server_ip.c_str());
		writer.Key("url");
		writer.String(record.second.origin.url.c_str());
		writer.EndObject();
	}
	writer.EndObject();
	writer.EndObject();
	m_dirty = false;
	return true;
}

void c_mod_database::notify_record_changed(s_mod_package_id const &id) // 0x10852D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?notify_record_changed@c_mod_database@@QAEXABUs_mod_package_id@@@Z");

	m_dirty = true;
}

void c_mod_database::purge_any(std::function<bool __cdecl(s_mod_package_id const &,c_mod_database::s_record const &)> predicate) // 0x10852E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?purge_any@c_mod_database@@QAEXV?$function@$$A6A_NABUs_mod_package_id@@ABUs_record@c_mod_database@@@Z@std@@@Z");

	for (auto it = m_records.begin(); it != m_records.end();)
	{
		if (predicate(it->first, it->second))
			it = m_records.erase(it);
		else
			++it;
	}
}

void c_mod_database::purge_all_not_in_set(std::unordered_set<s_mod_package_id> set) // 0x10852DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?purge_all_not_in_set@c_mod_database@@QAEXV?$unordered_set@Us_mod_package_id@@U?$hash@Us_mod_package_id@@@std@@U?$equal_to@Us_mod_package_id@@@3@V?$allocator@Us_mod_package_id@@@3@@std@@@Z");

	purge_any([&set](auto &id, auto record) { return set.find(id) == set.end(); });
}

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_origin_info@@QAE@$$QAU0@@Z"); no body to assert in
// s_mod_origin_info::s_mod_origin_info(s_mod_origin_info &&__that) is implicit; 0x1084CC50

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_origin_info@@QAE@ABU0@@Z"); no body to assert in
// s_mod_origin_info::s_mod_origin_info(s_mod_origin_info const &__that) is implicit; 0x1084CD30

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@$$QAU01@@Z"); no body to assert in
// c_mod_database::s_record::s_record(c_mod_database::s_record &&__that) is implicit; 0x1084CE60

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@ABU01@@Z"); no body to assert in
// c_mod_database::s_record::s_record(c_mod_database::s_record const &__that) is implicit; 0x1084CF40

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@XZ"); no body to assert in

/* ---------- private code */

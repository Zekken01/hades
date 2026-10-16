/* ---------- headers */

#include "Player/PlayerCustomizationDB.hpp"
#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Prefab.hpp"
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
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x107D6D00  // hades: added for 0x107D6D00

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
#include <map>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Player
{
	class CPlayerCustomizationDB;
	struct SPersistentCharacterCustomization;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	extern Player::SPersistentCharacterCustomization LoadCustomization(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value);
	extern std::map<std::string,Player::SPersistentCharacterCustomization> LoadCustomizations(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SaveCustomization(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, Player::SPersistentCharacterCustomization const &customization);
	extern void SaveCustomizations(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,Player::SPersistentCharacterCustomization> const &customizations);
	extern std::map<std::string,std::string> LoadPreferredCharacters(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SavePreferredCharacters(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,std::string> const &preferredCharacters);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	Player::SPersistentCharacterCustomization LoadCustomization(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value) // 0x107D70B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadCustomization@Player@@YA?AUSPersistentCharacterCustomization@1@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");

		Player::SPersistentCharacterCustomization customization;
		auto const &permutations = value["permutations"].GetObject();
		auto const &colors = value["colors"].GetObject();
		for (auto it = permutations.MemberBegin(); it != permutations.MemberEnd(); ++it)
			customization.permutations.insert({ it->name.GetString(), it->value.GetString() });
		for (auto it = colors.MemberBegin(); it != colors.MemberEnd(); ++it)
			customization.colors.insert({ it->name.GetString(), it->value.GetString() });
		return customization;
	}
}


namespace Player
{
	std::map<std::string,Player::SPersistentCharacterCustomization> LoadCustomizations(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x107D7470
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadCustomizations@Player@@YA?AV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@@std@@@2@@std@@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");

		std::map<std::string,Player::SPersistentCharacterCustomization> customizations;
		for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
			customizations.insert({ it->name.GetString(), LoadCustomization(it->value) });
		return customizations;
	}

	void SaveCustomization(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, Player::SPersistentCharacterCustomization const &customization) // 0x107D7CA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SaveCustomization@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUSPersistentCharacterCustomization@1@@Z");

		writer.StartObject();
		writer.Key("permutations");
		writer.StartObject();
		for (auto const &[regionName, permutationName] : customization.permutations)
		{
			writer.Key(regionName.c_str());
			writer.String(permutationName.c_str());
		}
		writer.EndObject();
		writer.Key("colors");
		writer.StartObject();
		for (auto const &[colorName, colorValue] : customization.colors)
		{
			writer.Key(colorName.c_str());
			writer.String(colorValue.c_str());
		}
		writer.EndObject();
		writer.EndObject();
	}

	void SaveCustomizations(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,Player::SPersistentCharacterCustomization> const &customizations) // 0x107D7F40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SaveCustomizations@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@@std@@@2@@std@@@Z");

		writer.StartObject();
		for (auto const &[characterName, customization] : customizations)
		{
			writer.Key(characterName.c_str());
			SaveCustomization(writer, customization);
		}
		writer.EndObject();
	}
}


namespace Player
{
	std::map<std::string,std::string> LoadPreferredCharacters(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x107D76E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadPreferredCharacters@Player@@YA?AV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");

		std::map<std::string,std::string> results;
		for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
			results.insert({ it->name.GetString(), it->value.GetString() });
		return results;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistentCharacterCustomization@Player@@QAE@$$QAU01@@Z"); no body to assert in
	_inline SPersistentCharacterCustomization::SPersistentCharacterCustomization(Player::SPersistentCharacterCustomization &&__that) = default; // 0x107D5200

	void SavePreferredCharacters(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,std::string> const &preferredCharacters) // 0x107D80A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SavePreferredCharacters@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@@Z");

		writer.StartObject();
		for (auto const &[target, characterName] : preferredCharacters)
		{
			writer.Key(target.c_str());
			writer.String(characterName.c_str());
		}
		writer.EndObject();
	}

	// mangled_x86(MANGLED_DEFAULT, "??4SPersistentCharacterCustomization@Player@@QAEAAU01@ABU01@@Z"); no body to assert in
	_inline Player::SPersistentCharacterCustomization &SPersistentCharacterCustomization::operator=(Player::SPersistentCharacterCustomization const &__that) = default; // 0x107D5C70

	bool CPlayerCustomizationDB::Load(std::string const &filename) // 0x107D6D00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Load@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		m_fileName = filename;
		std::ifstream stream(std::filesystem::absolute(filename));
		rapidjson::IStreamWrapper isw(stream);
		rapidjson::Document doc;
		doc.ParseStream(isw);
		if (doc.HasParseError())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Invalid json in player_customization.json. Player customizations will not be applied!");
			return false;
		}
		auto const &root = doc.GetObject();
		m_customizations = LoadCustomizations(root["customization"]);
		m_preferredCharacters = LoadPreferredCharacters(root["preferredCharacters"]);
		return true;
	}

	void CPlayerCustomizationDB::Save(std::string const &filename) // 0x107D79B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Save@CPlayerCustomizationDB@Player@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		m_fileName = filename;
		Save();
	}

	void CPlayerCustomizationDB::Save() // 0x107D7A10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Save@CPlayerCustomizationDB@Player@@QAEXXZ");

		std::ofstream stream(std::filesystem::absolute(m_fileName));
		rapidjson::OStreamWrapper isw(stream);
		rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(isw);
		writer.StartObject();
		writer.Key("version");
		writer.Int(1);
		writer.Key("customization");
		SaveCustomizations(writer, m_customizations);
		writer.Key("preferredCharacters");
		SavePreferredCharacters(writer, m_preferredCharacters);
		writer.EndObject();
	}

	void CPlayerCustomizationDB::Reload() // 0x107D7900
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reload@CPlayerCustomizationDB@Player@@QAEXXZ");

		Load(m_fileName);
	}

	void CPlayerCustomizationDB::Reset() // 0x107D7950
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@CPlayerCustomizationDB@Player@@QAEXXZ");

		m_customizations.clear();
		m_preferredCharacters.clear();
	}

	bool CPlayerCustomizationDB::GetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization &customization) const // 0x107D65E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterCustomization@CPlayerCustomizationDB@Player@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUSPersistentCharacterCustomization@2@@Z");

		if (auto it = m_customizations.find(characterName); it != m_customizations.end())
		{
			customization = it->second;
			return true;
		}
		return false;
	}

	bool CPlayerCustomizationDB::SetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization const &customization) // 0x107D8290
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetCharacterCustomization@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUSPersistentCharacterCustomization@2@@Z");

		if (customization.permutations.empty() && customization.colors.empty())
			m_customizations.erase(characterName);
		else
			m_customizations[characterName] = customization;
		return true;
	}

	bool CPlayerCustomizationDB::SetCharacterColor(std::string const &characterName, std::string const &colorName, std::string const &colorValue) // 0x107D8200
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetCharacterColor@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");

		m_customizations[characterName].colors[colorName] = colorValue;
		return true;
	}

	bool CPlayerCustomizationDB::SetCharacterPermutation(std::string const &characterName, std::string const &regionName, std::string const &permutationName) // 0x107D8360
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetCharacterPermutation@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");

		m_customizations[characterName].permutations[regionName] = permutationName;
		return true;
	}
}


namespace Player
{
	std::string CPlayerCustomizationDB::GetPreferredCharacter(std::string const &target) const // 0x107D6B00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPreferredCharacter@CPlayerCustomizationDB@Player@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");

		if (auto it = m_preferredCharacters.find(target); it != m_preferredCharacters.end())
			return it->second;
		return "";
	}

	bool CPlayerCustomizationDB::SetPreferredCharacter(std::string const &target, std::string const &characterName) // 0x107D8400
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetPreferredCharacter@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

		m_preferredCharacters[target] = characterName;
		return true;
	}
}


namespace Player
{
	std::vector<std::string> CPlayerCustomizationDB::GetCharacters() // 0x107D67A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacters@CPlayerCustomizationDB@Player@@QAE?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");

		std::vector<std::string> characterNames;
		characterNames.reserve(m_customizations.size());
		for (auto const &[characterName, _] : m_customizations)
			characterNames.push_back(characterName);
		return characterNames;
	}
}

/* ---------- private code */

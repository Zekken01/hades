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
	extern SPersistentCharacterCustomization _sub_107D70B0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &);
	Player::SPersistentCharacterCustomization LoadCustomization(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value) // 0x107D70B0
	{
		mangled_x86(MANGLED_TODO, "?LoadCustomization@Player@@YA?AUSPersistentCharacterCustomization@1@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");
		// static ...; // 0x107D739E
		// static ...; // 0x107D739A
		// static ...; // 0x107D7396
		// static ...; // 0x107D7393
		// static ...; // 0x107D7390
		// static ...; // 0x107D7354
		// static ...; // 0x107D734C
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value;
		// rapidjson::GenericObject<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &colors;
		// Player::SPersistentCharacterCustomization customization;
		// rapidjson::GenericObject<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &permutations;
		{
			// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		}
		{
		}
		todo("implement");
		Player::SPersistentCharacterCustomization __result = _sub_107D70B0(value);
		return __result;
	}
}

extern std::map<std::string,Player::SPersistentCharacterCustomization> _sub_107D7470(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &);
namespace Player
{
	std::map<std::string,Player::SPersistentCharacterCustomization> LoadCustomizations(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x107D7470
	{
		mangled_x86(MANGLED_TODO, "?LoadCustomizations@Player@@YA?AV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@@std@@@2@@std@@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");
		// static ...; // 0x107D764F
		// static ...; // 0x107D764C
		// static ...; // 0x107D7634
		// static ...; // 0x107D762C
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value;
		// std::map<std::string,Player::SPersistentCharacterCustomization> customizations;
		{
			// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		}
		todo("implement");
		std::map<std::string,Player::SPersistentCharacterCustomization> __result = _sub_107D7470(value);
		return __result;
	}

	_extern void _sub_107D7CA0(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, Player::SPersistentCharacterCustomization const &);
	void SaveCustomization(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, Player::SPersistentCharacterCustomization const &customization) // 0x107D7CA0
	{
		mangled_x86(MANGLED_TODO, "?SaveCustomization@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUSPersistentCharacterCustomization@1@@Z");
		// static ...; // 0x107D7E9C
		// static ...; // 0x107D7E91
		// static ...; // 0x107D7E88
		// static ...; // 0x107D7E58
		// static ...; // 0x107D7E50
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
		// Player::SPersistentCharacterCustomization const &customization;
		{
			// std::map<std::string,std::string> const &<range>$L0;
			// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > >,std::_Iterator_base0> <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::string const &regionName;
				// std::string const &permutationName;
			}
		}
		{
			// std::_Default_sentinel <end>$L1;
			// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > >,std::_Iterator_base0> <begin>$L1;
			// std::map<std::string,std::string> const &<range>$L1;
			{
				// std::string const &colorName;
				// std::string const &colorValue;
			}
		}
		todo("implement");
		_sub_107D7CA0(writer, customization);
	}

	_extern void _sub_107D7F40(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, std::map<std::string,Player::SPersistentCharacterCustomization> const &);
	void SaveCustomizations(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,Player::SPersistentCharacterCustomization> const &customizations) // 0x107D7F40
	{
		mangled_x86(MANGLED_TODO, "?SaveCustomizations@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USPersistentCharacterCustomization@Player@@@std@@@2@@std@@@Z");
		// static ...; // 0x107D803C
		// static ...; // 0x107D8024
		// static ...; // 0x107D801C
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
		// std::map<std::string,Player::SPersistentCharacterCustomization> const &customizations;
		{
			// std::map<std::string,Player::SPersistentCharacterCustomization> const &<range>$L0;
			// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,Player::SPersistentCharacterCustomization> > >,std::_Iterator_base0> <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// Player::SPersistentCharacterCustomization const &customization;
				// std::string const &characterName;
			}
		}
		todo("implement");
		_sub_107D7F40(writer, customizations);
	}
}

extern std::map<std::string,std::string> _sub_107D76E0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &);
namespace Player
{
	std::map<std::string,std::string> LoadPreferredCharacters(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x107D76E0
	{
		mangled_x86(MANGLED_TODO, "?LoadPreferredCharacters@Player@@YA?AV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");
		// static ...; // 0x107D7887
		// static ...; // 0x107D7884
		// static ...; // 0x107D786C
		// static ...; // 0x107D7864
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value;
		// std::map<std::string,std::string> results;
		{
			// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		}
		todo("implement");
		std::map<std::string,std::string> __result = _sub_107D76E0(value);
		return __result;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistentCharacterCustomization@Player@@QAE@$$QAU01@@Z"); no body to assert in
	_inline SPersistentCharacterCustomization::SPersistentCharacterCustomization(Player::SPersistentCharacterCustomization &&__that) = default; // 0x107D5200

	_extern void _sub_107D80A0(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, std::map<std::string,std::string> const &);
	void SavePreferredCharacters(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,std::string> const &preferredCharacters) // 0x107D80A0
	{
		mangled_x86(MANGLED_TODO, "?SavePreferredCharacters@Player@@YAXAAV?$PrettyWriter@V?$BasicOStreamWrapper@V?$basic_ostream@DU?$char_traits@D@std@@@std@@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@@Z");
		// static ...; // 0x107D819C
		// static ...; // 0x107D8184
		// static ...; // 0x107D817C
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
		// std::map<std::string,std::string> const &preferredCharacters;
		{
			// std::map<std::string,std::string> const &<range>$L0;
			// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > >,std::_Iterator_base0> <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::string const &target;
				// std::string const &characterName;
			}
		}
		todo("implement");
		_sub_107D80A0(writer, preferredCharacters);
	}

	// mangled_x86(MANGLED_DEFAULT, "??4SPersistentCharacterCustomization@Player@@QAEAAU01@ABU01@@Z"); no body to assert in
	_inline Player::SPersistentCharacterCustomization &SPersistentCharacterCustomization::operator=(Player::SPersistentCharacterCustomization const &__that) = default; // 0x107D5C70

	_extern bool _sub_107D6D00(Player::CPlayerCustomizationDB *const, std::string const &);
	bool CPlayerCustomizationDB::Load(std::string const &filename) // 0x107D6D00
	{
		mangled_x86(MANGLED_TODO, "?Load@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107D6FE1
		// static ...; // 0x107D6FDD
		// static ...; // 0x107D6FD8
		// static ...; // 0x107D6FA8
		// static ...; // 0x107D6FA0
		// Player::CPlayerCustomizationDB *const this;
		// std::string const &filename;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
		// rapidjson::GenericObject<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &root;
		// std::ifstream stream;
		// rapidjson::BasicIStreamWrapper<std::istream > isw;
		todo("implement");
		bool __result = _sub_107D6D00(this, filename);
		return __result;
	}

	_extern void _sub_107D79B0(Player::CPlayerCustomizationDB *const, std::string const &);
	void CPlayerCustomizationDB::Save(std::string const &filename) // 0x107D79B0
	{
		mangled_x86(MANGLED_TODO, "?Save@CPlayerCustomizationDB@Player@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &filename;
		todo("implement");
		_sub_107D79B0(this, filename);
	}

	_extern void _sub_107D7A10(Player::CPlayerCustomizationDB *const);
	void CPlayerCustomizationDB::Save() // 0x107D7A10
	{
		mangled_x86(MANGLED_TODO, "?Save@CPlayerCustomizationDB@Player@@QAEXXZ");
		// static ...; // 0x107D7C0F
		// static ...; // 0x107D7C0B
		// static ...; // 0x107D7C04
		// static ...; // 0x107D7BE0
		// static ...; // 0x107D7BD8
		// Player::CPlayerCustomizationDB *const this;
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		// std::ofstream stream;
		// rapidjson::BasicOStreamWrapper<std::ostream > isw;
		todo("implement");
		_sub_107D7A10(this);
	}

	void CPlayerCustomizationDB::Reload() // 0x107D7900
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reload@CPlayerCustomizationDB@Player@@QAEXXZ");
		// Player::CPlayerCustomizationDB *const this;

		Load(m_fileName);
	}

	void CPlayerCustomizationDB::Reset() // 0x107D7950
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@CPlayerCustomizationDB@Player@@QAEXXZ");
		// Player::CPlayerCustomizationDB *const this;

		m_customizations.clear();
		m_preferredCharacters.clear();
	}

	_extern bool _sub_107D65E0(Player::CPlayerCustomizationDB const *const, std::string const &, Player::SPersistentCharacterCustomization &);
	bool CPlayerCustomizationDB::GetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization &customization) const // 0x107D65E0
	{
		mangled_x86(MANGLED_TODO, "?GetCharacterCustomization@CPlayerCustomizationDB@Player@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUSPersistentCharacterCustomization@2@@Z");
		// static ...; // 0x107D672C
		// Player::CPlayerCustomizationDB const *const this;
		// std::string const &characterName;
		// Player::SPersistentCharacterCustomization &customization;
		{
			// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,Player::SPersistentCharacterCustomization> > > > it;
		}
		todo("implement");
		bool __result = _sub_107D65E0((Player::CPlayerCustomizationDB const *)this, characterName, customization);
		return __result;
	}

	_extern bool _sub_107D8290(Player::CPlayerCustomizationDB *const, std::string const &, Player::SPersistentCharacterCustomization const &);
	bool CPlayerCustomizationDB::SetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization const &customization) // 0x107D8290
	{
		mangled_x86(MANGLED_TODO, "?SetCharacterCustomization@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUSPersistentCharacterCustomization@2@@Z");
		// Player::SPersistentCharacterCustomization const &customization;
		todo("implement");
		bool __result = _sub_107D8290(this, characterName, customization);
		return __result;
	}

	_extern bool _sub_107D8200(Player::CPlayerCustomizationDB *const, std::string const &, std::string const &, std::string const &);
	bool CPlayerCustomizationDB::SetCharacterColor(std::string const &characterName, std::string const &colorName, std::string const &colorValue) // 0x107D8200
	{
		mangled_x86(MANGLED_TODO, "?SetCharacterColor@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");
		// std::string const &colorValue;
		todo("implement");
		bool __result = _sub_107D8200(this, characterName, colorName, colorValue);
		return __result;
	}

	_extern bool _sub_107D8360(Player::CPlayerCustomizationDB *const, std::string const &, std::string const &, std::string const &);
	bool CPlayerCustomizationDB::SetCharacterPermutation(std::string const &characterName, std::string const &regionName, std::string const &permutationName) // 0x107D8360
	{
		mangled_x86(MANGLED_TODO, "?SetCharacterPermutation@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");
		// std::string const &permutationName;
		todo("implement");
		bool __result = _sub_107D8360(this, characterName, regionName, permutationName);
		return __result;
	}
}

extern std::string _sub_107D6B00(Player::CPlayerCustomizationDB const *const, std::string const &);
namespace Player
{
	std::string CPlayerCustomizationDB::GetPreferredCharacter(std::string const &target) const // 0x107D6B00
	{
		mangled_x86(MANGLED_TODO, "?GetPreferredCharacter@CPlayerCustomizationDB@Player@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
		// static ...; // 0x107D6C80
		// static ...; // 0x107D6C78
		// Player::CPlayerCustomizationDB const *const this;
		// std::string const &target;
		{
			// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;
		}
		todo("implement");
		std::string __result = _sub_107D6B00((Player::CPlayerCustomizationDB const *)this, target);
		return __result;
	}

	_extern bool _sub_107D8400(Player::CPlayerCustomizationDB *const, std::string const &, std::string const &);
	bool CPlayerCustomizationDB::SetPreferredCharacter(std::string const &target, std::string const &characterName) // 0x107D8400
	{
		mangled_x86(MANGLED_TODO, "?SetPreferredCharacter@CPlayerCustomizationDB@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// std::string const &characterName;
		todo("implement");
		bool __result = _sub_107D8400(this, target, characterName);
		return __result;
	}
}

extern std::vector<std::string> _sub_107D67A0(Player::CPlayerCustomizationDB *const);
namespace Player
{
	std::vector<std::string> CPlayerCustomizationDB::GetCharacters() // 0x107D67A0
	{
		mangled_x86(MANGLED_TODO, "?GetCharacters@CPlayerCustomizationDB@Player@@QAE?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// static ...; // 0x107D6924
		// static ...; // 0x107D6919
		// static ...; // 0x107D6910
		// static ...; // 0x107D68EC
		// static ...; // 0x107D68E4
		// Player::CPlayerCustomizationDB *const this;
		// std::vector<std::string> characterNames;
		{
			// std::map<std::string,Player::SPersistentCharacterCustomization> &<range>$L0;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,Player::SPersistentCharacterCustomization> > > > <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// Player::SPersistentCharacterCustomization const &_;
				// std::string const &characterName;
			}
		}
		todo("implement");
		std::vector<std::string> __result = _sub_107D67A0(this);
		return __result;
	}
}

/* ---------- private code */

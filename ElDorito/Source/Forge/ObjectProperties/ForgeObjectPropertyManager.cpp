/* ---------- headers */

#include "Forge/ObjectProperties/ForgeObjectPropertyManager.hpp"
#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyDefinitions.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "Utils/NameValueTable.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Forge
{
	class CObjectPropertyManager;
	struct SPropertyDefinition;
}

namespace Utils {}
using namespace ::Utils;
namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	extern CObjectPropertyManager* _sub_108453B0(Forge::CObjectPropertyManager *const);
	CObjectPropertyManager::CObjectPropertyManager() // 0x108453B0
	{
		mangled_x86(MANGLED_TODO, "??0CObjectPropertyManager@Forge@@QAE@XZ");
		// Forge::CObjectPropertyManager *const this;
		todo("implement");
		_sub_108453B0(this);
	}

	_extern void _sub_10846D70(Forge::CObjectPropertyManager *const, Forge::EPropertyValueType, char const *, Forge::EObjectProperty);
	void CObjectPropertyManager::Register(Forge::EPropertyValueType valueType, char const *name, Forge::EObjectProperty property) // 0x10846D70
	{
		mangled_x86(MANGLED_TODO, "?Register@CObjectPropertyManager@Forge@@AAEXW4EPropertyValueType@2@PBDW4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;
		todo("implement");
		_sub_10846D70(this, valueType, name, property);
	}
}

extern std::array<Forge::SPropertyDefinition,90> const _sub_10846C50(Forge::CObjectPropertyManager const *const);
namespace Forge
{
	std::array<Forge::SPropertyDefinition,90> const CObjectPropertyManager::GetProperties() const // 0x10846C50
	{
		mangled_x86(MANGLED_TODO, "?GetProperties@CObjectPropertyManager@Forge@@QBE?BV?$array@USPropertyDefinition@Forge@@$0FK@@std@@XZ");
		// Forge::CObjectPropertyManager const *const this;
		todo("implement");
		std::array<Forge::SPropertyDefinition,90> const __result = _sub_10846C50((Forge::CObjectPropertyManager const *)this);
		return __result;
	}

	extern EObjectProperty _sub_10846A60(Forge::CObjectPropertyManager *const, char const *);
	Forge::EObjectProperty CObjectPropertyManager::FindPropertyByName(char const *name) // 0x10846A60
	{
		mangled_x86(MANGLED_TODO, "?FindPropertyByName@CObjectPropertyManager@Forge@@QAE?AW4EObjectProperty@2@PBD@Z");
		// static ...; // 0x10846BD8
		// static ...; // 0x10846BD0
		// Forge::CObjectPropertyManager *const this;
		// char const *name;
		{
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,enum Forge::EObjectProperty> > > > it;
		}
		todo("implement");
		Forge::EObjectProperty __result = _sub_10846A60(this, name);
		return __result;
	}

	Forge::SPropertyDefinition const *CObjectPropertyManager::GetProperty(Forge::EObjectProperty property) const // 0x10846C90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProperty@CObjectPropertyManager@Forge@@QBEPBUSPropertyDefinition@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;

		return &m_registeredProperties[property];
	}
}

extern char const *_sub_10846D00(Forge::CObjectPropertyManager *const, Forge::EObjectProperty);
namespace Forge
{
	char const *CObjectPropertyManager::GetPropertyName(Forge::EObjectProperty property) // 0x10846D00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPropertyName@CObjectPropertyManager@Forge@@QAEPBDW4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;

		return m_registeredProperties[property].name;
	}
}

/* ---------- private code */

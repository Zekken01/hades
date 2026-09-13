#ifndef __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYMANAGER_HPP__
#define __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyDefinitions.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

namespace Forge
{
	class CObjectPropertyManager;
	struct SPropertyDefinition;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CObjectPropertyManager :
		public Utils::Singleton<Forge::CObjectPropertyManager>
	{
	public:
		typedef std::array<Forge::SPropertyDefinition,90> TPropertyDefinitionArray;
		CObjectPropertyManager();
		std::array<Forge::SPropertyDefinition,90> const GetProperties() const;
		Forge::SPropertyDefinition const *GetProperty(Forge::EObjectProperty property) const;
		Forge::EObjectProperty FindPropertyByName(char const *name);
		char const *GetPropertyName(Forge::EObjectProperty property);
	private:
		std::array<Forge::SPropertyDefinition,90> m_registeredProperties; // 0x0
		std::unordered_map<std::string,enum Forge::EObjectProperty> m_nameLookup; // 0x438
		void Register(Forge::EPropertyValueType valueType, char const *name, Forge::EObjectProperty property);
	public:
		~CObjectPropertyManager() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Forge::CObjectPropertyManager) == 1120, "Invalid Forge::CObjectPropertyManager size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYMANAGER_HPP__

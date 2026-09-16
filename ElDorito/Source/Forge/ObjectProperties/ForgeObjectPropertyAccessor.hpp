#ifndef __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYACCESSOR_HPP__
#define __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYACCESSOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyManager.hpp"
#include "Forge/ObjectProperties/ForgePropertyValue.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

namespace Forge
{
	class CDefaultPropertyAccessor;
	class CDeferredPropertySetter;
	class CObjectPropertyAccessor;
	class CObjectPropertyManager;
	struct SPropertyValue;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CObjectPropertyAccessor
	{
	public:
		virtual _inline ~CObjectPropertyAccessor() = default; // 0x1083B2F0
		virtual void SetPropertyValue(Forge::EObjectProperty, Forge::SPropertyValue) = 0;
		virtual Forge::SPropertyValue GetPropertyValue(Forge::EObjectProperty) = 0;
		Forge::CObjectPropertyManager &GetManager();
		CObjectPropertyAccessor(Forge::CObjectPropertyAccessor const &); /* compiler_generated() */
		_inline CObjectPropertyAccessor() = default; /* compiler_generated() */
		Forge::CObjectPropertyAccessor &operator=(Forge::CObjectPropertyAccessor const &); /* compiler_generated() */
	};
	static_assert(sizeof(Forge::CObjectPropertyAccessor) == 4, "Invalid Forge::CObjectPropertyAccessor size");

	class CDefaultPropertyAccessor :
		public Forge::CObjectPropertyAccessor
	{
	public:
		CDefaultPropertyAccessor(Forge::CDefaultPropertyAccessor &); /* compiler_generated() */
		CDefaultPropertyAccessor(Forge::CDefaultPropertyAccessor const &); /* compiler_generated() */
		CDefaultPropertyAccessor(long playerIndex, long objectIndex);
		virtual void SetPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		virtual Forge::SPropertyValue GetPropertyValue(Forge::EObjectProperty property);
	private:
		_inline Forge::SPropertyValue GetGeneralPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetReforgePropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetForgeLightPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetForgeFxPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetGarbageVolumePropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetKillVolumePropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetMapModifierPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetBudgetPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetForgeDevicePropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetForgeSceneryPropertyValue(Forge::EObjectProperty property);
		_inline Forge::SPropertyValue GetForgeChangeColorsPropertyValue(Forge::EObjectProperty property);
		_inline void SetGeneralPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetReforgePropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetForgeLightPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetForgeFxPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetGarbageVolumePropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetKillVolumePropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetMapModifierPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetBudgetPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetForgeDevicePropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		void SetForgeSceneryPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		_inline void SetForgeChangeColorsPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		long m_objectIndex; // 0x4
		long m_playerIndex; // 0x8
	public:
		virtual _inline ~CDefaultPropertyAccessor() = default; /* compiler_generated() */ // 0x1083B2A0
		Forge::CDefaultPropertyAccessor &operator=(Forge::CDefaultPropertyAccessor &); /* compiler_generated() */
		Forge::CDefaultPropertyAccessor &operator=(Forge::CDefaultPropertyAccessor const &); /* compiler_generated() */
	};
	static_assert(sizeof(Forge::CDefaultPropertyAccessor) == 12, "Invalid Forge::CDefaultPropertyAccessor size");
}

#pragma pack(push, 4)
namespace Forge
{
	class CDeferredPropertySetter :
		public Forge::CObjectPropertyAccessor
	{
	public:
		virtual void SetPropertyValue(Forge::EObjectProperty property, Forge::SPropertyValue value);
		virtual Forge::SPropertyValue GetPropertyValue(Forge::EObjectProperty property);
		void Reset();
		void Apply(long playerIndex, long objectIndex);
	private:
		std::unordered_map<enum Forge::EObjectProperty,Forge::SPropertyValue> m_values; // 0x4
	public:
		CDeferredPropertySetter(Forge::CDeferredPropertySetter &); /* compiler_generated() */
		CDeferredPropertySetter(Forge::CDeferredPropertySetter const &); /* compiler_generated() */
		_inline CDeferredPropertySetter() = default; /* compiler_generated() */
		virtual _inline ~CDeferredPropertySetter() = default; /* compiler_generated() */ // 0x10CA67C0
		Forge::CDeferredPropertySetter &operator=(Forge::CDeferredPropertySetter &); /* compiler_generated() */
		Forge::CDeferredPropertySetter &operator=(Forge::CDeferredPropertySetter const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Forge::CDeferredPropertySetter) == 44, "Invalid Forge::CDeferredPropertySetter size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Forge
{
}

/* ---------- private code */

#endif // __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYACCESSOR_HPP__

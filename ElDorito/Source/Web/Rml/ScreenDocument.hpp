#ifndef __WEB_RML_SCREENDOCUMENT_HPP__
#define __WEB_RML_SCREENDOCUMENT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/ElementInstancer.h>
#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/EventListenerInstancer.h>
#include <RmlUi/Lua/LuaType.h>

#include <functional>
#include <string>

/* ---------- definitions */

// The Lua plugin's type specialisations live in its private headers; redeclare the ones we
// push so the templates in LuaType.inl resolve to the definitions in rmlui_lua.lib.
namespace Rml
{
	namespace Lua
	{
		RMLUI_LUATYPE_DECLARE(Element)
		RMLUI_LUATYPE_DECLARE(ElementDocument)
		RMLUI_LUATYPE_DECLARE(Event)
	}
}

namespace Web
{
	namespace RmlUi
	{
		// One screen = one document = one Lua environment.  RmlUi's own LuaDocument runs every
		// script in _G; this subclass gives each document its own _ENV (falling back to _G) so
		// the screens keep the per-iframe globals they were written with.
		class ScreenDocument final : public ::Rml::ElementDocument
		{
		public:
			RMLUI_RTTI_DeclareWithParent(ScreenDocument, ::Rml::ElementDocument)

			using EnvHook = std::function<void(ScreenDocument &document, int envRef)>;

			explicit ScreenDocument(const ::Rml::String &tag);
			~ScreenDocument() override;

			void LoadInlineScript(const ::Rml::String &content, const ::Rml::String &source_path, int source_line) override;
			void LoadExternalScript(const ::Rml::String &source_path) override;

			// Registry reference of this document's environment (created on first use).
			int GetEnvRef();
			const std::string &GetScreenId() const { return m_screenId; }

			// The id the next constructed document belongs to (documents are created inside
			// Context::LoadDocument, before the caller can name them).
			static void SetNextScreenId(const std::string &screenId);
			// Called right after an environment is created (UiRoot installs `dew` there).
			static void SetEnvCreatedHook(EnvHook hook);
			// Called before the environment is released (UiRoot drops timers, requests, subscriptions).
			static void SetEnvReleasedHook(EnvHook hook);

		private:
			std::string m_screenId;
			int m_envRef = 0;
		};

		using ScreenDocumentInstancer = ::Rml::ElementInstancerGeneric<ScreenDocument>;

		// `onclick="..."`-style attributes compiled in the owning document's environment.
		class EnvEventListenerInstancer final : public ::Rml::EventListenerInstancer
		{
		public:
			::Rml::EventListener *InstanceEventListener(const ::Rml::String &value, ::Rml::Element *element) override;
		};
	}
}

#endif // __WEB_RML_SCREENDOCUMENT_HPP__

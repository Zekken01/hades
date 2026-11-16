/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/ScreenDocument.hpp"

#include "Web/Rml/LuaState.hpp"
#include "Web/Rml/SystemInterface.hpp"

#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/Element.h>
#include <RmlUi/Core/Event.h>
#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/Log.h>
#include <RmlUi/Core/StringUtilities.h>

/* ---------- private variables */

namespace
{
	std::string g_nextScreenId;
	Web::RmlUi::ScreenDocument::EnvHook g_envCreated;
	Web::RmlUi::ScreenDocument::EnvHook g_envReleased;
}

/* ---------- private code */

namespace Web
{
	namespace RmlUi
	{
		// Attribute handler: `return function(event, element, document) <code> end`, compiled
		// with the document's environment, called with the Lua wrappers of the three objects.
		class EnvEventListener final : public ::Rml::EventListener
		{
		public:
			EnvEventListener(const ::Rml::String &code, ::Rml::Element *element) : m_code(code), m_element(element) {}

			~EnvEventListener() override
			{
				if (auto *lua = LuaState::Current())
					lua->Unref(m_functionRef);
			}

			void ProcessEvent(::Rml::Event &event) override
			{
				auto *lua = LuaState::Current();
				if (!lua)
					return;
				lua_State *L = lua->L();
				if (m_functionRef <= 0 && !m_failed)
					Compile(*lua);
				if (m_functionRef <= 0)
					return;
				const int top = lua_gettop(L);
				lua->PushRef(m_functionRef);
				::Rml::Lua::LuaType<::Rml::Event>::push(L, &event, false);
				::Rml::Lua::LuaType<::Rml::Element>::push(L, m_element, false);
				::Rml::Lua::LuaType<::Rml::ElementDocument>::push(L, m_element->GetOwnerDocument(), false);
				lua->PCall(3, 0);
				lua_settop(L, top);
			}

			void OnDetach(::Rml::Element *) override
			{
				delete this;
			}

		private:
			void Compile(LuaState &lua)
			{
				lua_State *L = lua.L();
				int envRef = 0;
				std::string name = "=inline handler";
				if (auto *document = rmlui_dynamic_cast<ScreenDocument *>(m_element->GetOwnerDocument()))
				{
					envRef = document->GetEnvRef();
					name = "=" + document->GetSourceURL() + " on" + m_element->GetTagName();
				}
				const std::string wrapped = "return function(event, element, document) " + m_code + " end";
				const int top = lua_gettop(L);
				if (lua.LoadChunk(wrapped.c_str(), wrapped.size(), name, envRef) && lua.PCall(0, 1) && lua_isfunction(L, -1))
					m_functionRef = lua.Ref(-1);
				else
					m_failed = true;
				lua_settop(L, top);
			}

			std::string m_code;
			::Rml::Element *m_element;
			int m_functionRef = 0;
			bool m_failed = false;
		};

		/* ScreenDocument */

		RMLUI_RTTI_Define(ScreenDocument)

		ScreenDocument::ScreenDocument(const ::Rml::String &tag) : ::Rml::ElementDocument(tag)
		{
			m_screenId = g_nextScreenId;
			g_nextScreenId.clear();
		}

		ScreenDocument::~ScreenDocument()
		{
			if (m_envRef > 0)
			{
				if (g_envReleased)
					g_envReleased(*this, m_envRef);
				if (auto *lua = LuaState::Current())
					lua->ReleaseEnv(m_envRef);
			}
		}

		void ScreenDocument::SetNextScreenId(const std::string &screenId)
		{
			g_nextScreenId = screenId;
		}

		void ScreenDocument::SetEnvCreatedHook(EnvHook hook)
		{
			g_envCreated = std::move(hook);
		}

		void ScreenDocument::SetEnvReleasedHook(EnvHook hook)
		{
			g_envReleased = std::move(hook);
		}

		int ScreenDocument::GetEnvRef()
		{
			if (m_envRef > 0)
				return m_envRef;
			auto *lua = LuaState::Current();
			if (!lua)
				return 0;
			lua_State *L = lua->L();
			m_envRef = lua->CreateEnv();
			lua->PushEnv(m_envRef);
			::Rml::Lua::LuaType<::Rml::ElementDocument>::push(L, this, false);
			lua_setfield(L, -2, "document");
			lua_pushstring(L, m_screenId.c_str());
			lua_setfield(L, -2, "screenId");
			lua_pop(L, 1);
			if (g_envCreated)
				g_envCreated(*this, m_envRef);
			return m_envRef;
		}

		void ScreenDocument::LoadInlineScript(const ::Rml::String &content, const ::Rml::String &source_path, int source_line)
		{
			auto *lua = LuaState::Current();
			if (!lua)
				return;
			// Pad with newlines so Lua's line numbers match the .rml file.
			std::string code(std::max(source_line - 1, 0), '\n');
			code += content;
			lua->RunChunk(code.c_str(), code.size(), "@" + SystemInterface::NormalizePath(source_path), GetEnvRef());
		}

		void ScreenDocument::LoadExternalScript(const ::Rml::String &source_path)
		{
			auto *lua = LuaState::Current();
			if (!lua)
				return;
			::Rml::String code;
			if (!::Rml::GetFileInterface()->LoadFile(source_path, code))
			{
				::Rml::Log::Message(::Rml::Log::LT_WARNING, "Unable to open script \"%s\"", source_path.c_str());
				return;
			}
			lua->RunChunk(code.c_str(), code.size(), "@" + SystemInterface::NormalizePath(source_path), GetEnvRef());
		}

		/* EnvEventListenerInstancer */

		::Rml::EventListener *EnvEventListenerInstancer::InstanceEventListener(const ::Rml::String &value, ::Rml::Element *element)
		{
			return new EnvEventListener(value, element);
		}
	}
}

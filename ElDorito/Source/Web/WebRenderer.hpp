#ifndef __WEB_WEBRENDERER_HPP__
#define __WEB_WEBRENDERER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <d3d9.h>

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Rml
{
	class Context;
}

namespace Web
{
	namespace Browser
	{
		class WebRenderer;
		namespace Bridge
		{
			class WebRendererQueryHandler;
		}
	}
	namespace RmlUi
	{
		class AsyncTextures;
		class FileInterface;
		class LuaState;
		class RenderInterfaceD3D9;
		class SystemInterface;
		class UiRoot;
		class EnvEventListenerInstancer;
	}
}

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		// The UI host.  Keeps the name and lifecycle API the CEF-based renderer had so the
		// device hooks and screen code keep their call sites, but draws with RmlUi.
		class WebRenderer
		{
		public:
			WebRenderer();
			~WebRenderer();
			static std::shared_ptr<Web::Browser::WebRenderer> GetInstance();
			// For tools that host the UI outside the game (the window resolution global is game memory).
			static void OverrideWindowResolution(int width, int height);

			// Device hooks (Patches/DirectXHook.cpp)
			bool InitRenderer(IDirect3DDevice9 *device);
			bool Init(std::string const &url, bool debugEnable);
			bool Render(IDirect3DDevice9 *device);
			bool PreReset();
			bool PostReset();
			bool Shutdown();

			// Per game tick (Web::Ui::ScreenLayer::Tick)
			bool Update();
			bool Initialized();
			bool IsRendering();
			bool ShowRenderer(bool show, bool overlay);
			bool Resize(unsigned __int32 width, unsigned __int32 height);
			bool Reload();
			void ToggleDebugger();

			bool SetState(Web::Browser::RendererState p_State);
			Web::Browser::RendererState GetState();
			std::string GetUIDirectory();

			Web::Browser::Bridge::WebRendererQueryHandler *GetQueryHandler() const { return m_QueryHandler.get(); }
			Web::RmlUi::UiRoot *GetUiRoot() const { return m_UiRoot.get(); }
			::Rml::Context *GetContext() const { return m_Context; }

		private:
			void LoadFonts();
			double Now() const;

			Web::Browser::RendererState m_State = Web::Browser::RendererState_Disabled;
			std::unique_ptr<Web::RmlUi::RenderInterfaceD3D9> m_RenderInterface;
			std::unique_ptr<Web::RmlUi::SystemInterface> m_SystemInterface;
			std::unique_ptr<Web::RmlUi::FileInterface> m_FileInterface;
			std::unique_ptr<Web::RmlUi::AsyncTextures> m_AsyncTextures;
			std::unique_ptr<Web::RmlUi::LuaState> m_Lua;
			std::unique_ptr<Web::RmlUi::UiRoot> m_UiRoot;
			std::unique_ptr<Web::RmlUi::EnvEventListenerInstancer> m_ListenerInstancer;
			std::unique_ptr<Web::Browser::Bridge::WebRendererQueryHandler> m_QueryHandler;
			void *m_DocumentInstancer = nullptr;
			::Rml::Context *m_Context = nullptr;
			bool m_RmlInitialised = false;
			bool m_Debugging = false;
			unsigned __int32 m_Width = 0;
			unsigned __int32 m_Height = 0;
			unsigned long m_RenderThread = 0;
		};
	}
}

/* ---------- prototypes */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			// Web/Bridge/Client/RegisterClientFunctions.cpp
			extern void RegisterClientFunctions(Web::Browser::Bridge::WebRendererQueryHandler &handler);
		}
	}
}

#endif // __WEB_WEBRENDERER_HPP__

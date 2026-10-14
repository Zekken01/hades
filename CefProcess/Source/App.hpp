#ifndef __APP_HPP__
#define __APP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class App;
class CefProcessMessage;

/* ---------- constants */

/* ---------- definitions */

class App :
	public CefApp,
	public CefRenderProcessHandler,
	public virtual CefBaseRefCounted
{
private:
	scoped_refptr<CefMessageRouterRendererSide> router; // 0x10
	CefRefCount ref_count_; // 0x14
public:
	App();
	virtual void OnRegisterCustomSchemes(CefSchemeRegistrar *);
	virtual scoped_refptr<CefRenderProcessHandler> GetRenderProcessHandler();
	virtual void OnContextCreated(scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>);
	virtual void OnContextReleased(scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>);
	virtual bool OnProcessMessageReceived(scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>);
	virtual _inline void AddRef() const;
	virtual _inline bool Release() const;
	virtual _inline bool HasOneRef() const;
	virtual _inline bool HasAtLeastOneRef() const;
	virtual _inline ~App(); /* compiler_generated() */
};
static_assert(sizeof(App) == 32, "Invalid App size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline void App::AddRef() const // 0x427DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@App@@UBEXXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	// App const *const this; // r18

	ref_count_.AddRef();
}

_inline bool App::HasAtLeastOneRef() const // 0x427FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	// App const *const this; // r18

	return ref_count_.HasAtLeastOneRef();
}

_inline bool App::HasOneRef() const // 0x428000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	// App const *const this; // r18

	return ref_count_.HasOneRef();
}

_inline bool App::Release() const // 0x428790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Release@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	// App const *const this; // r18
	// function call : void *(unsigned __int32)

	if (ref_count_.Release())
	{
		delete static_cast<App const *>(this);
		return true;
	}
	return false;
}

/* ---------- private code */

#endif // __APP_HPP__

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

_extern void _sub_427DD0(CefBaseRefCounted * const);
_inline void App::AddRef() const // 0x427DD0
{
	mangled_x86(MANGLED_TODO, "?AddRef@App@@UBEXXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	/* function callee list:
Pointer(
	PointerType {
		underlying_type: TypeIndex(0x1323),
		attributes: PointerAttributes(
			32778,
		),
		containing_class: None,
	},
) */
	// App const *const this; // r18
	todo("implement");
	_sub_427DD0((CefBaseRefCounted *)this);
}

_extern bool _sub_427FD0(CefBaseRefCounted * const);
_inline bool App::HasAtLeastOneRef() const // 0x427FD0
{
	mangled_x86(MANGLED_TODO, "?HasAtLeastOneRef@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2571,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x1330),
		this_adjustment: 0,
	},
) */
	// App const *const this; // r18
	todo("implement");
	bool __result = _sub_427FD0((CefBaseRefCounted *)this);
	return __result;
}

_extern bool _sub_428000(CefBaseRefCounted * const);
_inline bool App::HasOneRef() const // 0x428000
{
	mangled_x86(MANGLED_TODO, "?HasOneRef@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	/* function callee list:
Pointer(
	PointerType {
		underlying_type: TypeIndex(0x1332),
		attributes: PointerAttributes(
			32810,
		),
		containing_class: None,
	},
) */
	// App const *const this; // r18
	todo("implement");
	bool __result = _sub_428000((CefBaseRefCounted *)this);
	return __result;
}

_extern bool _sub_428790(CefBaseRefCounted * const);
_inline bool App::Release() const // 0x428790
{
	mangled_x86(MANGLED_TODO, "?Release@App@@UBE_NXZ");
	// __shifted(App, 28);
	// App const *const this; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: None,
		attributes: FunctionAttributes(
			0,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x1336),
		this_adjustment: 0,
	},
) */
	// App const *const this; // r18
	// function call : void *(unsigned __int32)
	todo("implement");
	bool __result = _sub_428790((CefBaseRefCounted *)this);
	return __result;
}

/* ---------- private code */

#endif // __APP_HPP__

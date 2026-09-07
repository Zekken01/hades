/* ---------- headers */

#include "App.hpp"
#include "hades/hades.h"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_app.h>
#include <cef_audio_handler.h>
#include <cef_base.h>
#include <cef_browser_process_handler.h>
#include <cef_client.h>
#include <cef_command_handler.h>
#include <cef_context_menu_handler.h>
#include <cef_devtools_message_observer.h>
#include <cef_dialog_handler.h>
#include <cef_display_handler.h>
#include <cef_download_handler.h>
#include <cef_drag_handler.h>
#include <cef_extension_handler.h>
#include <cef_find_handler.h>
#include <cef_focus_handler.h>
#include <cef_frame_handler.h>
#include <cef_jsdialog_handler.h>
#include <cef_keyboard_handler.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_menu_model_delegate.h>
#include <cef_print_handler.h>
#include <cef_render_handler.h>
#include <cef_render_process_handler.h>
#include <cef_request_handler.h>
#include <cef_resource_handler.h>
#include <cef_resource_request_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_message_router.h>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class App;
class CefProcessMessage;
struct CefStringTraitsUTF16;

namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern App* _sub_426AF0(App *const);
App::App() // 0x426AF0
{
	mangled_x86(MANGLED_TODO, "??0App@@QAE@XZ");
	// App *const this; // local
	// CefMessageRouterConfig config; // local
	/* function callee list:
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
)
MethodList(
	MethodList {
		methods: [
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e8),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12e9),
				vtable_offset: None,
			},
			MethodListEntry {
				attributes: FieldAttributes(
					3,
				),
				method_type: TypeIndex(0x12ea),
				vtable_offset: None,
			},
		],
	},
) */
	// App *const this; // r18
	// CefMessageRouterConfig config;
	todo("implement");
	_sub_426AF0(this);
}

_extern void _sub_427690(App * const);
_inline App::~App() // 0x427690
{
	mangled_x86(MANGLED_TODO, "??1App@@UAE@XZ");
	// __shifted(App, 28);
	// App *const this; // local
	// App *const this; // r18
	compiler_generated();
	todo("implement");
	_sub_427690(this);
}

extern scoped_refptr<CefRenderProcessHandler> _sub_427F50(App *const);
scoped_refptr<CefRenderProcessHandler> App::GetRenderProcessHandler() // 0x427F50
{
	mangled_x86(MANGLED_TODO, "?GetRenderProcessHandler@App@@UAE?AV?$scoped_refptr@VCefRenderProcessHandler@@@@XZ");
	// App *const this; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			523,
		),
		parameter_count: 2,
		argument_list: TypeIndex(0x132d),
		this_adjustment: 0,
	},
) */
	// App *const this; // r18
	todo("implement");
	scoped_refptr<CefRenderProcessHandler> __result = _sub_427F50(this);
	return __result;
}

_extern void _sub_428420(App *const, CefSchemeRegistrar *);
void App::OnRegisterCustomSchemes(CefSchemeRegistrar * __formal1) // 0x428420
{
	mangled_x86(MANGLED_TODO, "?OnRegisterCustomSchemes@App@@UAEXPAVCefSchemeRegistrar@@@Z");
	// CefSchemeRegistrar *registrar; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x1340),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			11,
		),
		parameter_count: 1,
		argument_list: TypeIndex(0x112c),
		this_adjustment: 0,
	},
) */
	// App *const this; // r18
	// CefSchemeRegistrar *registrar;
	// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
	// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
	// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
	todo("implement");
	_sub_428420(this, __formal1);
}

_extern void _sub_4280E0(CefRenderProcessHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>);
void App::OnContextCreated(scoped_refptr<CefBrowser> __formal1, scoped_refptr<CefFrame> __formal2, scoped_refptr<CefV8Context> __formal3) // 0x4280E0
{
	mangled_x86(MANGLED_TODO, "?OnContextCreated@App@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefV8Context@@@@@Z");
	// __shifted(App, 8);
	// scoped_refptr<CefV8Context> context; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
) */
	// App *const this; // r18
	// scoped_refptr<CefBrowser> browser;
	// scoped_refptr<CefFrame> frame;
	// scoped_refptr<CefV8Context> context;
	// function call : void (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>)
	todo("implement");
	_sub_4280E0((CefRenderProcessHandler *)this, __formal1, __formal2, __formal3);
}

_extern void _sub_4281E0(CefRenderProcessHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>);
void App::OnContextReleased(scoped_refptr<CefBrowser> __formal1, scoped_refptr<CefFrame> __formal2, scoped_refptr<CefV8Context> __formal3) // 0x4281E0
{
	mangled_x86(MANGLED_TODO, "?OnContextReleased@App@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefV8Context@@@@@Z");
	// __shifted(App, 8);
	// scoped_refptr<CefV8Context> context; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
) */
	// App *const this; // r18
	// scoped_refptr<CefBrowser> browser;
	// scoped_refptr<CefFrame> frame;
	// scoped_refptr<CefV8Context> context;
	// function call : void (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>)
	todo("implement");
	_sub_4281E0((CefRenderProcessHandler *)this, __formal1, __formal2, __formal3);
}

_extern bool _sub_428310(CefRenderProcessHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>);
bool App::OnProcessMessageReceived(scoped_refptr<CefBrowser> __formal1, scoped_refptr<CefFrame> __formal2, cef_process_id_t __formal3, scoped_refptr<CefProcessMessage> __formal4) // 0x428310
{
	mangled_x86(MANGLED_TODO, "?OnProcessMessageReceived@App@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@W4cef_process_id_t@@V?$scoped_refptr@VCefProcessMessage@@@@@Z");
	// __shifted(App, 8);
	// scoped_refptr<CefProcessMessage> message; // local
	/* function callee list:
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
)
MemberFunction(
	MemberFunctionType {
		return_type: TypeIndex(0x3),
		class_type: TypeIndex(0x132a),
		this_pointer_type: Some(
			TypeIndex(0x132b),
		),
		attributes: FunctionAttributes(
			2059,
		),
		parameter_count: 0,
		argument_list: TypeIndex(0x102a),
		this_adjustment: 0,
	},
) */
	// App *const this; // r18
	// scoped_refptr<CefBrowser> browser;
	// scoped_refptr<CefFrame> frame;
	// cef_process_id_t source_process;
	// scoped_refptr<CefProcessMessage> message;
	// function call : bool (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>)
	todo("implement");
	bool __result = _sub_428310((CefRenderProcessHandler *)this, __formal1, __formal2, __formal3, __formal4);
	return __result;
}

/* ---------- private code */

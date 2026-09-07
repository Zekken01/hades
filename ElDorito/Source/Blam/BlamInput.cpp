/* ---------- headers */

#include "Blam/BlamInput.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleInput.hpp"
#include "Utils/Macros.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <type_traits>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
		enum GameAction : unsigned char;
		enum InputType : unsigned __int32;
		enum KeyCode : unsigned short;
		struct ActionState;
		struct BindingsTable;
		struct KeyEvent;
		struct KeyState;
		struct PlayerInputState;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Blam
{
	namespace Input
	{
		extern unsigned char GetKeyTicks(Blam::Input::KeyCode key, Blam::Input::InputType type);
		extern unsigned short GetKeyMs(Blam::Input::KeyCode key, Blam::Input::InputType type);
		extern Blam::Input::KeyState *GetKeyState(Blam::Input::KeyCode key);
		extern unsigned char GetMouseButtonTicks(Blam::Input::MouseButton button, Blam::Input::InputType type);
		extern bool ReadKeyEvent(Blam::Input::KeyEvent *result, Blam::Input::InputType type);
		extern void BlockInput(Blam::Input::InputType type, bool block);
		extern bool GetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable *result);
		extern bool InputIsBlocked(Blam::Input::InputType type);
		extern bool SetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable const &newBindings);
		extern void PostUiAction(__int32 localPlayerIndex, Blam::Input::GameAction action);
		extern __int32 GetVirtualKey(Blam::Input::KeyCode kc);
		extern __int32 GetDirectInputKey(Blam::Input::KeyCode kc);
		extern char const *GetKeyCodeName(Blam::Input::KeyCode kc);
		extern Blam::Input::ActionState *GetActionState(Blam::Input::GameAction action);
		extern Blam::Input::PlayerInputState *GetPlayerInputState(__int32 localPlayerIndex);
	}
}

/* ---------- globals */

namespace Blam
{
	namespace Input
	{
		extern __int32 WinKeyCode[111]; // 0x113534D0
		extern unsigned char DIKeyCode[104]; // 0x11353690
		extern char const *KeyCodeNames[109]; // 0x113536F8
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	namespace Input
	{
		_extern unsigned char _sub_1092AA40(Blam::Input::KeyCode, Blam::Input::InputType);
		unsigned char GetKeyTicks(Blam::Input::KeyCode key, Blam::Input::InputType type) // 0x1092AA40
		{
			mangled_x86(MANGLED_TODO, "?GetKeyTicks@Input@Blam@@YAEW4KeyCode@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetKeyTicks)(Blam::Input::KeyCode, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::KeyCode, Blam::Input::InputType)
			todo("implement");
			unsigned char __result = _sub_1092AA40(key, type);
			return __result;
		}

		_extern unsigned short _sub_1092A980(Blam::Input::KeyCode, Blam::Input::InputType);
		unsigned short GetKeyMs(Blam::Input::KeyCode key, Blam::Input::InputType type) // 0x1092A980
		{
			mangled_x86(MANGLED_TODO, "?GetKeyMs@Input@Blam@@YAGW4KeyCode@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetKeyMs)(Blam::Input::KeyCode, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::KeyCode, Blam::Input::InputType)
			todo("implement");
			unsigned short __result = _sub_1092A980(key, type);
			return __result;
		}

		extern KeyState *_sub_1092AA00(Blam::Input::KeyCode);
		Blam::Input::KeyState *GetKeyState(Blam::Input::KeyCode key) // 0x1092AA00
		{
			mangled_x86(MANGLED_TODO, "?GetKeyState@Input@Blam@@YAPAUKeyState@12@W4KeyCode@12@@Z");
			// Blam::Input::KeyCode key;
			todo("implement");
			Blam::Input::KeyState * __result = _sub_1092AA00(key);
			return __result;
		}

		_extern unsigned char _sub_1092AAB0(Blam::Input::MouseButton, Blam::Input::InputType);
		unsigned char GetMouseButtonTicks(Blam::Input::MouseButton button, Blam::Input::InputType type) // 0x1092AAB0
		{
			mangled_x86(MANGLED_TODO, "?GetMouseButtonTicks@Input@Blam@@YAEW4MouseButton@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetMousButtonTicks)(Blam::Input::MouseButton, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::MouseButton, Blam::Input::InputType)
			todo("implement");
			unsigned char __result = _sub_1092AAB0(button, type);
			return __result;
		}

		_extern bool _sub_1092AC20(Blam::Input::KeyEvent *, Blam::Input::InputType);
		bool ReadKeyEvent(Blam::Input::KeyEvent *result, Blam::Input::InputType type) // 0x1092AC20
		{
			mangled_x86(MANGLED_TODO, "?ReadKeyEvent@Input@Blam@@YA_NPAUKeyEvent@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// bool (*EngineReadKeyEvent)(Blam::Input::KeyEvent *, Blam::Input::InputType);
			// function call : bool (*)(Blam::Input::KeyEvent *, Blam::Input::InputType)
			todo("implement");
			bool __result = _sub_1092AC20(result, type);
			return __result;
		}

		_extern void _sub_1092A7A0(Blam::Input::InputType, bool);
		void BlockInput(Blam::Input::InputType type, bool block) // 0x1092A7A0
		{
			mangled_x86(MANGLED_TODO, "?BlockInput@Input@Blam@@YAXW4InputType@12@_N@Z");
			// bool block;
			// unsigned char (*EngineBlockInput)(Blam::Input::InputType, bool);
			// function call : unsigned char (*)(Blam::Input::InputType, bool)
			todo("implement");
			_sub_1092A7A0(type, block);
		}

		_extern bool _sub_1092A890(__int32, Blam::Input::BindingsTable *);
		bool GetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable *result) // 0x1092A890
		{
			mangled_x86(MANGLED_TODO, "?GetBindings@Input@Blam@@YA_NHPAUBindingsTable@12@@Z");
			// Blam::Input::BindingsTable *result;
			// void (*EngineGetBindings)(__int32, Blam::Input::BindingsTable *);
			// function call : void (*)(__int32, Blam::Input::BindingsTable *)
			todo("implement");
			bool __result = _sub_1092A890(localPlayerIndex, result);
			return __result;
		}

		_extern bool _sub_1092AB80(Blam::Input::InputType);
		bool InputIsBlocked(Blam::Input::InputType type) // 0x1092AB80
		{
			mangled_x86(MANGLED_TODO, "?InputIsBlocked@Input@Blam@@YA_NW4InputType@12@@Z");
			// Blam::Input::InputType type;
			todo("implement");
			bool __result = _sub_1092AB80(type);
			return __result;
		}

		_extern bool _sub_1092ACC0(__int32, Blam::Input::BindingsTable const &);
		bool SetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable const &newBindings) // 0x1092ACC0
		{
			mangled_x86(MANGLED_TODO, "?SetBindings@Input@Blam@@YA_NHABUBindingsTable@12@@Z");
			// Blam::Input::BindingsTable const &newBindings;
			// void (*EngineSetBindings)(__int32, Blam::Input::BindingsTable const &);
			// function call : void (*)(__int32, Blam::Input::BindingsTable const &)
			todo("implement");
			bool __result = _sub_1092ACC0(localPlayerIndex, newBindings);
			return __result;
		}

		_extern void _sub_1092ABB0(__int32, Blam::Input::GameAction);
		void PostUiAction(__int32 localPlayerIndex, Blam::Input::GameAction action) // 0x1092ABB0
		{
			mangled_x86(MANGLED_TODO, "?PostUiAction@Input@Blam@@YAXHW4GameAction@12@@Z");
			// Blam::Input::GameAction action;
			// void (*const EnginePostUiAction)(__int32, char);
			// function call : void (*const)(__int32, char)
			todo("implement");
			_sub_1092ABB0(localPlayerIndex, action);
		}

		_extern __int32 _sub_1092AB50(Blam::Input::KeyCode);
		__int32 GetVirtualKey(Blam::Input::KeyCode kc) // 0x1092AB50
		{
			mangled_x86(MANGLED_TODO, "?GetVirtualKey@Input@Blam@@YAHW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;
			todo("implement");
			__int32 __result = _sub_1092AB50(kc);
			return __result;
		}

		_extern __int32 _sub_1092A920(Blam::Input::KeyCode);
		__int32 GetDirectInputKey(Blam::Input::KeyCode kc) // 0x1092A920
		{
			mangled_x86(MANGLED_TODO, "?GetDirectInputKey@Input@Blam@@YAHW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;
			todo("implement");
			__int32 __result = _sub_1092A920(kc);
			return __result;
		}
	}
}

extern char const *_sub_1092A950(Blam::Input::KeyCode);
namespace Blam
{
	namespace Input
	{
		char const *GetKeyCodeName(Blam::Input::KeyCode kc) // 0x1092A950
		{
			mangled_x86(MANGLED_TODO, "?GetKeyCodeName@Input@Blam@@YAPBDW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;
			todo("implement");
			char const * __result = _sub_1092A950(kc);
			return __result;
		}

		extern ActionState *_sub_1092A840(Blam::Input::GameAction);
		Blam::Input::ActionState *GetActionState(Blam::Input::GameAction action) // 0x1092A840
		{
			mangled_x86(MANGLED_TODO, "?GetActionState@Input@Blam@@YAPAUActionState@12@W4GameAction@12@@Z");
			// Blam::Input::GameAction action;
			// Blam::Input::ActionState *actions;
			todo("implement");
			Blam::Input::ActionState * __result = _sub_1092A840(action);
			return __result;
		}

		extern PlayerInputState *_sub_1092AB20(__int32);
		Blam::Input::PlayerInputState *GetPlayerInputState(__int32 localPlayerIndex) // 0x1092AB20
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerInputState@Input@Blam@@YAPAUPlayerInputState@12@H@Z");
			// __int32 localPlayerIndex;
			todo("implement");
			Blam::Input::PlayerInputState * __result = _sub_1092AB20(localPlayerIndex);
			return __result;
		}

		extern VirtualKeyboard* _sub_1092A660(Blam::Input::VirtualKeyboard *const, char const *, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32);
		VirtualKeyboard::VirtualKeyboard(char const *file, __int32 line, __int32 arg2, __int32 arg3, __int32 arg4, __int32 arg5, __int32 maxLength, __int32 arg7, __int32 arg8) // 0x1092A660
		{
			mangled_x86(MANGLED_TODO, "??0VirtualKeyboard@Input@Blam@@QAE@PBDHHHHHHHH@Z");
			// __int32 arg8;
			todo("implement");
			_sub_1092A660(this, file, line, arg2, arg3, arg4, arg5, maxLength, arg7, arg8);
		}

		_extern __int32 _sub_1092AFC0(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub0() // 0x1092AFC0
		{
			mangled_x86(MANGLED_TODO, "?Stub0@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092AFC0(this);
			return __result;
		}

		_extern __int32 _sub_1092B060(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub4() // 0x1092B060
		{
			mangled_x86(MANGLED_TODO, "?Stub4@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B060(this);
			return __result;
		}

		_extern __int32 _sub_1092B080(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub8() // 0x1092B080
		{
			mangled_x86(MANGLED_TODO, "?Stub8@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B080(this);
			return __result;
		}

		_extern __int32 _sub_1092B0A0(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::StubC() // 0x1092B0A0
		{
			mangled_x86(MANGLED_TODO, "?StubC@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B0A0(this);
			return __result;
		}

		_extern __int32 _sub_1092AFE0(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub10() // 0x1092AFE0
		{
			mangled_x86(MANGLED_TODO, "?Stub10@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092AFE0(this);
			return __result;
		}

		_extern __int32 _sub_1092B000(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub14() // 0x1092B000
		{
			mangled_x86(MANGLED_TODO, "?Stub14@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B000(this);
			return __result;
		}

		_extern __int32 _sub_1092B020(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub18() // 0x1092B020
		{
			mangled_x86(MANGLED_TODO, "?Stub18@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B020(this);
			return __result;
		}

		_extern void _sub_1092AC90(Blam::Input::VirtualKeyboard *const);
		void VirtualKeyboard::Reset() // 0x1092AC90
		{
			mangled_x86(MANGLED_TODO, "?Reset@VirtualKeyboard@Input@Blam@@UAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			_sub_1092AC90(this);
		}

		_extern __int32 _sub_1092B040(Blam::Input::VirtualKeyboard *const);
		__int32 VirtualKeyboard::Stub20() // 0x1092B040
		{
			mangled_x86(MANGLED_TODO, "?Stub20@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			__int32 __result = _sub_1092B040(this);
			return __result;
		}

		_extern void _sub_1092AE70(Blam::Input::VirtualKeyboard *const, wchar_t const *);
		void VirtualKeyboard::SetTitle(wchar_t const *newTitle) // 0x1092AE70
		{
			mangled_x86(MANGLED_TODO, "?SetTitle@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newTitle;
			// unsigned __int32 const TitleLength;
			todo("implement");
			_sub_1092AE70(this, newTitle);
		}

		_extern void _sub_1092ADE0(Blam::Input::VirtualKeyboard *const, wchar_t const *);
		void VirtualKeyboard::SetDescription(wchar_t const *newDescription) // 0x1092ADE0
		{
			mangled_x86(MANGLED_TODO, "?SetDescription@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newDescription;
			// unsigned __int32 const DescriptionLength;
			todo("implement");
			_sub_1092ADE0(this, newDescription);
		}

		_extern void _sub_1092AF00(Blam::Input::VirtualKeyboard *const, wchar_t const *);
		void VirtualKeyboard::SetValue(wchar_t const *newValue) // 0x1092AF00
		{
			mangled_x86(MANGLED_TODO, "?SetValue@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newValue;
			// unsigned __int32 const ValueLength;
			todo("implement");
			_sub_1092AF00(this, newValue);
		}

		_extern void _sub_1092AD50(Blam::Input::VirtualKeyboard *const, wchar_t const *);
		void VirtualKeyboard::SetDefaultValue(wchar_t const *newDefaultValue) // 0x1092AD50
		{
			mangled_x86(MANGLED_TODO, "?SetDefaultValue@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newDefaultValue;
			// unsigned __int32 const DefaultValueLength;
			todo("implement");
			_sub_1092AD50(this, newDefaultValue);
		}

		_extern void _sub_1092AF90(Blam::Input::VirtualKeyboard *const);
		void VirtualKeyboard::Start() // 0x1092AF90
		{
			mangled_x86(MANGLED_TODO, "?Start@VirtualKeyboard@Input@Blam@@QAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			_sub_1092AF90(this);
		}

		_extern void _sub_1092A810(Blam::Input::VirtualKeyboard *const);
		void VirtualKeyboard::Finish() // 0x1092A810
		{
			mangled_x86(MANGLED_TODO, "?Finish@VirtualKeyboard@Input@Blam@@QAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;
			todo("implement");
			_sub_1092A810(this);
		}
	}
}

/* ---------- private code */

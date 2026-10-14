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
		unsigned char GetKeyTicks(Blam::Input::KeyCode key, Blam::Input::InputType type) // 0x1092AA40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetKeyTicks@Input@Blam@@YAEW4KeyCode@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetKeyTicks)(Blam::Input::KeyCode, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::KeyCode, Blam::Input::InputType)

			unsigned char (__cdecl *GetKeyTicksImpl)(Blam::Input::KeyCode, Blam::Input::InputType) = (unsigned char(__cdecl *)(Blam::Input::KeyCode, Blam::Input::InputType))0x511b60;

			return GetKeyTicksImpl(key, type);
		}

		unsigned short GetKeyMs(Blam::Input::KeyCode key, Blam::Input::InputType type) // 0x1092A980
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetKeyMs@Input@Blam@@YAGW4KeyCode@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetKeyMs)(Blam::Input::KeyCode, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::KeyCode, Blam::Input::InputType)

			unsigned char (__cdecl *EngineGetKeyMs)(Blam::Input::KeyCode, Blam::Input::InputType) = (unsigned char(__cdecl *)(Blam::Input::KeyCode, Blam::Input::InputType))0x511ce0;

			return EngineGetKeyMs(key, type);
		}

		Blam::Input::KeyState *GetKeyState(Blam::Input::KeyCode key) // 0x1092AA00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetKeyState@Input@Blam@@YAPAUKeyState@12@W4KeyCode@12@@Z");
			// Blam::Input::KeyCode key;

			if (key < 0 || key >= eKeyCodeUnused68)
			{
				return nullptr;
			}

			return &((Blam::Input::KeyState *)0x238DBF4)[key];
		}

		unsigned char GetMouseButtonTicks(Blam::Input::MouseButton button, Blam::Input::InputType type) // 0x1092AAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetMouseButtonTicks@Input@Blam@@YAEW4MouseButton@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// unsigned char (*EngineGetMousButtonTicks)(Blam::Input::MouseButton, Blam::Input::InputType);
			// function call : unsigned char (*)(Blam::Input::MouseButton, Blam::Input::InputType)

			unsigned char (__cdecl *GetMouseButtonTicksImpl)(unsigned char, Blam::Input::InputType) = (unsigned char(__cdecl *)(unsigned char, Blam::Input::InputType))0x511df0;

			return (*GetMouseButtonTicksImpl)((unsigned char)button, type);
		}

		bool ReadKeyEvent(Blam::Input::KeyEvent *result, Blam::Input::InputType type) // 0x1092AC20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadKeyEvent@Input@Blam@@YA_NPAUKeyEvent@12@W4InputType@12@@Z");
			// Blam::Input::InputType type;
			// bool (*EngineReadKeyEvent)(Blam::Input::KeyEvent *, Blam::Input::InputType);
			// function call : bool (*)(Blam::Input::KeyEvent *, Blam::Input::InputType)

			bool (__cdecl *ReadKeyEventImpl)(Blam::Input::KeyEvent *, Blam::Input::InputType) = (bool(__cdecl *)(Blam::Input::KeyEvent *, Blam::Input::InputType))0x5118c0;

			return ReadKeyEventImpl(result, type);
		}

		void BlockInput(Blam::Input::InputType type, bool block) // 0x1092A7A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BlockInput@Input@Blam@@YAXW4InputType@12@_N@Z");
			// bool block;
			// unsigned char (*EngineBlockInput)(Blam::Input::InputType, bool);
			// function call : unsigned char (*)(Blam::Input::InputType, bool)

			void (__cdecl *BlockInputImpl)(Blam::Input::InputType, bool) = (void(__cdecl *)(Blam::Input::InputType, bool))0x512530;

			BlockInputImpl(type, block);
		}

		bool GetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable *result) // 0x1092A890
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetBindings@Input@Blam@@YA_NHPAUBindingsTable@12@@Z");
			// Blam::Input::BindingsTable *result;
			// void (*EngineGetBindings)(__int32, Blam::Input::BindingsTable *);
			// function call : void (*)(__int32, Blam::Input::BindingsTable *)

			if (localPlayerIndex < 0 || localPlayerIndex >= 4)
			{
				return false;
			}

			void (__cdecl *GetBindingsImpl)(__int32, Blam::Input::BindingsTable *) = (void(__cdecl *)(__int32, Blam::Input::BindingsTable *))0x60be70;

			GetBindingsImpl(localPlayerIndex, result);
			return true;
		}

		bool InputIsBlocked(Blam::Input::InputType type) // 0x1092AB80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InputIsBlocked@Input@Blam@@YA_NW4InputType@12@@Z");
			// Blam::Input::InputType type;

			return *(bool *)(0x238DBEB + type);
		}

		bool SetBindings(__int32 localPlayerIndex, Blam::Input::BindingsTable const &newBindings) // 0x1092ACC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetBindings@Input@Blam@@YA_NHABUBindingsTable@12@@Z");
			// Blam::Input::BindingsTable const &newBindings;
			// void (*EngineSetBindings)(__int32, Blam::Input::BindingsTable const &);
			// function call : void (*)(__int32, Blam::Input::BindingsTable const &)

			if (localPlayerIndex < 0 || localPlayerIndex >= 4)
				return false;

			void (__cdecl *SetBindingsImpl)(__int32, Blam::Input::BindingsTable const &) = (void(__cdecl *)(__int32, Blam::Input::BindingsTable const &))0x60d830;

			SetBindingsImpl(localPlayerIndex, newBindings);
			return true;
		}

		void PostUiAction(__int32 localPlayerIndex, Blam::Input::GameAction action) // 0x1092ABB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PostUiAction@Input@Blam@@YAXHW4GameAction@12@@Z");
			// Blam::Input::GameAction action;
			// void (*const EnginePostUiAction)(__int32, char);
			// function call : void (*const)(__int32, char)

			void (__cdecl *const F)(__int32, Blam::Input::GameAction) = (void(__cdecl *const)(__int32, Blam::Input::GameAction))0xa935c0;

			F(localPlayerIndex, action);
		}

		__int32 GetVirtualKey(Blam::Input::KeyCode kc) // 0x1092AB50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetVirtualKey@Input@Blam@@YAHW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;

			return WinKeyCode[kc];
		}

		__int32 GetDirectInputKey(Blam::Input::KeyCode kc) // 0x1092A920
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetDirectInputKey@Input@Blam@@YAHW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;

			return DIKeyCode[kc];
		}
	}
}


namespace Blam
{
	namespace Input
	{
		char const *GetKeyCodeName(Blam::Input::KeyCode kc) // 0x1092A950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetKeyCodeName@Input@Blam@@YAPBDW4KeyCode@12@@Z");
			// Blam::Input::KeyCode kc;

			return KeyCodeNames[kc];
		}

		Blam::Input::ActionState *GetActionState(Blam::Input::GameAction action) // 0x1092A840
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetActionState@Input@Blam@@YAPAUActionState@12@W4GameAction@12@@Z");
			// Blam::Input::GameAction action;
			// Blam::Input::ActionState *actions;

			if (action < 0 || action >= eGameAction_KeyboardMouseCount)
			{
				return nullptr;
			}

			Blam::Input::ActionState *actions = (Blam::Input::ActionState *)0x244D1F0;

			return &actions[action];
		}

		Blam::Input::PlayerInputState *GetPlayerInputState(__int32 localPlayerIndex) // 0x1092AB20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerInputState@Input@Blam@@YAPAUPlayerInputState@12@H@Z");
			// __int32 localPlayerIndex;

			return (Blam::Input::PlayerInputState *)0x244D1F0 + localPlayerIndex;
		}

		VirtualKeyboard::VirtualKeyboard(char const *file, __int32 line, __int32 arg2, __int32 arg3, __int32 arg4, __int32 arg5, __int32 maxLength, __int32 arg7, __int32 arg8) // 0x1092A660
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0VirtualKeyboard@Input@Blam@@QAE@PBDHHHHHHHH@Z");
			// __int32 arg8;

			Unknown4 = 0;
			State = eVirtualKeyboardStateClosed;
			Unknown8 = 0;
			UnknownC = 0;
			Unknown10 = 0;
			Unknown14 = 0;
			memset(Value, 0, sizeof(Value));
			memset(DefaultValue, 0, sizeof(DefaultValue));
			memset(Title, 0, sizeof(Title));
			memset(Description, 0, sizeof(Description));
			MaxLength = Utils::Clamp(maxLength, 0, 256);
		}

		__int32 VirtualKeyboard::Stub0() // 0x1092AFC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub0@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::Stub4() // 0x1092B060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub4@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::Stub8() // 0x1092B080
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub8@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::StubC() // 0x1092B0A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StubC@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::Stub10() // 0x1092AFE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub10@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::Stub14() // 0x1092B000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub14@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		__int32 VirtualKeyboard::Stub18() // 0x1092B020
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub18@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		void VirtualKeyboard::Reset() // 0x1092AC90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@VirtualKeyboard@Input@Blam@@UAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;

			State = eVirtualKeyboardStateClosed;
		}

		__int32 VirtualKeyboard::Stub20() // 0x1092B040
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Stub20@VirtualKeyboard@Input@Blam@@UAEHXZ");
			// Blam::Input::VirtualKeyboard *const this;

			return 0;
		}

		void VirtualKeyboard::SetTitle(wchar_t const *newTitle) // 0x1092AE70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetTitle@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newTitle;
			// unsigned __int32 const TitleLength;

			const int titleSize = 64;
			wcsncpy(Title, newTitle, titleSize - 1);
			Title[titleSize - 1] = 0;
		}

		void VirtualKeyboard::SetDescription(wchar_t const *newDescription) // 0x1092ADE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetDescription@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newDescription;
			// unsigned __int32 const DescriptionLength;

			const int size = 256;

			wcsncpy(Description, newDescription, size - 1);
			Description[size - 1] = 0;
		}

		void VirtualKeyboard::SetValue(wchar_t const *newValue) // 0x1092AF00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetValue@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newValue;
			// unsigned __int32 const ValueLength;

			const int maxLength = 256;

			wcsncpy(Value, newValue, maxLength - 1);
			Value[maxLength - 1] = 0;
		}

		void VirtualKeyboard::SetDefaultValue(wchar_t const *newDefaultValue) // 0x1092AD50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetDefaultValue@VirtualKeyboard@Input@Blam@@QAEXPB_W@Z");
			// wchar_t const *newDefaultValue;
			// unsigned __int32 const DefaultValueLength;

			const int size = 256;

			wcsncpy(DefaultValue, newDefaultValue, size - 1);
			DefaultValue[size - 1] = 0;
		}

		void VirtualKeyboard::Start() // 0x1092AF90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Start@VirtualKeyboard@Input@Blam@@QAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;

			State = eVirtualKeyboardStateBusy1;
		}

		void VirtualKeyboard::Finish() // 0x1092A810
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Finish@VirtualKeyboard@Input@Blam@@QAEXXZ");
			// Blam::Input::VirtualKeyboard *const this;

			State = eVirtualKeyboardStateFinished;
		}
	}
}

/* ---------- private code */

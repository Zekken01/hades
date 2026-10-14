#ifndef __BLAM_BLAMINPUT_HPP__
#define __BLAM_BLAMINPUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Patches/Audio.hpp"
#include "Patches/VirtualKeyboard.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

#include <functional>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
		struct ActionState;
		struct BindingsPreferences;
		struct BindingsTable;
		struct ConfigurableAction;
		struct KeyEvent;
		struct KeyState;
		struct PlayerInputState;
	}
}

/* ---------- constants */

namespace Blam
{
	namespace Input
	{
		enum UiButtonCode : unsigned __int32
		{
			eUiButtonCodeA = 0, // 0x0000
			eUiButtonCodeB = 1, // 0x0001
			eUiButtonCodeX = 2, // 0x0002
			eUiButtonCodeY = 3, // 0x0003
			eUiButtonCodeRB = 4, // 0x0004
			eUiButtonCodeLB = 5, // 0x0005
			eUiButtonCodeLT = 6, // 0x0006
			eUiButtonCodeRT = 7, // 0x0007
			eUiButtonCodeDpadUp = 8, // 0x0008
			eUiButtonCodeDpadDown = 9, // 0x0009
			eUiButtonCodeDpadLeft = 10, // 0x000A
			eUiButtonCodeDpadRight = 11, // 0x000B
			eUiButtonCodeStart = 12, // 0x000C
			eUiButtonCodeBack = 13, // 0x000D
			eUiButtonCodeLS = 14, // 0x000E
			eUiButtonCodeRS = 15, // 0x000F
			eUiButtonCodeEmulatedInput = 16, // 0x0010
			eUiButtonCodeUnk1 = 17, // 0x0011
			eUiButtonCodeLeft = 18, // 0x0012
			eUiButtonCodeRight = 19, // 0x0013
			eUiButtonCodeUp = 20, // 0x0014
			eUiButtonCodeDown = 21, // 0x0015
			eUiButtonCodeLSHorizontal = 26, // 0x001A
			eUiButtonCodeLSVertical = 27, // 0x001B
			eUiButtonCodeRSHorizontal = 28, // 0x001C
			eUiButtonCodeRSVertical = 29, // 0x001D
		};

		enum KeyCode : unsigned short
		{
			eKeyCodeEscape = 0, // 0x0000
			eKeyCodeF1 = 1, // 0x0001
			eKeyCodeF2 = 2, // 0x0002
			eKeyCodeF3 = 3, // 0x0003
			eKeyCodeF4 = 4, // 0x0004
			eKeyCodeF5 = 5, // 0x0005
			eKeyCodeF6 = 6, // 0x0006
			eKeyCodeF7 = 7, // 0x0007
			eKeyCodeF8 = 8, // 0x0008
			eKeyCodeF9 = 9, // 0x0009
			eKeyCodeF10 = 10, // 0x000A
			eKeyCodeF11 = 11, // 0x000B
			eKeyCodeF12 = 12, // 0x000C
			eKeyCodePrintScreen = 13, // 0x000D
			eKeyCodeF14 = 14, // 0x000E
			eKeyCodeF15 = 15, // 0x000F
			eKeyCodeTilde = 16, // 0x0010
			eKeyCode1 = 17, // 0x0011
			eKeyCode2 = 18, // 0x0012
			eKeyCode3 = 19, // 0x0013
			eKeyCode4 = 20, // 0x0014
			eKeyCode5 = 21, // 0x0015
			eKeyCode6 = 22, // 0x0016
			eKeyCode7 = 23, // 0x0017
			eKeyCode8 = 24, // 0x0018
			eKeyCode9 = 25, // 0x0019
			eKeyCode0 = 26, // 0x001A
			eKeyCodeMinus = 27, // 0x001B
			eKeyCodePlus = 28, // 0x001C
			eKeyCodeBack = 29, // 0x001D
			eKeyCodeTab = 30, // 0x001E
			eKeyCodeQ = 31, // 0x001F
			eKeyCodeW = 32, // 0x0020 ' '
			eKeyCodeE = 33, // 0x0021 '!'
			eKeyCodeR = 34, // 0x0022 '"'
			eKeyCodeT = 35, // 0x0023 '#'
			eKeyCodeY = 36, // 0x0024 '$'
			eKeyCodeU = 37, // 0x0025 '%'
			eKeyCodeI = 38, // 0x0026 '&'
			eKeyCodeO = 39, // 0x0027 '''
			eKeyCodeP = 40, // 0x0028 '('
			eKeyCodeLBracket = 41, // 0x0029 ')'
			eKeyCodeRBracket = 42, // 0x002A '*'
			eKeyCodePipe = 43, // 0x002B '+'
			eKeyCodeCapital = 44, // 0x002C ','
			eKeyCodeA = 45, // 0x002D '-'
			eKeyCodeS = 46, // 0x002E '.'
			eKeyCodeD = 47, // 0x002F '/'
			eKeyCodeF = 48, // 0x0030 '0'
			eKeyCodeG = 49, // 0x0031 '1'
			eKeyCodeH = 50, // 0x0032 '2'
			eKeyCodeJ = 51, // 0x0033 '3'
			eKeyCodeK = 52, // 0x0034 '4'
			eKeyCodeL = 53, // 0x0035 '5'
			eKeyCodeColon = 54, // 0x0036 '6'
			eKeyCodeQuote = 55, // 0x0037 '7'
			eKeyCodeEnter = 56, // 0x0038 '8'
			eKeyCodeLShift = 57, // 0x0039 '9'
			eKeyCodeZ = 58, // 0x003A ':'
			eKeyCodeX = 59, // 0x003B ';'
			eKeyCodeC = 60, // 0x003C '<'
			eKeyCodeV = 61, // 0x003D '='
			eKeyCodeB = 62, // 0x003E '>'
			eKeyCodeN = 63, // 0x003F '?'
			eKeyCodeM = 64, // 0x0040 '@'
			eKeyCodeComma = 65, // 0x0041 'A'
			eKeyCodePeriod = 66, // 0x0042 'B'
			eKeyCodeQuestion = 67, // 0x0043 'C'
			eKeyCodeRShift = 68, // 0x0044 'D'
			eKeyCodeLControl = 69, // 0x0045 'E'
			eKeyCodeUnused46 = 70, // 0x0046 'F'
			eKeyCodeLAlt = 71, // 0x0047 'G'
			eKeyCodeSpace = 72, // 0x0048 'H'
			eKeyCodeRAlt = 73, // 0x0049 'I'
			eKeyCodeUnused4A = 74, // 0x004A 'J'
			eKeyCodeApps = 75, // 0x004B 'K'
			eKeyCodeRcontrol = 76, // 0x004C 'L'
			eKeyCodeUp = 77, // 0x004D 'M'
			eKeyCodeDown = 78, // 0x004E 'N'
			eKeyCodeLeft = 79, // 0x004F 'O'
			eKeyCodeRight = 80, // 0x0050 'P'
			eKeyCodeInsert = 81, // 0x0051 'Q'
			eKeyCodeHome = 82, // 0x0052 'R'
			eKeyCodePageUp = 83, // 0x0053 'S'
			eKeyCodeDelete = 84, // 0x0054 'T'
			eKeyCodeEnd = 85, // 0x0055 'U'
			eKeyCodePageDown = 86, // 0x0056 'V'
			eKeyCodeNumLock = 87, // 0x0057 'W'
			eKeyCodeDivide = 88, // 0x0058 'X'
			eKeyCodeMultiply = 89, // 0x0059 'Y'
			eKeyCodeNumpad0 = 90, // 0x005A 'Z'
			eKeyCodeNumpad1 = 91, // 0x005B '['
			eKeyCodeNumpad2 = 92, // 0x005C '\'
			eKeyCodeNumpad3 = 93, // 0x005D ']'
			eKeyCodeNumpad4 = 94, // 0x005E '^'
			eKeyCodeNumpad5 = 95, // 0x005F '_'
			eKeyCodeNumpad6 = 96, // 0x0060 '`'
			eKeyCodeNumpad7 = 97, // 0x0061 'a'
			eKeyCodeNumpad8 = 98, // 0x0062 'b'
			eKeyCodeNumpad9 = 99, // 0x0063 'c'
			eKeyCodeSubtract = 100, // 0x0064 'd'
			eKeyCodeAdd = 101, // 0x0065 'e'
			eKeyCodeNumpadEnter = 102, // 0x0066 'f'
			eKeyCodeDecimal = 103, // 0x0067 'g'
			eKeyCodeUnused68 = 104, // 0x0068 'h'
			eKeyCodeShift = 105, // 0x0069 'i'
			eKeyCodeCtrl = 106, // 0x006A 'j'
			eKeyCodeUnused6B = 107, // 0x006B 'k'
			eKeyCodeAlt = 108, // 0x006C 'l'
			eKeyCode_Count = 109, // 0x006D 'm'
			eKeyCode_None = 255, // 0x00FF
		};

		enum InputType : unsigned __int32
		{
			eInputTypeUi = 0,
			eInputTypeGame,
			eInputTypeSpecial,
			eInputType_Count,
		};

		enum GameAction : unsigned char
		{
			eGameActionUiLeftTrigger = 0, // 0x0000
			eGameActionUiRightTrigger = 1, // 0x0001
			eGameActionUiUp = 2, // 0x0002
			eGameActionUiDown = 3, // 0x0003
			eGameActionUiLeft = 4, // 0x0004
			eGameActionUiRight = 5, // 0x0005
			eGameActionUiStart = 6, // 0x0006
			eGameActionUiSelect = 7, // 0x0007
			eGameActionUiLeftStick = 8, // 0x0008
			eGameActionUiRightStick = 9, // 0x0009
			eGameActionUiA = 10, // 0x000A
			eGameActionUiB = 11, // 0x000B
			eGameActionUiX = 12, // 0x000C
			eGameActionUiY = 13, // 0x000D
			eGameActionUiLeftBumper = 14, // 0x000E
			eGameActionUiRightBumper = 15, // 0x000F
			eGameActionJump = 16, // 0x0010
			eGameActionSwitchGrenades = 17, // 0x0011
			eGameActionSwitchWeapons = 18, // 0x0012
			eGameActionUnk19 = 19, // 0x0013
			eGameActionReloadRight = 20, // 0x0014
			eGameActionUse = 21, // 0x0015
			eGameActionReloadLeft = 22, // 0x0016
			eGameActionPickUpLeft = 23, // 0x0017
			eGameActionMelee = 24, // 0x0018
			eGameActionThrowGrenade = 25, // 0x0019
			eGameActionFireRight = 26, // 0x001A
			eGameActionFireLeft = 27, // 0x001B
			eGameActionMeleeFire = 28, // 0x001C
			eGameActionCrouch = 29, // 0x001D
			eGameActionZoom = 30, // 0x001E
			eGameActionEmote = 31, // 0x001F
			eGameActionUnk32 = 32, // 0x0020 ' '
			eGameActionSprint = 33, // 0x0021 '!'
			eGameActionFlashlight = 34, // 0x0022 '"'
			eGameActionUnk35 = 35, // 0x0023 '#'
			eGameActionUnk36 = 36, // 0x0024 '$'
			eGameActionUnk37 = 37, // 0x0025 '%'
			eGameActionUnk38 = 38, // 0x0026 '&'
			eGameActionGeneralChat = 39, // 0x0027 '''
			eGameActionTeamChat = 40, // 0x0028 '('
			eGameActionVoiceChat = 41, // 0x0029 ')'
			eGameActionUnk42 = 42, // 0x002A '*'
			eGameActionUnk43 = 43, // 0x002B '+'
			eGameActionUseConsumable1 = 44, // 0x002C ','
			eGameActionUseConsumable2 = 45, // 0x002D '-'
			eGameActionUseConsumable3 = 46, // 0x002E '.'
			eGameActionUseConsumable4 = 47, // 0x002F '/'
			eGameActionVehicleBoost = 48, // 0x0030 '0'
			eGameActionVehicleDive = 49, // 0x0031 '1'
			eGameActionVehicleRaise = 50, // 0x0032 '2'
			eGameActionVehicleAccelerate = 51, // 0x0033 '3'
			eGameActionVehicleBrake = 52, // 0x0034 '4'
			eGameActionVehicleFire = 53, // 0x0035 '5'
			eGameActionVehicleAltFire = 54, // 0x0036 '6'
			eGameActionVehicleExit = 55, // 0x0037 '7'
			eGameActionNextPlayer = 56, // 0x0038 '8'
			eGameActionPrevPlayer = 57, // 0x0039 '9'
			eGameActionUnk58 = 58, // 0x003A ':'
			eGameAction_ControllerCount = 59, // 0x003B ';'
			eGameActionMoveForward = 59, // 0x003B ';'
			eGameActionMoveBack = 60, // 0x003C '<'
			eGameActionMoveLeft = 61, // 0x003D '='
			eGameActionMoveRight = 62, // 0x003E '>'
			eGameAction_KeyboardMouseCount = 63, // 0x003F '?'
		};

		enum ActionStateFlags : unsigned char
		{
			eActionStateFlags_None = 0,
			eActionStateFlagsHandled,
		};

		enum VirtualKeyboardState : unsigned short
		{
			eVirtualKeyboardStateClosed = 0,
			eVirtualKeyboardStateBusy1,
			eVirtualKeyboardStateBusy2,
			eVirtualKeyboardStateBusy3,
			eVirtualKeyboardStateFinished,
		};
	}
}

/* ---------- definitions */

namespace Blam
{
	namespace Input
	{
		struct KeyEvent
		{
			Blam::Input::KeyEventModifiers Modifiers; // 0x0
			Blam::Input::KeyEventType Type; // 0x4
			Blam::Input::KeyCode Code; // 0x8
			char16_t Char; // 0xA
			bool PreviousState; // 0xC
		};
	}
}

// static_assert(sizeof(Blam::Input::KeyEvent) == 16, "Invalid Blam::Input::KeyEvent size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace Blam
{
	namespace Input
	{
		struct KeyState
		{
			unsigned short Msec; // 0x0
			unsigned char Ticks; // 0x2
			unsigned char unknown; // 0x3
		};
		static_assert(sizeof(Blam::Input::KeyState) == 4, "Invalid Blam::Input::KeyState size");
	}
}

#pragma pack(push, 4)
namespace Blam
{
	namespace Input
	{
		struct BindingsPreferences
		{
			Blam::Input::KeyCode PrimaryKeys[63]; // 0x0
			Blam::Input::MouseButton PrimaryMouseButtons[63]; // 0x7E
			unsigned char __pad0[1]; // 0xBD
			Blam::Input::KeyCode SecondaryKeys[63]; // 0xBE
			Blam::Input::MouseButton SecondaryMouseButtons[63]; // 0x13C
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Blam::Input::BindingsPreferences) == 380, "Invalid Blam::Input::BindingsPreferences size");

namespace Blam
{
	namespace Input
	{
		struct ActionState
		{
			unsigned short Msec; // 0x0
			unsigned char Ticks; // 0x2
			unsigned char Flags; // 0x3
			float Pressure; // 0x4
			unsigned char Unknown8; // 0x8
			unsigned char Unknown9; // 0x9
			unsigned short UnknownA; // 0xA
			_inline unsigned char GetDownTicks() const;
		};
		static_assert(sizeof(Blam::Input::ActionState) == 12, "Invalid Blam::Input::ActionState size");

		struct PlayerInputState
		{
			Blam::Input::ActionState Actions[63]; // 0x0
			short LeftThumbX; // 0x2F4
			short LeftThumbY; // 0x2F6
			short RightThumbX; // 0x2F8
			short RightThumbY; // 0x2FA
			float Forward; // 0x2FC
			float Strafe; // 0x300
			float Unknown304; // 0x304
			float LookHorizontal; // 0x308
			float LookVertical; // 0x30C
			float Unknown310; // 0x310
			float Unknown314; // 0x314
			float Unknown318; // 0x318
			float Unknown31C; // 0x31C
			float Unknown320; // 0x320
			float Unknown324; // 0x324
		};
		static_assert(sizeof(Blam::Input::PlayerInputState) == 808, "Invalid Blam::Input::PlayerInputState size");

		struct ConfigurableAction
		{
			char const *Name; // 0x0
			__int32 DefaultPrimaryKey; // 0x4
			__int32 DefaultSecondaryKey; // 0x8
			__int32 Action; // 0xC
		};
		static_assert(sizeof(Blam::Input::ConfigurableAction) == 16, "Invalid Blam::Input::ConfigurableAction size");
	}
}

#pragma pack(push, 4)
namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard
		{
		public:
			VirtualKeyboard(Blam::Input::VirtualKeyboard &); /* compiler_generated() */
			VirtualKeyboard(Blam::Input::VirtualKeyboard const &); /* compiler_generated() */
			VirtualKeyboard(char const *file, __int32 line, __int32 arg2, __int32 arg3, __int32 arg4, __int32 arg5, __int32 maxLength, __int32 arg7, __int32 arg8);
			virtual __int32 Stub0();
			virtual __int32 Stub4();
			virtual __int32 Stub8();
			virtual __int32 StubC();
			virtual __int32 Stub10();
			virtual __int32 Stub14();
			virtual __int32 Stub18();
			virtual void Reset();
			virtual __int32 Stub20();
			void SetTitle(wchar_t const *newTitle);
			void SetDescription(wchar_t const *newDescription);
			void SetValue(wchar_t const *newValue);
			void SetDefaultValue(wchar_t const *newDefaultValue);
			void Start();
			void Finish();
			short Unknown4; // 0x4
			Blam::Input::VirtualKeyboardState State; // 0x6
			__int32 Unknown8; // 0x8
			__int32 UnknownC; // 0xC
			__int32 Unknown10; // 0x10
			__int32 Unknown14; // 0x14
			wchar_t Value[256]; // 0x18
			wchar_t DefaultValue[256]; // 0x218
			wchar_t Title[64]; // 0x418
			wchar_t Description[256]; // 0x498
			__int32 MaxLength; // 0x698
			Blam::Input::VirtualKeyboard &operator=(Blam::Input::VirtualKeyboard &); /* compiler_generated() */
			Blam::Input::VirtualKeyboard &operator=(Blam::Input::VirtualKeyboard const &); /* compiler_generated() */
			public:
			void Init();
			void ApplyAll();
			void SetKeyboardHandler(std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> callback);
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Blam::Input::VirtualKeyboard) == 1692, "Invalid Blam::Input::VirtualKeyboard size");

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

/* ---------- public code */

namespace Blam
{
	namespace Input
	{
		inline unsigned char ActionState::GetDownTicks() const // 0x10A79440
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetDownTicks@ActionState@Input@Blam@@QBEEXZ");
			// Blam::Input::ActionState const *const this;
			// unsigned char result;
				// unsigned char v2;

			unsigned char downTicks = 0;
			if (!(Flags & 1))
			{
				unsigned char unknown9 = Unknown9;
				if (unknown9 == 255 || unknown9 == Unknown8)
				{
					downTicks = Ticks;
				}
			}
			return downTicks;
		}
	}
}

/* ---------- private code */

#endif // __BLAM_BLAMINPUT_HPP__

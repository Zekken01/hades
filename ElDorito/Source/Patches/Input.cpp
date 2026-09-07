/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/input/input_abstraction.hpp"
#include "Blam/interface/gui/gui_location_manager.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "CommandScript.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleInput.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Input.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_gui_screen_widget;
struct begin;
struct c_gui_location_manager;
struct end;
namespace Blam
{
	namespace Input
	{
		enum InputType : unsigned __int32;
		struct BindingsTable;
		struct ConfigurableAction;
	}
}
namespace Patches
{
	namespace Input
	{
		class InputContext;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

//struct SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION
//{
//	unsigned short LeftMotorSpeed; // 0x0
//	unsigned short RightMotorSpeed; // 0x2
//};
//static_assert(sizeof(SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION) == 4, "Invalid SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION size");

/* ---------- prototypes */

namespace Patches
{
	namespace Input
	{
		extern void ApplyAll();
		extern void PushContext(std::shared_ptr<Patches::Input::InputContext> context);
		extern void RegisterDefaultInputHandler(void (*func)());
		extern void RegisterMenuUIInputHandler(void (*func)());
		extern void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings);
		extern void TestControllerVibration(float durationSeconds);
		extern void InvalidateBindings();
	}
}

/* ---------- globals */

c_gui_screen_widget *(*c_gui_location_manager::get_location_gui_screen)(); // 0x1135459C

/* ---------- private variables */

namespace
{
	extern std::stack<std::shared_ptr<Patches::Input::InputContext>,std::deque<std::shared_ptr<Patches::Input::InputContext>,std::allocator<std::shared_ptr<Patches::Input::InputContext> > > > contextStack; // 0x12458880
	extern std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > defaultHandlers; // 0x12458850
	extern std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > uiHandlers; // 0x12458870
	extern bool contextDone; // 0x12458894
	extern bool blockStates[3]; // 0x124588A0
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > settings; // 0x12458860
	extern Blam::Input::InputType actionInputTypes[63]; // 0x11354458
	extern Blam::Input::BindingsTable s_ForgeMonitorModeBindings; // 0x124588A8
	extern unsigned __int32 s_ControllerVibrationTestTicks; // 0x124588A4
	extern unsigned __int32 bindingsNextUpdateTicks; // 0x11354454
	extern IDirectInput8A *g_diInterface; // 0x12458AB0
	extern IDirectInputDevice8A *g_diKeyboardDevice; // 0x12458AB4
	extern bool g_diInitialized; // 0x12458895
	extern std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > lastRotateUpdateTime; // 0x12458898
}
/* ---------- public code */

namespace Patches
{
	namespace Input
	{
		_extern void _sub_10A780B0();
		void ApplyAll() // 0x10A780B0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Input@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A78FA8
			// static ...; // 0x10A78F9C
			// static ...; // 0x10A78F94
			// unsigned __int32 keyboardFixPointers[6];
			{
				// unsigned __int32 &<range>$L0[6];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
				{
					// unsigned __int32 pointer;
				}
			}
			todo("implement");
			_sub_10A780B0();
		}

		_extern void _sub_10A7AB70(std::shared_ptr<Patches::Input::InputContext>);
		void PushContext(std::shared_ptr<Patches::Input::InputContext> context) // 0x10A7AB70
		{
			mangled_x86(MANGLED_TODO, "?PushContext@Input@Patches@@YAXV?$shared_ptr@VInputContext@Input@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Input::InputContext> context;
			{
				// __int32 i;
			}
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10A7AB70(context);
		}

		_extern void _sub_10A7AD30(void (*)());
		void RegisterDefaultInputHandler(void (*func)()) // 0x10A7AD30
		{
			mangled_x86(MANGLED_TODO, "?RegisterDefaultInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();
			todo("implement");
			_sub_10A7AD30(func);
		}

		_extern void _sub_10A7AD80(void (*)());
		void RegisterMenuUIInputHandler(void (*func)()) // 0x10A7AD80
		{
			mangled_x86(MANGLED_TODO, "?RegisterMenuUIInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();
			todo("implement");
			_sub_10A7AD80(func);
		}

		_extern void _sub_10A7AEB0(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &);
		void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings) // 0x10A7AEB0
		{
			mangled_x86(MANGLED_TODO, "?SetKeyboardSettingsMenu@Input@Patches@@YAXABV?$vector@UConfigurableAction@Input@Blam@@V?$allocator@UConfigurableAction@Input@Blam@@@std@@@std@@0@Z");
			// static ...; // 0x10A7B567
			// static ...; // 0x10A7B55B
			// static ...; // 0x10A7B545
			// static ...; // 0x10A7B530
			// static ...; // 0x10A7B4F4
			// static ...; // 0x10A7B4EC
			// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings;
			// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings;
			// unsigned __int32 vehiclePointers[5];
			// unsigned __int32 endPointers[1];
			// unsigned __int32 infantryCountPointers[3];
			// unsigned __int32 vehicleCountPointers[3];
			// unsigned __int32 vehicleCount;
			// unsigned __int32 infantryCount;
			// unsigned __int32 infantryPointers[4];
			{
				// unsigned __int32 &<range>$L0[4];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
				{
					// unsigned __int32 pointer;
				}
			}
			{
				// unsigned __int32 *<end>$L1;
				// unsigned __int32 *<begin>$L1;
				// unsigned __int32 &<range>$L1[5];
				{
				}
			}
			{
				// unsigned __int32 *<end>$L2;
				// unsigned __int32 &<range>$L2[1];
				// unsigned __int32 *<begin>$L2;
				{
				}
			}
			{
				// unsigned __int32 &<range>$L3[3];
				// unsigned __int32 *<begin>$L3;
				// unsigned __int32 *<end>$L3;
				{
				}
			}
			{
				// unsigned __int32 *<end>$L4;
				// unsigned __int32 *<begin>$L4;
				// unsigned __int32 &<range>$L4[3];
				{
				}
			}
			todo("implement");
			_sub_10A7AEB0(infantrySettings, vehicleSettings);
		}

		_extern void _sub_10A7B740(float);
		void TestControllerVibration(float durationSeconds) // 0x10A7B740
		{
			mangled_x86(MANGLED_TODO, "?TestControllerVibration@Input@Patches@@YAXM@Z");
			// float durationSeconds;
			// function call : long (*const)(float)
			todo("implement");
			_sub_10A7B740(durationSeconds);
		}

		_extern void _sub_10A79CA0();
		void InvalidateBindings() // 0x10A79CA0
		{
			mangled_x86(MANGLED_TODO, "?InvalidateBindings@Input@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A79CA0();
		}
	}
}

/* ---------- private code */

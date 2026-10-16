#ifndef __PATCHES_INPUT_HPP__
#define __PATCHES_INPUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
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

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace Input
	{
		class InputContext
		{
		public:
			virtual _inline ~InputContext();
			virtual void Activated() = 0;
			virtual void Deactivated() = 0;
			virtual bool GameInputTick() = 0;
			virtual bool UiInputTick() = 0;
			virtual _inline void InputBlock();
			virtual _inline void InputUnblock();
			bool allowHandlers = false; // 0x4
			InputContext(Patches::Input::InputContext const &); /* compiler_generated() */
			_inline InputContext() = default; /* compiler_generated() */
			Patches::Input::InputContext &operator=(Patches::Input::InputContext const &); /* compiler_generated() */
		};
		static_assert(sizeof(Patches::Input::InputContext) == 8, "Invalid Patches::Input::InputContext size");
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Input
	{
		extern void ApplyAll();
		extern void PushContext(std::shared_ptr<Patches::Input::InputContext> context);
		extern void RegisterDefaultInputHandler(void (*func)());
		extern void RegisterMenuUIInputHandler(void (*func)());
		extern void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction> const &infantrySettings, std::vector<Blam::Input::ConfigurableAction> const &vehicleSettings);
		extern void TestControllerVibration(float durationSeconds);
		extern void InvalidateBindings();
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace Input
	{
		inline InputContext::~InputContext() // 0x10C91D90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1InputContext@Input@Patches@@UAE@XZ");
		}

		inline void InputContext::InputBlock() // 0x10C940B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InputBlock@InputContext@Input@Patches@@UAEXXZ");

			memset((void *)0x238DBEB, 1, 3);
		}

		inline void InputContext::InputUnblock() // 0x10C94180
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InputUnblock@InputContext@Input@Patches@@UAEXXZ");

			memset((bool *)0x238DBEB, 0, 3);
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_INPUT_HPP__

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
			bool allowHandlers; // 0x4
			InputContext(Patches::Input::InputContext const &); /* compiler_generated() */
			_inline InputContext(); /* compiler_generated() */
			Patches::Input::InputContext &operator=(Patches::Input::InputContext const &); /* compiler_generated() */
		unsigned char __pad0[3]; // 0x5
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
		_extern void _sub_10C91D90(Patches::Input::InputContext *const);
		_inline InputContext::~InputContext() // 0x10C91D90
		{
			mangled_x86(MANGLED_TODO, "??1InputContext@Input@Patches@@UAE@XZ");
			// Patches::Input::InputContext *const this;
			todo("implement");
			_sub_10C91D90(this);
		}

		_extern void _sub_10C940B0(Patches::Input::InputContext *const);
		_inline void InputContext::InputBlock() // 0x10C940B0
		{
			mangled_x86(MANGLED_TODO, "?InputBlock@InputContext@Input@Patches@@UAEXXZ");
			// Patches::Input::InputContext *const this;
			todo("implement");
			_sub_10C940B0(this);
		}

		_extern void _sub_10C94180(Patches::Input::InputContext *const);
		_inline void InputContext::InputUnblock() // 0x10C94180
		{
			mangled_x86(MANGLED_TODO, "?InputUnblock@InputContext@Input@Patches@@UAEXXZ");
			// Patches::Input::InputContext *const this;
			todo("implement");
			_sub_10C94180(this);
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_INPUT_HPP__

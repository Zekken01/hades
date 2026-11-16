#ifndef __WEB_RML_INPUT_HPP__
#define __WEB_RML_INPUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Core/Input.h>

#include <Windows.h>

/* ---------- forward declarations */

namespace Rml
{
	class Context;
}

/* ---------- prototypes */

namespace Web
{
	namespace RmlUi
	{
		// Win32 message -> Rml::Context input.  Messages are queued from the window hook and
		// drained on the game thread, where the Lua state and the context live.
		namespace Input
		{
			int GetKeyModifierState();
			::Rml::Input::KeyIdentifier ConvertKey(int win32_key_code);
			void Enqueue(const MSG &msg);
			void Clear();
			// Feeds every queued message to the context; returns true if the UI consumed any.
			bool Drain(::Rml::Context *context);
		}
	}
}

#endif // __WEB_RML_INPUT_HPP__

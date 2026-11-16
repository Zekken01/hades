/* ---------- headers */

#include "hades/hades.h"

#include "Blam/hs/hs.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"

// hades: added. Script functions for rendering that Saber stripped from Halo 3.

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const hs_macro_function_evaluate = reinterpret_cast<hs_value *(*)(short, long, bool)>(0x5972F0);
	static auto const hs_return = reinterpret_cast<void (*)(long, hs_value)>(0x5974E0);
}

extern void render_texture_camera_set_bink(bool bink_is_active);  // Patches/bink_patches.cpp

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Render
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_texture_camera_bink_evaluate(short op, long thread_index, bool initial);

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Render
			{
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods)
				{
					methods.AddMethod("texture_camera_bink", "Shows the playing bink movie on the texture camera's surface instead of the camera's view while the texture camera is on; a movie from a bink tag is then not drawn to the screen", NetworkSafe, hs_texture_camera_bink_evaluate, _hs_type_void, { { _hs_type_boolean, "enabled", "True to show the bink movie, false to show the camera's view again" } });
				}
			}
		}
	}
}

/* ---------- private code */

void hs_texture_camera_bink_evaluate(short op, long thread_index, bool initial)
{
	hs_value *args = eldorado::hs_macro_function_evaluate(op, thread_index, initial);
	if (args)
	{
		render_texture_camera_set_bink(args[0].bool_value);
		eldorado::hs_return(thread_index, hs_value{});
	}
}

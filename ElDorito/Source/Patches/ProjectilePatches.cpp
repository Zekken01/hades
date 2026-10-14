/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/items/projectiles.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct real_vector3d;
struct s_projectile_data;
struct s_projectile_definition;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Projectiles {}
	using namespace Patches::Projectiles;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern float (*const game_tick_length)();  // hades: added for 0x1069E640
extern long (*const game_tick_rate)();  // hades: added for 0x1069E640
extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0x1069E640

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x1069E560
extern long (*const game_time_get)();  // hades: added for 0x1069E560

namespace Patches
{
	namespace Projectiles
	{
		extern void ApplyAll();
	}
}

void projectile_translate_tick_delta(long projectile_index, bool force_30hz);
float projectile_translate_game_tick_length_hook();
void projectile_update_translate_hook(long projectile_index, real_vector3d *unswept_velocity);
void projectile_initial_update_translate_hook(long projectile_index, real_vector3d *unswept_velocity);
bool projectile_new_hook(long projectile_index, void *data);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float g_projectile_translate_tick_delta; // 0x1138600C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Projectiles
	{
		void ApplyAll() // 0x1069E000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Projectiles@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x77FAE6, projectile_update_translate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x77DBB4, projectile_initial_update_translate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x77DB54, projectile_initial_update_translate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x77E857, projectile_translate_game_tick_length_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x1948740).Write(projectile_new_hook);
			Pointer(0x1948710).Write<unsigned short>(0x218);
		}
	}
}

/* ---------- private code */

void projectile_translate_tick_delta(long projectile_index, bool force_30hz) // 0x1069E640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_translate_tick_delta@@YAXJ_N@Z");
	// `anonymous-namespace'::projectile_translate_tick_delta
	// bool force_30hz;
	// float tick_delta;
	// s_projectile_data *const projectile;
	// s_projectile_definition *const definition;
	// function call : float (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()
	// function call : long (*const)()

	float tick_delta = game_tick_length();
	s_projectile_data *const projectile = object_get<s_projectile_data>(projectile_index);
	s_projectile_definition *const definition = (s_projectile_definition *)tag_get('proj', projectile->definition_index);
	if (definition->projectile_flags.test(static_cast<e_projectile_definition_flags>(5)))
	{
		if (force_30hz || projectile->creation_game_time == game_time_get())
		{
			tick_delta = game_tick_rate() / 30.0f * tick_delta;
		}
	}

	g_projectile_translate_tick_delta = tick_delta;
}

float projectile_translate_game_tick_length_hook() // 0x1069E620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_translate_game_tick_length_hook@@YAMXZ");
	// `anonymous-namespace'::projectile_translate_game_tick_length_hook
	// procedure flags: nofpo

	return g_projectile_translate_tick_delta;
}

void projectile_update_translate_hook(long projectile_index, real_vector3d *unswept_velocity) // 0x1069E770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_update_translate_hook@@YAXJPAUreal_vector3d@@@Z");
	// `anonymous-namespace'::projectile_update_translate_hook
	// real_vector3d *unswept_velocity;
	// function call : void (*const)(long, real_vector3d *)

	projectile_translate_tick_delta(projectile_index, 0);
	((void(__cdecl *)(long, real_vector3d *))0xb7e800)(projectile_index, unswept_velocity);
}

void projectile_initial_update_translate_hook(long projectile_index, real_vector3d *unswept_velocity) // 0x1069E4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_initial_update_translate_hook@@YAXJPAUreal_vector3d@@@Z");
	// `anonymous-namespace'::projectile_initial_update_translate_hook
	// real_vector3d *unswept_velocity;
	// function call : void (*const)(long, real_vector3d *)

	projectile_translate_tick_delta(projectile_index, 1);
	((void(__cdecl *)(long, real_vector3d *))0xb7e800)(projectile_index, unswept_velocity);
}

bool projectile_new_hook(long projectile_index, void *data) // 0x1069E560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_new_hook@@YA_NJPAX@Z");
	// `anonymous-namespace'::projectile_new_hook
	// void *data;
	// bool ret;
	// char (*const projectile_new)(long, void *);
	// s_projectile_data *const projectile;
	// function call : char (*const)(long, void *)
	// function call : long (*const)()

	unsigned char (*const projectile_new)(long, void *) = reinterpret_cast<unsigned char (*)(long, void *)>(0xB7DDB0);
	bool ret = projectile_new(projectile_index, data);
	s_projectile_data *projectile = object_get<s_projectile_data>(projectile_index);
	projectile->creation_game_time = game_time_get();
	return ret;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_projectile_definition_flags,long>::test(e_projectile_definition_flags) const;
template void Pointer::Write<bool (__cdecl*)(long,void *)>(bool (*const value)(long, void *)) const;

/* ---------- explicit instantiations */
template s_projectile_data * object_get<s_projectile_data>(unsigned long);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { float g_projectile_translate_tick_delta; }

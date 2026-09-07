/* ---------- headers */

#include "Blam/math/function_definitions.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct real_rgb_color;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_function_definition::e_function_type _sub_10F07EC0(c_function_definition const *const);
c_function_definition::e_function_type c_function_definition::get_type() const // 0x10F07EC0
{
	mangled_x86(MANGLED_TODO, "?get_type@c_function_definition@@QBE?AW4e_function_type@1@XZ");
	// c_function_definition const *const this;
	todo("implement");
	c_function_definition::e_function_type __result = _sub_10F07EC0((c_function_definition const *)this);
	return __result;
}

_extern float _sub_10F07E30(c_function_definition const *const, float, float);
float c_function_definition::evaluate_scalar(float x, float t) const // 0x10F07E30
{
	mangled_x86(MANGLED_TODO, "?evaluate_scalar@c_function_definition@@QBEMMM@Z");
	// float t;
	// float (*const evaluate_scalar)(c_function_definition const *, float, float);
	// function call : float (*const)(c_function_definition const *, float, float)
	todo("implement");
	float __result = _sub_10F07E30((c_function_definition const *)this, x, t);
	return __result;
}

_extern void _sub_10F07D90(c_function_definition const *const, float, float, real_rgb_color *);
void c_function_definition::evaluate_color(float x, float t, real_rgb_color *out_color) const // 0x10F07D90
{
	mangled_x86(MANGLED_TODO, "?evaluate_color@c_function_definition@@QBEXMMPAUreal_rgb_color@@@Z");
	// real_rgb_color *out_color;
	// float (*const evaluate_color)(c_function_definition const *, float, float, real_rgb_color *);
	// function call : float (*const)(c_function_definition const *, float, float, real_rgb_color *)
	todo("implement");
	_sub_10F07D90((c_function_definition const *)this, x, t, out_color);
}

/* ---------- private code */

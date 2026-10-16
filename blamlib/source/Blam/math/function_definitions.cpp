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

c_function_definition::e_function_type c_function_definition::get_type() const // 0x10F07EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_type@c_function_definition@@QBE?AW4e_function_type@1@XZ");

	return (e_function_type)*(char *)m_data.address;
}

float c_function_definition::evaluate_scalar(float x, float t) const // 0x10F07E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?evaluate_scalar@c_function_definition@@QBEMMM@Z");

	float (__thiscall *const evaluate)(const c_function_definition *, float, float) = (float(__thiscall *const)(const c_function_definition *, float, float))0x949ce0;

	return evaluate(this, x, t);
}

void c_function_definition::evaluate_color(float x, float t, real_rgb_color *out_color) const // 0x10F07D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?evaluate_color@c_function_definition@@QBEXMMPAUreal_rgb_color@@@Z");

	float (__thiscall *const evaluate_color)(const c_function_definition *, float, float, real_rgb_color *) = (float(__thiscall *const)(const c_function_definition *, float, float, real_rgb_color *))0x9498d0;

	evaluate_color(this, x, t, out_color);
}

/* ---------- private code */

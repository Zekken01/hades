#ifndef __BLAM_CSERIES_ENUMS_INL__
#define __BLAM_CSERIES_ENUMS_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/forge/forge_globals.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline bool c_enum<enum e_multiplayer_object_type,char>::operator<=(e_multiplayer_object_type const &other) const // 0x10A60140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_multiplayer_object_type@@D@@QBE_NABW4e_multiplayer_object_type@@@Z");
	// e_multiplayer_object_type const &other;

	return m_value <= (char)other;
}

_inline bool c_enum<enum e_hs_type,short>::operator<=(e_hs_type const &other) const // 0x10922480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_hs_type@@F@@QBE_NABW4e_hs_type@@@Z");
	// e_hs_type const &other;

	return m_value <= (short)other;
}

_inline bool c_enum<enum e_render_method_animated_parameter_type,long>::operator<=(e_render_method_animated_parameter_type const &other) const // 0x108E4140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_render_method_animated_parameter_type@@J@@QBE_NABW4e_render_method_animated_parameter_type@@@Z");
	// e_render_method_animated_parameter_type const &other;

	return m_value <= (long)other;
}

_inline c_enum<enum e_forge_object_property_setter_type,unsigned char>::operator unsigned char() const // 0x10CA6820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_forge_object_property_setter_type@@E@@QBEEXZ");
	// c_enum<enum e_forge_object_property_setter_type,unsigned char> const *const this;

	return m_value;
}

_inline c_enum<enum e_sound_compression,unsigned char>::operator unsigned char() const // 0x10A2BF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_compression@@E@@QBEEXZ");
	// c_enum<enum e_sound_compression,unsigned char> const *const this;

	return m_value;
}

_inline c_enum<enum e_sound_encoding,unsigned char>::operator unsigned char() const // 0x10A2BF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_encoding@@E@@QBEEXZ");
	// c_enum<enum e_sound_encoding,unsigned char> const *const this;

	return m_value;
}

_inline c_enum<enum e_sound_sample_rate,unsigned char>::operator unsigned char() const // 0x10A2BFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_sample_rate@@E@@QBEEXZ");
	// c_enum<enum e_sound_sample_rate,unsigned char> const *const this;

	return m_value;
}

_inline c_enum<enum e_multiplayer_teleporter_channel,unsigned char>::operator unsigned char() const // 0x1083B660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_multiplayer_teleporter_channel@@E@@QBEEXZ");
	// c_enum<enum e_multiplayer_teleporter_channel,unsigned char> const *const this;

	return m_value;
}

/* ---------- private code */

#endif // __BLAM_CSERIES_ENUMS_INL__

#ifndef __BLAM_CSERIES_FLAGS_INL__
#define __BLAM_CSERIES_FLAGS_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/models/model_definitions.hpp"

/* ---------- forward declarations */

struct s_single_screen_effect_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<> inline bool c_flags<enum e_multiplayer_team_designator,short>::operator<(e_multiplayer_team_designator const &other) const // 0x108DE240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??M?$c_flags@W4e_multiplayer_team_designator@@F@@QBE_NABW4e_multiplayer_team_designator@@@Z");
	// e_multiplayer_team_designator const &other;

	return m_value < (short)other;
}

template<> inline c_flags<enum e_weapon_definition_flags,unsigned long>::operator unsigned long() const // 0x10AEFE60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_weapon_definition_flags@@K@@QBEKXZ");
	// c_flags<enum e_weapon_definition_flags,unsigned long> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_game_engine_type,unsigned short>::operator unsigned short() const // 0x10A5FDA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_type@@G@@QBEGXZ");
	// c_flags<enum e_game_engine_type,unsigned short> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_effect_message_type,unsigned char>::operator unsigned char() const // 0x10910030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_effect_message_type@@E@@QBEEXZ");
	// c_flags<enum e_effect_message_type,unsigned char> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_part_flags,unsigned char>::operator unsigned char() const // 0x108E3FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_part_flags@@E@@QBEEXZ");
	// c_flags<enum e_part_flags,unsigned char> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_chud_widget_bitmap_flags,unsigned long>::operator unsigned long() const // 0x10858430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_chud_widget_bitmap_flags@@K@@QBEKXZ");
	// c_flags<enum e_chud_widget_bitmap_flags,unsigned long> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_game_engine_flags,unsigned short>::operator unsigned short() const // 0x1083B690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_flags@@G@@QBEGXZ");
	// c_flags<enum e_game_engine_flags,unsigned short> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_multiplayer_object_flags,unsigned char>::operator unsigned char() const // 0x1083B6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_multiplayer_object_flags@@E@@QBEEXZ");
	// c_flags<enum e_multiplayer_object_flags,unsigned char> const *const this;

	return m_value;
}

template<> inline c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::operator unsigned short() const // 0x107C0DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_flags@s_single_screen_effect_definition@@G@@QBEGXZ");
	// c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_hs_syntax_node_flags,unsigned short>::operator unsigned short() const // 0x106F6D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_hs_syntax_node_flags@@G@@QBEGXZ");
	// c_flags<enum e_hs_syntax_node_flags,unsigned short> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_unit_flags,unsigned long>::operator unsigned long() const // 0x106D6EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_unit_flags@@K@@QBEKXZ");
	// c_flags<enum e_unit_flags,unsigned long> const *const this;

	return m_value;
}

template<> inline c_flags<enum e_network_session_parameter_base_flags,unsigned char>::operator bool() const // 0x10F1EED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_network_session_parameter_base_flags@@E@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_game_looping_sound_flag,unsigned short>::operator bool() const // 0x1067D770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_looping_sound_flag@@G@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_instanced_geometry_flags,unsigned short>::operator bool() const // 0x108E3FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_instanced_geometry_flags@@G@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_game_engine_flags,unsigned short>::operator bool() const // 0x10A5FD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_flags@@G@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_game_engine_type,unsigned short>::operator bool() const // 0x10A5FDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_type@@G@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_unit_flags,unsigned long>::operator bool() const // 0x106BE1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_unit_flags@@K@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_cinematic_object_flags,long>::operator bool() const // 0x107B2DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_cinematic_object_flags@@J@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_part_flags,unsigned char>::operator bool() const // 0x107BEAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_part_flags@@E@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum s_model_target::e_model_target_flags,long>::operator bool() const // 0x10858460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_model_target_flags@s_model_target@@J@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_effect_message_type,unsigned long>::operator bool() const // 0x10910060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_effect_message_type@@K@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_tag_resource_page_flags,unsigned char>::operator bool() const // 0x109223C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_tag_resource_page_flags@@E@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_unit_seat_flags,long>::operator bool() const // 0x10956E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_unit_seat_flags@@J@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_object_datum_flags,unsigned char>::operator bool() const // 0x10ACCC30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_object_datum_flags@@E@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_unit_control_flags,unsigned long>::operator bool() const // 0x10ACCCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_unit_control_flags@@K@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_forge_object_property_setter_flags,unsigned char>::operator bool() const // 0x10CA6880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_forge_object_property_setter_flags@@E@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_flags<enum e_multiplayer_team_designator,short>::operator short() const // 0x106A10F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_multiplayer_team_designator@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_flags<enum e_bitmap_runtime_flags,short>::operator short() const // 0x10922390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_bitmap_runtime_flags@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_flags<enum e_mod_package_modifier_flags,long>::operator long() const // 0x1089D310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_mod_package_modifier_flags@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_flags<enum e_object_flags,long>::operator long() const // 0x10ACCC80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_object_flags@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_flags<enum e_barrel_flags,long>::operator long() const // 0x10AEFE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_barrel_flags@@J@@QBEJXZ");

	return m_value;
}

/* ---------- private code */

#endif // __BLAM_CSERIES_FLAGS_INL__

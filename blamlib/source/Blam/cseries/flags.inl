#ifndef __BLAM_CSERIES_FLAGS_INL__
#define __BLAM_CSERIES_FLAGS_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"

/* ---------- forward declarations */

struct s_single_screen_effect_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline bool c_flags<enum e_multiplayer_team_designator,short>::operator<(e_multiplayer_team_designator const &other) const // 0x108DE240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??M?$c_flags@W4e_multiplayer_team_designator@@F@@QBE_NABW4e_multiplayer_team_designator@@@Z");
	// e_multiplayer_team_designator const &other;

	return m_value < (short)other;
}

_inline c_flags<enum e_weapon_definition_flags,unsigned long>::operator unsigned long() const // 0x10AEFE60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_weapon_definition_flags@@K@@QBEKXZ");
	// c_flags<enum e_weapon_definition_flags,unsigned long> const *const this;

	return m_value;
}

_inline c_flags<enum e_game_engine_type,unsigned short>::operator unsigned short() const // 0x10A5FDA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_type@@G@@QBEGXZ");
	// c_flags<enum e_game_engine_type,unsigned short> const *const this;

	return m_value;
}

_inline c_flags<enum e_effect_message_type,unsigned char>::operator unsigned char() const // 0x10910030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_effect_message_type@@E@@QBEEXZ");
	// c_flags<enum e_effect_message_type,unsigned char> const *const this;

	return m_value;
}

_inline c_flags<enum e_part_flags,unsigned char>::operator unsigned char() const // 0x108E3FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_part_flags@@E@@QBEEXZ");
	// c_flags<enum e_part_flags,unsigned char> const *const this;

	return m_value;
}

_inline c_flags<enum e_chud_widget_bitmap_flags,unsigned long>::operator unsigned long() const // 0x10858430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_chud_widget_bitmap_flags@@K@@QBEKXZ");
	// c_flags<enum e_chud_widget_bitmap_flags,unsigned long> const *const this;

	return m_value;
}

_inline c_flags<enum e_game_engine_flags,unsigned short>::operator unsigned short() const // 0x1083B690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_game_engine_flags@@G@@QBEGXZ");
	// c_flags<enum e_game_engine_flags,unsigned short> const *const this;

	return m_value;
}

_inline c_flags<enum e_multiplayer_object_flags,unsigned char>::operator unsigned char() const // 0x1083B6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_multiplayer_object_flags@@E@@QBEEXZ");
	// c_flags<enum e_multiplayer_object_flags,unsigned char> const *const this;

	return m_value;
}

_inline c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::operator unsigned short() const // 0x107C0DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_flags@s_single_screen_effect_definition@@G@@QBEGXZ");
	// c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short> const *const this;

	return m_value;
}

_inline c_flags<enum e_hs_syntax_node_flags,unsigned short>::operator unsigned short() const // 0x106F6D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_hs_syntax_node_flags@@G@@QBEGXZ");
	// c_flags<enum e_hs_syntax_node_flags,unsigned short> const *const this;

	return m_value;
}

_inline c_flags<enum e_unit_flags,unsigned long>::operator unsigned long() const // 0x106D6EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_flags@W4e_unit_flags@@K@@QBEKXZ");
	// c_flags<enum e_unit_flags,unsigned long> const *const this;

	return m_value;
}

/* ---------- private code */

#endif // __BLAM_CSERIES_FLAGS_INL__

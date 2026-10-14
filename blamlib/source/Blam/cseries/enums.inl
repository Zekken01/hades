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

template<> inline bool c_enum<enum e_multiplayer_object_type,char>::operator<=(e_multiplayer_object_type const &other) const // 0x10A60140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_multiplayer_object_type@@D@@QBE_NABW4e_multiplayer_object_type@@@Z");
	// e_multiplayer_object_type const &other;

	return m_value <= (char)other;
}

template<> inline bool c_enum<enum e_hs_type,short>::operator<=(e_hs_type const &other) const // 0x10922480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_hs_type@@F@@QBE_NABW4e_hs_type@@@Z");
	// e_hs_type const &other;

	return m_value <= (short)other;
}

template<> inline bool c_enum<enum e_render_method_animated_parameter_type,long>::operator<=(e_render_method_animated_parameter_type const &other) const // 0x108E4140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??N?$c_enum@W4e_render_method_animated_parameter_type@@J@@QBE_NABW4e_render_method_animated_parameter_type@@@Z");
	// e_render_method_animated_parameter_type const &other;

	return m_value <= (long)other;
}

template<> inline c_enum<enum e_forge_object_property_setter_type,unsigned char>::operator unsigned char() const // 0x10CA6820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_forge_object_property_setter_type@@E@@QBEEXZ");
	// c_enum<enum e_forge_object_property_setter_type,unsigned char> const *const this;

	return m_value;
}

template<> inline c_enum<enum e_sound_compression,unsigned char>::operator unsigned char() const // 0x10A2BF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_compression@@E@@QBEEXZ");
	// c_enum<enum e_sound_compression,unsigned char> const *const this;

	return m_value;
}

template<> inline c_enum<enum e_sound_encoding,unsigned char>::operator unsigned char() const // 0x10A2BF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_encoding@@E@@QBEEXZ");
	// c_enum<enum e_sound_encoding,unsigned char> const *const this;

	return m_value;
}

template<> inline c_enum<enum e_sound_sample_rate,unsigned char>::operator unsigned char() const // 0x10A2BFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sound_sample_rate@@E@@QBEEXZ");
	// c_enum<enum e_sound_sample_rate,unsigned char> const *const this;

	return m_value;
}

template<> inline c_enum<enum e_multiplayer_teleporter_channel,unsigned char>::operator unsigned char() const // 0x1083B660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_multiplayer_teleporter_channel@@E@@QBEEXZ");
	// c_enum<enum e_multiplayer_teleporter_channel,unsigned char> const *const this;

	return m_value;
}

template<> inline c_enum<enum e_network_session_state,unsigned char>::operator e_network_session_state() const // 0x10EF77F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_network_session_state@@E@@QBE?AW4e_network_session_state@@XZ");

	return (e_network_session_state)m_value;
}

template<> inline c_enum<unsigned short,enum e_hs_type>::operator e_hs_type() const // 0x10F02A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@GW4e_hs_type@@@@QBE?AW4e_hs_type@@XZ");

	return m_value;
}

template<> inline c_enum<enum e_object_definition_runtime_flags,long>::operator bool() const // 0x108DE0B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_object_definition_runtime_flags@@J@@QBE_NXZ");

	return (bool)m_value;
}

template<> inline c_enum<enum e_object_type,char>::operator e_object_type() const // 0x1067D740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_object_type@@D@@QBE?AW4e_object_type@@XZ");

	return (e_object_type)m_value;
}

template<> inline c_enum<enum e_hs_script_type,short>::operator e_hs_script_type() const // 0x106E8170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_hs_script_type@@F@@QBE?AW4e_hs_script_type@@XZ");

	return (e_hs_script_type)m_value;
}

template<> inline c_enum<enum e_hs_type,short>::operator e_hs_type() const // 0x106E81A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_hs_type@@F@@QBE?AW4e_hs_type@@XZ");

	return (e_hs_type)m_value;
}

template<> inline c_enum<enum e_object_type,short>::operator short() const // 0x107A9430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_object_type@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_enum<enum e_hs_type,short>::operator short() const // 0x107B2D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_hs_type@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_enum<enum e_machine_type,short>::operator short() const // 0x10860DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_machine_type@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_enum<enum e_prt_vertex_type,char>::operator e_prt_vertex_type() const // 0x108E3E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_prt_vertex_type@@D@@QBE?AW4e_prt_vertex_type@@XZ");

	return (e_prt_vertex_type)m_value;
}

template<> inline c_enum<enum e_sorting_layer,char>::operator e_sorting_layer() const // 0x108E3EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sorting_layer@@D@@QBE?AW4e_sorting_layer@@XZ");

	return (e_sorting_layer)m_value;
}

template<> inline c_enum<enum e_vertex_type,char>::operator e_vertex_type() const // 0x108E3F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_vertex_type@@D@@QBE?AW4e_vertex_type@@XZ");

	return (e_vertex_type)m_value;
}

template<> inline c_enum<enum e_game_engine_event_audience,short>::operator short() const // 0x10C89FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_engine_event_audience@@F@@QBEFXZ");

	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_type,char>::operator e_multiplayer_object_type() const // 0x10CA6850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_multiplayer_object_type@@D@@QBE?AW4e_multiplayer_object_type@@XZ");

	return (e_multiplayer_object_type)m_value;
}

template<> inline c_enum<enum e_game_engine_type,long>::operator e_game_engine_type() const // 0x1068DF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_engine_type@@J@@QBE?AW4e_game_engine_type@@XZ");

	return (e_game_engine_type)m_value;
}

template<> inline c_enum<enum e_game_mode,long>::operator e_game_mode() const // 0x1068DF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_mode@@J@@QBE?AW4e_game_mode@@XZ");

	return (e_game_mode)m_value;
}

template<> inline c_enum<enum e_object_type,char>::operator char() const // 0x107B2D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_object_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_game_engine_symmetric_placement,char>::operator char() const // 0x1083B600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_engine_symmetric_placement@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_boundary_shape,char>::operator char() const // 0x1083B630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_multiplayer_object_boundary_shape@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_sorting_layer,char>::operator char() const // 0x108DE100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_sorting_layer@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_entry_point,long>::operator long() const // 0x108E3E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_entry_point@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_prt_vertex_type,char>::operator char() const // 0x108E3E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_prt_vertex_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_render_method_animated_parameter_type,long>::operator long() const // 0x108E3EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_render_method_animated_parameter_type@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_surface,long>::operator e_surface() const // 0x108E3F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_surface@@J@@QBE?AW4e_surface@@XZ");

	return (e_surface)m_value;
}

template<> inline c_enum<enum e_vertex_type,char>::operator char() const // 0x108E3F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_vertex_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_effect_camera_mode,char>::operator char() const // 0x1090FF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_effect_camera_mode@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_effect_event_part_scales,long>::operator long() const // 0x1090FF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_effect_event_part_scales@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_emission_shape,char>::operator char() const // 0x1090FFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_particle_emitter_emission_shape@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_model_axis,char>::operator char() const // 0x1090FFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_particle_emitter_model_axis@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_reference_axis,char>::operator char() const // 0x10910000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_particle_emitter_reference_axis@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_type,char>::operator char() const // 0x10A5FD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_multiplayer_object_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_game_engine_type,long>::operator long() const // 0x10A829B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_engine_type@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_game_mode,long>::operator long() const // 0x10A829E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_mode@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_gui_error_icon,char>::operator char() const // 0x10AD6380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_gui_error_icon@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_damage_reporting_type,long>::operator long() const // 0x10B26950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_damage_reporting_type@@J@@QBEJXZ");

	return m_value;
}

template<> inline c_enum<enum e_game_results_event_type,char>::operator char() const // 0x10B26980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_results_event_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_game_engine_event_type,char>::operator char() const // 0x10C8A020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_enum@W4e_game_engine_event_type@@D@@QBEDXZ");

	return m_value;
}

template<> inline c_enum<enum e_tag_field_type,long>::c_enum(long const &value) // 0x10F00610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0?$c_enum@W4e_tag_field_type@@J@@QAE@ABJ@Z");

	m_value = value;
}

template<> inline c_enum<enum e_tag_field_type,long>::c_enum(e_tag_field_type const &value) : // 0x10F00670
	c_enum(static_cast<long>(value))
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0?$c_enum@W4e_tag_field_type@@J@@QAE@ABW4e_tag_field_type@@@Z");
}

/* ---------- private code */

#endif // __BLAM_CSERIES_ENUMS_INL__

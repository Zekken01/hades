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
	return m_value <= (char)other;
}

template<> inline bool c_enum<enum e_hs_type,short>::operator<=(e_hs_type const &other) const // 0x10922480
{
	return m_value <= (short)other;
}

template<> inline bool c_enum<enum e_render_method_animated_parameter_type,long>::operator<=(e_render_method_animated_parameter_type const &other) const // 0x108E4140
{
	return m_value <= (long)other;
}

template<> inline c_enum<enum e_forge_object_property_setter_type,unsigned char>::operator unsigned char() const // 0x10CA6820
{
	return m_value;
}

template<> inline c_enum<enum e_sound_compression,unsigned char>::operator unsigned char() const // 0x10A2BF40
{
	return m_value;
}

template<> inline c_enum<enum e_sound_encoding,unsigned char>::operator unsigned char() const // 0x10A2BF70
{
	return m_value;
}

template<> inline c_enum<enum e_sound_sample_rate,unsigned char>::operator unsigned char() const // 0x10A2BFA0
{
	return m_value;
}

template<> inline c_enum<enum e_multiplayer_teleporter_channel,unsigned char>::operator unsigned char() const // 0x1083B660
{
	return m_value;
}

template<> inline c_enum<enum e_network_session_state,unsigned char>::operator e_network_session_state() const // 0x10EF77F0
{
	return (e_network_session_state)m_value;
}

template<> inline c_enum<unsigned short,enum e_hs_type>::operator e_hs_type() const // 0x10F02A30
{
	return m_value;
}

template<> inline c_enum<enum e_object_definition_runtime_flags,long>::operator bool() const // 0x108DE0B0
{
	return (bool)m_value;
}

template<> inline c_enum<enum e_object_type,char>::operator e_object_type() const // 0x1067D740
{
	return (e_object_type)m_value;
}

template<> inline c_enum<enum e_hs_script_type,short>::operator e_hs_script_type() const // 0x106E8170
{
	return (e_hs_script_type)m_value;
}

template<> inline c_enum<enum e_hs_type,short>::operator e_hs_type() const // 0x106E81A0
{
	return (e_hs_type)m_value;
}

template<> inline c_enum<enum e_object_type,short>::operator short() const // 0x107A9430
{
	return m_value;
}

template<> inline c_enum<enum e_hs_type,short>::operator short() const // 0x107B2D50
{
	return m_value;
}

template<> inline c_enum<enum e_machine_type,short>::operator short() const // 0x10860DA0
{
	return m_value;
}

template<> inline c_enum<enum e_prt_vertex_type,char>::operator e_prt_vertex_type() const // 0x108E3E50
{
	return (e_prt_vertex_type)m_value;
}

template<> inline c_enum<enum e_sorting_layer,char>::operator e_sorting_layer() const // 0x108E3EE0
{
	return (e_sorting_layer)m_value;
}

template<> inline c_enum<enum e_vertex_type,char>::operator e_vertex_type() const // 0x108E3F40
{
	return (e_vertex_type)m_value;
}

template<> inline c_enum<enum e_game_engine_event_audience,short>::operator short() const // 0x10C89FF0
{
	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_type,char>::operator e_multiplayer_object_type() const // 0x10CA6850
{
	return (e_multiplayer_object_type)m_value;
}

template<> inline c_enum<enum e_game_engine_type,long>::operator e_game_engine_type() const // 0x1068DF50
{
	return (e_game_engine_type)m_value;
}

template<> inline c_enum<enum e_game_mode,long>::operator e_game_mode() const // 0x1068DF80
{
	return (e_game_mode)m_value;
}

template<> inline c_enum<enum e_object_type,char>::operator char() const // 0x107B2D80
{
	return m_value;
}

template<> inline c_enum<enum e_game_engine_symmetric_placement,char>::operator char() const // 0x1083B600
{
	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_boundary_shape,char>::operator char() const // 0x1083B630
{
	return m_value;
}

template<> inline c_enum<enum e_sorting_layer,char>::operator char() const // 0x108DE100
{
	return m_value;
}

template<> inline c_enum<enum e_entry_point,long>::operator long() const // 0x108E3E20
{
	return m_value;
}

template<> inline c_enum<enum e_prt_vertex_type,char>::operator char() const // 0x108E3E80
{
	return m_value;
}

template<> inline c_enum<enum e_render_method_animated_parameter_type,long>::operator long() const // 0x108E3EB0
{
	return m_value;
}

template<> inline c_enum<enum e_surface,long>::operator e_surface() const // 0x108E3F10
{
	return (e_surface)m_value;
}

template<> inline c_enum<enum e_vertex_type,char>::operator char() const // 0x108E3F70
{
	return m_value;
}

template<> inline c_enum<enum e_effect_camera_mode,char>::operator char() const // 0x1090FF40
{
	return m_value;
}

template<> inline c_enum<enum e_effect_event_part_scales,long>::operator long() const // 0x1090FF70
{
	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_emission_shape,char>::operator char() const // 0x1090FFA0
{
	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_model_axis,char>::operator char() const // 0x1090FFD0
{
	return m_value;
}

template<> inline c_enum<enum e_particle_emitter_reference_axis,char>::operator char() const // 0x10910000
{
	return m_value;
}

template<> inline c_enum<enum e_multiplayer_object_type,char>::operator char() const // 0x10A5FD20
{
	return m_value;
}

template<> inline c_enum<enum e_game_engine_type,long>::operator long() const // 0x10A829B0
{
	return m_value;
}

template<> inline c_enum<enum e_game_mode,long>::operator long() const // 0x10A829E0
{
	return m_value;
}

template<> inline c_enum<enum e_gui_error_icon,char>::operator char() const // 0x10AD6380
{
	return m_value;
}

template<> inline c_enum<enum e_damage_reporting_type,long>::operator long() const // 0x10B26950
{
	return m_value;
}

template<> inline c_enum<enum e_game_results_event_type,char>::operator char() const // 0x10B26980
{
	return m_value;
}

template<> inline c_enum<enum e_game_engine_event_type,char>::operator char() const // 0x10C8A020
{
	return m_value;
}

template<> inline c_enum<enum e_tag_field_type,long>::c_enum(long const &value) // 0x10F00610
{
	m_value = value;
}

template<> inline c_enum<enum e_tag_field_type,long>::c_enum(e_tag_field_type const &value) : // 0x10F00670
	c_enum(static_cast<long>(value))
{
}

/* ---------- private code */

#endif // __BLAM_CSERIES_ENUMS_INL__

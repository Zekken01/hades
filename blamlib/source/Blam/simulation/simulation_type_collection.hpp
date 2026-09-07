#ifndef __BLAM_SIMULATION_SIMULATION_TYPE_COLLECTION_HPP__
#define __BLAM_SIMULATION_SIMULATION_TYPE_COLLECTION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/bitstream.hpp"
#include "Blam/simulation/simulation_types.hpp"

/* ---------- forward declarations */

class c_bitstream;
class c_simulation_event_definition;
class c_simulation_type_collection;
struct c_replication_outgoing_event;
struct c_simulation_entity_definition;
struct simulation_event_definition_return_value;

/* ---------- constants */

/* ---------- definitions */

class c_simulation_event_definition
{
public:
	virtual e_simulation_event_type event_type() const = 0;
	virtual char const *event_name() const = 0;
	virtual long payload_size() const = 0;
	virtual long number_of_entity_references() const = 0;
	virtual bool reference_delays_entity_deletion() const = 0;
	virtual bool event_can_be_transmitted(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const = 0;
	virtual long minimum_required_bits(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, long *) const = 0;
	virtual float calculate_relevance(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float) const = 0;
	virtual void write_description_to_string(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float, long, char *) const = 0;
	virtual simulation_event_definition_return_value *gather_requirements_data(simulation_event_definition_return_value *, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const = 0;
	virtual void event_payload_encode(long, void const *, c_bitstream *, bool) const = 0;
	virtual bool event_payload_decode(long, void *, c_bitstream *, bool) const = 0;
	virtual void prepare_event_data_for_gameworld(long, void *) = 0;
	virtual bool apply_game_event(long, long const *, long, void const *) = 0;
	c_simulation_event_definition(c_simulation_event_definition &); /* compiler_generated() */
	c_simulation_event_definition(c_simulation_event_definition const &); /* compiler_generated() */
	c_simulation_event_definition(); /* compiler_generated() */
	c_simulation_event_definition &operator=(c_simulation_event_definition &); /* compiler_generated() */
	c_simulation_event_definition &operator=(c_simulation_event_definition const &); /* compiler_generated() */
};
static_assert(sizeof(c_simulation_event_definition) == 4, "Invalid c_simulation_event_definition size");

class c_simulation_type_collection
{
public:
	void register_event_definition(e_simulation_event_type type, c_simulation_event_definition *definition);
private:
	long m_entity_type_count; // 0x0
	c_simulation_entity_definition *m_entities_types[32]; // 0x4
	long m_event_type_count; // 0x84
	c_simulation_event_definition *m_event_types[64]; // 0x88
};
static_assert(sizeof(c_simulation_type_collection) == 392, "Invalid c_simulation_type_collection size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_SIMULATION_TYPE_COLLECTION_HPP__

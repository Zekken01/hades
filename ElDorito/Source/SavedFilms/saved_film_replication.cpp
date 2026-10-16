#include "SavedFilms/saved_film_manager.hpp"

#include "Patches/Core.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <vector>

// Films of online games recorded as a client.
//
// A client of a distributed game simulates only its own players; the host sends it
// everything else - entity creations, updates and deletions, events, and player
// motion - as replication packets, which all reach the client through
// c_replication_scheduler::read_from_packet (it hands the packet to the event,
// entity and control views). A client's film therefore records each of those packets
// alongside its simulation updates, so that playback can feed them back to a client
// world in place of the host.
//
// A packet is recorded as the c_bitstream the scheduler was handed - its read
// position, accumulator and all - and the packet's bytes, so it can be read back
// exactly as the game read it:
//   s_recorded_packet header | c_bitstream (0xA0) | packet bytes

namespace SavedFilms
{
	namespace
	{
		unsigned long const k_replication_scheduler_read_from_packet_slot = 0x0161E990; // c_replication_scheduler vtable +0x14
		auto const replication_scheduler_read_from_packet = reinterpret_cast<long(__thiscall *)(void *, long *, void *)>(0x0049EEE0);

		auto const simulation_globals = reinterpret_cast<unsigned char *>(0x019A9FA0);
		unsigned long const k_simulation_globals_world = 0x14;
		unsigned long const k_world_next_update_number = 0x34;

		// c_bitstream (ManagedDonkey memory/bitstream.hpp).
		unsigned long const k_bitstream_size = 0xA0;
		unsigned long const k_bitstream_data = 0x00;
		unsigned long const k_bitstream_data_size_bytes = 0x08;

		struct s_recorded_packet
		{
			unsigned long version;
			long update_number; // the client world's next update when the packet arrived
			long sequence_number;
			unsigned long data_size;
		};
		static_assert(sizeof(s_recorded_packet) == 0x10, "Invalid s_recorded_packet size");

		unsigned long const k_recorded_packet_version = 1;

		long current_update_number()
		{
			unsigned char *world = *reinterpret_cast<unsigned char **>(simulation_globals + k_simulation_globals_world);
			return world ? *reinterpret_cast<long *>(world + k_world_next_update_number) : -1;
		}

		// Reforge properties. A client's map variant carries an object's placement but not
		// its reforge properties (the material, texture and flags kept in the boundary
		// fields of a shapeless object); the host sends those with each object it creates,
		// as ElDewrito's creation data (Patches/Simulation.cpp). Playback spawns the objects
		// from the film's map variant, so they are put back into it when the film closes.
		unsigned long const k_generic_entity_creation_decode_slots[] = { 0x01642F5C, 0x01643154 };
		typedef bool(__fastcall *creation_decode_t)(void *, void *, long, unsigned char *, void *, long);
		creation_decode_t g_creation_decode[2];

		long const k_map_variant_object_count = 640;
		long const k_creation_data_map_variant_index = 0x4; // short
		long const k_creation_data_reforge = 0x14; // s_simulation_reforge_object_creation_datum
		long const k_reforge_valid = 0x0;
		long const k_reforge_placement = 0x4; // position, forward, up
		long const k_reforge_properties = 0x28; // s_map_variant_placement_properties
		long const k_placement_size = 0x24;
		long const k_properties_size = 0x18;

		long const k_game_options_map_variant_objects = 0x590 + 0x130; // game_options.map_variant.objects
		long const k_variant_datum_size = 0x54;
		long const k_variant_datum_placement = 0x10;
		long const k_variant_datum_properties = 0x3C;

		struct s_received_placement
		{
			bool valid;
			unsigned char placement[k_placement_size];
			unsigned char properties[k_properties_size];
		};
		s_received_placement g_received_placements[k_map_variant_object_count];

		template <long index>
		bool __fastcall generic_entity_creation_decode_hook(void *definition, void *edx, long creation_data_size, unsigned char *creation_data, void *packet, long a5)
		{
			bool result = g_creation_decode[index](definition, edx, creation_data_size, creation_data, packet, a5);
			long map_variant_index = *reinterpret_cast<short const *>(creation_data + k_creation_data_map_variant_index);
			unsigned char const *reforge = creation_data + k_creation_data_reforge;
			if (result && map_variant_index >= 0 && map_variant_index < k_map_variant_object_count && reforge[k_reforge_valid])
			{
				s_received_placement &received = g_received_placements[map_variant_index];
				received.valid = true;
				memcpy(received.placement, reforge + k_reforge_placement, k_placement_size);
				memcpy(received.properties, reforge + k_reforge_properties, k_properties_size);
			}
			return result;
		}

		long __fastcall replication_scheduler_read_from_packet_hook(void *scheduler, void *, long *sequence_number, void *packet)
		{
			unsigned char const *bitstream = static_cast<unsigned char const *>(packet);
			unsigned char const *data = *reinterpret_cast<unsigned char *const *>(bitstream + k_bitstream_data);
			long data_size = *reinterpret_cast<long const *>(bitstream + k_bitstream_data_size_bytes);

			if (data && data_size > 0 && data_size < 0x10000)
			{
				s_recorded_packet header = { k_recorded_packet_version, current_update_number(), sequence_number ? *sequence_number : -1, unsigned long(data_size) };
				std::vector<unsigned char> record(sizeof(header) + k_bitstream_size + data_size);
				memcpy(record.data(), &header, sizeof(header));
				memcpy(record.data() + sizeof(header), bitstream, k_bitstream_size);
				memcpy(record.data() + sizeof(header) + k_bitstream_size, data, data_size);
				record_replication_packet(record.data(), long(record.size()));
			}

			return replication_scheduler_read_from_packet(scheduler, sequence_number, packet);
		}
	}

	namespace
	{
		// Diagnostics: what of a film's simulation queues reaches the game.
		auto const simulation_gamestate_entity_create_at_index = reinterpret_cast<long (*)(long)>(0x00471E60);
		auto const simulation_queue_entity_creation_apply = reinterpret_cast<void (*)(void const *)>(0x004A9220);
		auto const simulation_queue_entity_deletion_apply = reinterpret_cast<void (*)(void const *)>(0x004A9370);
		auto const simulation_queue_event_apply = reinterpret_cast<void (*)(void const *)>(0x004A8A60);

		long g_film_creations = 0;
		long g_film_creation_failures = 0;
		long g_film_deletions = 0;
		long g_film_events = 0;
		DWORD g_film_queue_report_time = 0;

		void report_film_queues()
		{
			DWORD now = GetTickCount();
			if (now - g_film_queue_report_time < 5000)
				return;
			g_film_queue_report_time = now;
			char text[160];
			sprintf_s(text, "film queues: %ld creations (%ld failed), %ld deletions, %ld events", g_film_creations, g_film_creation_failures, g_film_deletions, g_film_events);
			film_log(text);
		}

		long __cdecl create_at_index_hook(long gamestate_index)
		{
			long result = simulation_gamestate_entity_create_at_index(gamestate_index);
			if (film_is_playing() && result != gamestate_index)
			{
				g_film_creation_failures++;
				char text[128];
				sprintf_s(text, "film: entity creation at gamestate %08lX failed (got %08lX)", gamestate_index, result);
				film_log(text);
			}
			return result;
		}

		void __cdecl creation_apply_hook(void const *element)
		{
			if (film_is_playing())
				g_film_creations++, report_film_queues();
			simulation_queue_entity_creation_apply(element);
		}

		void __cdecl deletion_apply_hook(void const *element)
		{
			if (film_is_playing())
				g_film_deletions++, report_film_queues();
			simulation_queue_entity_deletion_apply(element);
		}

		// hs_object_hide (0x96E230), which scripts' object_hide calls: logged during playback.
		auto const object_set_hidden = reinterpret_cast<void (*)(long, bool)>(0x00B32D50);

		void __cdecl hs_object_hide_hook(long object_index, bool hidden)
		{
			if (film_is_playing())
			{
				char text[128];
				sprintf_s(text, "film: script object_hide %08lX %d", object_index, int(hidden));
				film_log(text);
			}
			if (object_index != -1)
				object_set_hidden(object_index, hidden);
		}

		void __cdecl event_apply_hook(void const *element)
		{
			if (film_is_playing())
				g_film_events++, report_film_queues();
			simulation_queue_event_apply(element);
		}
	}

	void apply_received_map_variant_placements(void *game_options)
	{
		if (!game_options)
			return;
		unsigned char *objects = static_cast<unsigned char *>(game_options) + k_game_options_map_variant_objects;
		for (long index = 0; index < k_map_variant_object_count; index++)
		{
			s_received_placement const &received = g_received_placements[index];
			if (!received.valid)
				continue;
			unsigned char *datum = objects + index * k_variant_datum_size;
			memcpy(datum + k_variant_datum_placement, received.placement, k_placement_size);
			memcpy(datum + k_variant_datum_properties, received.properties, k_properties_size);
		}
	}

	// Applied after Patches::Simulation, whose creation decode it wraps.
	void ApplyReplication()
	{
		Pointer(k_replication_scheduler_read_from_packet_slot).Write(reinterpret_cast<unsigned long>(&replication_scheduler_read_from_packet_hook));

		g_creation_decode[0] = *reinterpret_cast<creation_decode_t *>(k_generic_entity_creation_decode_slots[0]);
		g_creation_decode[1] = *reinterpret_cast<creation_decode_t *>(k_generic_entity_creation_decode_slots[1]);
		Pointer(k_generic_entity_creation_decode_slots[0]).Write(reinterpret_cast<unsigned long>(&generic_entity_creation_decode_hook<0>));
		Pointer(k_generic_entity_creation_decode_slots[1]).Write(reinterpret_cast<unsigned long>(&generic_entity_creation_decode_hook<1>));

		Hook(0x004A9288 - 0x00400000, reinterpret_cast<void *>(&create_at_index_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Hook(0x00467E40 - 0x00400000, reinterpret_cast<void *>(&creation_apply_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Hook(0x00467E50 - 0x00400000, reinterpret_cast<void *>(&deletion_apply_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Hook(0x00467E38 - 0x00400000, reinterpret_cast<void *>(&event_apply_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Hook(0x0096E230 - 0x00400000, reinterpret_cast<void *>(&hs_object_hide_hook)).Apply();

		Patches::Core::OnMapLoaded([](char const *)
		{
			g_film_creations = g_film_creation_failures = g_film_deletions = g_film_events = 0;
			clear_pending_replication_packets();
			memset(g_received_placements, 0, sizeof(g_received_placements));
		});
	}
}

#include "SavedFilms/saved_film_manager.hpp"

#include "Patches/Core.hpp"
#include "Pointer.hpp"

#include <string.h>
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

	void ApplyReplication()
	{
		Pointer(k_replication_scheduler_read_from_packet_slot).Write(reinterpret_cast<unsigned long>(&replication_scheduler_read_from_packet_hook));
		Patches::Core::OnMapLoaded([](char const *)
		{
			clear_pending_replication_packets();
		});
	}
}

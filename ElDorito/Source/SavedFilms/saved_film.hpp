#pragma once

// Saved films, ported from ManagedDonkey (game/source/saved_games/saved_film.cpp).
//
// A film is the game's s_blf_saved_film header (0x25B80 bytes: start-of-file, content
// header, author, 'flmh' film header holding the game_options the game was started
// with, and the 'flmd' data chunk header), followed by one record per simulation update
// and an '_eof' chunk. Each record is a 32-bit word - the update type in the top 2 bits,
// the payload size in the low 30 - and the update as the game's own
// simulation_update_write_to_buffer encodes it. Replaying the updates on top of the
// same game_options reproduces the game.

#include <stdio.h>
#include <string>
#include <vector>

struct s_game_options;

namespace SavedFilms
{
	enum
	{
		k_saved_film_header_size = 0x25B80,
		k_saved_film_maximum_size = 0x6400000,
		k_saved_film_update_size_bits = 30,
		k_saved_film_update_size_max = (1 << k_saved_film_update_size_bits) - 1,
		k_simulation_update_size = 0x1658,
	};

	enum e_saved_film_update_type
	{
		_saved_film_update_type_simulation_update = 0,
		_saved_film_update_type_gamestate,
		_saved_film_update_type_replication_packet, // ElDewrito: what an online client was sent (saved_film_replication.cpp)
	};

	class c_saved_film
	{
	public:
		c_saved_film();
		~c_saved_film();

		// mod_hash/mod_file name the ElDewrito mod package the game ran from ("" for none).
		bool open_for_write(char const *path, s_game_options const *options, char const *mod_hash, char const *mod_file);
		// A clip (snippet): the source film's updates up to stop_tick, played from
		// start_tick, as ManagedDonkey's mark_film_as_snippet marks it.
		static bool write_clip(char const *source_path, char const *clip_path, long start_tick, long stop_tick);
		bool is_snippet() const;
		long get_snippet_start_tick() const;

		bool has_mod_info() const; // films recorded before the mod was stored have none
		std::string get_mod_hash() const;
		std::string get_mod_file() const;
		bool write_simulation_update(void const *simulation_update);
		bool write_record(e_saved_film_update_type type, void const *data, long size);

		bool open_for_read(char const *path);
		// Reads the next record. Returns false at the end of the film or on a bad record.
		bool read_simulation_update(void *simulation_update_out);
		bool at_end() const;

		void close();

		bool is_open() const;
		bool is_writing() const;
		s_game_options const *get_game_options() const;
		s_game_options *get_game_options(); // written with the header when the film closes
		long get_current_tick() const;
		long get_length_in_ticks() const;
		std::string const &get_path() const;

	private:
		bool write_finish();
		unsigned long read_header_long(long offset) const;
		void write_header_long(long offset, unsigned long value);

		FILE *m_file;
		bool m_writing;
		bool m_big_endian; // the BLF chunk headers' byte order, as the game's constructor wrote them
		bool m_fatal_error;
		std::vector<unsigned char> m_header;
		long m_current_offset;
		long m_end_of_data_offset;
		long m_current_tick;
		std::string m_path;
	};

	// The film header's fields, as offsets into s_blf_saved_film.
	enum
	{
		k_film_header_offset = 0x188, // 'flmh'
		k_film_header_is_snippet_offset = k_film_header_offset + 0x92,
		k_film_header_game_options_offset = k_film_header_offset + 0x118,
		k_film_header_snippet_start_tick_offset = k_film_header_offset + 0x24C68,
		k_film_header_recorded_time_offset = k_film_header_offset + 0x24C60,
		k_film_header_length_in_ticks_offset = k_film_header_offset + 0x24C64,
		k_film_data_offset = 0x25B74, // 'flmd'

		// ElDewrito's addition, in the film header's padding_to_align_for_utility_drive:
		// the mod package the game ran from, as "HADESMOD", a 64-byte hash string and a
		// 260-byte file name.
		k_film_header_mod_offset = k_film_header_offset + 0x24C6C,
		k_film_header_mod_hash_offset = k_film_header_mod_offset + 8,
		k_film_header_mod_file_offset = k_film_header_mod_hash_offset + 64,
	};
}

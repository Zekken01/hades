#pragma once

#include <string>

// Saved film playback controls, used by the game's own film control pad
// (saved_film_control_pad.cpp) and the Film.* console commands.

namespace SavedFilms
{
	void ApplyAll();
	void ApplyControlPad();
	void ApplyReplication();
	void ApplyTheater();

	std::string get_films_directory();
	// While a film plays: its players' Server.PlayersInfoClient (ranks, emblems), keyed by
	// player index as recorded; "" when it has none.
	std::string get_film_players_info();
	bool play_film(char const *path); // starts the film from the main loop, as Film.Play does
	// The squad session's theater game is starting with these (the session's film's)
	// game_options: opens the film and sets them up for playback.
	bool begin_session_film(void *options, char const *path);

	// The film's mod package (as Film.Play switches to it): true once it is the loaded
	// one; otherwise starts loading it, which ModSessionManager passes on to the squad.
	bool prepare_film_mod(char const *path);
	std::string get_loaded_mod_hash();
	void update_theater(); // every frame (saved_film_theater.cpp)

	// Online-client films: the replication packets the host sent (saved_film_replication.cpp).
	void record_replication_packet(void const *data, long size);
	void clear_pending_replication_packets();
	// Puts the reforge properties a client was sent for each map variant object into
	// the map variant in a film's game_options.
	void apply_received_map_variant_placements(void *game_options);

	bool film_is_playing(); // a film's game is running
	bool film_is_ended(); // the film has played to its end

	float get_playback_speed();
	void set_playback_speed(float speed); // 0 pauses; 1 is normal speed
	void skip(float seconds); // forward by fast-forwarding, back by restarting and fast-forwarding
	// Chapters, as Halo 3's theater marks them on the timeline: every tenth of the film.
	long const k_film_chapter_count = 10;
	void skip_chapter(long direction); // to the next (1) or previous (-1) chapter mark
	float film_position_theta(); // how far through the playing film, 0-1
	bool is_skipping();
	void replay_film();
	void end_film(); // stops the film and returns to the main menu

	// Clips (ManagedDonkey's snippets): the film from start to stop, saved beside it.
	bool clip_is_recording();
	bool clip_start();
	bool clip_stop();
}

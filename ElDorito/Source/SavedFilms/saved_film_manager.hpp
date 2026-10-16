#pragma once

// Saved film playback controls, used by the game's own film control pad
// (saved_film_control_pad.cpp) and the Film.* console commands.

namespace SavedFilms
{
	void ApplyAll();
	void ApplyControlPad();
	void ApplyReplication();
	void ApplyTheater();

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
	bool is_skipping();
	void replay_film();
	void end_film(); // stops the film and returns to the main menu

	// Clips (ManagedDonkey's snippets): the film from start to stop, saved beside it.
	bool clip_is_recording();
	bool clip_start();
	bool clip_stop();
}

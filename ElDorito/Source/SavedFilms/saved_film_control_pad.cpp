#include "SavedFilms/saved_film_manager.hpp"

#include "Patch.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"

// The game's saved film control pad (c_saved_film_control_pad), after ManagedDonkey's
// gui_screen_saved_film_control_pad.cpp. The release build kept the screen but
// compiled out its calls into the film manager: play/pause, skip and replay did
// nothing, play was always shown and disabled, and skip back/forward were always
// disabled. The screen's update and list handlers are wrapped through its vtable and
// its menu-item filter is replaced, with the actions going to SavedFilms.

namespace SavedFilms
{
	namespace
	{
		// c_saved_film_control_pad's vtable and the slots replaced in it.
		unsigned long const k_control_pad_vtable = 0x0169F424;
		unsigned long const k_slot_update = 0x60;
		unsigned long const k_slot_handle_list_item_chosen = 0xC4;
		unsigned long const k_slot_handle_dialog_result = 0xC8;

		// The originals.
		auto const control_pad_update = reinterpret_cast<void(__thiscall *)(void *, unsigned long)>(0x00AE4D80);
		auto const control_pad_handle_list_item_chosen = reinterpret_cast<bool(__thiscall *)(void *, void const *, long, void *, void *)>(0x00AE4B10);
		auto const control_pad_handle_dialog_result = reinterpret_cast<bool(__thiscall *)(void *, void const *)>(0x00AE4A20);
		unsigned long const k_control_pad_update_enabled_menu_items = 0x00AE4F90;

		// GUI helpers.
		auto const c_gui_screen_widget_get_data = reinterpret_cast<void *(__thiscall *)(void *, long, long *)>(0x00AB0DB0);
		auto const c_gui_widget_get_child_list_widget = reinterpret_cast<void *(__thiscall *)(void *, long)>(0x00AB8AA0);
		auto const c_gui_widget_get_first_child_widget_by_type = reinterpret_cast<void *(__thiscall *)(void *, long)>(0x00AB8F80);
		auto const c_gui_widget_get_next_list_item_widget = reinterpret_cast<void *(__thiscall *)(void *, bool)>(0x00AB9230);

		long const k_gui_list_item = 5;

		// Virtual functions, as offsets into their vtables.
		unsigned long const k_widget_set_enabled = 0x24;
		unsigned long const k_list_item_get_element_handle = 0x18;
		unsigned long const k_data_get_string_id_value = 0x34;
		unsigned long const k_data_clear_disabled_elements = 0x5C;
		unsigned long const k_data_set_disabled_element = 0x60;

		// String ids (gui).
		long const k_saved_film_control_buttons = 0x105ED;
		long const k_button_list = 0x105EE;
		long const k_gui_item = 0x10010;
		long const k_skip_back = 0x105EF;
		long const k_skip_forward = 0x105F0;
		long const k_take_screenshot_upload = 0x105F2;
		long const k_take_screenshot_disabled = 0x105F3;
		long const k_record_clip = 0x105F4;
		long const k_play_film = 0x105F5;
		long const k_pause_film = 0x105F6;
		long const k_stop_recording = 0x105F7;
		long const k_replay_film = 0x105FB;
		long const k_end_preview = 0x105FC;
		long const k_dialog_in_game_exit_film_playback = 0x30017; // gui_dialog

		// c_dialog_result_message fields.
		unsigned long const k_dialog_result = 0x18;
		unsigned long const k_dialog_name = 0x1C;

		float const k_skip_seconds = 30.0f;

		template<typename t_function>
		t_function virtual_function(void *object, unsigned long offset)
		{
			return *reinterpret_cast<t_function *>(*static_cast<unsigned char **>(object) + offset);
		}

		bool get_item_name(void *data, void *list_item, long *name_out)
		{
			long element_handle = virtual_function<long(__thiscall *)(void *)>(list_item, k_list_item_get_element_handle)(list_item);
			if (element_handle == -1)
				return false;
			return virtual_function<bool(__thiscall *)(void *, long, long, long *)>(data, k_data_get_string_id_value)(data, element_handle, k_gui_item, name_out);
		}

		void set_enabled(void *widget, bool enabled)
		{
			virtual_function<void(__thiscall *)(void *, bool)>(widget, k_widget_set_enabled)(widget, enabled);
		}

		// Which items the pad lists: play or pause while the film runs, replay once it
		// has ended, record clip or stop recording (ManagedDonkey's snippet states:
		// none / recording). The screenshot upload variants are not supported.
		void __fastcall update_enabled_menu_items(void *control_pad, void *)
		{
			void *data = c_gui_screen_widget_get_data(control_pad, k_saved_film_control_buttons, nullptr);
			if (!data)
				return;

			auto disable = [data](long item)
			{
				virtual_function<void(__thiscall *)(void *, long, long)>(data, k_data_set_disabled_element)(data, k_gui_item, item);
			};

			virtual_function<void(__thiscall *)(void *)>(data, k_data_clear_disabled_elements)(data);
			disable(k_take_screenshot_upload);
			disable(k_take_screenshot_disabled);
			disable(k_end_preview);
			disable(clip_is_recording() ? k_record_clip : k_stop_recording);

			if (film_is_ended())
			{
				disable(k_play_film);
				disable(k_pause_film);
			}
			else
			{
				disable(get_playback_speed() > 0.0f ? k_play_film : k_pause_film);
				disable(k_replay_film);
			}
		}

		// The original update shows each button's icon and then disables play, skip
		// and clip outright; enable what the film can do.
		void __fastcall control_pad_update_hook(void *control_pad, void *, unsigned long current_milliseconds)
		{
			control_pad_update(control_pad, current_milliseconds);

			void *data = c_gui_screen_widget_get_data(control_pad, k_saved_film_control_buttons, nullptr);
			void *button_list = c_gui_widget_get_child_list_widget(control_pad, k_button_list);
			if (!data || !button_list)
				return;

			bool playing = film_is_playing();
			bool ended = film_is_ended();
			for (void *button = c_gui_widget_get_first_child_widget_by_type(button_list, k_gui_list_item);
				button;
				button = c_gui_widget_get_next_list_item_widget(button, true))
			{
				long name;
				if (!get_item_name(data, button, &name))
					continue;

				switch (name)
				{
				case k_play_film:
				case k_pause_film:
				case k_skip_forward:
					set_enabled(button, playing && !ended && !is_skipping());
					break;
				case k_skip_back:
					set_enabled(button, playing && !is_skipping());
					break;
				case k_replay_film:
					set_enabled(button, playing);
					break;
				case k_record_clip:
					set_enabled(button, playing && !ended && !is_skipping());
					break;
				case k_stop_recording:
					set_enabled(button, clip_is_recording());
					break;
				}
			}
		}

		bool __fastcall control_pad_handle_list_item_chosen_hook(void *control_pad, void *, void const *message, long list_name, void *list_item, void *data)
		{
			long name;
			if (list_name == k_button_list && get_item_name(data, list_item, &name))
			{
				switch (name)
				{
				case k_play_film:
					set_playback_speed(1.0f);
					return true;
				case k_pause_film:
					set_playback_speed(0.0f);
					return true;
				case k_skip_back:
					skip(-k_skip_seconds);
					return true;
				case k_skip_forward:
					skip(k_skip_seconds);
					return true;
				case k_replay_film:
					replay_film();
					return true;
				case k_record_clip:
					clip_start();
					return true;
				case k_stop_recording:
					clip_stop();
					return true;
				}
			}
			return control_pad_handle_list_item_chosen(control_pad, message, list_name, list_item, data);
		}

		// "Exit film playback?": the first choice leaves the film.
		bool __fastcall control_pad_handle_dialog_result_hook(void *control_pad, void *, void const *message)
		{
			unsigned char const *result_message = static_cast<unsigned char const *>(message);
			bool exit_film = *reinterpret_cast<long const *>(result_message + k_dialog_name) == k_dialog_in_game_exit_film_playback
				&& *reinterpret_cast<long const *>(result_message + k_dialog_result) == 0;

			bool handled = control_pad_handle_dialog_result(control_pad, message);
			if (exit_film)
				end_film();
			return handled;
		}
	}

	namespace
	{
		/* ---------- tag fixups */

		// Halo Online's UI tags name the datasource column the control pad reads (and the
		// text widgets that show it) global::item, where the code asks for gui::gui_item.
		// Every lookup failed, so the pad never knew which button was which: each showed
		// its default icon and no action ran. ManagedDonkey renames them back after the
		// tags load (apply_gui_datasource/skin_definition_tag_instance_modification).
		auto const tag_iterator_new = reinterpret_cast<void (*)(void *, unsigned long)>(0x005033E0);
		auto const tag_iterator_next = reinterpret_cast<long (*)(void *)>(0x00503400);
		auto const tag_get = reinterpret_cast<void *(*)(unsigned long, long)>(0x00503370);

		long const k_global_item = 0x5C0;

		struct s_tag_block
		{
			long count;
			unsigned char *address;
			long definition;
		};

		template<typename t_visit>
		void for_each_tag(unsigned long group_tag, t_visit visit)
		{
			unsigned char iterator[20];
			tag_iterator_new(iterator, group_tag);
			for (long tag_index; (tag_index = tag_iterator_next(iterator)) != -1; )
			{
				if (unsigned char *definition = static_cast<unsigned char *>(tag_get(group_tag, tag_index)))
					visit(definition);
			}
		}

		void rename_global_item(long *string_id, long *renamed)
		{
			if (*string_id == k_global_item)
			{
				*string_id = k_gui_item;
				++*renamed;
			}
		}

		void fix_gui_item_string_ids(char const *)
		{
			long renamed = 0;

			// 'dsrc': elements (+0x10, 0x28 each) -> string id nuggets (+0x18, 8 each, name first).
			for_each_tag('dsrc', [&renamed](unsigned char *datasource)
			{
				s_tag_block const &elements = *reinterpret_cast<s_tag_block *>(datasource + 0x10);
				for (long element = 0; element < elements.count; element++)
				{
					s_tag_block const &nuggets = *reinterpret_cast<s_tag_block *>(elements.address + element * 0x28 + 0x18);
					for (long nugget = 0; nugget < nuggets.count; nugget++)
						rename_global_item(reinterpret_cast<long *>(nuggets.address + nugget * 8), &renamed);
				}
			});

			// 'skn3': text blocks (+0x4, 0x4C each): widget_identifier +0x14, value_identifier +0x40.
			for_each_tag('skn3', [&renamed](unsigned char *skin)
			{
				s_tag_block const &text_blocks = *reinterpret_cast<s_tag_block *>(skin + 0x4);
				for (long block = 0; block < text_blocks.count; block++)
				{
					unsigned char *text_block = text_blocks.address + block * 0x4C;
					rename_global_item(reinterpret_cast<long *>(text_block + 0x14), &renamed);
					rename_global_item(reinterpret_cast<long *>(text_block + 0x40), &renamed);
				}
			});
		}
	}

	namespace
	{
		/* ---------- opening the control pad */

		// c_saved_film_director::update opens the control pad when X is released after
		// being pressed with no pad up. In the release build the film manager's "no ticks
		// remaining" check, which picks Eject over Play, was compiled out to true, and the
		// code after it opened the pad every frame in an authoritative playback, so the
		// pad came straight back when closed. And the X press that closes the pad, still
		// held once the pad has gone, armed the director, so its release reopened it.
		//
		// Replaces 0x727CE0-0x727CFE: dl is X's down frames, edi the director, bl whether X
		// was released after a press, [ebp-0xD] play_or_eject. X arms the director only
		// when freshly pressed; the pad opens only on its release; Eject is offered once
		// the film has ended.
		unsigned long const k_director_x_update = 0x00727CE0;
		unsigned long const k_director_open_control_pad = 0x00727CFE;
		unsigned long const k_director_skip_control_pad = 0x00727D78;
		unsigned long const k_director_x_authoritative_only = 0x00727CA8; // jz: X does nothing in a client's playback

		bool __cdecl director_film_ended()
		{
			return film_is_ended();
		}

		__declspec(naked) void director_x_update_hook()
		{
			__asm
			{
				movzx   eax, dl
				cmp     byte ptr [edi + 0x159], 0
				jnz     was_down
				cmp     eax, 1
				sete    al
				jmp     store
			was_down:
				test    eax, eax
				setnz   al
			store:
				mov     byte ptr [edi + 0x159], al

				call    director_film_ended
				mov     byte ptr [ebp - 0x0D], al

				test    bl, bl
				jz      no_pad
				push    k_director_open_control_pad
				ret
			no_pad:
				push    k_director_skip_control_pad
				ret
			}
		}
	}

	void ApplyControlPad()
	{
		Hook(k_director_x_update - 0x00400000, reinterpret_cast<void *>(&director_x_update_hook)).Apply();
		Patch::NopFill(Pointer::Base(k_director_x_authoritative_only - 0x00400000), 2);
		Patches::Core::OnMapLoaded(fix_gui_item_string_ids);
		Pointer(k_control_pad_vtable + k_slot_update).Write(reinterpret_cast<unsigned long>(&control_pad_update_hook));
		Pointer(k_control_pad_vtable + k_slot_handle_list_item_chosen).Write(reinterpret_cast<unsigned long>(&control_pad_handle_list_item_chosen_hook));
		Pointer(k_control_pad_vtable + k_slot_handle_dialog_result).Write(reinterpret_cast<unsigned long>(&control_pad_handle_dialog_result_hook));
		Hook(k_control_pad_update_enabled_menu_items - 0x00400000, reinterpret_cast<void *>(&update_enabled_menu_items)).Apply();
	}
}

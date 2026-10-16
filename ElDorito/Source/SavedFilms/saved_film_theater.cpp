#include "SavedFilms/saved_film_manager.hpp"

#include "Patches/Core.hpp"

#include <string.h>

// The theater lobby, reached from the main menu.
//
// c_main_menu_screen_widget::handle_list_item_chosen still sends gui::theater to the
// theater pregame lobby, and the menu's string list still has its text, but Halo
// Online's main menu datasource (ui\halox\main_menu\main_menu_list) dropped the
// element. It is put back after the tags load, after Forge (gui::mapeditor) as in
// Halo 3.

namespace SavedFilms
{
	namespace
	{
		auto const tag_iterator_new = reinterpret_cast<void (*)(void *, unsigned long)>(0x005033E0);
		auto const tag_iterator_next = reinterpret_cast<long (*)(void *)>(0x00503400);
		auto const tag_get = reinterpret_cast<void *(*)(unsigned long, long)>(0x00503370);

		long const k_global_name = 0x2AA;
		long const k_gui_main_menu = 0x10083;
		long const k_gui_mapeditor = 0x1007B;
		long const k_gui_theater = 0x1007C;

		struct s_tag_block
		{
			long count;
			void *address;
			long definition;
		};
		static_assert(sizeof(s_tag_block) == 0xC, "Invalid s_tag_block size");

		struct s_string_id_data_nugget
		{
			long name;
			long value;
		};

		// 'dsrc' (ManagedDonkey's s_datasource_definition): name, then the elements.
		struct s_datasource_element
		{
			s_tag_block integer_nuggets;
			s_tag_block text_nuggets;
			s_tag_block string_id_nuggets;
			long submenu_control_name;
		};
		static_assert(sizeof(s_datasource_element) == 0x28, "Invalid s_datasource_element size");

		long const k_datasource_name = 0x0;
		long const k_datasource_elements = 0x10;

		long const k_main_menu_elements_max = 32;
		s_datasource_element g_main_menu_elements[k_main_menu_elements_max];
		s_string_id_data_nugget g_theater_nuggets[] = { { k_global_name, k_gui_theater } };

		long element_name(s_datasource_element const &element)
		{
			auto const *nuggets = static_cast<s_string_id_data_nugget const *>(element.string_id_nuggets.address);
			for (long index = 0; index < element.string_id_nuggets.count; index++)
			{
				if (nuggets[index].name == k_global_name)
					return nuggets[index].value;
			}
			return -1;
		}

		void add_theater_to_main_menu(unsigned char *datasource)
		{
			s_tag_block &elements = *reinterpret_cast<s_tag_block *>(datasource + k_datasource_elements);
			if (elements.count <= 0 || elements.count >= k_main_menu_elements_max || elements.address == g_main_menu_elements)
				return;

			auto const *old_elements = static_cast<s_datasource_element const *>(elements.address);
			long insert_at = elements.count;
			for (long index = 0; index < elements.count; index++)
			{
				long name = element_name(old_elements[index]);
				if (name == k_gui_theater)
					return;
				if (name == k_gui_mapeditor)
					insert_at = index + 1;
			}

			s_datasource_element theater = {};
			theater.integer_nuggets.definition = old_elements[0].integer_nuggets.definition;
			theater.text_nuggets.definition = old_elements[0].text_nuggets.definition;
			theater.string_id_nuggets = { _countof(g_theater_nuggets), g_theater_nuggets, old_elements[0].string_id_nuggets.definition };

			memcpy(g_main_menu_elements, old_elements, insert_at * sizeof(s_datasource_element));
			g_main_menu_elements[insert_at] = theater;
			memcpy(g_main_menu_elements + insert_at + 1, old_elements + insert_at, (elements.count - insert_at) * sizeof(s_datasource_element));

			elements.address = g_main_menu_elements;
			elements.count++;
		}

		void main_menu_add_theater(char const *)
		{
			unsigned char iterator[20];
			tag_iterator_new(iterator, 'dsrc');
			for (long tag_index; (tag_index = tag_iterator_next(iterator)) != -1; )
			{
				auto *datasource = static_cast<unsigned char *>(tag_get('dsrc', tag_index));
				if (datasource && *reinterpret_cast<long *>(datasource + k_datasource_name) == k_gui_main_menu)
					add_theater_to_main_menu(datasource);
			}
		}
	}

	void ApplyTheater()
	{
		Patches::Core::OnMapLoaded(main_menu_add_theater);
	}
}

#ifndef __BLAM_MULTITHREADING_SYNCHRONIZATION_CRITICAL_SECTION_HPP__
#define __BLAM_MULTITHREADING_SYNCHRONIZATION_CRITICAL_SECTION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

enum e_critical_section
{
	_critical_section_netdebug = 4, // 0x0004
	_critical_section_user_interface_memory_pool = 19, // 0x0013
	_critical_section_gui_bitmap_storage = 20, // 0x0014
	_critical_section_storage_device = 21, // 0x0015
	_critical_section_levels = 22, // 0x0016
	_critical_section_overlapped_task = 24, // 0x0018
	_critical_section_overlapped_memory_pool = 25, // 0x0019
	_critical_section_network_http_request_queue = 27, // 0x001B
	_critical_section_online_lsp_manager = 28, // 0x001C
	_critical_section_online_files = 29, // 0x001D
	_critical_section_bink = 33, // 0x0021 '!'
	_critical_section_font_cache = 37, // 0x0025 '%'
	_critical_section_cache_file_tag_resource_runtime = 47, // 0x002F '/'
	_critical_section_observer_global_update_list = 49, // 0x0031 '1'
	_critical_section_network_http_buffer_downloader = 50, // 0x0032 '2'
	_critical_section_network_storage_cache = 50, // 0x0032 '2'
	_critical_section_global_preferences = 57, // 0x0039 '9'
	_critical_section_hf2p_render_texture = 58, // 0x003A ':'
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MULTITHREADING_SYNCHRONIZATION_CRITICAL_SECTION_HPP__

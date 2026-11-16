/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/bink/bink.hpp"
#include "Blam/cache/cache_file_tag_resources.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "mods/tag_resource_streaming.hpp"

#include <Windows.h>
#include <cstdarg>
#include <cstring>
#include <detours.h>

// hades: makes play_bink_movie_from_tag (and predict_bink_movie_from_tag) work.
//
// The engine plays a bink tag straight out of its tag resource, which it only finds when
// the resource is already in the resource cache. Nothing pages a bink tag in on demand
// (main_render_predict_tag_resources is empty in this build), so a bink tag that the
// active zone set does not reach, such as one only a script references, could never
// play. Its resource is streamed here into a buffer of its own, and the engine's lookups
// are handed that buffer.
//
// Tag movies (flag 0x1000) were also never drawn fullscreen, since bink_playback_render
// left them to the shop video's render-to-texture view, and in-game the bink memory pool
// is 4 MB, too small for a movie's frame buffers.
//
// Halo 3's render texture camera could also show the playing movie instead of its camera
// view, putting it on an in-game surface. Saber stripped the flag that chose this
// (s_render_texture_camera_globals::bink_is_active), the script function that set it and
// the branch of c_player_view::create_frame_textures that drew it. The flag is back in the
// byte the structure still leaves free after dynamic_lights, set by the texture_camera_bink
// script function (Scripting/HaloScript/Methods/HsRenderMethods.cpp), and the branch is
// restored here.

/* ---------- constants */

namespace
{
	unsigned long const k_bink_tag = 'bink';
	unsigned long const k_bink_flag_fill_screen = 0x10;
	unsigned long const k_bink_flag_from_tag = 0x1000;
	unsigned long const k_main_menu_bink_memory_size = 0x2200000;
	long const k_render_target_type_texture_camera = 1;
	long const k_texture_camera_render_target_width = 512;  // c_dynamic_render_targets::allocate_global_temporary_buffers
	long const k_texture_camera_render_target_height = 288;
	unsigned long const k_render_texture_camera_active_offset = 0x0;
	unsigned long const k_render_texture_camera_bink_is_active_offset = 0x2;  // free byte after dynamic_lights (0x1)
}

/* ---------- definitions */

namespace
{
	// What prepare_bink_movie_for_playback_async and bink_playback_update_internal read
	// from a bink tag's resource: the address of the movie at 0xC.
	struct s_bink_resource_stand_in
	{
		unsigned char __pad0[0xC];
		void const *address; // 0xC
		unsigned char __pad10[0x10];
	};

	// One allocation request for allocate_aligned_buffers (0x94B150), laid out as the
	// engine's frame-buffer setup (0x618010) fills it.
	struct s_bink_plane_buffer_description
	{
		void **buffer; // 0x0: receives the address carved out for this plane
		long count; // 0x4
		long size; // 0x8
		long reserved_size; // 0xC: size plus the alignment slack
		long alignment_bits; // 0x10
	};
	static_assert(sizeof(s_bink_plane_buffer_description) == 20, "Invalid s_bink_plane_buffer_description size");

	struct s_streamed_bink
	{
		long tag_index;
		long resource_handle;
		void *buffer;
		unsigned long buffer_size;
		c_async_completion_flag completion;
		bool streaming;
		bool ready;
		bool play_when_ready;
		bool used;
		s_bink_resource_stand_in stand_in;
	};
}

/* ---------- prototypes */

extern void bink_patches_apply();
extern void render_texture_camera_set_bink(bool bink_is_active);

namespace
{
	void *bink_tag_resource_try_to_get(void *resource);
	bool bink_tag_resource_available(void *resource);
	void play_bink_movie_from_tag_hook(long tag_index);
	void predict_bink_movie_from_tag_hook(long tag_index);
	void bink_playback_update_hook();
	void bink_playback_render_hook();
	void bink_playback_grab_memory_hook();
	void bink_playback_return_memory_hook();
	bool bink_allocate_frame_plane_buffers(IDirect3DTexture9 **textures, BINKFRAMEPLANESET *planes, bool allocate_all, void *allocation, void *out_base, void *out_size);
	void __fastcall c_player_view_create_frame_textures_hook(void *player_view, void *, long player_window_index);
}

namespace eldorado
{
	// Functions in eldorado.exe used by the texture camera's bink branch, named from the
	// game's own symbols.
	static auto const c_player_view_create_frame_textures = reinterpret_cast<void (__thiscall *)(void *, long)>(0xA38D70);
	static auto const c_rasterizer_set_gprs_allocation = reinterpret_cast<long (*)(long)>(0xA228C0);
	static auto const c_dynamic_render_targets_idle = reinterpret_cast<void (*)()>(0xA75020);
	static auto const c_dynamic_render_targets_target_allocated = reinterpret_cast<bool (*)(long)>(0xA75100);
	static auto const c_dynamic_render_targets_get_target_index_from_type = reinterpret_cast<long (*)(long)>(0xA75010);
	static auto const c_dynamic_render_targets_allocate_target = reinterpret_cast<long (*)(long, long, long, long, long, char const *)>(0xA74E70);
	static auto const c_dynamic_render_targets_get_target = reinterpret_cast<void *(*)(unsigned short)>(0xA74FC0);  // s_dynamic_render_target; accumulation_surface at 0xC
	static auto const c_render_globals_get_frame_index = reinterpret_cast<long (*)()>(0xA29590);
	static auto const interface_get_current_display_settings = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
	static auto const c_view_begin = reinterpret_cast<void (*)(void *)>(0xA289D0);
	static auto const c_view_end = reinterpret_cast<void (*)()>(0xA28B10);
	static auto const c_rasterizer_begin = reinterpret_cast<void (*)(short_rectangle2d, short_rectangle2d)>(0xA1F7E0);
	static auto const c_rasterizer_set_render_target_texture = reinterpret_cast<void (*)(long, long, long, long)>(0xA48DD0);  // (index, c_rasterizer_texture_ref, face, level)
	static auto const c_rasterizer_set_render_target_surface = reinterpret_cast<void (*)(long, long, unsigned long)>(0xA48E40);  // (index, e_surface, force_is_srgb)
	static auto const c_rasterizer_set_depth_stencil_surface = reinterpret_cast<void (*)(long)>(0xA48CB0);
	static auto const c_rasterizer_clear = reinterpret_cast<void (*)(unsigned long, unsigned long, float, unsigned char)>(0xA213F0);
	static auto const c_rasterizer_enable_clip_planes = reinterpret_cast<void (*)(long)>(0xA22B50);
	static auto const c_rasterizer_set_scissor_rect = reinterpret_cast<void (*)(short_rectangle2d const *)>(0xA239B0);
	static auto const c_rasterizer_set_color_write_enable = reinterpret_cast<void (*)(long, long)>(0xA231E0);
	static auto const c_rasterizer_set_z_buffer_mode = reinterpret_cast<void (*)(long)>(0xA247E0);
	static auto const c_rasterizer_set_cull_mode = reinterpret_cast<void (*)(long)>(0xA232D0);
	static auto const c_rasterizer_set_srgbwrite = reinterpret_cast<void (*)(bool)>(0xA48EB0);
	void const *const c_bink_texture_view_vftable = reinterpret_cast<void const *>(0x1681F1C);  // the shop video's view; every member does nothing
	void *&c_player_view_x_current_player_view = *reinterpret_cast<void **>(0x50DEDF0);
}

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols where it has them.
	static auto const tag_get = reinterpret_cast<void *(*)(unsigned long, long)>(0x503370);
	static auto const tag_resource_available = reinterpret_cast<bool (*)(void *)>(0x563DC0);
	static auto const tag_resource_try_to_get = reinterpret_cast<void *(*)(void *)>(0x563F30);
	static auto const play_bink_movie_from_tag = reinterpret_cast<void (*)(long)>(0x618260);
	static auto const predict_bink_movie_from_tag = reinterpret_cast<void (*)(long)>(0x618410);
	static auto const bink_playback_update = reinterpret_cast<void (*)()>(0x6173A0);
	static auto const bink_playback_active = reinterpret_cast<bool (*)()>(0x616910);
	static auto const bink_draw_frame = reinterpret_cast<void (*)()>(0x616420);
	static auto const c_rasterizer_clear_sampler_textures = reinterpret_cast<void (*)(unsigned long)>(0xA22AB0);
	static auto const allocate_aligned_buffers = reinterpret_cast<bool (*)(void *, long, s_bink_plane_buffer_description *, char const *, void *, void *)>(0x94B150);  // no symbol; named from what it does
	static auto bink_playback_grab_memory = reinterpret_cast<void (*)()>(0x616A30);  // detoured
	static auto bink_playback_return_memory = reinterpret_cast<void (*)()>(0x616D00);  // detoured
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	s_streamed_bink g_streamed_bink = { -1, -1 };
	void *g_bink_memory_pool = nullptr;
}

/* ---------- public code */

void bink_patches_apply()
{
	Hook(0x218616, bink_tag_resource_try_to_get, static_cast<__int32>(HookFlags::IsCall)).Apply();  // prepare_bink_movie_for_playback_async
	Hook(0x2174B2, bink_tag_resource_available, static_cast<__int32>(HookFlags::IsCall)).Apply();  // bink_playback_update_internal
	Hook(0x2174C3, bink_tag_resource_try_to_get, static_cast<__int32>(HookFlags::IsCall)).Apply();  // bink_playback_update_internal
	Hook(0x34199A, play_bink_movie_from_tag_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();  // play_bink_movie_from_tag's script evaluate
	Hook(0x33047A, predict_bink_movie_from_tag_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();  // predict_bink_movie_from_tag's script evaluate
	Hook(0x105DBE, bink_playback_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();  // main_loop_body_main_part
	Hook(0x216CC0, bink_playback_render_hook).Apply();
	Hook(0x218733, bink_allocate_frame_plane_buffers, static_cast<__int32>(HookFlags::IsCall)).Apply();  // prepare_bink_movie_for_playback_async
	Hook(0x204707, c_player_view_create_frame_textures_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();  // main_render_game
	Hook(0x204D98, c_player_view_create_frame_textures_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();  // main_render_view
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&reinterpret_cast<PVOID &>(eldorado::bink_playback_grab_memory), reinterpret_cast<PVOID>(bink_playback_grab_memory_hook));
	DetourAttach(&reinterpret_cast<PVOID &>(eldorado::bink_playback_return_memory), reinterpret_cast<PVOID>(bink_playback_return_memory_hook));
	DetourTransactionCommit();
}

// Halo 3's texture_camera_bink. The texture camera still has to be on (texture_camera_on)
// for the movie to be drawn to it.
void render_texture_camera_set_bink(bool bink_is_active)
{
	unsigned char *globals = reinterpret_cast<unsigned char *>(tls_getd().render_texture_globals);
	if (globals)
		globals[k_render_texture_camera_bink_is_active_offset] = bink_is_active;
}

/* ---------- private code */

namespace
{
	// bink_globals fields the hades s_bink_globals does not name yet.
	template <typename t_type>
	t_type &bink_globals_field(unsigned long offset)
	{
		return *reinterpret_cast<t_type *>(reinterpret_cast<char *>(s_bink_globals::get()) + offset);
	}

	unsigned long &bink_playback_flags() { return bink_globals_field<unsigned long>(0x14); }
	long bink_memory_size_for_map() { return bink_globals_field<long>(0x12C); }  // use_large_bink_size
	void *&bink_memory_pool_base() { return bink_globals_field<void *>(0x350); }
	unsigned long &bink_memory_pool_offset() { return bink_globals_field<unsigned long>(0x354); }
	unsigned long &bink_memory_pool_size() { return bink_globals_field<unsigned long>(0x358); }

	void log_error(char const *format, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Error, std::string("bink: ") + buffer);
	}

	void *bink_tag_get_resource(long tag_index)
	{
		void *tag = tag_index == -1 ? nullptr : eldorado::tag_get(k_bink_tag, tag_index);
		return tag ? static_cast<char *>(tag) + 4 : nullptr;
	}

	long bink_resource_handle(void const *resource)
	{
		return *static_cast<long const *>(resource);
	}

	// Read through the calling thread's copy: the main thread's for scripts, the render
	// thread's mirror while drawing.
	bool render_texture_camera_bink_active()
	{
		unsigned char const *globals = reinterpret_cast<unsigned char const *>(tls_getd().render_texture_globals);
		return globals && globals[k_render_texture_camera_active_offset] && globals[k_render_texture_camera_bink_is_active_offset];
	}

	bool streamed_bink_matches(void const *resource)
	{
		return g_streamed_bink.ready && resource && bink_resource_handle(resource) == g_streamed_bink.resource_handle;
	}

	bool streamed_bink_in_use()
	{
		s_bink_globals *bink_globals = s_bink_globals::get();
		return bink_globals->playing
			|| bink_globals->bink_runtime.bink_h
			|| bink_globals->pending_prediction_message.queued_state
			|| bink_globals->bink_runtime.prediction_message.queued_state;
	}

	void streamed_bink_release()
	{
		if (g_streamed_bink.buffer)
			VirtualFree(g_streamed_bink.buffer, 0, MEM_RELEASE);
		g_streamed_bink.tag_index = -1;
		g_streamed_bink.resource_handle = -1;
		g_streamed_bink.buffer = nullptr;
		g_streamed_bink.buffer_size = 0;
		g_streamed_bink.streaming = false;
		g_streamed_bink.ready = false;
		g_streamed_bink.play_when_ready = false;
		g_streamed_bink.used = false;
		g_streamed_bink.stand_in = {};
	}

	// Starts streaming a bink tag's resource. The movie is the resource's whole page.
	void streamed_bink_begin(long tag_index, void const *resource, bool play_when_ready)
	{
		long resource_handle = bink_resource_handle(resource);
		if (g_streamed_bink.resource_handle == resource_handle && (g_streamed_bink.streaming || g_streamed_bink.ready))
		{
			g_streamed_bink.tag_index = tag_index;
			g_streamed_bink.play_when_ready |= play_when_ready;
			return;
		}
		if (g_streamed_bink.streaming)
		{
			log_error("cannot stream bink tag 0x%lX while tag 0x%lX is still streaming", tag_index, g_streamed_bink.tag_index);
			return;
		}
		if (g_streamed_bink.ready && g_streamed_bink.used && streamed_bink_in_use())
		{
			log_error("cannot stream bink tag 0x%lX while tag 0x%lX is playing", tag_index, g_streamed_bink.tag_index);
			return;
		}
		streamed_bink_release();

		void *resource_runtime_manager = *reinterpret_cast<void **>(0x23916C8);
		s_cache_file_tag_resource_table_runtime *resource_table = *reinterpret_cast<s_cache_file_tag_resource_table_runtime **>(static_cast<char *>(resource_runtime_manager) + 0x24);
		short resource_index = static_cast<short>(resource_handle);
		if (resource_index < 0 || resource_index >= resource_table->count)
		{
			log_error("bink tag 0x%lX has no resource (handle 0x%lX)", tag_index, resource_handle);
			return;
		}
		unsigned long buffer_size = (resource_table->resources[resource_index]->uncompressed_block_size + 0xFFF) & ~0xFFFul;
		void *buffer = VirtualAlloc(nullptr, buffer_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (!buffer)
		{
			log_error("cannot allocate %lu bytes for bink tag 0x%lX", buffer_size, tag_index);
			return;
		}
		g_streamed_bink.tag_index = tag_index;
		g_streamed_bink.resource_handle = resource_handle;
		g_streamed_bink.buffer = buffer;
		g_streamed_bink.buffer_size = buffer_size;
		g_streamed_bink.play_when_ready = play_when_ready;
		g_streamed_bink.streaming = true;
		if (tag_resource_stream_async(resource_handle, buffer, buffer_size, &g_streamed_bink.completion) == -1)
		{
			log_error("cannot stream the resource of bink tag 0x%lX (handle 0x%lX)", tag_index, resource_handle);
			streamed_bink_release();
		}
	}

	// The movie should open the page; a bink file starts with BIK or KB2.
	bool streamed_bink_find_movie()
	{
		unsigned char const *data = static_cast<unsigned char const *>(g_streamed_bink.buffer);
		unsigned long limit = g_streamed_bink.buffer_size < 0x1000 ? g_streamed_bink.buffer_size : 0x1000;
		for (unsigned long offset = 0; offset + 3 <= limit; offset += 4)
		{
			if (memcmp(data + offset, "BIK", 3) == 0 || memcmp(data + offset, "KB2", 3) == 0)
			{
				g_streamed_bink.stand_in.address = data + offset;
				return true;
			}
		}
		return false;
	}

	void play_bink_movie_from_tag_now(long tag_index)
	{
		eldorado::play_bink_movie_from_tag(tag_index);
		// Scripted tag movies cover the screen like play_bink_movie's do.
		s_bink_globals *bink_globals = s_bink_globals::get();
		if (bink_globals->playing && (bink_playback_flags() & k_bink_flag_from_tag))
			bink_playback_flags() |= k_bink_flag_fill_screen;
	}

	void *bink_tag_resource_try_to_get(void *resource)
	{
		void *data = eldorado::tag_resource_try_to_get(resource);
		if (data)
			return data;
		if (!streamed_bink_matches(resource))
			return nullptr;
		g_streamed_bink.used = true;
		return &g_streamed_bink.stand_in;
	}

	bool bink_tag_resource_available(void *resource)
	{
		return eldorado::tag_resource_available(resource) || streamed_bink_matches(resource);
	}

	void play_bink_movie_from_tag_hook(long tag_index)
	{
		void *resource = bink_tag_get_resource(tag_index);
		if (!resource || eldorado::tag_resource_available(resource) || streamed_bink_matches(resource))
			play_bink_movie_from_tag_now(tag_index);
		else
			streamed_bink_begin(tag_index, resource, true);
	}

	void predict_bink_movie_from_tag_hook(long tag_index)
	{
		void *resource = bink_tag_get_resource(tag_index);
		if (!resource || eldorado::tag_resource_available(resource) || streamed_bink_matches(resource))
			eldorado::predict_bink_movie_from_tag(tag_index);
		else
			streamed_bink_begin(tag_index, resource, false);
	}

	void bink_playback_update_hook()
	{
		if (g_streamed_bink.streaming && g_streamed_bink.completion.is_done())
		{
			g_streamed_bink.streaming = false;
			if (g_streamed_bink.completion.get_internal_data())
			{
				log_error("streaming bink tag 0x%lX failed (%ld)", g_streamed_bink.tag_index, g_streamed_bink.completion.get_internal_data());
				streamed_bink_release();
			}
			else if (!streamed_bink_find_movie())
			{
				log_error("bink tag 0x%lX's resource does not hold a bink movie", g_streamed_bink.tag_index);
				streamed_bink_release();
			}
			else
			{
				g_streamed_bink.ready = true;
				if (g_streamed_bink.play_when_ready)
				{
					g_streamed_bink.play_when_ready = false;
					play_bink_movie_from_tag_now(g_streamed_bink.tag_index);
				}
			}
		}
		eldorado::bink_playback_update();
		// A played movie's buffer goes once the movie is closed; a predicted one waits for
		// its play_bink_movie_from_tag.
		if (g_streamed_bink.ready && g_streamed_bink.used && !streamed_bink_in_use())
			streamed_bink_release();
	}

	// The engine's, except that a tag movie is drawn too unless it is the shop video,
	// which goes to its render-to-texture view (c_bink_texture_view), or the texture camera
	// is showing it (texture_camera_bink).
	void bink_playback_render_hook()
	{
		s_bink_globals *bink_globals = s_bink_globals::get();
		if (!bink_globals->initialized || !bink_globals->playing)
			return;
		if ((bink_playback_flags() & k_bink_flag_from_tag) && (*reinterpret_cast<long *>(0x504C834) != -1 || render_texture_camera_bink_active()))
			return;
		if (bink_globals_field<unsigned char>(0x13C) || bink_globals_field<unsigned char>(0x140))  // movie finished, stopping
			return;
		// In game the scene leaves sRGB reads on for samplers bink_setup_rasterizer binds the
		// Y, Cr and Cb planes to, which turned the picture dark green. This unbinds every
		// sampler and turns its sRGB read off through the rasterizer, so its state cache
		// stays right; bink_display_frame already does the same once it has drawn.
		eldorado::c_rasterizer_clear_sampler_textures(0xF);
		eldorado::bink_draw_frame();
	}

	// Outside the main menu the optional cache gives bink 4 MB at most (none in
	// multiplayer), which a movie's frame buffers alone outgrow. Those maps get a pool the
	// size of the main menu's, freed again when the movie ends.
	void bink_playback_grab_memory_hook()
	{
		if (bink_memory_size_for_map() != k_main_menu_bink_memory_size)
		{
			if (!g_bink_memory_pool)
				g_bink_memory_pool = VirtualAlloc(nullptr, k_main_menu_bink_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (g_bink_memory_pool)
			{
				bink_memory_pool_size() = k_main_menu_bink_memory_size;
				bink_memory_pool_offset() = 0;
				bink_memory_pool_base() = g_bink_memory_pool;
				return;
			}
		}
		eldorado::bink_playback_grab_memory();
	}

	void bink_playback_return_memory_hook()
	{
		bool own_pool = g_bink_memory_pool && bink_memory_pool_base() == g_bink_memory_pool;
		eldorado::bink_playback_return_memory();
		if (own_pool)
		{
			VirtualFree(g_bink_memory_pool, 0, MEM_RELEASE);
			g_bink_memory_pool = nullptr;
		}
	}

	// Replaces the engine's frame-buffer setup (0x618010) at its one call. The engine gave
	// each plane the pitch and size of the texture it is later copied into, so a movie
	// bigger than those textures had Bink decode past the end of its buffers, and every
	// movie took texture-sized buffers out of the bink pool. The planes are now sized from
	// what Bink decodes; the copy into the textures reads each plane by its own pitch.
	// prepare_bink_movie_for_playback_async only runs on bink_globals' runtime, whose
	// framebuffers header BinkGetFrameBuffersInfo has just filled.
	bool bink_allocate_frame_plane_buffers(IDirect3DTexture9 **, BINKFRAMEPLANESET *planes, bool allocate_all, void *allocation, void *out_base, void *out_size)
	{
		BINKFRAMEBUFFERS const &framebuffers = s_bink_globals::get()->bink_runtime.frame.framebuffers;
		BINKPLANE *plane_list[4] = { &planes->YPlane, &planes->cRPlane, &planes->cBPlane, &planes->APlane };
		s_bink_plane_buffer_description descriptions[4];
		for (long i = 0; i < 4; i++)
		{
			BINKPLANE *plane = plane_list[i];
			bool chroma = i == 1 || i == 2;
			unsigned long pitch = 0;
			unsigned long rows = 0;
			if (plane->Allocate || allocate_all)
			{
				pitch = chroma ? framebuffers.cRcBBufferWidth : framebuffers.YABufferWidth;
				rows = chroma ? framebuffers.cRcBBufferHeight : framebuffers.YABufferHeight;
			}
			plane->BufferPitch = pitch;
			long size = static_cast<long>(pitch * rows);
			descriptions[i] = { &plane->Buffer, 1, size, size + 4095, 12 };
		}
		return eldorado::allocate_aligned_buffers(allocation, 4, descriptions, "bink!", out_base, out_size);
	}

	// Halo 3's bink branch of c_player_view::create_frame_textures: the movie goes into the
	// texture camera's target in place of the camera's view. It is set up as the shop
	// video's render-to-texture view does it: binding the target resets the viewport to the
	// target's size, and bink_display_frame maps the screen-sized rectangle onto it.
	void render_bink_to_texture_camera()
	{
		long target_index = eldorado::c_dynamic_render_targets_target_allocated(k_render_target_type_texture_camera)
			? eldorado::c_dynamic_render_targets_get_target_index_from_type(k_render_target_type_texture_camera)
			: eldorado::c_dynamic_render_targets_allocate_target(k_render_target_type_texture_camera, k_texture_camera_render_target_width, k_texture_camera_render_target_height, -1, eldorado::c_render_globals_get_frame_index(), "texture camera");
		if (target_index == -1)
			return;
		void *target = eldorado::c_dynamic_render_targets_get_target(static_cast<unsigned short>(target_index));
		long accumulation_surface = *reinterpret_cast<long *>(static_cast<char *>(target) + 0xC);

		short_rectangle2d frame_bounds;
		eldorado::interface_get_current_display_settings(&frame_bounds, nullptr, nullptr, nullptr);
		struct { void const *vftable; unsigned char data[0x290]; } view = { eldorado::c_bink_texture_view_vftable };
		eldorado::c_view_begin(&view);
		eldorado::c_rasterizer_begin(frame_bounds, frame_bounds);
		eldorado::c_rasterizer_set_render_target_texture(0, accumulation_surface, 0, 0);
		for (long target_slot = 1; target_slot <= 3; target_slot++)
			eldorado::c_rasterizer_set_render_target_surface(target_slot, 0, 0xFFFFFFFF);  // _surface_none
		eldorado::c_rasterizer_set_depth_stencil_surface(0);  // _surface_none
		eldorado::c_rasterizer_clear(1, 0xFF000000, 1.0f, 0);
		eldorado::c_rasterizer_enable_clip_planes(0);
		eldorado::c_rasterizer_set_scissor_rect(nullptr);
		eldorado::c_rasterizer_set_color_write_enable(0, 0xF);
		eldorado::c_rasterizer_set_z_buffer_mode(2);  // off
		eldorado::c_rasterizer_set_cull_mode(1);  // off
		eldorado::c_rasterizer_clear_sampler_textures(0xF);  // sRGB reads off, see bink_playback_render_hook
		// The target holds the movie as it is, gamma and all; it is read through sRGB.
		eldorado::c_rasterizer_set_srgbwrite(false);
		// bink_display_frame maps the rectangle against the current player view's window
		// when there is one; against the full screen here, as frame_bounds is.
		void *player_view = eldorado::c_player_view_x_current_player_view;
		eldorado::c_player_view_x_current_player_view = nullptr;
		bink_display_frame(&frame_bounds);
		eldorado::c_player_view_x_current_player_view = player_view;
		eldorado::c_rasterizer_set_srgbwrite(true);
		eldorado::c_view_end();
	}

	// Replaces both calls of c_player_view::create_frame_textures (0xA38D70). Of its three
	// frame texture types only the texture camera ever has a source in this build
	// (frame_texture_get_source), so while the camera shows the movie the engine's
	// function, which would draw the camera's view into the same target, is skipped.
	void __fastcall c_player_view_create_frame_textures_hook(void *player_view, void *, long player_window_index)
	{
		if (!render_texture_camera_bink_active())
		{
			eldorado::c_player_view_create_frame_textures(player_view, player_window_index);
			return;
		}
		eldorado::c_rasterizer_set_gprs_allocation(3);  // _gpr_max_to_vertex_shader
		if (player_window_index == 0)
			eldorado::c_dynamic_render_targets_idle();
		render_bink_to_texture_camera();
	}
}

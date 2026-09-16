/* ---------- headers */

#include "Forge/ForgeVisionRenderer.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/vision_mode/vision_mode_globals.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "Modules/ModuleForge.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct real_argb_color;
struct real_rectangle2d;
struct real_vector3d;
struct s_data_array;
struct s_data_iterator;
struct s_datum;
struct s_object_data;
struct s_vision_mode_globals;
namespace Forge
{
	class CForgeVisionRenderer;
}
namespace Modules
{
	class ModuleForge;
}
namespace hades_file_local
{
	struct s_hud_camera_object;
	struct s_hud_camera_globals;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_hud_camera_object
	{
		long object_index; // 0x0
		unsigned char __pad0[28]; // 0x4
	};
	static_assert(sizeof(s_hud_camera_object) == 32, "Invalid s_hud_camera_object size");

	struct s_hud_camera_globals
	{
		char flags; // 0x0
		char field_1; // 0x1
		short field_2; // 0x2
		long explict_shader_index; // 0x4
		void (*render)(void *, void *); // 0x8
		e_surface surface; // 0xC
		unsigned char __pad0[24]; // 0x10
		real_rectangle2d pixel_bounds; // 0x28
		__int32 unknown_object_index; // 0x38
		unsigned long unknown_marker_name; // 0x3C
		__int32 field_40; // 0x40
		real_vector3d camera_offset; // 0x44
		__int32 unknown_object_index2; // 0x50
		unsigned long unknown_marker2; // 0x54
		unsigned char __pad1[40]; // 0x58
		float field_80; // 0x80
		s_hud_camera_object objects[4]; // 0x84
		unsigned char __pad2[16]; // 0x104
		long stencil_value; // 0x114
		float near_clip; // 0x118
		float maximum_distance; // 0x11C
	};
	static_assert(sizeof(s_hud_camera_globals) == 288, "Invalid s_hud_camera_globals size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern float (*const game_tick_length)();  // hades: added for 0x10838CB0

/* ---------- globals */

namespace Forge
{
	bool CForgeVisionRenderer::m_bActive; // 0x116F4A6C
	bool CForgeVisionRenderer::m_visibleThroughWalls; // 0x116F4A6D
}

namespace Utils
{
	Modules::ModuleForge *Utils::Singleton<Modules::ModuleForge>::m_instance; // 0x116F4A7C
}

/* ---------- private variables */

namespace Forge
{
	namespace hades_file_local_Forge
	{
		extern float colorAnimation; // 0x116F4A70
		extern long selectionColor; // 0x116F4A74
	}
	using namespace hades_file_local_Forge;
}
/* ---------- public code */

namespace Forge
{
	void CForgeVisionRenderer::Update() // 0x10838CB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeVisionRenderer@Forge@@SAXXZ");
		// procedure flags: nofpo
		// function call : float (*const)()

		Forge::colorAnimation = Forge::colorAnimation + game_tick_length() * 5.0f;
		if (Forge::colorAnimation >= 6.2831855f)
		{
			Forge::colorAnimation = Forge::colorAnimation - 6.2831855f;
		}
	}

	_extern void _sub_108383F0(real_argb_color *);
	void CForgeVisionRenderer::GetVisionColors(real_argb_color *colors) // 0x108383F0
	{
		mangled_x86(MANGLED_TODO, "?GetVisionColors@CForgeVisionRenderer@Forge@@SAXPAUreal_argb_color@@@Z");
		// static ...; // 0x10838614
		// static ...; // 0x10838608
		// static ...; // 0x10838600
		// real_argb_color *colors;
		// real_argb_color color;
		// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
		todo("implement");
		_sub_108383F0(colors);
	}

	_extern void _sub_108380B0(long, long, long, void const *, bool);
	void CForgeVisionRenderer::Generate(long windowIndex, long playerIndex, long unitIndex, void const *windowData, bool pass) // 0x108380B0
	{
		mangled_x86(MANGLED_TODO, "?Generate@CForgeVisionRenderer@Forge@@SAXJJJPBX_N@Z");
		// long playerIndex;
		// long unitIndex;
		// void const *windowData;
		// bool pass;
		// void (*const c_visible_items__push_marker)();
		// void (*const render_visibility_add_object_to_items)(long, long, bool, bool);
		// void (*const render_objects_visibility_push_marker)();
		// void (*const render_visible_objects)(unsigned long);
		// s_data_iterator iter;
		// void (*const render_objects_visibility_pop_marker)();
		// void (*const c_visible_items__pop_marker)();
		// void (*const objects_render_shadows_generate)(long, long);
		{
			// long object_index;
			// s_object_data *object;
			{
				// long vision_output_type;
			}
		}
		// function call : void (*const)(s_data_iterator *, s_data_array const *)
		// function call : s_datum *(*const)(s_data_iterator *)
		// function call : void (*const)()
		// function call : void (*const)()
		// function call : void (*const)(long, long, bool, bool)
		// function call : void (*const)(unsigned long)
		// function call : e_surface (*const)(long, e_surface, long)
		// function call : void (*const)(long, unsigned char)
		// function call : e_surface (*const)(long, e_surface, long)
		// function call : void (*const)(long, long)
		// function call : e_surface (*const)(long, e_surface, long)
		// function call : e_surface (*const)(long, e_surface, long)
		// function call : void (*const)()
		// function call : void (*const)()
		todo("implement");
		_sub_108380B0(windowIndex, playerIndex, unitIndex, windowData, pass);
	}

	_extern void _sub_10838910(long, void *);
	void CForgeVisionRenderer::Render(long windowIndex, void *view) // 0x10838910
	{
		mangled_x86(MANGLED_TODO, "?Render@CForgeVisionRenderer@Forge@@SAXJPAX@Z");
		// static ...; // 0x10838B80
		// static ...; // 0x10838B78
		// long windowIndex;
		// void *view;
		// void (*const vision_mode_setup_camera_globals)(s_hud_camera_globals *);
		// s_hud_camera_globals *hud_camera_globals;
		// void (*const s_hud_camera_globals_initialize)(s_hud_camera_globals *);
		// void *(*const vision_mode_definition_get)();
		// unsigned char hud_camera_view[10224];
		// s_vision_mode_globals *vision_mode_globals;
		// void (*const c_player_view__ctor)(void *);
		// void (*const sub_14E3720)(void const *, float *);
		// void (*const c_hud_camera_view__render)(void *, long, void *, s_hud_camera_globals *);
		// function call : void (*const)(void *)
		// function call : void *(*const)()
		// function call : void (*const)(void const *, float *)
		// function call : void (*const)(s_hud_camera_globals *)
		// function call : void (*const)(s_hud_camera_globals *)
		// function call : e_surface (*const)(long)
		// function call : void (*const)(void *, long, void *, s_hud_camera_globals *)
		todo("implement");
		_sub_10838910(windowIndex, view);
	}

	long CForgeVisionRenderer::GetMaskBitmap(long *bitmapIndex) // 0x108383D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetMaskBitmap@CForgeVisionRenderer@Forge@@SAJPAJ@Z");
		// long *bitmapIndex;

		return -1;
	}

	void CForgeVisionRenderer::SetActive(bool active) // 0x10838C40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetActive@CForgeVisionRenderer@Forge@@SAX_N@Z");
		// bool active;

		if (m_bActive != active)
		{
			if (active)
			{
				OnActivate();
			}

			m_bActive = active;
		}
	}

	void CForgeVisionRenderer::OnActivate() // 0x108387E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnActivate@CForgeVisionRenderer@Forge@@CAXXZ");
		// procedure flags: nofpo
		// std::string const &color;

		std::string &selectionColorString = *(std::string *)((unsigned char *)Modules::ModuleForge::Instance().VarSelectionColor + 0x8C);
		if (selectionColorString == "rainbow")
		{
			selectionColor = -1;
		}
		else
		{
			selectionColor = std::stoi(selectionColorString.substr(1), 0, 16);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleForge & Utils::Singleton<Modules::ModuleForge>::Instance();

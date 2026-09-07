/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_test.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer_d3d_allocations.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "Debug/DebugDraw.hpp"
#include "Forge/Magnets.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_collision_result;
namespace
{
	class CRenderDebugCollisionTest;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace HavokMemory {}
	using namespace Patches::HavokMemory;
	namespace Core {}
	using namespace Patches::Core;
	namespace Debug {}
	using namespace Patches::Debug;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	class CRenderDebugCollisionTest
	{
	public:
		static void Update();
		static void UpdateInternal();
		static void Render();
		static std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetHitDescription(s_collision_result const &);
		static std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetFriendlyTagName(long);
		static void ResetForNewMap();
	private:
		static bool m_collisionResultValid;
		static s_collision_result m_collisionResult;
		static std::mutex m_mutex;
	};
	static_assert(sizeof(CRenderDebugCollisionTest) == 1, "Invalid CRenderDebugCollisionTest size");
}
typedef long long long64;

/* ---------- prototypes */

namespace Patches
{
	namespace Debug
	{
		extern void OnMapLoaded(char const *mapPath);
		extern void ApplyAll();
		extern void Tick();
		extern void RenderPlayerView();
	}
}

/* ---------- globals */

/* ---------- private variables */

bool CRenderDebugCollisionTest::m_collisionResultValid; // 0x124082B4
s_collision_result CRenderDebugCollisionTest::m_collisionResult; // 0x124082B8
std::mutex CRenderDebugCollisionTest::m_mutex; // 0x12408280
namespace
{
	extern long assassination_capsule_counter; // 0x12408314
}
/* ---------- public code */

namespace Patches
{
	namespace Debug
	{
		_extern void _sub_108C8D00(char const *);
		void OnMapLoaded(char const *mapPath) // 0x108C8D00
		{
			mangled_x86(MANGLED_TODO, "?OnMapLoaded@Debug@Patches@@YAXPBD@Z");
			// char const *mapPath;
			todo("implement");
			_sub_108C8D00(mapPath);
		}

		_extern void _sub_108C76E0();
		void ApplyAll() // 0x108C76E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108C76E0();
		}

		_extern void _sub_108C9470();
		void Tick() // 0x108C9470
		{
			mangled_x86(MANGLED_TODO, "?Tick@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			todo("implement");
			_sub_108C9470();
		}

		_extern void _sub_108C9370();
		void RenderPlayerView() // 0x108C9370
		{
			mangled_x86(MANGLED_TODO, "?RenderPlayerView@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108C9370();
		}
	}
}

/* ---------- private code */

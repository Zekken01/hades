/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
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
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace
{
	class CRenderFullScreenBlur;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MenuBlur {}
	using namespace Patches::MenuBlur;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	class CRenderFullScreenBlur
	{
	public:
		void Update();
		void Render();
	private:
		float m_alpha; // 0x0
	public:
		CRenderFullScreenBlur(); /* compiler_generated() */
	};
	static_assert(sizeof(CRenderFullScreenBlur) == 4, "Invalid CRenderFullScreenBlur size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace MenuBlur
	{
		extern void ApplyAll();
		extern void Tick();
		extern void RenderUIPostProcess();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace MenuBlur
	{
		_extern void _sub_108D17D0();
		void ApplyAll() // 0x108D17D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D17D0();
		}

		_extern void _sub_108D1FE0();
		void Tick() // 0x108D1FE0
		{
			mangled_x86(MANGLED_TODO, "?Tick@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D1FE0();
		}

		_extern void _sub_108D1F80();
		void RenderUIPostProcess() // 0x108D1F80
		{
			mangled_x86(MANGLED_TODO, "?RenderUIPostProcess@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D1F80();
		}
	}
}

/* ---------- private code */

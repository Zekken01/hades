/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patches/Ui.hpp"
#include "Utils/Singleton.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Tweaks {}
	using namespace Patches::Tweaks;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Tweaks
	{
		extern void ApplyAfterTagsLoaded();
		extern void EnableHitmarkers(bool enabled);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern bool tagsloaded; // 0x12467418
}
/* ---------- public code */

namespace Patches
{
	namespace Tweaks
	{
		_extern void _sub_10AD2060();
		void ApplyAfterTagsLoaded() // 0x10AD2060
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Tweaks@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AD2060();
		}

		_extern void _sub_10AD22B0(bool);
		void EnableHitmarkers(bool enabled) // 0x10AD22B0
		{
			mangled_x86(MANGLED_TODO, "?EnableHitmarkers@Tweaks@Patches@@YAX_N@Z");
			// bool enabled;
			todo("implement");
			_sub_10AD22B0(enabled);
		}
	}
}

/* ---------- private code */

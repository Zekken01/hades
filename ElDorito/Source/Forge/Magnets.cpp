/* ---------- headers */

#include "Forge/Magnets.hpp"
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
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectSet.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/en.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
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
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct real_point3d;
namespace Forge
{
	namespace Magnets
	{
		struct Magnet;
		struct MagnetPair;
	}
}
namespace
{
	class MagnetManager;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Magnets {}
	using namespace Forge::Magnets;
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Geoemetry {}
	using namespace Forge::Geoemetry;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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
	class MagnetManager
	{
	public:
		MagnetManager();
		void Update();
		void Render();
		void RenderMagnet(Forge::Magnets::Magnet const &);
		Forge::Magnets::MagnetPair const &GetMagnetPair() const;
	private:
		unsigned __int32 m_LastCheck; // 0x0
		__int32 m_NumSourceMagnets; // 0x4
		__int32 m_NumDestMagnets; // 0x8
		Forge::Magnets::MagnetPair m_MagnetPairing; // 0xC
		Forge::Magnets::Magnet m_SourceMagnets[512]; // 0x18
		Forge::Magnets::Magnet m_DestMagnets[2048]; // 0x1818
		void GetObjectMarkers(unsigned __int32, std::vector<real_point3d,std::allocator<real_point3d> > &);
		void AddSourceObject(unsigned __int32);
		void AddDestObject(unsigned __int32);
		void PerformPairing();
	};
	static_assert(sizeof(MagnetManager) == 30744, "Invalid MagnetManager size");

}
/* ---------- prototypes */

namespace Forge
{
	namespace Magnets
	{
		extern bool Initialize();
		extern void Shutdown();
		extern void Update();
		extern void Render();
		extern Forge::Magnets::MagnetPair const &GetMagnetPair();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *MARKER_GROUP_NAME; // 0x11353D3C
	extern unsigned long markerGroupName; // 0x1240FB58
}
/* ---------- public code */

namespace Forge
{
	namespace Magnets
	{
		_extern bool _sub_1096D1B0();
		bool Initialize() // 0x1096D1B0
		{
			mangled_x86(MANGLED_TODO, "?Initialize@Magnets@Forge@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_1096D1B0();
			return __result;
		}

		_extern void _sub_1096DE20();
		void Shutdown() // 0x1096DE20
		{
			mangled_x86(MANGLED_TODO, "?Shutdown@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096DE20();
		}

		_extern void _sub_1096E210();
		void Update() // 0x1096E210
		{
			mangled_x86(MANGLED_TODO, "?Update@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096E210();
		}

		_extern void _sub_1096D8C0();
		void Render() // 0x1096D8C0
		{
			mangled_x86(MANGLED_TODO, "?Render@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096D8C0();
		}

		extern MagnetPair const &_sub_1096CB80();
		Forge::Magnets::MagnetPair const &GetMagnetPair() // 0x1096CB80
		{
			mangled_x86(MANGLED_TODO, "?GetMagnetPair@Magnets@Forge@@YAABUMagnetPair@12@XZ");
			// procedure flags: nofpo
			// static Forge::Magnets::MagnetPair nullMagnetPair; // 0x1240FB5C
			todo("implement");
			Forge::Magnets::MagnetPair const & __result = _sub_1096CB80();
			return __result;
		}
	}
}

/* ---------- private code */

/* ---------- headers */

#include "Modules/ModuleForge.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Geoemetry.hpp"
#include "Modules/ModuleBase.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
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

namespace Modules
{
	class ModuleBase;
	class ModuleForge;
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Prefabs {}
	using namespace Forge::Prefabs;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const PREFAB_DIR[14]; // 0x1119CB90
	extern char const PREFAB_EXT[8]; // 0x1119CBA0
}
/* ---------- public code */

namespace Modules
{
	extern ModuleForge* _sub_10982310(Modules::ModuleForge *const);
	ModuleForge::ModuleForge() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10982310
	{
		mangled_x86(MANGLED_TODO, "??0ModuleForge@Modules@@QAE@XZ");
		// Modules::ModuleForge *const this;
		todo("implement");
		_sub_10982310(this);
	}
}

/* ---------- private code */

namespace Modules
{
	_extern void _sub_109841D0(Modules::ModuleForge::s_CommandState *const);
	_inline ModuleForge::s_CommandState::~s_CommandState() // 0x109841D0
	{
		// Modules::ModuleForge::<unnamed-type-CommandState>::~<unnamed-type-CommandState>
		// Modules::ModuleForge::s_CommandState *const this;
		compiler_generated();
		todo("implement");
		_sub_109841D0(this);
	}

	_extern void _sub_10984220(Modules::ModuleForge::s_CommandState::s_Prefabs *const);
	_inline ModuleForge::s_CommandState::s_Prefabs::~s_Prefabs() // 0x10984220
	{
		// Modules::ModuleForge::<unnamed-type-CommandState>::<unnamed-type-Prefabs>::~<unnamed-type-Prefabs>
		// Modules::ModuleForge::s_CommandState::s_Prefabs *const this;
		compiler_generated();
		todo("implement");
		_sub_10984220(this);
	}
}

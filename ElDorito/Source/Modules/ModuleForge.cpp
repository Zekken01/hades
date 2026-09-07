/* ---------- headers */

#include "Modules/ModuleForge.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/ForgeUtil.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Prefab.hpp"
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

namespace Forge
{
	struct ForgeObjectQuota;
}
namespace Forge
{
	namespace Prefabs
	{
		struct PrefabHeader;
	}
}
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

bool CommandDeleteAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandCanvas(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandDeselectAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandDeselectAllOf(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSelectAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSelectAllMaterial(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSelectEverything(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandExpandSelection(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandInvertSelection(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSavePrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandLoadPrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandDumpPrefabs(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandDeletePrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool TryParseTagIndex(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned __int32 *value);
bool CommandSpawnItem(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool TryParseInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, __int32 *value);
bool CommandPrematchCamera(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandResetRuntime(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandForgeBudget(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandMapOptions(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandForgeUndo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandForgeRedo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const PREFAB_DIR[14]; // 0x1119CB90
	extern char const PREFAB_EXT[8]; // 0x1119CBA0
}
using namespace hades_file_local;
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

_extern bool _sub_109842D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDeleteAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109842D0
{
	// `anonymous-namespace'::CommandDeleteAll
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109842D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984280(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandCanvas(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984280
{
	// `anonymous-namespace'::CommandCanvas
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	bool __result = _sub_10984280(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984590(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDeselectAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984590
{
	// `anonymous-namespace'::CommandDeselectAll
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10984590(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109845D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDeselectAllOf(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109845D0
{
	// `anonymous-namespace'::CommandDeselectAllOf
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109845D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985880(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSelectAll(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985880
{
	// `anonymous-namespace'::CommandSelectAll
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10985880(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109858C0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSelectAllMaterial(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109858C0
{
	// `anonymous-namespace'::CommandSelectAllMaterial
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109858C0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985900(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSelectEverything(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985900
{
	// `anonymous-namespace'::CommandSelectEverything
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10985900(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984C40(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandExpandSelection(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984C40
{
	// `anonymous-namespace'::CommandExpandSelection
	// static ...; // 0x10984CEC
	// static ...; // 0x10984CE4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// char *endp;
	// float radius;
	todo("implement");
	bool __result = _sub_10984C40(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985040(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandInvertSelection(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985040
{
	// `anonymous-namespace'::CommandInvertSelection
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10985040(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985550(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSavePrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985550
{
	// `anonymous-namespace'::CommandSavePrefab
	// static ...; // 0x109857C0
	// static ...; // 0x109857A8
	// static ...; // 0x109857A0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
	todo("implement");
	bool __result = _sub_10985550(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985080(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandLoadPrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985080
{
	// `anonymous-namespace'::CommandLoadPrefab
	// static ...; // 0x109852CC
	// static ...; // 0x109852B4
	// static ...; // 0x109852AC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	todo("implement");
	bool __result = _sub_10985080(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984610(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDumpPrefabs(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984610
{
	// `anonymous-namespace'::CommandDumpPrefabs
	// static ...; // 0x10984AF2
	// static ...; // 0x10984AEB
	// static ...; // 0x10984AE4
	// static ...; // 0x10984AE0
	// static ...; // 0x10984ADB
	// static ...; // 0x10984AD7
	// static ...; // 0x10984AD3
	// static ...; // 0x10984ACC
	// static ...; // 0x10984A60
	// static ...; // 0x10984A58
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::filesystem::directory_iterator end_itr;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::filesystem::path p;
	{
		// std::filesystem::directory_iterator itr;
		{
			// std::filesystem::path path;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ext;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
			{
				// Forge::Prefabs::PrefabHeader header;
			}
		}
	}
	todo("implement");
	bool __result = _sub_10984610(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984310(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDeletePrefab(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984310
{
	// `anonymous-namespace'::CommandDeletePrefab
	// static ...; // 0x109844F4
	// static ...; // 0x109844DC
	// static ...; // 0x109844D4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	todo("implement");
	bool __result = _sub_10984310(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985B00(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned __int32 *);
bool TryParseTagIndex(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, unsigned __int32 *value) // 0x10985B00
{
	// `anonymous-namespace'::TryParseTagIndex
	// static ...; // 0x10985BA0
	// static ...; // 0x10985B98
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
	// unsigned __int32 *value;
	// char const *c_str;
	// char *endp;
	todo("implement");
	bool __result = _sub_10985B00(str, value);
	return __result;
}

_extern bool _sub_10985940(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSpawnItem(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985940
{
	// `anonymous-namespace'::CommandSpawnItem
	// static ...; // 0x109859D8
	// static ...; // 0x109859D0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// unsigned __int32 tagIndex;
	todo("implement");
	bool __result = _sub_10985940(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985A20(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, __int32 *);
bool TryParseInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, __int32 *value) // 0x10985A20
{
	// `anonymous-namespace'::TryParseInt
	// static ...; // 0x10985AC0
	// static ...; // 0x10985AB8
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
	// __int32 *value;
	// char const *c_str;
	// char *endp;
	todo("implement");
	bool __result = _sub_10985A20(str, value);
	return __result;
}

_extern bool _sub_109853D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPrematchCamera(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109853D0
{
	// `anonymous-namespace'::CommandPrematchCamera
	// static ...; // 0x109854B0
	// static ...; // 0x109854A8
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	{
		// __int32 team;
	}
	todo("implement");
	bool __result = _sub_109853D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985500(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandResetRuntime(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985500
{
	// `anonymous-namespace'::CommandResetRuntime
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	bool __result = _sub_10985500(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984D30(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandForgeBudget(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984D30
{
	// `anonymous-namespace'::CommandForgeBudget
	// static ...; // 0x10984EBF
	// static ...; // 0x10984EB8
	// static ...; // 0x10984E94
	// static ...; // 0x10984E8C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Forge::ForgeObjectQuota const &quota;
	todo("implement");
	bool __result = _sub_10984D30(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985380(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandMapOptions(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10985380
{
	// `anonymous-namespace'::CommandMapOptions
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	bool __result = _sub_10985380(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984FC0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandForgeUndo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984FC0
{
	// `anonymous-namespace'::CommandForgeUndo
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10984FC0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984F40(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandForgeRedo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10984F40
{
	// `anonymous-namespace'::CommandForgeRedo
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10984F40(Arguments, returnInfo);
	return __result;
}

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

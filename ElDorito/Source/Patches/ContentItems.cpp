/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/dirent.h"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <propkeydef.h>
#include <propsys.h>
#include <shlobj_core.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
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
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <mutex>
#include <optional>
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

struct s_ContentItemRenameState;
struct s_datum;
namespace
{
	struct c_content_item;
	struct c_content_catalog;
	struct c_content_item_overlapped_task;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace ContentItems {}
	using namespace Patches::ContentItems;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct c_content_item :
		public s_datum
	{
		unsigned short Unknown02; // 0x2
		unsigned __int32 Unknown04; // 0x4
		__int32 ContentType; // 0x8
		c_content_catalog *Catalog; // 0xC
		unsigned char ContentHeader[248]; // 0x10
		__int32 Unknown108; // 0x108
		__int32 Unknown10C; // 0x10C
		wchar_t RelativeFilePath[128]; // 0x110
	};
	static_assert(sizeof(c_content_item) == 528, "Invalid c_content_item size");

	struct c_content_catalog
	{
		__int32 LocalProfileIndex; // 0x0
		c_data_array<c_content_item> *Items; // 0x4
		unsigned char Unknown08[680]; // 0x8
	};
	static_assert(sizeof(c_content_catalog) == 688, "Invalid c_content_catalog size");

	//@@anonymous-namespace@@
	struct c_content_item_overlapped_task
	{
		__int32 LocalProfileIndex; // 0x0
		unsigned __int32 ContentItemDatumIndex; // 0x4
		wchar_t *NewContentName; // 0x8
		wchar_t *NewContentDescription; // 0xC
		long *CompletionState; // 0x10
		long *CompletionStatus; // 0x14
	};
	static_assert(sizeof(c_content_item_overlapped_task) == 24, "Invalid c_content_item_overlapped_task size");
}
struct s_ContentItemRenameState
{
	bool IsValid; // 0x0
	wchar_t NewPath[128]; // 0x2
};
// static_assert(sizeof(s_ContentItemRenameState) == 258, "Invalid s_ContentItemRenameState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace Patches
{
	namespace ContentItems
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern bool saving_new_gametype; // 0x12458148
	extern unsigned char *contentItemsGlobal; // 0x12458254
	extern bool enumerated; // 0x12458149
}
/* ---------- public code */

namespace Patches
{
	namespace ContentItems
	{
		_extern void _sub_10A3ACF0();
		void ApplyAll() // 0x10A3ACF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ContentItems@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A3ACF0();
		}
	}
}

/* ---------- private code */

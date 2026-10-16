/* ---------- headers */

#include "Common/D3D/D3DAdapters.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"

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
#include <memory>
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
#include <vector>

/* ---------- forward declarations */

struct _D3DDISPLAYMODE;
struct begin;
struct end;
namespace Common
{
	namespace D3DAdapters
	{
		struct DisplayMode;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Common {}
using namespace ::Common;
namespace Common
{
	namespace D3DAdapters {}
	using namespace Common::D3DAdapters;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Common
{
	namespace D3DAdapters
	{
		extern void EnumerateDisplayModes();
		extern std::vector<Common::D3DAdapters::DisplayMode> const &GetAdapterDisplayModes(__int32 adapterIndex);
		extern Common::D3DAdapters::DisplayMode GetClosestSupportedDisplayMode(__int32 preferredWidth, __int32 preferredHeight);
		extern __int32 GetCurrentAdapterIndex();
	}
}

void FatalError(char const *message);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<std::vector<Common::D3DAdapters::DisplayMode> > adapterModes; // 0x11371944
}
using namespace hades_file_local;
/* ---------- public code */

namespace Common
{
	namespace D3DAdapters
	{
		void EnumerateDisplayModes() // 0x106874A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EnumerateDisplayModes@D3DAdapters@Common@@YAXXZ");

			adapterModes.clear();
			__int32 foundModes = 0;
			IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);
			if (!d3d)
			{
				FatalError("Direct3DCreate9 Failed.");
				return;
			}
			_D3DFORMAT const format = D3DFMT_X8R8G8B8;
			__int32 numAdapters = d3d->GetAdapterCount();
			for (__int32 adapterIndex = 0; adapterIndex < numAdapters; adapterIndex++)
			{
				std::vector<DisplayMode> &modes = adapterModes.emplace_back();
				__int32 numModes = d3d->GetAdapterModeCount(adapterIndex, format);
				for (__int32 modeIndex = 0; modeIndex < numModes; modeIndex++)
				{
					_D3DDISPLAYMODE d3dMode;
					if (SUCCEEDED(d3d->EnumAdapterModes(adapterIndex, format, modeIndex, &d3dMode)))
					{
						DisplayMode mode;
						mode.adapterIndex = adapterIndex;
						mode.width = d3dMode.Width;
						mode.height = d3dMode.Height;
						auto it = std::lower_bound(modes.begin(), modes.end(), mode);
						if (it == modes.end() || !(*it == mode))
							modes.insert(it, mode);
						foundModes++;
					}
				}
			}
			d3d->Release();
			if (!foundModes)
				FatalError("Failed init D3D. No supported display modes were found");
		}
	}
}


namespace Common
{
	namespace D3DAdapters
	{
		std::vector<Common::D3DAdapters::DisplayMode> const &GetAdapterDisplayModes(__int32 adapterIndex) // 0x10687970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetAdapterDisplayModes@D3DAdapters@Common@@YAABV?$vector@UDisplayMode@D3DAdapters@Common@@V?$allocator@UDisplayMode@D3DAdapters@Common@@@std@@@std@@H@Z");

			return adapterModes[adapterIndex];
		}

		Common::D3DAdapters::DisplayMode GetClosestSupportedDisplayMode(__int32 preferredWidth, __int32 preferredHeight) // 0x106879C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetClosestSupportedDisplayMode@D3DAdapters@Common@@YA?AUDisplayMode@12@HH@Z");

			Common::D3DAdapters::DisplayMode closestMode = {};
			__int32 minDifference = INT_MAX;
			for (unsigned __int32 i = 0; i < adapterModes.size(); i++)
			{
				for (auto const &mode : adapterModes[i])
				{
					__int32 difference = abs(mode.width - preferredWidth) + abs(mode.height - preferredHeight);
					if (difference < minDifference)
					{
						minDifference = difference;
						closestMode = mode;
					}
				}
			}
			return closestMode;
		}

		__int32 GetCurrentAdapterIndex() // 0x10687B70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetCurrentAdapterIndex@D3DAdapters@Common@@YAHXZ");

			return *(__int32 *)0x50dd9c4;
		}
	}
}

/* ---------- private code */

void FatalError(char const *message) // 0x10687900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FatalError@@YAXPBD@Z");

	MessageBoxA(nullptr, "Error", message, 0x10);
	ExitProcess(0xFFFFFFFF);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

// operator< is emitted through std::lower_bound in EnumerateDisplayModes; an explicit
// instantiation of a non-template breaks that lookup at the end of the unit.

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::vector<std::vector<Common::D3DAdapters::DisplayMode> > adapterModes; }

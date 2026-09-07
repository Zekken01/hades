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
		extern std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > const &GetAdapterDisplayModes(__int32 adapterIndex);
		extern Common::D3DAdapters::DisplayMode GetClosestSupportedDisplayMode(__int32 preferredWidth, __int32 preferredHeight);
		extern __int32 GetCurrentAdapterIndex();
	}
}

void FatalError(char const *message);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> >,std::allocator<std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > > > adapterModes; // 0x11371944
}
using namespace hades_file_local;
/* ---------- public code */

namespace Common
{
	namespace D3DAdapters
	{
		_extern void _sub_106874A0();
		void EnumerateDisplayModes() // 0x106874A0
		{
			mangled_x86(MANGLED_TODO, "?EnumerateDisplayModes@D3DAdapters@Common@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10687810
			// static ...; // 0x1068780B
			// static ...; // 0x10687808
			// static ...; // 0x106877E4
			// static ...; // 0x106877DC
			// __int32 numAdapters;
			// __int32 foundModes;
			// _D3DFORMAT format;
			// IDirect3D9 *d3d;
			{
				// __int32 adapterIndex;
				{
					// std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > &modes;
					// __int32 numModes;
					{
						// __int32 modeIndex;
						{
							// _D3DDISPLAYMODE d3dMode;
							{
								// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Common::D3DAdapters::DisplayMode> > > it;
								// Common::D3DAdapters::DisplayMode mode;
							}
						}
					}
				}
			}
			// function call : unsigned __int32 ()
			// function call : unsigned __int32 (unsigned __int32, _D3DFORMAT)
			// function call : HRESULT (unsigned __int32, _D3DFORMAT, unsigned __int32, _D3DDISPLAYMODE *)
			// function call : unsigned long ()
			todo("implement");
			_sub_106874A0();
		}
	}
}

extern std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > const &_sub_10687970(__int32);
namespace Common
{
	namespace D3DAdapters
	{
		std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > const &GetAdapterDisplayModes(__int32 adapterIndex) // 0x10687970
		{
			mangled_x86(MANGLED_TODO, "?GetAdapterDisplayModes@D3DAdapters@Common@@YAABV?$vector@UDisplayMode@D3DAdapters@Common@@V?$allocator@UDisplayMode@D3DAdapters@Common@@@std@@@std@@H@Z");
			// __int32 adapterIndex;
			todo("implement");
			std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > const & __result = _sub_10687970(adapterIndex);
			return __result;
		}

		extern DisplayMode _sub_106879C0(__int32, __int32);
		Common::D3DAdapters::DisplayMode GetClosestSupportedDisplayMode(__int32 preferredWidth, __int32 preferredHeight) // 0x106879C0
		{
			mangled_x86(MANGLED_TODO, "?GetClosestSupportedDisplayMode@D3DAdapters@Common@@YA?AUDisplayMode@12@HH@Z");
			// static ...; // 0x10687B00
			// static ...; // 0x10687AF8
			// __int32 preferredWidth;
			// __int32 preferredHeight;
			// __int32 minDifference;
			// Common::D3DAdapters::DisplayMode closestMode;
			{
				// unsigned __int32 i;
				{
					// std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > &<range>$L0;
					// Common::D3DAdapters::DisplayMode *<begin>$L0;
					// Common::D3DAdapters::DisplayMode *<end>$L0;
					{
						// Common::D3DAdapters::DisplayMode const &mode;
						{
							// __int32 difference;
						}
					}
				}
			}
			todo("implement");
			Common::D3DAdapters::DisplayMode __result = _sub_106879C0(preferredWidth, preferredHeight);
			return __result;
		}

		_extern __int32 _sub_10687B70();
		__int32 GetCurrentAdapterIndex() // 0x10687B70
		{
			mangled_x86(MANGLED_TODO, "?GetCurrentAdapterIndex@D3DAdapters@Common@@YAHXZ");
			// procedure flags: nofpo
			todo("implement");
			__int32 __result = _sub_10687B70();
			return __result;
		}
	}
}

/* ---------- private code */

_extern void _sub_10687900(char const *);
void FatalError(char const *message) // 0x10687900
{
	// `anonymous-namespace'::FatalError
	// char const *message;
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	// function call : void (unsigned __int32)
	todo("implement");
	_sub_10687900(message);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool Common::D3DAdapters::operator<(Common::D3DAdapters::DisplayMode const &, Common::D3DAdapters::DisplayMode const &);

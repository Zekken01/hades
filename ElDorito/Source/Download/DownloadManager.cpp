/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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
#include <limits>
#include <map>
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

namespace Download
{
	class CHttpFileDownload;
	class CHttpFileDownloadManager;
}

namespace Utils {}
using namespace ::Utils;
namespace Download {}
using namespace ::Download;
namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Download
{
	extern void Init();
	extern void Shutdown();
	extern void Tick();
	extern std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload();
}

/* ---------- globals */

namespace Utils
{
	Download::CHttpFileDownloadManager *Utils::Singleton<Download::CHttpFileDownloadManager>::m_instance; // 0x116F47F4
}

/* ---------- private variables */

/* ---------- public code */

namespace Download
{
	_extern void _sub_10820440();
	void Init() // 0x10820440
	{
		mangled_x86(MANGLED_TODO, "?Init@Download@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10820440();
	}

	_extern void _sub_10820640();
	void Shutdown() // 0x10820640
	{
		mangled_x86(MANGLED_TODO, "?Shutdown@Download@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10820640();
	}

	_extern void _sub_108207D0();
	void Tick() // 0x108207D0
	{
		mangled_x86(MANGLED_TODO, "?Tick@Download@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_108207D0();
	}
}

extern std::shared_ptr<Download::CHttpFileDownload> _sub_108203B0();
namespace Download
{
	std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload() // 0x108203B0
	{
		mangled_x86(MANGLED_TODO, "?CreateHttpFileDownload@Download@@YA?AV?$shared_ptr@VCHttpFileDownload@Download@@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::shared_ptr<Download::CHttpFileDownload> __result = _sub_108203B0();
		return __result;
	}

	extern CHttpFileDownloadManager* _sub_10820020(Download::CHttpFileDownloadManager *const);
	_inline CHttpFileDownloadManager::CHttpFileDownloadManager() // 0x10820020
	{
		mangled_x86(MANGLED_TODO, "??0CHttpFileDownloadManager@Download@@QAE@XZ");
		// Download::CHttpFileDownloadManager *const this;
		compiler_generated();
		todo("implement");
		_sub_10820020(this);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Download::CHttpFileDownloadManager & Utils::Singleton<Download::CHttpFileDownloadManager>::Instance();

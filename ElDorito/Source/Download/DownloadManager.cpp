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
	void Init() // 0x10820440
	{
		Download::CHttpFileDownloadManager::Instance().Init();
	}

	void Shutdown() // 0x10820640
	{
		Download::CHttpFileDownloadManager::Instance().Shutdown();
	}

	void Tick() // 0x108207D0
	{
		Download::CHttpFileDownloadManager::Instance().Tick();
	}
}


namespace Download
{
	std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload() // 0x108203B0
	{
		return std::make_shared<Download::CHttpFileDownload>();
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Download::CHttpFileDownloadManager & Utils::Singleton<Download::CHttpFileDownloadManager>::Instance();

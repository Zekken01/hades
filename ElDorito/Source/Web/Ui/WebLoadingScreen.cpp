/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/LoadingScreen.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
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
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Patches
{
	namespace LoadingScreen
	{
		class LoadingScreenUi;
		struct LoadingScreenShowInfo;
	}
}
namespace
{
	class WebLoadingScreenUi;
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
		namespace WebLoadingScreen {}
		using namespace Web::Ui::WebLoadingScreen;
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
	namespace LoadingScreen {}
	using namespace Patches::LoadingScreen;
}

namespace Console {}
using namespace ::Console;
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
	class WebLoadingScreenUi :
		public Patches::LoadingScreen::LoadingScreenUi
	{
	private:
		unsigned __int32 currentBytes; // 0x4
		unsigned __int32 totalBytes; // 0x8
		unsigned char __pad0[4]; // 0xC
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > lastUpdateTime; // 0x10
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > benchmark_start; // 0x18
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > benchmark_end; // 0x20
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > benchmarkMapName; // 0x28
	public:
		WebLoadingScreenUi(WebLoadingScreenUi &); /* compiler_generated() */
		WebLoadingScreenUi(WebLoadingScreenUi const &); /* compiler_generated() */
		WebLoadingScreenUi();
		virtual void Show(Patches::LoadingScreen::LoadingScreenShowInfo const &);
		virtual void Begin(unsigned __int32);
		virtual void UpdateProgress(unsigned __int32);
		virtual void Hide();
		virtual ~WebLoadingScreenUi(); /* compiler_generated() */
		WebLoadingScreenUi &operator=(WebLoadingScreenUi &); /* compiler_generated() */
		WebLoadingScreenUi &operator=(WebLoadingScreenUi const &); /* compiler_generated() */
	unsigned char __pad1[4]; // 0x44
	};
	static_assert(sizeof(WebLoadingScreenUi) == 72, "Invalid WebLoadingScreenUi size");
}
/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebLoadingScreen
		{
			extern void Init();
		}
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebLoadingScreen
		{
			_extern void _sub_10CAAAE0();
			void Init() // 0x10CAAAE0
			{
				mangled_x86(MANGLED_TODO, "?Init@WebLoadingScreen@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10CAAB9C
				// static ...; // 0x10CAAB90
				// static ...; // 0x10CAAB88
				// std::shared_ptr<WebLoadingScreenUi> ui;
				todo("implement");
				_sub_10CAAAE0();
			}
		}
	}
}

namespace Patches
{
	namespace LoadingScreen
	{
		extern LoadingScreenUi* _sub_10CA9FB0(Patches::LoadingScreen::LoadingScreenUi *const);
		_inline LoadingScreenUi::LoadingScreenUi() // 0x10CA9FB0
		{
			mangled_x86(MANGLED_TODO, "??0LoadingScreenUi@LoadingScreen@Patches@@QAE@XZ");
			// Patches::LoadingScreen::LoadingScreenUi *const this;
			compiler_generated();
			todo("implement");
			_sub_10CA9FB0(this);
		}
	}
}

/* ---------- private code */

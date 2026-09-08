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
namespace hades_file_local
{
	class WebLoadingScreenUi;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
		std::string benchmarkMapName; // 0x28
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
using namespace hades_file_local;
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
		_inline LoadingScreenUi::LoadingScreenUi() // 0x10CA9FB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0LoadingScreenUi@LoadingScreen@Patches@@QAE@XZ");
			// Patches::LoadingScreen::LoadingScreenUi *const this;

			compiler_generated();
		}
	}
}

/* ---------- private code */

extern WebLoadingScreenUi* _sub_10CA9FE0(WebLoadingScreenUi *const);
_inline WebLoadingScreenUi::WebLoadingScreenUi() // 0x10CA9FE0
{
	// `anonymous-namespace'::WebLoadingScreenUi::WebLoadingScreenUi
	// WebLoadingScreenUi *const this;
	todo("implement");
	_sub_10CA9FE0(this);
}

_inline WebLoadingScreenUi::~WebLoadingScreenUi() // 0x10CAA170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1WebLoadingScreenUi@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::WebLoadingScreenUi::~WebLoadingScreenUi
	// WebLoadingScreenUi *const this;

	compiler_generated();
}

_extern void _sub_10CAAC00(WebLoadingScreenUi *const, Patches::LoadingScreen::LoadingScreenShowInfo const &);
void WebLoadingScreenUi::Show(Patches::LoadingScreen::LoadingScreenShowInfo const &info) // 0x10CAAC00
{
	// `anonymous-namespace'::WebLoadingScreenUi::Show
	// static ...; // 0x10CAB1CF
	// static ...; // 0x10CAB1C4
	// static ...; // 0x10CAB1A0
	// static ...; // 0x10CAB198
	// WebLoadingScreenUi *const this;
	// Patches::LoadingScreen::LoadingScreenShowInfo const &info;
	// unsigned __int32 separatorIndex;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// std::string mapName;
	// static bool `WebLoadingScreenUi::Show'::`2'::firstShow; // 0x1247EDC8
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	{
		// unsigned __int32 i;
	}
	todo("implement");
	_sub_10CAAC00(this, info);
}

_extern void _sub_10CAA320(WebLoadingScreenUi *const, unsigned __int32);
void WebLoadingScreenUi::Begin(unsigned __int32 totalBytes) // 0x10CAA320
{
	// `anonymous-namespace'::WebLoadingScreenUi::Begin
	// unsigned __int32 totalBytes;
	todo("implement");
	_sub_10CAA320(this, totalBytes);
}

_extern void _sub_10CAB360(WebLoadingScreenUi *const, unsigned __int32);
void WebLoadingScreenUi::UpdateProgress(unsigned __int32 bytes) // 0x10CAB360
{
	// `anonymous-namespace'::WebLoadingScreenUi::UpdateProgress
	// static ...; // 0x10CAB59B
	// static ...; // 0x10CAB590
	// static ...; // 0x10CAB56C
	// static ...; // 0x10CAB564
	// WebLoadingScreenUi *const this;
	// unsigned __int32 bytes;
	// std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > currentTime;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// long long elapsed;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	todo("implement");
	_sub_10CAB360(this, bytes);
}

_extern void _sub_10CAA3A0(WebLoadingScreenUi *const);
void WebLoadingScreenUi::Hide() // 0x10CAA3A0
{
	// `anonymous-namespace'::WebLoadingScreenUi::Hide
	// static ...; // 0x10CAA957
	// static ...; // 0x10CAA952
	// static ...; // 0x10CAA94C
	// static ...; // 0x10CAA928
	// static ...; // 0x10CAA920
	// WebLoadingScreenUi *const this;
	// float tag_memory_used;
	// float used_data_memory_size;
	// s_static_string<4096> stats;
	// float physical_memory_percent;
	// float used_resource_memory_size;
	// char buff[256];
	// double const k_mb;
	// float loaded_tags_percent;
	// float tag_memory_size;
	// float physical_memory_total_size;
	// float used_tag_memory_size;
	// std::chrono::duration<double,std::ratio<1,1> > time_span;
	// float physical_memory_used_size;
	todo("implement");
	_sub_10CAA3A0(this);
}

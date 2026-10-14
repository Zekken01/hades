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
#include "mods/memory/physical_memory_manager.hpp"
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
		virtual ~WebLoadingScreenUi() = default; /* compiler_generated() */
		WebLoadingScreenUi &operator=(WebLoadingScreenUi &); /* compiler_generated() */
		WebLoadingScreenUi &operator=(WebLoadingScreenUi const &); /* compiler_generated() */
	unsigned char __pad1[4]; // 0x44
	};
	static_assert(sizeof(WebLoadingScreenUi) == 72, "Invalid WebLoadingScreenUi size");
}
using namespace hades_file_local;
/* ---------- prototypes */
extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0x10CAA3A0

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
			void Init() // 0x10CAAAE0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebLoadingScreen@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10CAAB9C
				// static ...; // 0x10CAAB90
				// static ...; // 0x10CAAB88
				// std::shared_ptr<WebLoadingScreenUi> ui;

				std::shared_ptr<WebLoadingScreenUi> ui = std::make_shared<WebLoadingScreenUi>();
				Patches::LoadingScreen::SetUi(ui);
			}
		}
	}
}

namespace Patches
{
	namespace LoadingScreen
	{
		// mangled_x86(MANGLED_DEFAULT, "??0LoadingScreenUi@LoadingScreen@Patches@@QAE@XZ"); no body to assert in
	}
}

/* ---------- private code */

_inline WebLoadingScreenUi::WebLoadingScreenUi() : currentBytes(0), totalBytes(0) /* hades-mem-init:  */ // 0x10CA9FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0WebLoadingScreenUi@hades_file_local@@QAE@XZ");
	// the original is empty
	// `anonymous-namespace'::WebLoadingScreenUi::WebLoadingScreenUi
	// WebLoadingScreenUi *const this;
}


void WebLoadingScreenUi::Show(Patches::LoadingScreen::LoadingScreenShowInfo const &info) // 0x10CAAC00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebLoadingScreenUi@hades_file_local@@UAEXABULoadingScreenShowInfo@LoadingScreen@Patches@@@Z");
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
		// unsigned __int32 i;

	benchmark_start = std::chrono::steady_clock::now();
	unsigned __int32 separatorIndex = info.MapPath.find_last_of("\\/");
	std::string mapName = info.MapPath.substr(separatorIndex + 1);
	benchmarkMapName = mapName;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("map");
	jsonWriter.String(mapName.c_str());
	jsonWriter.Key("mapName");
	jsonWriter.String(info.MapName.c_str());
	jsonWriter.Key("mapAuthor");
	jsonWriter.String(info.MapAuthor.c_str());
	jsonWriter.Key("serverName");
	jsonWriter.String(info.ServerName.c_str());
	jsonWriter.Key("serverMessage");
	jsonWriter.String(info.ServerMessage.c_str());
	jsonWriter.Key("mode");
	jsonWriter.Int(info.VariantType);
	jsonWriter.Key("gameType");
	jsonWriter.String(info.VariantName.c_str());
	jsonWriter.Key("rounds");
	jsonWriter.Int(info.NumberOfRounds);
	jsonWriter.Key("timeLimit");
	jsonWriter.Int(info.TimeLimit);
	jsonWriter.Key("scoreToWin");
	jsonWriter.Int(info.ScoreToWin);
	jsonWriter.Key("gameMode");
	jsonWriter.Int(info.GameMode);
	jsonWriter.Key("mapDescription");
	jsonWriter.String(info.MapDescription.c_str());
	jsonWriter.Key("insertionPointName");
	jsonWriter.String(info.InsertionName.c_str());
	jsonWriter.Key("insertionPointDescription");
	jsonWriter.String(info.InsertionDescription.c_str());
	jsonWriter.Key("skulls");
	jsonWriter.StartArray();
	for (unsigned __int32 i = 0; i < info.Skulls.size(); i++)
		jsonWriter.String(info.Skulls[i].c_str());
	jsonWriter.EndArray();
	jsonWriter.Key("difficulty");
	jsonWriter.String(info.Difficulty.c_str());
	jsonWriter.Key("modHash");
	jsonWriter.String(info.modHash.c_str());
	jsonWriter.Key("modName");
	jsonWriter.String(info.modName.c_str());
	jsonWriter.Key("modDescription");
	jsonWriter.String(info.modDescription.c_str());
	jsonWriter.Key("modAuthor");
	jsonWriter.String(info.modAuthor.c_str());
	jsonWriter.Key("modVersion");
	jsonWriter.String(info.modVersion.c_str());
	jsonWriter.EndObject();
	Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Loading, jsonBuffer.GetString());
	static bool firstShow = false;
	if (!firstShow && !ElDorito::Instance().IsConnectingToServer())
	{
		Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Title, "{ firstBoot: true }");
		firstShow = true;
	}
}

void WebLoadingScreenUi::Begin(unsigned __int32 totalBytes) // 0x10CAA320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Begin@WebLoadingScreenUi@hades_file_local@@UAEXI@Z");
	// `anonymous-namespace'::WebLoadingScreenUi::Begin
	// unsigned __int32 totalBytes;

	currentBytes = 0;
	this->totalBytes = totalBytes;
	lastUpdateTime = std::chrono::steady_clock::now();
}

void WebLoadingScreenUi::UpdateProgress(unsigned __int32 bytes) // 0x10CAB360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateProgress@WebLoadingScreenUi@hades_file_local@@UAEXI@Z");
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

	currentBytes += bytes;
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (elapsed < 75)
		return;
	lastUpdateTime = currentTime;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("currentBytes");
	jsonWriter.Int64(currentBytes);
	jsonWriter.Key("totalBytes");
	jsonWriter.Int64(totalBytes);
	jsonWriter.EndObject();
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Loading, "loadprogress", jsonBuffer.GetString());
}

void WebLoadingScreenUi::Hide() // 0x10CAA3A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@WebLoadingScreenUi@hades_file_local@@UAEXXZ");
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
	// std::chrono::duration<double,std::ratio<1> > time_span;
	// float physical_memory_used_size;

	ScreenLayer::Hide(ScreenLayer::Loading);
	ScreenLayer::Notify("loadingFinished", "{}", true);
	benchmark_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(benchmark_end - benchmark_start);
	char buff[256];
	sprintf_s(buff, "%.2f", time_span.count());
	Console::WriteLine(benchmarkMapName + " Map loading took " + std::string(buff) + " seconds.");
	double const k_mb = 1048576.0;
	float used_tag_memory_size = g_cache_file_tag_globals->memory_used / k_mb;
	float tag_memory_size = g_cache_file_tag_globals->memory_size / k_mb;
	float used_data_memory_size = c_physical_memory_manager::get_stage_used_size((e_physical_memory_stage)0) / k_mb;
	float tag_memory_used = c_physical_memory_manager::get_stage_used_size((e_physical_memory_stage)1) / k_mb;
	float used_resource_memory_size = c_physical_memory_manager::get_stage_used_size((e_physical_memory_stage)2) / k_mb;
	float physical_memory_used_size = c_physical_memory_manager::get_used_size() / k_mb;
	float physical_memory_total_size = c_physical_memory_manager::get_total_size() / k_mb;
	float physical_memory_percent = physical_memory_used_size / physical_memory_total_size * 100.0;
	float loaded_tags_percent = (double)g_cache_file_tag_globals->loaded_instance_count / g_cache_file_tag_globals->total_instance_count * 100.0;
	s_static_string<4096> stats;
	stats.print("Physical Memory: %.2f MB / %.2f MB (%.2f%%)\nData Memory Used: %.2f MB\nTag Memory Used: %.2f MB\nTag Instance Memory: %.2f / %.2f MB\nResource Memory Used: %.2f MB\nLoaded Tags: %ld / %ld (%.2f%%)\n", physical_memory_used_size, physical_memory_total_size, physical_memory_percent, used_data_memory_size, tag_memory_used, used_tag_memory_size, tag_memory_size, used_resource_memory_size, g_cache_file_tag_globals->loaded_instance_count, g_cache_file_tag_globals->total_instance_count, loaded_tags_percent);
	Console::WriteLine(stats.get_string());
}

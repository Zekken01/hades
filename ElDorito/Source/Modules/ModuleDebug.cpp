/* ---------- headers */

#include "Modules/ModuleDebug.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
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
#include "Utils/CommandLineUtils.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <cef_app.h>
#include <cef_audio_handler.h>
#include <cef_base.h>
#include <cef_browser_process_handler.h>
#include <cef_client.h>
#include <cef_command_handler.h>
#include <cef_context_menu_handler.h>
#include <cef_devtools_message_observer.h>
#include <cef_dialog_handler.h>
#include <cef_display_handler.h>
#include <cef_download_handler.h>
#include <cef_drag_handler.h>
#include <cef_extension_handler.h>
#include <cef_find_handler.h>
#include <cef_focus_handler.h>
#include <cef_frame_handler.h>
#include <cef_jsdialog_handler.h>
#include <cef_keyboard_handler.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_menu_model_delegate.h>
#include <cef_print_handler.h>
#include <cef_render_handler.h>
#include <cef_render_process_handler.h>
#include <cef_request_handler.h>
#include <cef_resource_handler.h>
#include <cef_resource_request_handler.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
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

struct begin;
struct end;
struct lambda_1;
struct s_object_definition;
struct s_object_header;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleDebug;
}
namespace Web
{
	namespace Browser
	{
		class WebRenderer;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
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
	namespace DeterminismDebug {}
	using namespace Patches::DeterminismDebug;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

//class CommandDialogTest::__l2::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
//};
//static_assert(sizeof(CommandDialogTest::__l2::<lambda_1>) == 1, "Invalid CommandDialogTest::__l2::<lambda_1> size");

/* ---------- prototypes */

bool CommandCrash(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandNuke(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDumpTags(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDialogTest(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDebugTint(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandRasterizerSetZPlanes(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandTeleportToCamera(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandReflectionDebug(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandStartRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandStopRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandCefOpenURL(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandLaunchClient(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandTileWindows(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandRenderGeoHitTest(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameShowCrte(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandHideForgeObjects(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleDebug* _sub_1097C0F0(Modules::ModuleDebug *const);
	ModuleDebug::ModuleDebug() : ModuleBase(todo_result<std::string>()) // 0x1097C0F0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleDebug@Modules@@QAE@XZ");
		// Modules::ModuleDebug *const this;
		todo("implement");
		_sub_1097C0F0(this);
	}
}

/* ---------- private code */

_extern bool _sub_1097F460(std::vector<std::string> const &, std::string &);
bool CommandCrash(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F460
{
	// `anonymous-namespace'::CommandCrash
	// static ...; // 0x1097F588
	// static ...; // 0x1097F580
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;
	// __int32 volatile *a;
	todo("implement");
	bool __result = _sub_1097F460(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109807F0(std::vector<std::string> const &, std::string &);
bool CommandNuke(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109807F0
{
	// `anonymous-namespace'::CommandNuke
	// static ...; // 0x1098090C
	// static ...; // 0x10980904
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;
	// function call : void *()
	// function call : __int32 (void *, unsigned __int32)
	todo("implement");
	bool __result = _sub_109807F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097FBB0(std::vector<std::string> const &, std::string &);
bool CommandDumpTags(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FBB0
{
	// `anonymous-namespace'::CommandDumpTags
	// static ...; // 0x1097FD94
	// static ...; // 0x1097FD7C
	// static ...; // 0x1097FD74
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// _iobuf *fp;
	// char const *filename;
	{
		// __int32 i;
		{
			// char const *tag_name;
			// long index;
			// char tag_group_name[5];
		}
	}
	todo("implement");
	bool __result = _sub_1097FBB0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097FA00(std::vector<std::string> const &, std::string &);
bool CommandDialogTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FA00
{
	// `anonymous-namespace'::CommandDialogTest
	// static ...; // 0x1097FB40
	// static ...; // 0x1097FB38
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Web::Ui::ScreenLayer::SDialogShowParams params;
	todo("implement");
	bool __result = _sub_1097FA00(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097F5F0(std::vector<std::string> const &, std::string &);
bool CommandDebugTint(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F5F0
{
	// `anonymous-namespace'::CommandDebugTint
	// static ...; // 0x1097F91C
	// static ...; // 0x1097F914
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	{
		// std::stringstream ss;
	}
	todo("implement");
	bool __result = _sub_1097F5F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10980970(std::vector<std::string> const &, std::string &);
bool CommandRasterizerSetZPlanes(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980970
{
	// `anonymous-namespace'::CommandRasterizerSetZPlanes
	// static ...; // 0x10980EE0
	// static ...; // 0x10980ED8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// static float `CommandRasterizerSetZPlanes'::`2'::far_clip_plane; // 0x12454D64
	// static float `CommandRasterizerSetZPlanes'::`2'::near_clip_plane; // 0x12454D60
	{
		// float far_plane;
		// float near_plane;
	}
	{
		// std::stringstream ss;
	}
	todo("implement");
	bool __result = _sub_10980970(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10981480(std::vector<std::string> const &, std::string &);
bool CommandTeleportToCamera(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981480
{
	// `anonymous-namespace'::CommandTeleportToCamera
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_10981480(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10981050(std::vector<std::string> const &, std::string &);
bool CommandReflectionDebug(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981050
{
	// `anonymous-namespace'::CommandReflectionDebug
	// static ...; // 0x109811C4
	// static ...; // 0x109811BC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool &g_reflection_debug;
	// __int32 const value;
	{
		// std::stringstream ss;
	}
	todo("implement");
	bool __result = _sub_10981050(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10981370(std::vector<std::string> const &, std::string &);
bool CommandStartRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981370
{
	// `anonymous-namespace'::CommandStartRandomTrace
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_10981370(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10981420(std::vector<std::string> const &, std::string &);
bool CommandStopRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981420
{
	// `anonymous-namespace'::CommandStopRandomTrace
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_10981420(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097F2D0(std::vector<std::string> const &, std::string &);
bool CommandCefOpenURL(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F2D0
{
	// `anonymous-namespace'::CommandCefOpenURL
	// static ...; // 0x1097F3F0
	// static ...; // 0x1097F3E8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	todo("implement");
	bool __result = _sub_1097F2D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10980230(std::vector<std::string> const &, std::string &);
bool CommandLaunchClient(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980230
{
	// `anonymous-namespace'::CommandLaunchClient
	// static ...; // 0x109806B2
	// static ...; // 0x109806A4
	// static ...; // 0x10980680
	// static ...; // 0x10980678
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool hasConnect;
	// std::vector<std::string> args;
	// std::string formattedArgs;
	// char exePath[260];
	{
		// std::vector<std::string> const &<range>$L0;
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
		{
			// std::string const &arg;
		}
	}
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
	// function call : unsigned long ()
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	// function call : unsigned long ()
	todo("implement");
	bool __result = _sub_10980230(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109814D0(std::vector<std::string> const &, std::string &);
bool CommandTileWindows(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109814D0
{
	// `anonymous-namespace'::CommandTileWindows
	// static ...; // 0x1098174B
	// static ...; // 0x10981748
	// static ...; // 0x10981724
	// static ...; // 0x1098171C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// HWND__ *windows[32];
	// __int32 rowHeight;
	// __int32 posX;
	// __int32 screenHeight;
	// HWND__ *hwnd;
	// __int32 numWindows;
	// __int32 posY;
	// __int32 screenWidth;
	{
		// char windowTitle[1024];
	}
	{
		// __int32 i;
		{
			// __int32 ww;
			// HWND__ *hwnd;
			// tagRECT wr;
			// __int32 wh;
		}
	}
	// function call : __int32 (__int32)
	// function call : __int32 (__int32)
	// function call : HWND__ *(HWND__ *, HWND__ *, char const *, char const *)
	// function call : __int32 (HWND__ *, char *, __int32)
	// function call : __int32 (HWND__ *, __int32)
	// function call : __int32 (HWND__ *, tagRECT *)
	// function call : __int32 (HWND__ *, HWND__ *, __int32, __int32, __int32, __int32, unsigned __int32)
	todo("implement");
	bool __result = _sub_109814D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10981240(std::vector<std::string> const &, std::string &);
bool CommandRenderGeoHitTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981240
{
	// `anonymous-namespace'::CommandRenderGeoHitTest
	// std::string &returnInfo;
	// bool &globalVar;
	todo("implement");
	bool __result = _sub_10981240(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097FE30(std::vector<std::string> const &, std::string &);
bool CommandGameShowCrte(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FE30
{
	// `anonymous-namespace'::CommandGameShowCrte
	// static ...; // 0x1097FF94
	// static ...; // 0x1097FF7C
	// static ...; // 0x1097FF74
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// short tag_index;
	// constexpr void (*const `CommandGameShowCrte'::`2'::cortana_globals__play_effect)(__int32); // constant == 11267264
	{
		// std::stringstream ss;
	}
	// function call : void (*const)(__int32)
	todo("implement");
	bool __result = _sub_1097FE30(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10980000(std::vector<std::string> const &, std::string &);
bool CommandHideForgeObjects(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980000
{
	// `anonymous-namespace'::CommandHideForgeObjects
	// static ...; // 0x109801B0
	// static ...; // 0x109801A8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// void (*const object_hide)(long, bool);
	// bool hidden;
	// Blam::Network::Session *session;
	{
		// c_data_array<s_object_header> *object_headers;
		{
			// c_data_iterator<s_object_header> it;
			{
				// s_object_definition *object_definition;
				// long definition_index;
				// unsigned long objectIndex;
			}
		}
	}
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, bool)
	todo("implement");
	bool __result = _sub_10980000(Arguments, returnInfo);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::WriteFast<float>(float const) const;

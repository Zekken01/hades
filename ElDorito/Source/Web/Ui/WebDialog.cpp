/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
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
#include "Utils/EventSink.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <limits>
#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

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
namespace
{
	struct SDialogCallbackInfo;
	struct SDialogQueueInfo;
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
		namespace WebDialog {}
		using namespace Web::Ui::WebDialog;
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

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct SDialogCallbackInfo
	{
		__int32 id; // 0x0
		unsigned char __pad0[4]; // 0x4
		std::function<void __cdecl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &)> callback; // 0x8
		SDialogCallbackInfo(SDialogCallbackInfo &); /* compiler_generated() */
		SDialogCallbackInfo(SDialogCallbackInfo const &); /* compiler_generated() */
		SDialogCallbackInfo(); /* compiler_generated() */
		~SDialogCallbackInfo(); /* compiler_generated() */
		SDialogCallbackInfo &operator=(SDialogCallbackInfo &); /* compiler_generated() */
		SDialogCallbackInfo &operator=(SDialogCallbackInfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(SDialogCallbackInfo) == 48, "Invalid SDialogCallbackInfo size");

	struct SDialogQueueInfo
	{
		__int32 id; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > title; // 0x4
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > body; // 0x20
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > templateName; // 0x3C
		SDialogQueueInfo(SDialogQueueInfo &); /* compiler_generated() */
		SDialogQueueInfo(SDialogQueueInfo const &); /* compiler_generated() */
		SDialogQueueInfo(); /* compiler_generated() */
		~SDialogQueueInfo(); /* compiler_generated() */
		SDialogQueueInfo &operator=(SDialogQueueInfo &); /* compiler_generated() */
		SDialogQueueInfo &operator=(SDialogQueueInfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(SDialogQueueInfo) == 88, "Invalid SDialogQueueInfo size");
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			typedef std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> TDialogHandler;
			typedef std::function<void __cdecl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &)> TDialogResultCallback;
		}
	}
}

namespace
{

}
/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebDialog
		{
			extern void HandleDialogShowRequest(Web::Ui::ScreenLayer::SDialogShowParams const &params);
			extern void Init();
			extern void SubmitDialogResult(__int32 id, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &result);
			extern void Clear();
		}
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern __int32 idCounter; // 0x1247ED78
}
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebDialog
		{
			_extern void _sub_10CA1610(Web::Ui::ScreenLayer::SDialogShowParams const &);
			void HandleDialogShowRequest(Web::Ui::ScreenLayer::SDialogShowParams const &params) // 0x10CA1610
			{
				mangled_x86(MANGLED_TODO, "?HandleDialogShowRequest@WebDialog@Ui@Web@@YAXABUSDialogShowParams@ScreenLayer@23@@Z");
				// static ...; // 0x10CA1B61
				// static ...; // 0x10CA1B54
				// static ...; // 0x10CA1B4F
				// static ...; // 0x10CA1B48
				// static ...; // 0x10CA1B18
				// static ...; // 0x10CA1B10
				// Web::Ui::ScreenLayer::SDialogShowParams const &params;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// SDialogCallbackInfo callbackInfo;
				// SDialogQueueInfo queueInfo;
				{
					// unsigned __int32 i;
				}
				todo("implement");
				_sub_10CA1610(params);
			}

			_extern void _sub_10CA1CD0();
			void Init() // 0x10CA1CD0
			{
				mangled_x86(MANGLED_TODO, "?Init@WebDialog@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CA1CD0();
			}

			_extern void _sub_10CA1DE0(__int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
			void SubmitDialogResult(__int32 id, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &result) // 0x10CA1DE0
			{
				mangled_x86(MANGLED_TODO, "?SubmitDialogResult@WebDialog@Ui@Web@@YAXHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10CA1FE4
				// static ...; // 0x10CA1FDC
				// __int32 id;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &result;
				// SDialogCallbackInfo nextCallback;
				{
					// unsigned __int32 i;
				}
				todo("implement");
				_sub_10CA1DE0(id, result);
			}

			_extern void _sub_10CA15B0();
			void Clear() // 0x10CA15B0
			{
				mangled_x86(MANGLED_TODO, "?Clear@WebDialog@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CA15B0();
			}
		}
	}
}

/* ---------- private code */

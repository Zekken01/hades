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
namespace hades_file_local
{
	struct SDialogCallbackInfo;
	struct SDialogQueueInfo;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	struct SDialogCallbackInfo
	{
		__int32 id; // 0x0
		unsigned char __pad0[4]; // 0x4
		std::function<void __cdecl(std::string const &)> callback; // 0x8
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
		std::string title; // 0x4
		std::string body; // 0x20
		std::string templateName; // 0x3C
		SDialogQueueInfo(SDialogQueueInfo &); /* compiler_generated() */
		SDialogQueueInfo(SDialogQueueInfo const &); /* compiler_generated() */
		SDialogQueueInfo(); /* compiler_generated() */
		~SDialogQueueInfo(); /* compiler_generated() */
		SDialogQueueInfo &operator=(SDialogQueueInfo &); /* compiler_generated() */
		SDialogQueueInfo &operator=(SDialogQueueInfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(SDialogQueueInfo) == 88, "Invalid SDialogQueueInfo size");
}
using namespace hades_file_local;
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			typedef std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> TDialogHandler;
			typedef std::function<void __cdecl(std::string const &)> TDialogResultCallback;
		}
	}
}

namespace hades_file_local
{

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebDialog
		{
			extern void HandleDialogShowRequest(Web::Ui::ScreenLayer::SDialogShowParams const &params);
			extern void Init();
			extern void SubmitDialogResult(__int32 id, std::string const &result);
			extern void Clear();
		}
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 idCounter; // 0x1247ED78
}
using namespace hades_file_local;
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

			_extern void _sub_10CA1DE0(__int32, std::string const &);
			void SubmitDialogResult(__int32 id, std::string const &result) // 0x10CA1DE0
			{
				mangled_x86(MANGLED_TODO, "?SubmitDialogResult@WebDialog@Ui@Web@@YAXHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10CA1FE4
				// static ...; // 0x10CA1FDC
				// __int32 id;
				// std::string const &result;
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

_inline SDialogCallbackInfo::SDialogCallbackInfo(SDialogCallbackInfo const &__that) // 0x10CA0890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SDialogCallbackInfo@hades_file_local@@QAE@ABU01@@Z");
	// `anonymous-namespace'::SDialogCallbackInfo::SDialogCallbackInfo
	// SDialogCallbackInfo const &__that;

	compiler_generated();
}

_inline SDialogCallbackInfo::SDialogCallbackInfo() // 0x10CA0910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SDialogCallbackInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SDialogCallbackInfo::SDialogCallbackInfo
	// SDialogCallbackInfo *const this;

	compiler_generated();
}

_inline SDialogQueueInfo::SDialogQueueInfo(SDialogQueueInfo &__that) // 0x10CA0970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SDialogQueueInfo@hades_file_local@@QAE@AAU01@@Z");
	// `anonymous-namespace'::SDialogQueueInfo::SDialogQueueInfo
	// SDialogQueueInfo &__that;

	compiler_generated();
}

_inline SDialogQueueInfo::SDialogQueueInfo(SDialogQueueInfo const &__that) // 0x10CA0A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SDialogQueueInfo@hades_file_local@@QAE@ABU01@@Z");
	// `anonymous-namespace'::SDialogQueueInfo::SDialogQueueInfo
	// SDialogQueueInfo const &__that;

	compiler_generated();
}

_inline SDialogQueueInfo::SDialogQueueInfo() // 0x10CA0B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SDialogQueueInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SDialogQueueInfo::SDialogQueueInfo
	// SDialogQueueInfo *const this;

	compiler_generated();
}

_inline SDialogCallbackInfo::~SDialogCallbackInfo() // 0x10CA0F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SDialogCallbackInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SDialogCallbackInfo::~SDialogCallbackInfo
	// SDialogCallbackInfo *const this;

	compiler_generated();
}

_inline SDialogQueueInfo::~SDialogQueueInfo() // 0x10CA0FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SDialogQueueInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SDialogQueueInfo::~SDialogQueueInfo
	// SDialogQueueInfo *const this;

	compiler_generated();
}

extern SDialogQueueInfo &_sub_10CA1010(SDialogQueueInfo *const, SDialogQueueInfo &);
_inline SDialogQueueInfo &SDialogQueueInfo::operator=(SDialogQueueInfo &__that) // 0x10CA1010
{
	// `anonymous-namespace'::SDialogQueueInfo::operator=
	// SDialogQueueInfo &__that;
	compiler_generated();
	todo("implement");
	SDialogQueueInfo & __result = _sub_10CA1010(this, __that);
	return __result;
}

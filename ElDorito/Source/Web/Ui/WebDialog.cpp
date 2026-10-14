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
		std::function<void __cdecl(std::string const &)> callback; // 0x8
		SDialogCallbackInfo(SDialogCallbackInfo &); /* compiler_generated() */
		SDialogCallbackInfo(SDialogCallbackInfo const &); /* compiler_generated() */
		SDialogCallbackInfo(); /* compiler_generated() */
		~SDialogCallbackInfo() = default;
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
		// SDialogQueueInfo(SDialogQueueInfo &&);  // hades: implicit /* compiler_generated() */
		// SDialogQueueInfo(SDialogQueueInfo const &);  // hades: implicit /* compiler_generated() */
		// SDialogQueueInfo();  // hades: implicit /* compiler_generated() */
		// ~SDialogQueueInfo();  // hades: implicit /* compiler_generated() */
		// SDialogQueueInfo &operator=(SDialogQueueInfo &&);  // hades: implicit /* compiler_generated() */  // hades: the PDB's `T &` is the move assignment (it moves the strings)
		// SDialogQueueInfo &operator=(SDialogQueueInfo const &);  // hades: implicit /* compiler_generated() */
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

namespace Web { namespace Ui { namespace ScreenLayer { extern CEventSink<> BeforeReload; } } }  // hades: added for 0x10CA1CD0

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
	extern std::vector<SDialogQueueInfo> queueList; // 0x1247ED54
	extern "C" {
	std::queue<SDialogCallbackInfo> callbacks; // 0x1247ED64
	}
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
			void HandleDialogShowRequest(Web::Ui::ScreenLayer::SDialogShowParams const &params) // 0x10CA1610
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?HandleDialogShowRequest@WebDialog@Ui@Web@@YAXABUSDialogShowParams@ScreenLayer@23@@Z");
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
					// unsigned __int32 i;

				for (unsigned __int32 i = 0; i < queueList.size(); i++)
				{
					if (params.templateName == "alert_template" && params.customTitle == queueList[i].title && params.customBody == queueList[i].body && params.templateName == queueList[i].templateName)
					{
						params.callback("ok");
						return;
					}
				}
				SDialogQueueInfo queueInfo;
				queueInfo.id = idCounter;
				queueInfo.title = params.customTitle;
				queueInfo.body = params.customBody;
				queueInfo.templateName = params.templateName;
				queueList.push_back(queueInfo);
				SDialogCallbackInfo callbackInfo;
				callbackInfo.id = idCounter++;
				callbackInfo.callback = params.callback;
				callbacks.push(callbackInfo);
				rapidjson::StringBuffer buff;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
				writer.StartObject();
				writer.Key("native");
				writer.Bool(true);
				writer.Key("nativeId");
				writer.Int(callbackInfo.id);
				writer.Key("template");
				writer.String(params.templateName.c_str());
				writer.Key("data");
				writer.StartObject();
				if (!params.customTitle.empty())
				{
					writer.Key("title");
					writer.String(params.customTitle.c_str());
				}
				if (!params.customBody.empty())
				{
					writer.Key("body");
					writer.String(params.customBody.c_str());
				}
				if (!params.initialValue.empty())
				{
					writer.Key("initialValue");
					writer.String(params.initialValue.c_str());
				}
				if (params.dialogHeight != 0)
				{
					writer.Key("dialogHeight");
					writer.Double(params.dialogHeight);
				}
				if (params.maxLength != 0)
				{
					writer.Key("maxLength");
					writer.Int(params.maxLength);
				}
				if (params.numRows != 0)
				{
					writer.Key("numRows");
					writer.Int(params.numRows);
				}
				writer.EndObject();
				writer.EndObject();
				ScreenLayer::Notify("dialog", buff.GetString(), true);
			}

			void Init() // 0x10CA1CD0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebDialog@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Web::Ui::ScreenLayer::BeforeReload.Subscribe(Clear);
				Web::Ui::ScreenLayer::SetDialogHandler(HandleDialogShowRequest);
			}


			void SubmitDialogResult(__int32 id, std::string const &result) // 0x10CA1DE0
			{ mangled_x86(MANGLED_TODO, "?SubmitDialogResult@WebDialog@Ui@Web@@YAXHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				assert(!callbacks.empty());
				SDialogCallbackInfo nextCallback = callbacks.front();

				assert(nextCallback.id == id);
				if (nextCallback.id != id)
					return;
				nextCallback.callback(result);
				for (unsigned __int32 i = 0; i < queueList.size(); i++)
				{
					if (queueList.at(i).id == nextCallback.id)
					{
						// hades: the erase emits vector::begin, the iterator's operator+ and its
						// (pointer, container) constructor (0x10CA0590) in this object
						queueList.erase(queueList.begin() + i);
						break;
					}
				}
				callbacks.pop();
			}
			// hades: the PDB notes for SubmitDialogResult (statics at 0x10CA1FE4, 0x10CA1FDC; locals id,
			// result, nextCallback and the loop's i) were moved here so its asserts sit on the original's
			// lines relative to the opening brace; the file keeps its line count.







			void Clear() // 0x10CA15B0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@WebDialog@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				while (!callbacks.empty())
				{
					callbacks.pop();
				}
			}
		}
	}
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0SDialogCallbackInfo@hades_file_local@@QAE@ABU01@@Z"); no body to assert in
_inline SDialogCallbackInfo::SDialogCallbackInfo(SDialogCallbackInfo const &__that) = default; // 0x10CA0890

// mangled_x86(MANGLED_DEFAULT, "??0SDialogCallbackInfo@hades_file_local@@QAE@XZ"); no body to assert in
_inline SDialogCallbackInfo::SDialogCallbackInfo() = default; // 0x10CA0910

// mangled_x86(MANGLED_DEFAULT, "??0SDialogQueueInfo@hades_file_local@@QAE@AAU01@@Z"); no body to assert in
// _inline SDialogQueueInfo::SDialogQueueInfo(SDialogQueueInfo &&__that) = default; // 0x10CA0970  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0SDialogQueueInfo@hades_file_local@@QAE@ABU01@@Z"); no body to assert in
// _inline SDialogQueueInfo::SDialogQueueInfo(SDialogQueueInfo const &__that) = default; // 0x10CA0A40  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0SDialogQueueInfo@hades_file_local@@QAE@XZ"); no body to assert in
// _inline SDialogQueueInfo::SDialogQueueInfo() = default; // 0x10CA0B50  // hades: implicit


// mangled_x86(MANGLED_DEFAULT, "??1SDialogQueueInfo@hades_file_local@@QAE@XZ"); no body to assert in
// _inline SDialogQueueInfo::~SDialogQueueInfo() = default; // 0x10CA0FA0  // hades: implicit

// _inline SDialogQueueInfo &SDialogQueueInfo::operator=(SDialogQueueInfo &&__that) = default; // 0x10CA1010  // hades: implicit

/* ---------- explicit instantiations */
template class std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<SDialogQueueInfo> > >;
template class std::_Vector_iterator<std::_Vector_val<std::_Simple_types<SDialogQueueInfo> > >;
template class std::queue<SDialogCallbackInfo>;
template std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<SDialogQueueInfo> > >::~_Vector_const_iterator();
template std::_Vector_iterator<std::_Vector_val<std::_Simple_types<SDialogQueueInfo> > >::~_Vector_iterator();
template std::queue<SDialogCallbackInfo>::~queue();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::vector<SDialogQueueInfo> queueList; }
namespace hades_file_local { __int32 idCounter; }

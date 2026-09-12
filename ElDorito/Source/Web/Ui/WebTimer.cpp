/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
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
#include "Web/Ui/Screen.hpp"

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
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

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
		namespace WebTimer {}
		using namespace Web::Ui::WebTimer;
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

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebTimer
		{
			extern void Start(std::string const &type, __int32 initialValue);
			extern void Update(__int32 value);
			extern void End();
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
		namespace WebTimer
		{
			_extern void _sub_10CB5BB0(std::string const &, __int32);
			void Start(std::string const &type, __int32 initialValue) // 0x10CB5BB0
			{
				mangled_x86(MANGLED_TODO, "?Start@WebTimer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
				// static ...; // 0x10CB5D5C
				// static ...; // 0x10CB5D44
				// static ...; // 0x10CB5D3C
				// std::string const &type;
				// __int32 initialValue;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
				todo("implement");
				_sub_10CB5BB0(type, initialValue);
			}

			void Update(__int32 value) // 0x10CB5DF0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Update@WebTimer@Ui@Web@@YAXH@Z");
				// static ...; // 0x10CB5F67
				// static ...; // 0x10CB5F5C
				// static ...; // 0x10CB5F44
				// static ...; // 0x10CB5F3C
				// __int32 value;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;

				rapidjson::StringBuffer jsonBuffer;
				rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);

				jsonWriter.StartObject();
				jsonWriter.Key("value");
				jsonWriter.Int(value);
				jsonWriter.EndObject();

				Web::Ui::ScreenLayer::Notify("timerUpdate", jsonBuffer.GetString(), true);
			}

			void End() // 0x10CB5A00
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?End@WebTimer@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10CB5B4B
				// static ...; // 0x10CB5B40
				// static ...; // 0x10CB5B28
				// static ...; // 0x10CB5B20
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;

				rapidjson::StringBuffer jsonBuffer;
				rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);

				Web::Ui::ScreenLayer::Notify("timerEnd", "{}", true);
			}
		}
	}
}

/* ---------- private code */

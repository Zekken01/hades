/* ---------- headers */

#include "Modules/ModuleVoIP.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/input/input.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Modules/ModuleInput.hpp"
#include "Patch.hpp"
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
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"

#include "Web/Ui/ScreenLayer.hpp"  // hades: added for 0x10A258C0

#include "Patches/Core.hpp"  // hades: added for 0x10A24050

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		enum KeyCode : unsigned short;
		struct BindingsTable;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleVoIP;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
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
		namespace WebChat {}
		using namespace Web::Ui::WebChat;
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
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "Patches/Ui.hpp"  // hades: added for 0x10A24EC0
namespace Web { namespace Ui { namespace WebChat { extern bool IsChatBoxVisible(); } } }  // hades: added for 0x10A24EC0

bool UpdateVoip(std::vector<std::string> const &Arguments, std::string &returnInfo);
void RendererStarted(char const *map);
bool VariableListenToMicrophone(std::vector<std::string> const &arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool ready; // 0x124578D0
	extern bool isMainMenu; // 0x124578D1
	extern bool isChatting; // 0x124578D2
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	void ModuleVoIP::Tick() // 0x10A24EC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ModuleVoIP@Modules@@QAEXXZ");

		bool isUsingController = *(bool *)0x244DE98;
		Blam::Input::BindingsTable bindings;
		Blam::Input::GetBindings(0, &bindings);
		if (Modules::ModuleVoIP::Instance().VarPTTEnabled->ValueInt == 1)
		{
			if (!Modules::ModuleVoIP::Instance().voipConnected)
				return;
			if (!isUsingController)
			{
				bool infocus = false;
				HWND__ *hWnd = *(HWND__ **)0x199C014;
				if (hWnd && GetForegroundWindow() == hWnd)
					infocus = true;
				Blam::Input::KeyCode primaryBind = bindings.PrimaryKeys[Blam::Input::eGameActionVoiceChat];
				Blam::Input::KeyCode secondaryBind = bindings.SecondaryKeys[Blam::Input::eGameActionVoiceChat];
				short kbmKeyPrimary = GetAsyncKeyState(Blam::Input::GetVirtualKey(primaryBind));
				short kbmKeySecondary = GetAsyncKeyState(Blam::Input::GetVirtualKey(secondaryBind));
				if (primaryBind == Blam::Input::eKeyCode_None)
					kbmKeyPrimary = 0;
				if (secondaryBind == Blam::Input::eKeyCode_None)
					kbmKeySecondary = 0;
				unsigned char *mouseButtons = (unsigned char *)0x238E6AC;
				bool mousePrimary = mouseButtons[bindings.PrimaryMouseButtons[Blam::Input::eGameActionVoiceChat]] != 0;
				bool mouseSeconday = mouseButtons[bindings.SecondaryMouseButtons[Blam::Input::eGameActionVoiceChat]] != 0;
				if (isChatting && !kbmKeyPrimary && !kbmKeySecondary && !mousePrimary && !mouseSeconday)
				{
					isChatting = false;
					Patches::Ui::TogglePTTSound(false);
					Web::Ui::ScreenLayer::Notify("voip-ptt", "{\"talk\":0}", true);
				}
				else if (!isChatting && (kbmKeyPrimary || kbmKeySecondary || mousePrimary || mouseSeconday) && infocus && !Web::Ui::WebChat::IsChatBoxVisible())
				{
					isChatting = true;
					Patches::Ui::TogglePTTSound(true);
					Web::Ui::ScreenLayer::Notify("voip-ptt", "{\"talk\":1}", true);
				}
			}
			else
			{
				if (isChatting && !Blam::Input::GetActionState(Blam::Input::eGameActionVoiceChat)->Ticks)
				{
					isChatting = false;
					Patches::Ui::TogglePTTSound(false);
					Web::Ui::ScreenLayer::Notify("voip-ptt", "{\"talk\":0}", true);
				}
				else if (!isChatting && Blam::Input::GetActionState(Blam::Input::eGameActionVoiceChat)->Ticks == 1)
				{
					isChatting = true;
					Patches::Ui::TogglePTTSound(true);
					Web::Ui::ScreenLayer::Notify("voip-ptt", "{\"talk\":1}", true);
				}
			}
		}
	}

	ModuleVoIP::ModuleVoIP() : ModuleBase("VoIP"), voipConnected(false), voiceDetected(false), playersSpeaking(0), playersSpoke(0), playersMuted(0) /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A24050
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleVoIP@Modules@@QAE@XZ");

		VarVoipEnabled = AddVariableInt("Enabled", "enabled", "Toggle voip on or off", eCommandFlagsArchived, 1);
		VarVoipEnabled->ValueIntMin = 0;
		VarVoipEnabled->ValueIntMax = 1;
		VarPTTEnabled = AddVariableInt("PTT_Enabled", "ptt_enabled", "Enable PTT(1) or voice activation(0)", eCommandFlagsArchived, 1);
		VarPTTEnabled->ValueIntMin = 0;
		VarPTTEnabled->ValueIntMax = 1;
		VarMicrophone = AddVariableString("MicrophoneID", "microphoneid", "microphone label to use for voip, blank is default device", eCommandFlagsArchived, "");
		VarEchoCancellation = AddVariableInt("EchoCancelation", "echocancellation", "Toggle echo cancellation", eCommandFlagsArchived, 1);
		VarEchoCancellation->ValueIntMin = 0;
		VarEchoCancellation->ValueIntMax = 1;
		VarAGC = AddVariableInt("AGC", "agc", "Toggle automatic gain control", eCommandFlagsArchived, 1);
		VarAGC->ValueIntMin = 0;
		VarAGC->ValueIntMax = 1;
		VarNoiseSupress = AddVariableInt("NoiseSupress", "noisesupress", "Toggle noise supression", eCommandFlagsArchived, 1);
		VarNoiseSupress->ValueIntMin = 0;
		VarNoiseSupress->ValueIntMax = 1;
		AddCommand("Update", "voip_update", "Updates the voip screen layer with variable states", eCommandFlagsNone, UpdateVoip);
		VarPTTSoundEnabled = AddVariableInt("PTTSoundEnabled", "ptt_sound_enabled", "Toggles the sound played when using Push-To-Talk.", eCommandFlagsArchived, 1);
		VarPTTSoundEnabled->ValueIntMin = 0;
		VarPTTSoundEnabled->ValueIntMax = 1;
		VarSpeakingPlayerOnHUD = AddVariableInt("SpeakingPlayerOnHUD", "speaking_player_hud", "Shows the speaking player on the HUD, rather than the web overlay.", eCommandFlagsArchived, 0);
		VarSpeakingPlayerOnHUD->ValueIntMin = 0;
		VarSpeakingPlayerOnHUD->ValueIntMax = 1;
		VarIncomingVolume = AddVariableFloat("IncomingVolume", "voip_incoming_volume", "Set the default incoming voice chat volume", eCommandFlagsArchived, 1.0f);
		VarIncomingVolume->ValueFloatMin = 0.0f;
		VarIncomingVolume->ValueFloatMax = 2.0f;
		VarStatsEnabled = AddVariableInt("Stats", "voip_stats", "Enable voip statics overlay", eCommandFlagsNone, 0);
		VarStatsEnabled->ValueIntMin = 0;
		VarStatsEnabled->ValueIntMax = 1;
		VarOutgoingVolume = AddVariableFloat("OutgoingVolume", "voip_outgoing_volume", "Set the outgoing voice volume", eCommandFlagsArchived, 1.0f);
		VarOutgoingVolume->ValueFloatMin = 0.0f;
		VarOutgoingVolume->ValueFloatMax = 2.0f;
		VarListenToMicrophone = AddVariableInt("ListenToMicrophone", "listen_to_microphone", "toggle playback of the current audio device", eCommandFlagsHidden, 0, VariableListenToMicrophone);
		VarListenToMicrophone->ValueIntMin = 0;
		VarListenToMicrophone->ValueIntMax = 1;
		VarMaximumBitrate = AddVariableInt("MaximumBitrate", "max_bitrate", "Set the maximum bitrate for each voip peer", eCommandFlagsArchived, 0x7D00);
		Patches::Core::OnMapLoaded(RendererStarted);
	}

	bool ModuleVoIP::IsChatting() // 0x10A24D90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsChatting@ModuleVoIP@Modules@@QAE_NXZ");

		return isChatting;
	}
}

/* ---------- private code */

bool UpdateVoip(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A25520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateVoip@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (!ready)
	{
		returnInfo = "Game is not ready yet";
		return true;
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writer.StartObject();
	writer.Key("PTT_Enabled");
	writer.Int(Modules::ModuleVoIP::Instance().VarPTTEnabled->ValueInt);
	writer.Key("MicrophoneID");
	writer.String(Modules::ModuleVoIP::Instance().VarMicrophone->ValueString.c_str());
	writer.Key("EchoCancellation");
	writer.Int(Modules::ModuleVoIP::Instance().VarEchoCancellation->ValueInt);
	writer.Key("AGC");
	writer.Int(Modules::ModuleVoIP::Instance().VarAGC->ValueInt);
	writer.Key("NoiseSupress");
	writer.Int(Modules::ModuleVoIP::Instance().VarNoiseSupress->ValueInt);
	writer.Key("Enabled");
	writer.Int(Modules::ModuleVoIP::Instance().VarVoipEnabled->ValueInt);
	writer.Key("IncomingVolume");
	writer.Double(Modules::ModuleVoIP::Instance().VarIncomingVolume->ValueFloat);
	writer.Key("OutgoingVolume");
	writer.Double(Modules::ModuleVoIP::Instance().VarOutgoingVolume->ValueFloat);
	writer.Key("MaximumBitrate");
	writer.Int(Modules::ModuleVoIP::Instance().VarMaximumBitrate->ValueInt);
	writer.EndObject();
	Web::Ui::ScreenLayer::Notify("voip-settings", buffer.GetString(), true);
	returnInfo = "";
	return true;
}

void RendererStarted(char const *map) // 0x10A24DC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RendererStarted@@YAXPBD@Z");

	if (std::string(map).find("mainmenu") == std::string::npos)
		isMainMenu = false;
	else
		isMainMenu = true;
	ready = true;
}

bool VariableListenToMicrophone(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10A258C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableListenToMicrophone@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer(buffer);
	writer.StartObject();
	writer.Key("listen");
	writer.Bool(Modules::ModuleVoIP::Instance().VarListenToMicrophone->ValueInt);
	writer.EndObject();
	Web::Ui::ScreenLayer::Notify("voip-toggle-test-audio", buffer.GetString(), true);
	return true;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool ready; }
namespace hades_file_local { bool isMainMenu; }
namespace hades_file_local { bool isChatting; }

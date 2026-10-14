/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/HsGlobalSync.hpp"
#include "Utils/Bits.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct ObserverChannel;
		struct PeerChannel;
		struct Session;
		struct SessionMembership;
	}
}
namespace Modules
{
	struct Command;
}
namespace hades_file_local
{
	struct SynchronizationBinding;
	class SyncUpdateHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomPackets {}
	using namespace Patches::CustomPackets;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct SynchronizationBinding
	{
		unsigned __int32 ID; // 0x0
		Modules::Command *ServerVariable; // 0x4
		Modules::Command *ClientVariable; // 0x8
		std::bitset<17> SynchronizedPeers; // 0xC
		SynchronizationBinding() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
	};
	static_assert(sizeof(SynchronizationBinding) == 16, "Invalid SynchronizationBinding size");

	//@@anonymous-namespace@@
	// SyncUpdatePacketVar is defined in hades/recovered_types.h, which the synthesised
	// templates in hades/recovered_templates.h inherit from.

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	class SyncUpdateHandler :
		public Patches::CustomPackets::VariadicPacketHandler<SyncUpdatePacketData,SyncUpdatePacketVar>
	{
	public:
		SyncUpdateHandler(SyncUpdateHandler &); /* compiler_generated() */
		SyncUpdateHandler(SyncUpdateHandler const &); /* compiler_generated() */
		SyncUpdateHandler();
		virtual void Serialize(Blam::BitStream *, SyncUpdatePacketData const *, __int32, SyncUpdatePacketVar const *);
		virtual bool Deserialize(Blam::BitStream *, SyncUpdatePacketData *, __int32, SyncUpdatePacketVar *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *);
		virtual ~SyncUpdateHandler() = default; /* compiler_generated() */
		SyncUpdateHandler &operator=(SyncUpdateHandler &); /* compiler_generated() */
		SyncUpdateHandler &operator=(SyncUpdateHandler const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(SyncUpdateHandler) == 12, "Invalid SyncUpdateHandler size");

}
using namespace hades_file_local;
typedef unsigned __int32 SyncID;

namespace hades_file_local
{

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches { namespace CustomPackets { template<typename TData, typename TVarData> std::shared_ptr<VariadicPacketSender<TData, TVarData> > RegisterVariadicPacket(std::string const &name, std::shared_ptr<VariadicPacketHandler<TData, TVarData> > handler); } }  // hades: added for 0x10C3CB00

namespace Blam::Network { Session *GetActiveSession(); }  // hades: added for 0X10C3DE10

namespace Server
{
	namespace VariableSynchronization
	{
		extern void Initialize();
		extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable);
		extern void Tick();
	}
}

unsigned __int32 GenerateID(SynchronizationBinding const &binding);
void AddBinding(SynchronizationBinding const &binding);
bool CompareVariables(Modules::Command const *lhs, Modules::Command const *rhs);
void SetVariable(Modules::Command *var, Modules::Command const *value);
void SetVariable(Modules::Command *var, SyncUpdatePacketVar const *value);
void TickBinding(SynchronizationBinding *binding);
void TickBindings();
std::vector<SynchronizationBinding *> FindOutOfDateBindings(__int32 peerIndex);
void BuildVariableUpdate(SynchronizationBinding const *binding, SyncUpdatePacketVar *result);
std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > BuildUpdatePacket(std::vector<SynchronizationBinding *> const &bindings);
void SynchronizePeer(__int32 peerIndex);
bool IsPeerReady(Blam::Network::Session *session, __int32 peerIndex);
void SynchronizePeers(Blam::Network::Session *session);
void HostTick(Blam::Network::Session *session);

/* ---------- globals */

namespace Utils { namespace Cryptography { bool Hash32(std::string const &str, unsigned __int32 *out); } }  // hades: added for 0X10C3C5F0

/* ---------- private variables */

namespace hades_file_local
{
	std::unordered_map<unsigned int,SynchronizationBinding> syncBindings; // 0x1246862C  // hades: defined, so its atexit destructor emits ~unordered_map and ~_Hash here
	std::shared_ptr<Patches::CustomPackets::VariadicPacketSender<SyncUpdatePacketData,SyncUpdatePacketVar> > updateSender; // 0x12468654
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace VariableSynchronization
	{
		void Initialize() // 0x10C3CB00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C3CC28
			// static ...; // 0x10C3CC1C
			// static ...; // 0x10C3CC14
			// std::shared_ptr<SyncUpdateHandler> updateHandler;

			auto updateHandler = std::make_shared<SyncUpdateHandler>();
			updateSender = Patches::CustomPackets::RegisterVariadicPacket<SyncUpdatePacketData, SyncUpdatePacketVar>("eldewrito-sync-var", updateHandler);
		}

		void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable) // 0x10C3D8F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Synchronize@VariableSynchronization@Server@@YAXPAUCommand@Modules@@0@Z");
			// static ...; // 0x10C3D9B4
			// static ...; // 0x10C3D9AC
			// Modules::Command *serverVariable;
			// Modules::Command *clientVariable;
			// SynchronizationBinding binding;

			if (serverVariable->Type != clientVariable->Type)
			{
				throw std::runtime_error("Server and client variable types do not match");
			}

			SynchronizationBinding binding;
			binding.ServerVariable = serverVariable;
			binding.ClientVariable = clientVariable;
			binding.ID = GenerateID(binding);
			binding.SynchronizedPeers.reset();
			AddBinding(binding);
		}

		void Tick() // 0x10C3DE10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;

			auto session = Blam::Network::GetActiveSession();
			if (session)
			{
				if (session->IsHost())
					HostTick(session);
			}
		}
	}
}

/* ---------- private code */

_inline SyncUpdateHandler::SyncUpdateHandler() : VariadicPacketHandler(1) /* hades-mem-init:  */ // 0x10C3A1B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SyncUpdateHandler@hades_file_local@@QAE@XZ");
	// the original is empty
	// `anonymous-namespace'::SyncUpdateHandler::SyncUpdateHandler
	// SyncUpdateHandler *const this;
}

// mangled_x86(MANGLED_DEFAULT, "??0SynchronizationBinding@hades_file_local@@QAE@XZ"); no body to assert in
// _inline SynchronizationBinding::SynchronizationBinding() = default; // 0x10C3A210  // hades: defaulted on its declaration


unsigned __int32 GenerateID(SynchronizationBinding const &binding) // 0x10C3C5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateID@@YAIABUSynchronizationBinding@hades_file_local@@@Z");
	// `anonymous-namespace'::GenerateID
	// static ...; // 0x10C3C707
	// static ...; // 0x10C3C700
	// static ...; // 0x10C3C6E8
	// static ...; // 0x10C3C6E0
	// SynchronizationBinding const &binding;
	// std::string str;
	// unsigned __int32 result;

	std::string str = binding.ServerVariable->Name + binding.ClientVariable->Name;
	unsigned __int32 result;
	if (!Utils::Cryptography::Hash32(str, &result))
		throw std::runtime_error("Failed to generate sync ID");
	return result;
}

void AddBinding(SynchronizationBinding const &binding) // 0x10C3B810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddBinding@@YAXABUSynchronizationBinding@hades_file_local@@@Z");
	// `anonymous-namespace'::AddBinding
	// SynchronizationBinding const &binding;

	if (syncBindings.find(binding.ID) != syncBindings.end())
		throw std::runtime_error("Duplicate sync ID");
	syncBindings[binding.ID] = binding;
}

bool CompareVariables(Modules::Command const *lhs, Modules::Command const *rhs) // 0x10C3BEE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CompareVariables@@YA_NPBUCommand@Modules@@0@Z");
	// `anonymous-namespace'::CompareVariables
// $LN8:
// $LN7:
// $LN6:
// $LN5:
	// Modules::Command const *lhs;
	// Modules::Command const *rhs;

	if (lhs->Type != rhs->Type)
		throw std::runtime_error("Cannot compare variables of different types");
	switch (lhs->Type)
	{
	case eCommandTypeVariableInt:
		return lhs->ValueInt == rhs->ValueInt;
	case eCommandTypeVariableInt64:
		return lhs->ValueInt64 == rhs->ValueInt64;
	case eCommandTypeVariableFloat:
		return lhs->ValueFloat == rhs->ValueFloat;
	case eCommandTypeVariableString:
		return lhs->ValueString == rhs->ValueString;
	default:
		throw std::runtime_error("Unsupported variable type");
	}
}

void SetVariable(Modules::Command *var, Modules::Command const *value) // 0x10C3D1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable@@YAXPAUCommand@Modules@@PBU12@@Z");
	// `anonymous-namespace'::SetVariable
	// static ...; // 0x10C3D420
	// static ...; // 0x10C3D414
	// static ...; // 0x10C3D40C
// $LN8:
// $LN7:
// $LN6:
// $LN5:
	// Modules::Command *var;
	// Modules::Command const *value;
		// std::string returnInfo;
	// function call : bool (*)(std::vector<std::string> const &, std::string &)

	if (var->Type != value->Type)
		throw std::runtime_error("Cannot set a variable of one type to a variable of another type");
	var->ValueString = value->ValueString;
	switch (var->Type)
	{
	case Modules::eCommandTypeVariableInt:
		var->ValueInt = value->ValueInt;
		break;
	case Modules::eCommandTypeVariableInt64:
		var->ValueInt64 = value->ValueInt64;
		break;
	case Modules::eCommandTypeVariableFloat:
		var->ValueFloat = value->ValueFloat;
		break;
	case Modules::eCommandTypeVariableString:
		break;
	default:
		throw std::runtime_error("Unsupported variable type");
	}
	if (var->UpdateEvent)
	{
		std::string returnInfo;
		var->UpdateEvent({ var->ValueString }, returnInfo);
	}
	Modules::CommandMap::Instance().NotifyVariableUpdated(var);
}

void SetVariable(Modules::Command *var, SyncUpdatePacketVar const *value) // 0x10C3D4F0
{
	// `anonymous-namespace'::SetVariable
	// static ...; // 0x10C3D7FC
	// static ...; // 0x10C3D7F0
	// static ...; // 0x10C3D7E8
// $LN8:
// $LN7:
// $LN6:
// $LN5:
	// Modules::Command *var;
	// SyncUpdatePacketVar const *value;
		// std::string returnInfo;
	// function call : bool (*)(std::vector<std::string> const &, std::string &)

	if (var->Type != value->Type)
		return;
	switch (var->Type)
	{
	case Modules::eCommandTypeVariableInt:
		var->ValueInt = (unsigned long)value->Value.Int;
		var->ValueString = std::to_string(var->ValueInt);
		break;
	case Modules::eCommandTypeVariableInt64:
		var->ValueInt64 = value->Value.Int;
		var->ValueString = std::to_string(var->ValueInt64);
		break;
	case Modules::eCommandTypeVariableFloat:
		var->ValueFloat = value->Value.Float;
		var->ValueString = std::to_string(var->ValueFloat);
		break;
	case Modules::eCommandTypeVariableString:
		var->ValueString = value->Value.String;
		break;
	default:
		return;
	}
	if (var->UpdateEvent)
	{
		std::string returnInfo;
		var->UpdateEvent({ var->ValueString }, returnInfo);
	}
	Modules::CommandMap::Instance().NotifyVariableUpdated(var);
}

void TickBinding(SynchronizationBinding *binding) // 0x10C3DE80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TickBinding@@YAXPAUSynchronizationBinding@hades_file_local@@@Z");
	// `anonymous-namespace'::TickBinding
	// SynchronizationBinding *binding;

	if (CompareVariables(binding->ServerVariable, binding->ClientVariable))
		return;

	SetVariable(binding->ClientVariable, binding->ServerVariable);
	binding->SynchronizedPeers.reset();
}

void TickBindings() // 0x10C3DF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TickBindings@@YAXXZ");
	// `anonymous-namespace'::TickBindings
	// procedure flags: nofpo
	// static ...; // 0x10C3DFD1
	// static ...; // 0x10C3DFC8
	// static ...; // 0x10C3DFB0
	// static ...; // 0x10C3DFA8
		// std::unordered_map<unsigned int,SynchronizationBinding> &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;

	for (auto &binding : syncBindings)
		TickBinding(&binding.second);
}

std::vector<SynchronizationBinding *> FindOutOfDateBindings(__int32 peerIndex) // 0x10C3C370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindOutOfDateBindings@@YA?AV?$vector@PAUSynchronizationBinding@hades_file_local@@V?$allocator@PAUSynchronizationBinding@hades_file_local@@@std@@@std@@H@Z");
	// `anonymous-namespace'::FindOutOfDateBindings
	// static ...; // 0x10C3C540
	// static ...; // 0x10C3C535
	// static ...; // 0x10C3C52C
	// static ...; // 0x10C3C508
	// static ...; // 0x10C3C500
	// __int32 peerIndex;
	// std::vector<SynchronizationBinding *> result;
		// std::unordered_map<unsigned int,SynchronizationBinding> &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;

	std::vector<SynchronizationBinding *> result;
	for (auto &binding : syncBindings)
	{
		if (!binding.second.SynchronizedPeers[peerIndex])
			result.push_back(&binding.second);
	}
	return result;
}

void BuildVariableUpdate(SynchronizationBinding const *binding, SyncUpdatePacketVar *result) // 0x10C3BCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildVariableUpdate@@YAXPBUSynchronizationBinding@hades_file_local@@PAUSyncUpdatePacketVar@@@Z");
	// `anonymous-namespace'::BuildVariableUpdate
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// SynchronizationBinding const *binding;
	// SyncUpdatePacketVar *result;
	// Modules::Command *var;

	Modules::Command *var = binding->ServerVariable;
	result->ID = binding->ID;
	result->Type = var->Type;
	switch (var->Type)
	{
	case Modules::eCommandTypeVariableInt:
		result->Value.Int = var->ValueInt;
		break;
	case Modules::eCommandTypeVariableInt64:
		result->Value.Int = var->ValueInt64;
		break;
	case Modules::eCommandTypeVariableFloat:
		result->Value.Float = var->ValueFloat;
		break;
	case Modules::eCommandTypeVariableString:
		strncpy_s(result->Value.String, var->ValueString.c_str(), sizeof(result->Value.String) - 1);
		result->Value.String[sizeof(result->Value.String) - 1] = 0;
		break;
	default:
		throw std::runtime_error("Unsupported variable type");
	}
}

std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > BuildUpdatePacket(std::vector<SynchronizationBinding *> const &bindings) // 0x10C3BB00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildUpdatePacket@@YA?AV?$shared_ptr@V?$VariadicPacket@USyncUpdatePacketData@@USyncUpdatePacketVar@@@CustomPackets@Patches@@@std@@ABV?$vector@PAUSynchronizationBinding@hades_file_local@@V?$allocator@PAUSynchronizationBinding@hades_file_local@@@std@@@2@@Z");
	// `anonymous-namespace'::BuildUpdatePacket
	// static ...; // 0x10C3BC48
	// static ...; // 0x10C3BC3C
	// static ...; // 0x10C3BC34
	// std::vector<SynchronizationBinding *> const &bindings;
	// std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > result;
		// unsigned __int32 i;
			// SynchronizationBinding *binding;
			// SyncUpdatePacketVar *update;

	auto result = updateSender->New(bindings.size());
	for (size_t i = 0; i < bindings.size(); i++)
	{
		auto binding = bindings[i];
		auto update = &result->ExtraData[i];
		BuildVariableUpdate(binding, update);
	}
	return result;
}

void SynchronizePeer(__int32 peerIndex) // 0x10C3DA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SynchronizePeer@@YAXH@Z");
	// `anonymous-namespace'::SynchronizePeer
	// static ...; // 0x10C3DBA7
	// static ...; // 0x10C3DBA0
	// static ...; // 0x10C3DB88
	// static ...; // 0x10C3DB80
	// __int32 peerIndex;
	// std::vector<SynchronizationBinding *> outOfDateBindings;
	// std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > packet;
		// std::vector<SynchronizationBinding *> &<range>$L0;
		// SynchronizationBinding **<begin>$L0;
		// SynchronizationBinding **<end>$L0;
			// SynchronizationBinding *binding;

	auto outOfDateBindings = FindOutOfDateBindings(peerIndex);
	if (!outOfDateBindings.size())
		return;
	auto packet = BuildUpdatePacket(outOfDateBindings);
	updateSender->Send(peerIndex, packet);
	for (auto binding : outOfDateBindings)
		binding->SynchronizedPeers[peerIndex] = true;
}

bool IsPeerReady(Blam::Network::Session *session, __int32 peerIndex) // 0x10C3CC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsPeerReady@@YA_NPAUSession@Network@Blam@@H@Z");
	// `anonymous-namespace'::IsPeerReady
	// __int32 peerIndex;
	// Blam::Network::PeerChannel *channelInfo;
	// Blam::Network::SessionMembership *membership;

	auto *membership = &session->MembershipInfo;
	if (peerIndex == membership->LocalPeerIndex || !membership->Peers[peerIndex].IsEstablished())
	{
		return false;
	}
	auto &channel = membership->PeerChannels[peerIndex];
	return !channel.Unavailable && channel.ChannelIndex >= 0;
}

void SynchronizePeers(Blam::Network::Session *session) // 0x10C3DC30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SynchronizePeers@@YAXPAUSession@Network@Blam@@@Z");
	// `anonymous-namespace'::SynchronizePeers
	// static ...; // 0x10C3DDA0
	// static ...; // 0x10C3DD95
	// static ...; // 0x10C3DD8C
	// static ...; // 0x10C3DD68
	// static ...; // 0x10C3DD60
	// Blam::Network::Session *session;
	// Blam::Network::SessionMembership *membership;
	// std::bitset<17> visitedPeers;
		// __int32 peer;
		// std::unordered_map<unsigned int,SynchronizationBinding> &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;

	std::bitset<17> visitedPeers;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	for (__int32 peer = membership->FindFirstPeer(); peer != -1; peer = membership->FindNextPeer(peer))
	{
		if (peer != membership->LocalPeerIndex && IsPeerReady(session, peer))
		{
			SynchronizePeer(peer);
			visitedPeers[peer] = true;
		}
	}
	for (auto &binding : syncBindings)
		binding.second.SynchronizedPeers &= visitedPeers;
}

void HostTick(Blam::Network::Session *session) // 0x10C3CAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HostTick@@YAXPAUSession@Network@Blam@@@Z");
	// `anonymous-namespace'::HostTick
	// Blam::Network::Session *session;

	TickBindings();
	SynchronizePeers(session);
}

void SyncUpdateHandler::Serialize(Blam::BitStream *stream, SyncUpdatePacketData const *data, __int32 extraDataCount, SyncUpdatePacketVar const *extraData) // 0x10C3CF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@SyncUpdateHandler@hades_file_local@@UAEXPAVBitStream@Blam@@PBUSyncUpdatePacketData@@HPBUSyncUpdatePacketVar@@@Z");
	// `anonymous-namespace'::SyncUpdateHandler::Serialize
// $LN7:
	// SyncUpdateHandler *const this;
	// Blam::BitStream *stream;
	// SyncUpdatePacketData const *data;
	// __int32 extraDataCount;
	// SyncUpdatePacketVar const *extraData;
		// __int32 i;
			// SyncUpdatePacketVar const *var;

	for (__int32 i = 0; i < extraDataCount; i++)
	{
		SyncUpdatePacketVar const *var = &extraData[i];
		stream->WriteUnsigned<unsigned int>(var->ID, 32);
		stream->WriteUnsigned<unsigned int>(*(unsigned int const *)&var->Type, 0, 4);
		switch (*(unsigned int const *)&var->Type)
		{
		case 1:
			stream->WriteUnsigned<unsigned __int64>(*(unsigned __int64 const *)&var->Value, 32);
			break;
		case 2:
			stream->WriteUnsigned<unsigned __int64>(*(unsigned __int64 const *)&var->Value, 64);
			break;
		case 3:
			stream->WriteBlock(32, (unsigned char const *)&var->Value);
			break;
		case 4:
			stream->WriteString(var->Value.String);
			break;
		default:
			throw std::runtime_error("Unsupported variable type");
		}
	}
}

bool SyncUpdateHandler::Deserialize(Blam::BitStream *stream, SyncUpdatePacketData *data, __int32 extraDataCount, SyncUpdatePacketVar *extraData) // 0x10C3C100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@SyncUpdateHandler@hades_file_local@@UAE_NPAVBitStream@Blam@@PAUSyncUpdatePacketData@@HPAUSyncUpdatePacketVar@@@Z");
	// `anonymous-namespace'::SyncUpdateHandler::Deserialize
// $LN7:
	// SyncUpdateHandler *const this;
	// Blam::BitStream *stream;
	// SyncUpdatePacketData *data;
	// __int32 extraDataCount;
	// SyncUpdatePacketVar *extraData;
		// __int32 i;
			// SyncUpdatePacketVar *var;

	for (__int32 i = 0; i < extraDataCount; i++)
	{
		SyncUpdatePacketVar *var = &extraData[i];
		var->ID = stream->ReadUnsigned<unsigned int>(32);
		*(unsigned int *)&var->Type = stream->ReadUnsigned<unsigned int>(0, 4);
		switch (*(unsigned int *)&var->Type)
		{
		case 1:
			*(unsigned __int64 *)&var->Value = stream->ReadUnsigned<unsigned __int64>(32);
			break;
		case 2:
			*(unsigned __int64 *)&var->Value = stream->ReadUnsigned<unsigned __int64>(64);
			break;
		case 3:
			stream->ReadBlock(32, (unsigned char *)&var->Value);
			break;
		case 4:
			stream->ReadString(var->Value.String);
			break;
		default:
			return false;
		}
	}
	return true;
}

void SyncUpdateHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *packet) // 0x10C3C850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacket@SyncUpdateHandler@hades_file_local@@UAEXPAUObserverChannel@Network@Blam@@PBV?$VariadicPacket@USyncUpdatePacketData@@USyncUpdatePacketVar@@@CustomPackets@Patches@@@Z");
	// `anonymous-namespace'::SyncUpdateHandler::HandlePacket
	// static ...; // 0x10C3C9B4
	// SyncUpdateHandler *const this;
	// Blam::Network::ObserverChannel *sender;
	// Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *packet;
	// Blam::Network::Session *session;
		// __int32 i;
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > it;
			// SyncUpdatePacketVar const *value;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || session->IsHost())
		return;
	for (__int32 i = 0; i < packet->GetExtraDataCount(); i++)
	{
		SyncUpdatePacketVar const *value = &packet->ExtraData[i];
		auto it = syncBindings.find(value->ID);
		if (it == syncBindings.end())
			continue;
		SetVariable(it->second.ClientVariable, value);
	}
}

/* ---------- explicit instantiations */
template std::_Hash<std::_Umap_traits<unsigned int,SynchronizationBinding,std::_Uhash_compare<unsigned int,std::hash<unsigned int>,std::equal_to<unsigned int> >,std::allocator<std::pair<unsigned int const ,SynchronizationBinding> >,0> >::~_Hash();
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > >::_List_const_iterator(std::_List_node<std::pair<unsigned int const ,SynchronizationBinding>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > const *);
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > >::_List_iterator(std::_List_node<std::pair<unsigned int const ,SynchronizationBinding>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > const *);
template std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > >::_List_unchecked_iterator(std::_List_node<std::pair<unsigned int const ,SynchronizationBinding>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > const *);
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > >::~_List_const_iterator();
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > >::~_List_iterator();
template std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > >,std::_Iterator_base12>::~_List_unchecked_const_iterator();
template std::unordered_map<unsigned int,SynchronizationBinding>::~unordered_map();

/* ---------- explicit instantiations (hades: the original object carries these) */
template bool Blam::BitStream::ReadString<char,2049>(char (&)[2049]);
template void Blam::BitStream::WriteString<char,2049>(char const (&)[2049]);

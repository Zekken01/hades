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
		SynchronizationBinding(); /* compiler_generated() */
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
		virtual ~SyncUpdateHandler(); /* compiler_generated() */
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
std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > FindOutOfDateBindings(__int32 peerIndex);
void BuildVariableUpdate(SynchronizationBinding const *binding, SyncUpdatePacketVar *result);
std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > BuildUpdatePacket(std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > const &bindings);
void SynchronizePeer(__int32 peerIndex);
bool IsPeerReady(Blam::Network::Session *session, __int32 peerIndex);
void SynchronizePeers(Blam::Network::Session *session);
void HostTick(Blam::Network::Session *session);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Server
{
	namespace VariableSynchronization
	{
		_extern void _sub_10C3CB00();
		void Initialize() // 0x10C3CB00
		{
			mangled_x86(MANGLED_TODO, "?Initialize@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C3CC28
			// static ...; // 0x10C3CC1C
			// static ...; // 0x10C3CC14
			// std::shared_ptr<SyncUpdateHandler> updateHandler;
			todo("implement");
			_sub_10C3CB00();
		}

		_extern void _sub_10C3D8F0(Modules::Command *, Modules::Command *);
		void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable) // 0x10C3D8F0
		{
			mangled_x86(MANGLED_TODO, "?Synchronize@VariableSynchronization@Server@@YAXPAUCommand@Modules@@0@Z");
			// static ...; // 0x10C3D9B4
			// static ...; // 0x10C3D9AC
			// Modules::Command *serverVariable;
			// Modules::Command *clientVariable;
			// SynchronizationBinding binding;
			todo("implement");
			_sub_10C3D8F0(serverVariable, clientVariable);
		}

		_extern void _sub_10C3DE10();
		void Tick() // 0x10C3DE10
		{
			mangled_x86(MANGLED_TODO, "?Tick@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			todo("implement");
			_sub_10C3DE10();
		}
	}
}

/* ---------- private code */

extern SyncUpdateHandler* _sub_10C3A1B0(SyncUpdateHandler *const);
_inline SyncUpdateHandler::SyncUpdateHandler() // 0x10C3A1B0
{
	// `anonymous-namespace'::SyncUpdateHandler::SyncUpdateHandler
	// SyncUpdateHandler *const this;
	todo("implement");
	_sub_10C3A1B0(this);
}

_inline SynchronizationBinding::SynchronizationBinding() // 0x10C3A210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SynchronizationBinding@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SynchronizationBinding::SynchronizationBinding
	// SynchronizationBinding *const this;

	compiler_generated();
}

_inline SyncUpdateHandler::~SyncUpdateHandler() // 0x10C3AD10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SyncUpdateHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::SyncUpdateHandler::~SyncUpdateHandler
	// SyncUpdateHandler *const this;

	compiler_generated();
}

_extern unsigned __int32 _sub_10C3C5F0(SynchronizationBinding const &);
unsigned __int32 GenerateID(SynchronizationBinding const &binding) // 0x10C3C5F0
{
	// `anonymous-namespace'::GenerateID
	// static ...; // 0x10C3C707
	// static ...; // 0x10C3C700
	// static ...; // 0x10C3C6E8
	// static ...; // 0x10C3C6E0
	// SynchronizationBinding const &binding;
	// std::string str;
	// unsigned __int32 result;
	todo("implement");
	unsigned __int32 __result = _sub_10C3C5F0(binding);
	return __result;
}

_extern void _sub_10C3B810(SynchronizationBinding const &);
void AddBinding(SynchronizationBinding const &binding) // 0x10C3B810
{
	// `anonymous-namespace'::AddBinding
	// SynchronizationBinding const &binding;
	todo("implement");
	_sub_10C3B810(binding);
}

_extern bool _sub_10C3BEE0(Modules::Command const *, Modules::Command const *);
bool CompareVariables(Modules::Command const *lhs, Modules::Command const *rhs) // 0x10C3BEE0
{
	// `anonymous-namespace'::CompareVariables
// $LN8:
// $LN7:
// $LN6:
// $LN5:
	// Modules::Command const *lhs;
	// Modules::Command const *rhs;
	todo("implement");
	bool __result = _sub_10C3BEE0(lhs, rhs);
	return __result;
}

_extern void _sub_10C3D1A0(Modules::Command *, Modules::Command const *);
void SetVariable(Modules::Command *var, Modules::Command const *value) // 0x10C3D1A0
{
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
	{
		// std::string returnInfo;
	}
	// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
	todo("implement");
	_sub_10C3D1A0(var, value);
}

_extern void _sub_10C3D4F0(Modules::Command *, SyncUpdatePacketVar const *);
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
	{
		// std::string returnInfo;
	}
	// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
	todo("implement");
	_sub_10C3D4F0(var, value);
}

_extern void _sub_10C3DE80(SynchronizationBinding *);
void TickBinding(SynchronizationBinding *binding) // 0x10C3DE80
{
	// `anonymous-namespace'::TickBinding
	// SynchronizationBinding *binding;
	todo("implement");
	_sub_10C3DE80(binding);
}

_extern void _sub_10C3DF10();
void TickBindings() // 0x10C3DF10
{
	// `anonymous-namespace'::TickBindings
	// procedure flags: nofpo
	// static ...; // 0x10C3DFD1
	// static ...; // 0x10C3DFC8
	// static ...; // 0x10C3DFB0
	// static ...; // 0x10C3DFA8
	{
		// std::unordered_map<unsigned int,SynchronizationBinding,std::hash<unsigned int>,std::equal_to<unsigned int>,std::allocator<std::pair<unsigned int const ,SynchronizationBinding> > > &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
		{
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;
		}
	}
	todo("implement");
	_sub_10C3DF10();
}

extern std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > _sub_10C3C370(__int32);
std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > FindOutOfDateBindings(__int32 peerIndex) // 0x10C3C370
{
	// `anonymous-namespace'::FindOutOfDateBindings
	// static ...; // 0x10C3C540
	// static ...; // 0x10C3C535
	// static ...; // 0x10C3C52C
	// static ...; // 0x10C3C508
	// static ...; // 0x10C3C500
	// __int32 peerIndex;
	// std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > result;
	{
		// std::unordered_map<unsigned int,SynchronizationBinding,std::hash<unsigned int>,std::equal_to<unsigned int>,std::allocator<std::pair<unsigned int const ,SynchronizationBinding> > > &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
		{
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;
		}
	}
	todo("implement");
	std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > __result = _sub_10C3C370(peerIndex);
	return __result;
}

_extern void _sub_10C3BCB0(SynchronizationBinding const *, SyncUpdatePacketVar *);
void BuildVariableUpdate(SynchronizationBinding const *binding, SyncUpdatePacketVar *result) // 0x10C3BCB0
{
	// `anonymous-namespace'::BuildVariableUpdate
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// SynchronizationBinding const *binding;
	// SyncUpdatePacketVar *result;
	// Modules::Command *var;
	todo("implement");
	_sub_10C3BCB0(binding, result);
}

extern std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > _sub_10C3BB00(std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > const &);
std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > BuildUpdatePacket(std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > const &bindings) // 0x10C3BB00
{
	// `anonymous-namespace'::BuildUpdatePacket
	// static ...; // 0x10C3BC48
	// static ...; // 0x10C3BC3C
	// static ...; // 0x10C3BC34
	// std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > const &bindings;
	// std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > result;
	{
		// unsigned __int32 i;
		{
			// SynchronizationBinding *binding;
			// SyncUpdatePacketVar *update;
		}
	}
	todo("implement");
	std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > __result = _sub_10C3BB00(bindings);
	return __result;
}

_extern void _sub_10C3DA00(__int32);
void SynchronizePeer(__int32 peerIndex) // 0x10C3DA00
{
	// `anonymous-namespace'::SynchronizePeer
	// static ...; // 0x10C3DBA7
	// static ...; // 0x10C3DBA0
	// static ...; // 0x10C3DB88
	// static ...; // 0x10C3DB80
	// __int32 peerIndex;
	// std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > outOfDateBindings;
	// std::shared_ptr<Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> > packet;
	{
		// std::vector<SynchronizationBinding *,std::allocator<SynchronizationBinding *> > &<range>$L0;
		// SynchronizationBinding **<begin>$L0;
		// SynchronizationBinding **<end>$L0;
		{
			// SynchronizationBinding *binding;
		}
	}
	todo("implement");
	_sub_10C3DA00(peerIndex);
}

_extern bool _sub_10C3CC90(Blam::Network::Session *, __int32);
bool IsPeerReady(Blam::Network::Session *session, __int32 peerIndex) // 0x10C3CC90
{
	// `anonymous-namespace'::IsPeerReady
	// __int32 peerIndex;
	// Blam::Network::PeerChannel *channelInfo;
	// Blam::Network::SessionMembership *membership;
	todo("implement");
	bool __result = _sub_10C3CC90(session, peerIndex);
	return __result;
}

_extern void _sub_10C3DC30(Blam::Network::Session *);
void SynchronizePeers(Blam::Network::Session *session) // 0x10C3DC30
{
	// `anonymous-namespace'::SynchronizePeers
	// static ...; // 0x10C3DDA0
	// static ...; // 0x10C3DD95
	// static ...; // 0x10C3DD8C
	// static ...; // 0x10C3DD68
	// static ...; // 0x10C3DD60
	// Blam::Network::Session *session;
	// Blam::Network::SessionMembership *membership;
	// std::bitset<17> visitedPeers;
	{
		// __int32 peer;
	}
	{
		// std::unordered_map<unsigned int,SynchronizationBinding,std::hash<unsigned int>,std::equal_to<unsigned int>,std::allocator<std::pair<unsigned int const ,SynchronizationBinding> > > &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > <end>$L0;
		{
			// std::pair<unsigned int const ,SynchronizationBinding> &binding;
		}
	}
	todo("implement");
	_sub_10C3DC30(session);
}

_extern void _sub_10C3CAB0(Blam::Network::Session *);
void HostTick(Blam::Network::Session *session) // 0x10C3CAB0
{
	// `anonymous-namespace'::HostTick
	// Blam::Network::Session *session;
	todo("implement");
	_sub_10C3CAB0(session);
}

_extern void _sub_10C3CF10(SyncUpdateHandler *const, Blam::BitStream *, SyncUpdatePacketData const *, __int32, SyncUpdatePacketVar const *);
void SyncUpdateHandler::Serialize(Blam::BitStream *stream, SyncUpdatePacketData const *data, __int32 extraDataCount, SyncUpdatePacketVar const *extraData) // 0x10C3CF10
{
	// `anonymous-namespace'::SyncUpdateHandler::Serialize
// $LN7:
	// SyncUpdateHandler *const this;
	// Blam::BitStream *stream;
	// SyncUpdatePacketData const *data;
	// __int32 extraDataCount;
	// SyncUpdatePacketVar const *extraData;
	{
		// __int32 i;
		{
			// SyncUpdatePacketVar const *var;
		}
	}
	todo("implement");
	_sub_10C3CF10(this, stream, data, extraDataCount, extraData);
}

_extern bool _sub_10C3C100(SyncUpdateHandler *const, Blam::BitStream *, SyncUpdatePacketData *, __int32, SyncUpdatePacketVar *);
bool SyncUpdateHandler::Deserialize(Blam::BitStream *stream, SyncUpdatePacketData *data, __int32 extraDataCount, SyncUpdatePacketVar *extraData) // 0x10C3C100
{
	// `anonymous-namespace'::SyncUpdateHandler::Deserialize
// $LN7:
	// SyncUpdateHandler *const this;
	// Blam::BitStream *stream;
	// SyncUpdatePacketData *data;
	// __int32 extraDataCount;
	// SyncUpdatePacketVar *extraData;
	{
		// __int32 i;
		{
			// SyncUpdatePacketVar *var;
		}
	}
	todo("implement");
	bool __result = _sub_10C3C100(this, stream, data, extraDataCount, extraData);
	return __result;
}

_extern void _sub_10C3C850(SyncUpdateHandler *const, Blam::Network::ObserverChannel *, Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *);
void SyncUpdateHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *packet) // 0x10C3C850
{
	// `anonymous-namespace'::SyncUpdateHandler::HandlePacket
	// static ...; // 0x10C3C9B4
	// SyncUpdateHandler *const this;
	// Blam::Network::ObserverChannel *sender;
	// Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *packet;
	// Blam::Network::Session *session;
	{
		// __int32 i;
		{
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,SynchronizationBinding> > > > it;
			// SyncUpdatePacketVar const *value;
		}
	}
	todo("implement");
	_sub_10C3C850(this, sender, packet);
}

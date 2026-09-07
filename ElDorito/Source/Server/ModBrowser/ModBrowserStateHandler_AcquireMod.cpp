/* ---------- headers */

#include "Server/ModBrowser/ModBrowserStateHandler_AcquireMod.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Threading/SimpleMessageQueue.hpp"
#include "Console/Console.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserModDownloadUI.hpp"
#include "Server/ModBrowser/ModBrowserStateHandler.hpp"
#include "Server/ModBrowser/ModBrowserStateManager.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
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
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CModBrowserStateHandler;
class CModBrowserStateHandler_AcquireMod;
class IModBrowserModDownloadUI;
class SignatureVerificationJob;
class c_mod_package;
class c_mod_package_manager;
struct SModBrowserState;
struct SSignatureVerificationResult;
struct lambda_1;
struct lambda_2;
struct lambda_3;
struct lambda_4;
struct s_mod_origin_info;
struct s_mod_package_id;
namespace Download
{
	class CHttpFileDownload;
}

namespace Utils {}
using namespace ::Utils;
namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2>
//{
//public:
//	void operator()() const;
//	<lambda_2>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> &);
//	<lambda_2>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3>
//{
//public:
//	void operator()() const;
//	<lambda_3>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> &);
//	<lambda_3>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4>
//{
//public:
//	void operator()() const;
//	<lambda_4>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> &);
//	<lambda_4>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> size");

//class CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1>
//{
//public:
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *, SignatureVerificationJob *const &);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//	SignatureVerificationJob *job; // 0x4
//public:
//	CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1>) == 8, "Invalid CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern SignatureVerificationJob* _sub_107156E0(SignatureVerificationJob *const, __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
_inline SignatureVerificationJob::SignatureVerificationJob(__int32 queueIndex, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path) // 0x107156E0
{
	mangled_x86(MANGLED_TODO, "??0SignatureVerificationJob@@QAE@HABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
	todo("implement");
	_sub_107156E0(this, queueIndex, path);
}

extern SSignatureVerificationResult const &_sub_10717310(SignatureVerificationJob *const);
_inline SSignatureVerificationResult const &SignatureVerificationJob::GetResult() // 0x10717310
{
	mangled_x86(MANGLED_TODO, "?GetResult@SignatureVerificationJob@@QAEABUSSignatureVerificationResult@@XZ");
	// SignatureVerificationJob *const this;
	todo("implement");
	SSignatureVerificationResult const & __result = _sub_10717310(this);
	return __result;
}

_extern bool _sub_107196F0(SignatureVerificationJob *const);
_inline bool SignatureVerificationJob::Update() // 0x107196F0
{
	mangled_x86(MANGLED_TODO, "?Update@SignatureVerificationJob@@QAE_NXZ");
	// static ...; // 0x107198A4
	// static ...; // 0x107198A0
	// static ...; // 0x10719888
	// static ...; // 0x10719880
	// SignatureVerificationJob *const this;
	// c_mod_package::e_error err;
	// c_mod_package package;
	todo("implement");
	bool __result = _sub_107196F0(this);
	return __result;
}

_extern void _sub_10716F80(SignatureVerificationJob *const);
_inline void SignatureVerificationJob::Complete() // 0x10716F80
{
	mangled_x86(MANGLED_TODO, "?Complete@SignatureVerificationJob@@QAEXXZ");
	// SignatureVerificationJob *const this;
	todo("implement");
	_sub_10716F80(this);
}

extern CModBrowserStateHandler_AcquireMod* _sub_107154D0(CModBrowserStateHandler_AcquireMod *const);
CModBrowserStateHandler_AcquireMod::CModBrowserStateHandler_AcquireMod() // 0x107154D0
{
	mangled_x86(MANGLED_TODO, "??0CModBrowserStateHandler_AcquireMod@@QAE@XZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_107154D0(this);
}

extern SSignatureVerificationResult* _sub_10715680(SSignatureVerificationResult *const);
_inline SSignatureVerificationResult::SSignatureVerificationResult() // 0x10715680
{
	mangled_x86(MANGLED_TODO, "??0SSignatureVerificationResult@@QAE@XZ");
	// SSignatureVerificationResult *const this;
	compiler_generated();
	todo("implement");
	_sub_10715680(this);
}

_extern void _sub_10715C90(CModBrowserStateHandler_AcquireMod *const);
CModBrowserStateHandler_AcquireMod::~CModBrowserStateHandler_AcquireMod() // 0x10715C90
{
	mangled_x86(MANGLED_TODO, "??1CModBrowserStateHandler_AcquireMod@@QAE@XZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10715C90(this);
}

_extern void _sub_10715D80(SSignatureVerificationResult *const);
_inline SSignatureVerificationResult::~SSignatureVerificationResult() // 0x10715D80
{
	mangled_x86(MANGLED_TODO, "??1SSignatureVerificationResult@@QAE@XZ");
	// SSignatureVerificationResult *const this;
	compiler_generated();
	todo("implement");
	_sub_10715D80(this);
}

_extern void _sub_10715DD0(SignatureVerificationJob *const);
_inline SignatureVerificationJob::~SignatureVerificationJob() // 0x10715DD0
{
	mangled_x86(MANGLED_TODO, "??1SignatureVerificationJob@@QAE@XZ");
	// SignatureVerificationJob *const this;
	compiler_generated();
	todo("implement");
	_sub_10715DD0(this);
}

extern SSignatureVerificationResult &_sub_10715F50(SSignatureVerificationResult *const, SSignatureVerificationResult const &);
_inline SSignatureVerificationResult &SSignatureVerificationResult::operator=(SSignatureVerificationResult const &__that) // 0x10715F50
{
	mangled_x86(MANGLED_TODO, "??4SSignatureVerificationResult@@QAEAAU0@ABU0@@Z");
	// SSignatureVerificationResult const &__that;
	{
		// unsigned __int32 $S11;
	}
	compiler_generated();
	todo("implement");
	SSignatureVerificationResult & __result = _sub_10715F50(this, __that);
	return __result;
}

_extern void _sub_10718D40(CModBrowserStateHandler_AcquireMod *const, std::shared_ptr<IModBrowserModDownloadUI> const &);
void CModBrowserStateHandler_AcquireMod::SetUI(std::shared_ptr<IModBrowserModDownloadUI> const &ui) // 0x10718D40
{
	mangled_x86(MANGLED_TODO, "?SetUI@CModBrowserStateHandler_AcquireMod@@QAEXABV?$shared_ptr@VIModBrowserModDownloadUI@@@std@@@Z");
	// std::shared_ptr<IModBrowserModDownloadUI> const &ui;
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	todo("implement");
	_sub_10718D40(this, ui);
}

_extern void _sub_10718400(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnEnter() // 0x10718400
{
	mangled_x86(MANGLED_TODO, "?OnEnter@CModBrowserStateHandler_AcquireMod@@EAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// SModBrowserState &state;
	// SModBrowserState::SRequestedMod &mod;
	// function call : void (std::vector<SModBrowserState::SRequestedMod *,std::allocator<SModBrowserState::SRequestedMod *> > const &)
	todo("implement");
	_sub_10718400(this);
}

_extern void _sub_10718670(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnExit() // 0x10718670
{
	mangled_x86(MANGLED_TODO, "?OnExit@CModBrowserStateHandler_AcquireMod@@EAEXXZ");
	// static ...; // 0x107188F7
	// static ...; // 0x107188F4
	// static ...; // 0x107188DC
	// static ...; // 0x107188D4
	// CModBrowserStateHandler_AcquireMod *const this;
	{
	}
	{
		// unsigned __int32 i;
		{
			// std::filesystem::path tempPath;
			{
				// std::error_code ec;
			}
		}
	}
	// function call : void ()
	// function call : bool () const
	// function call : void ()
	todo("implement");
	_sub_10718670(this);
}

_extern void _sub_10718B80(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnUpdate() // 0x10718B80
{
	mangled_x86(MANGLED_TODO, "?OnUpdate@CModBrowserStateHandler_AcquireMod@@EAEXXZ");
	// static ...; // 0x10718C40
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10718B80(this);
}

_extern void _sub_10719A70(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::UpdateConfirmation() // 0x10719A70
{
	mangled_x86(MANGLED_TODO, "?UpdateConfirmation@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10719A70(this);
}

_extern void _sub_10719A90(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::UpdateDownloading() // 0x10719A90
{
	mangled_x86(MANGLED_TODO, "?UpdateDownloading@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	{
		// long long position;
		// long long length;
		// __int32 downloadSpeed;
		{
			// SModBrowserState::SRequestedMod *currentPackage;
		}
	}
	// function call : bool () const
	// function call : long long () const
	// function call : long long () const
	// function call : __int32 () const
	// function call : void (SModBrowserState::SRequestedMod const &, __int32, long long, long long, __int32)
	todo("implement");
	_sub_10719A90(this);
}

extern CModBrowserStateHandler* _sub_107154A0(CModBrowserStateHandler *const);
_inline CModBrowserStateHandler::CModBrowserStateHandler() // 0x107154A0
{
	mangled_x86(MANGLED_TODO, "??0CModBrowserStateHandler@@QAE@XZ");
	// CModBrowserStateHandler *const this;
	compiler_generated();
	todo("implement");
	_sub_107154A0(this);
}

_extern void _sub_10719920(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::UpdateCancelling() // 0x10719920
{
	mangled_x86(MANGLED_TODO, "?UpdateCancelling@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// c_mod_package_manager &packageManager;
	// function call : bool () const
	todo("implement");
	_sub_10719920(this);
}

_extern void _sub_10719D50(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::UpdateFinalizing() // 0x10719D50
{
	mangled_x86(MANGLED_TODO, "?UpdateFinalizing@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// c_mod_package_manager &packageManager;
	{
		// unsigned __int32 i;
	}
	{
		// SModBrowserState const &state;
	}
	// function call : void (SModBrowserState const &)
	todo("implement");
	_sub_10719D50(this);
}

_extern void _sub_10719F20(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::UpdateFinished() // 0x10719F20
{
	mangled_x86(MANGLED_TODO, "?UpdateFinished@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10719F20(this);
}

_extern void _sub_107171C0(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::EnterFinalizationState() // 0x107171C0
{
	mangled_x86(MANGLED_TODO, "?EnterFinalizationState@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// c_mod_package_manager &packageManager;
	// function call : void ()
	todo("implement");
	_sub_107171C0(this);
}

_extern void _sub_10717060(CModBrowserStateHandler_AcquireMod *const, Download::EDownloadError);
void CModBrowserStateHandler_AcquireMod::EnterFailedState(Download::EDownloadError error) // 0x10717060
{
	mangled_x86(MANGLED_TODO, "?EnterFailedState@CModBrowserStateHandler_AcquireMod@@AAEXW4EDownloadError@Download@@@Z");
	// Download::EDownloadError error;
	// function call : void (std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &)
	todo("implement");
	_sub_10717060(this, error);
}

_extern void _sub_10718D10(CModBrowserStateHandler_AcquireMod *const, CModBrowserStateHandler_AcquireMod::EState);
void CModBrowserStateHandler_AcquireMod::SetLocalState(CModBrowserStateHandler_AcquireMod::EState state) // 0x10718D10
{
	mangled_x86(MANGLED_TODO, "?SetLocalState@CModBrowserStateHandler_AcquireMod@@AAEXW4EState@1@@Z");
	// CModBrowserStateHandler_AcquireMod::EState state;
	todo("implement");
	_sub_10718D10(this, state);
}

_extern void _sub_107191A0(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::StartNextDownload() // 0x107191A0
{
	mangled_x86(MANGLED_TODO, "?StartNextDownload@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// static ...; // 0x10719565
	// static ...; // 0x1071955C
	// static ...; // 0x10719544
	// static ...; // 0x1071953C
	// CModBrowserStateHandler_AcquireMod *const this;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	// std::filesystem::path p;
	// SModBrowserState::SRequestedMod *next;
	{
		// SModBrowserState::SRequestedMod *currentPackage;
	}
	// function call : void ()
	// function call : void ()
	// function call : void (SModBrowserState::SRequestedMod const &, __int32, long long, long long, __int32)
	todo("implement");
	_sub_107191A0(this);
}

_extern void _sub_10717790(CModBrowserStateHandler_AcquireMod *const, SSignatureVerificationResult const &);
void CModBrowserStateHandler_AcquireMod::HandleSignatureVerificationResult(SSignatureVerificationResult const &result) // 0x10717790
{
	mangled_x86(MANGLED_TODO, "?HandleSignatureVerificationResult@CModBrowserStateHandler_AcquireMod@@AAEXABUSSignatureVerificationResult@@@Z");
	// static ...; // 0x10717E7D
	// static ...; // 0x10717E75
	// static ...; // 0x10717E73
	// static ...; // 0x10717E6F
	// static ...; // 0x10717E68
	// static ...; // 0x10717E20
	// static ...; // 0x10717E18
	// CModBrowserStateHandler_AcquireMod *const this;
	// SSignatureVerificationResult const &result;
	// std::error_code err;
	// SModBrowserState::SRequestedMod *package;
	// std::filesystem::path p;
	// SModBrowserState const &state;
	// std::filesystem::path newPath;
	// s_mod_package_id hash;
	// s_mod_origin_info origin;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier;
		// std::error_code err;
	}
	todo("implement");
	_sub_10717790(this, result);
}

_extern void _sub_10718130(CModBrowserStateHandler_AcquireMod *const, __int32);
void CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob(__int32 queueIndex) // 0x10718130
{
	mangled_x86(MANGLED_TODO, "?KickSignatureVerificationJob@CModBrowserStateHandler_AcquireMod@@AAEXH@Z");
	// static ...; // 0x10718304
	// static ...; // 0x107182FC
	// CModBrowserStateHandler_AcquireMod *const this;
	// __int32 queueIndex;
	// SignatureVerificationJob *job;
	todo("implement");
	_sub_10718130(this, queueIndex);
}

_extern void _sub_107173B0(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::HandleDownloadStopped() // 0x107173B0
{
	mangled_x86(MANGLED_TODO, "?HandleDownloadStopped@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// static ...; // 0x107176C0
	// static ...; // 0x107176BC
	// static ...; // 0x107176A4
	// static ...; // 0x1071769C
	// CModBrowserStateHandler_AcquireMod *const this;
	// Download::EDownloadStatus error;
	{
		// std::error_code err;
		// std::filesystem::path p;
	}
	// function call : Download::EDownloadStatus () const
	// function call : Download::EDownloadError () const
	// function call : Download::EDownloadError () const
	todo("implement");
	_sub_107173B0(this);
}

_extern bool _sub_10718F50(CModBrowserStateHandler_AcquireMod *const, SModBrowserState::SRequestedMod const &);
bool CModBrowserStateHandler_AcquireMod::ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package) // 0x10718F50
{
	mangled_x86(MANGLED_TODO, "?ShouldDownloadPackage@CModBrowserStateHandler_AcquireMod@@AAE_NABUSRequestedMod@SModBrowserState@@@Z");
	// static ...; // 0x1071910A
	// static ...; // 0x10719104
	// static ...; // 0x107190E0
	// static ...; // 0x107190D8
	// CModBrowserStateHandler_AcquireMod *const this;
	// SModBrowserState::SRequestedMod const &package;
	// c_mod_package_manager::s_entry package_entry;
	// unsigned char remote_hash[20];
	// c_mod_package cache;
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_10718F50(this, package);
	return __result;
}

_extern void _sub_10718A70(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnUIActionConfirm() // 0x10718A70
{
	mangled_x86(MANGLED_TODO, "?OnUIActionConfirm@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10718A70(this);
}

_extern void _sub_107189B0(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnUIActionCancel() // 0x107189B0
{
	mangled_x86(MANGLED_TODO, "?OnUIActionCancel@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// c_mod_package_manager &package_manager;
	// function call : void ()
	todo("implement");
	_sub_107189B0(this);
}

_extern void _sub_10718B10(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnUIActionRetry() // 0x10718B10
{
	mangled_x86(MANGLED_TODO, "?OnUIActionRetry@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	todo("implement");
	_sub_10718B10(this);
}

_extern void _sub_10718390(CModBrowserStateHandler_AcquireMod *const);
void CModBrowserStateHandler_AcquireMod::OnDownloadSingleFinished() // 0x10718390
{
	mangled_x86(MANGLED_TODO, "?OnDownloadSingleFinished@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;
	// CModBrowserStateHandler_AcquireMod::EState curState;
	todo("implement");
	_sub_10718390(this);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CSimpleMessageQueue<SSignatureVerificationResult,4>::CSimpleMessageQueue();
template CSimpleMessageQueue<SSignatureVerificationResult,4>::~CSimpleMessageQueue();
template SSignatureVerificationResult * CSimpleMessageQueue<SSignatureVerificationResult,4>::TryToAllocate();
template _SINGLE_LIST_ENTRY * CSimpleMessageQueue<SSignatureVerificationResult,4>::Reversed(_SINGLE_LIST_ENTRY *);
template void CSimpleMessageQueue<SSignatureVerificationResult,4>::FreeElement(CSimpleMessageQueue<SSignatureVerificationResult,4>::SQueueEntry *);
template void CSimpleMessageQueue<SSignatureVerificationResult,4>::Initialize();

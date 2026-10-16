/* ---------- headers */

#include "mods/mod_package_updater.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
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
#include "Common/Http/HttpRequest.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x108B1BF0

#include "Utils/Logger.hpp"  // hades: added for 0x108B1190

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
#include <conio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <format>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
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
#include <vector>

/* ---------- forward declarations */

class c_file_reference;
class c_mod_package;
class c_mod_package_manager;
class c_mod_package_updater_blocking;
struct lambda_1;
struct lambda_2;
struct s_file_reference;
struct s_mod_package_header;
namespace Download
{
	class CHttpFileDownload;
}
namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
	class IHttpResponse;
}

namespace Utils {}
using namespace ::Utils;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Download {}
using namespace ::Download;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

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

enum
{
	k_retry_interval_in_seconds = 5, // 0x0005
};

/* ---------- definitions */

//class download_mod_package_header::__l2::<lambda_1>
//{
//public:
//	void operator()(std::shared_ptr<Http::IHttpRequest>, bool) const;
//	<lambda_1>(download_mod_package_header::__l2::<lambda_1> &);
//	<lambda_1>(std::atomic<bool> &);
//private:
//	std::atomic<bool> &completion_flag; // 0x0
//public:
//	download_mod_package_header::__l2::<lambda_1> &operator=(download_mod_package_header::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(download_mod_package_header::__l2::<lambda_1>) == 4, "Invalid download_mod_package_header::__l2::<lambda_1> size");

//class download_mod_package_header::__l2::<lambda_2>
//{
//public:
//	bool operator()(char const *, unsigned __int32);
//	<lambda_2>(download_mod_package_header::__l2::<lambda_2> &);
//	<lambda_2>(char *&, char *&);
//private:
//	char *&end; // 0x0
//	char *&ptr; // 0x4
//public:
//	download_mod_package_header::__l2::<lambda_2> &operator=(download_mod_package_header::__l2::<lambda_2> const &);
//};
//static_assert(sizeof(download_mod_package_header::__l2::<lambda_2>) == 8, "Invalid download_mod_package_header::__l2::<lambda_2> size");

/* ---------- prototypes */

#include "Patches/Core.hpp"  // hades: added for 0x108B08C0
namespace Download { extern std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload(); }  // hades: added for 0x108B08C0
namespace hades_file_local { template<int N> static void print_progress(float complete_fraction, __int32 speed) { static int lastLen = 0; char buff[N + 3]; int filled = (int)(N * complete_fraction); buff[0] = '['; for (int i = 1; i < N; i++) { if (i < filled) buff[i] = '='; else buff[i] = ' '; } buff[N] = ']'; buff[N + 1] = 0; char const *unit = "KiB/s"; float rate = speed / 1024.0f; if (speed >= 1024 * 1024) { unit = "MiB/s"; rate /= 1024.0f; } if (lastLen > 0) { char cls[256]; memset(cls, ' ', lastLen); cls[lastLen] = 0; printf(cls); } float percent = complete_fraction * 100.0f; lastLen = printf("\r%s %.2f%% (%.2f %s)\r", buff, percent, rate, unit) + 1; } }  // hades: added for 0x108B08C0

namespace Utils { namespace FileUtils { extern long long GetFileSize64(char const *filename); } }  // hades: added for 0x108B0040

extern bool download_mod_package_header(char const *url, s_mod_package_header *out_header, bool use_range); extern bool mod_package_header_valid(s_mod_package_header const *header); extern s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool); extern bool (*const file_delete)(s_file_reference *); extern bool (*const file_rename)(s_file_reference *, char const *);  // hades: added for 0x108B23B0
namespace Http { extern std::shared_ptr<Http::IHttpRequest> CreateRequest(); }  // hades: added for 0x108B02E0

void shell_allocate_console();
void shell_free_console(bool dedicated);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@$$QAU01@@Z"); no body to assert in
_inline c_mod_package_updater_blocking::s_mod_package_description::s_mod_package_description(c_mod_package_updater_blocking::s_mod_package_description &&__that) = default; // 0x108ADB90

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@ABU01@@Z"); no body to assert in
_inline c_mod_package_updater_blocking::s_mod_package_description::s_mod_package_description(c_mod_package_updater_blocking::s_mod_package_description const &__that) = default; // 0x108ADCD0

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1s_mod_package_description@c_mod_package_updater_blocking@@QAE@XZ"); no body to assert in
_inline c_mod_package_updater_blocking::s_mod_package_description::~s_mod_package_description() = default; // 0x108ADFE0

void c_mod_package_updater_blocking::initialize(bool dedicated, char const *package_list_filename, char const *package_directory) // 0x108B1070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_mod_package_updater_blocking@@QAEX_NPBD1@Z");

	m_dedicated = dedicated;
	m_package_list_filename.set(package_list_filename);
	m_package_directory.set(package_directory);
}

bool c_mod_package_updater_blocking::locate_packages() // 0x108B1190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?locate_packages@c_mod_package_updater_blocking@@AAE_NXZ");

	printf("locating packages...\n");
	std::stringstream ss;
	std::ifstream ifs(m_package_list_filename);
	if (!ifs.is_open())
		return true;
	ss << ifs.rdbuf();
	std::string src = ss.str();
	rapidjson::Document doc;
	doc.Parse<0>(src.c_str());
	if ((doc.HasParseError() || !doc.HasMember("mods")) != false)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "server failed to parse mod package list");
		fprintf(stderr, "server failed to parse mod package list\n");
		return false;
	}
	rapidjson::Value const &mods = doc["mods"];
	for (auto it = mods.MemberBegin(); it != mods.MemberEnd(); ++it)
	{
		if (!it->value.IsObject() || !it->value.HasMember("package_url"))
			return false;
		rapidjson::Value const &mod = it->value;
		char const *package_url = mod["package_url"].GetString();
		s_mod_package_description description;
		description.package_url = std::string(package_url);
		description.local_name = std::string(it->name.GetString());
		m_download_queue.push(description);
	}
	printf("found %d packages\n", m_download_queue.size());
	return true;
}

bool c_mod_package_updater_blocking::download_package(char const *package_url, char const *filename) // 0x108B08C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?download_package@c_mod_package_updater_blocking@@AAE_NPBD0@Z");

	printf("downloading...\n");
	std::shared_ptr<Download::CHttpFileDownload> download = Download::CreateHttpFileDownload();
	download->SetUrl(package_url);
	download->SetDestinationFile(filename);
	download->Start();
	for (;;)
	{
		Utils::Singleton<Download::CHttpFileDownloadManager>::Instance().Tick();
		long long position = download->GetDownloadedBytes();
		long long length = download->GetTotalBytes();
		__int32 speed = download->GetDownloadSpeed();
		if (length > 0)
		{
			float complete_fraction = (double)position / (double)length;
			print_progress<24>(complete_fraction, speed);
		}
		if (download->IsComplete())
			break;
		Sleep(100);
	}
	printf("\n");
	if (download->GetStatus() != 3)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Download failed for reason: %s - %s", Download::DownloadErrorToString(download->GetError()), package_url);
		printf("Download failed for reason: %s\n", Download::DownloadErrorToString(download->GetError()));
		if (download->GetError() == 2)
		{
			printf("Press any key to continue or press ESC to exit...\n");
			__int32 x = getch();
			if (x == 27)
			{
				printf("Exiting...\n");
				Patches::Core::ExecuteShutdownCallbacks();
				shell_free_console(m_dedicated);
				exit(0);
			}
		}
		return false;
	}
	else
	{
		return true;
	}
}

#line 360
void c_mod_package_updater_blocking::build_mod_package_description(c_mod_package &package, c_mod_package_updater_blocking::s_mod_package_description *description) // 0x108B0040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_mod_package_description@c_mod_package_updater_blocking@@AAEXAAVc_mod_package@@PAUs_mod_package_description@1@@Z");
#line 368

	#line 362 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_package_updater.cpp"
		if (!(package.valid())) { display_assert("package.valid()", __FILE__, __LINE__, true); system_exit(-1); }
		#line 372 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_package_updater.cpp"
	s_static_string<32> metadata_name;
	metadata_name.set_wchar(package.get_metadata()->name);
	description->mod_name = metadata_name;
	description->mod_author = package.get_metadata()->author;
	description->mod_description = package.get_metadata()->description;
	description->package_size = Utils::FileUtils::GetFileSize64(package.get_file_name());
	Utils::String::BytesToHexString(package.get_header()->sha1, 20, description->hash);
}

bool download_mod_package_header(char const *url, s_mod_package_header *out_header, bool use_range) // 0x108B02E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?download_mod_package_header@@YA_NPBDPAUs_mod_package_header@@_N@Z");

	char *ptr = (char *)out_header;
	char *end = (char *)&out_header[1];
	std::atomic<bool> completion_flag;
	std::shared_ptr<Http::IHttpRequest> request = Http::CreateRequest();
	Http::CHttpHeaders headers;
	if (use_range)
		headers.Add("Range", std::format("bytes=0-{}", sizeof(s_mod_package_header)), Http::CHttpHeaders::Coalesce);
	request->SetHeaders(headers);
	request->SetUrl(url);
	request->Send();
	request->SetOnCompleted([&completion_flag](std::shared_ptr<Http::IHttpRequest> request, bool success)
	{
		completion_flag = true;
		completion_flag.notify_one();
	});
	request->SetReceiver([&end, &ptr](char const *data, unsigned int size)
	{
		size = std::min<unsigned int>(end - ptr, size);
		if (size == 0)
			return false;
		memcpy(ptr, data, size);
		ptr += size;
		return true;
	});
	completion_flag.wait(false);
	std::shared_ptr<Http::IHttpResponse> response = request->GetResponse();
	if (use_range && response && response->GetResponseCode() == 416)
		return download_mod_package_header(url, out_header, false);
	return ptr == end;
}

bool c_mod_package_updater_blocking::update_package(c_mod_package_updater_blocking::s_mod_package_description *description) // 0x108B23B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_package@c_mod_package_updater_blocking@@AAE_NPAUs_mod_package_description@1@@Z");

	char const *package_url = description->package_url.c_str();
	printf("checking remote package '%s'...\n", package_url);
	static s_mod_package_header remote_header;
	if (!download_mod_package_header(package_url, &remote_header, true))
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "failed to read remote package header: %s", description->package_url.c_str());
		fprintf(stderr, "failed to read remote package header.\n");
		return false;
	}
	if (!mod_package_header_valid(&remote_header))
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "invalid remote package header: %s", description->package_url.c_str());
		fprintf(stderr, "invalid remote package header!\n");
		return false;
	}
	bool needs_downloading = true;
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry package_entry;
	if (package_manager.find_package_by_hash(remote_header.sha1, &package_entry))
	{
		c_file_reference const &local_file = package_entry.file;
		if (local_file.exists())
		{
			c_mod_package local_package(local_file.filename);
			if (local_package.initialize(nullptr))
			{
				printf("checking local package hash for '%s'...\n", local_file.filename);
				if (!memcmp(local_package.get_header()->sha1, remote_header.sha1, sizeof(remote_header.sha1)))
				{
					printf("no update needed for mod '%s'.\n", description->local_name.c_str());
					build_mod_package_description(local_package, description);
					needs_downloading = false;
				}
			}
		}
	}
	if (needs_downloading)
	{
		printf("Update needed for mod '%s'.\n", description->local_name.c_str());
		std::string hash_str;
		Utils::String::BytesToHexString(remote_header.sha1, sizeof(remote_header.sha1), hash_str);
		s_static_string<256> temp_filename;
		temp_filename.print("%s\\%s.tmp", m_package_directory.get_string(), hash_str.c_str());
		s_file_reference temp_file_reference;
		file_reference_create_from_path(&temp_file_reference, temp_filename.get_string(), false);
		if (!download_package(package_url, temp_filename.get_string()))
		{
			file_delete(&temp_file_reference);
			return false;
		}
		c_mod_package package(temp_file_reference.filename);
		c_mod_package::e_error err;
		if (!package.initialize(&err))
		{
			file_delete(&temp_file_reference);
			fprintf(stderr, "failed to open local package! Error: %s\n", c_mod_package::get_error_string(err));
			return false;
		}
		std::wstring ws = package.get_metadata()->name;
		std::string mod_name(ws.begin(), ws.end());
		std::string mod_version = std::to_string(package.get_metadata()->version_major) + "." + std::to_string(package.get_metadata()->version_minor);
		s_static_string<256> new_name;
		new_name.print("%s.pak", c_mod_system::GetNewPackageFilename(mod_name, hash_str, mod_version).c_str());
		build_mod_package_description(package, description);
		package.dispose();
		file_rename(&temp_file_reference, new_name.get_string());
	}
	return true;
}

bool c_mod_package_updater_blocking::process_queue() // 0x108B1BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?process_queue@c_mod_package_updater_blocking@@AAE_NXZ");

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	package_manager.enumerate_blocking();
	while (!m_download_queue.empty())
	{
		s_mod_package_description &package_description = m_download_queue.front();
		if (!update_package(&package_description))
		{
			fprintf(stderr, "Retrying in %d seconds\n", 5);
			Sleep(5000);
			continue;
		}
		m_packages.push_back(package_description);
		m_download_queue.pop();
	}
	package_manager.enumerate_blocking();
	return true;
}

bool c_mod_package_updater_blocking::update_packages_blocking() // 0x108B2EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_packages_blocking@c_mod_package_updater_blocking@@QAE_NXZ");

	shell_allocate_console();
	printf("updating mods...\n");
	bool result = locate_packages();
	result &= process_queue();
	printf("starting game...\n");
	shell_free_console(m_dedicated);
	return result;
}

/* ---------- private code */

void shell_allocate_console() // 0x108B1F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shell_allocate_console@@YAXXZ");

	AllocConsole();
	HWND__ *consoleWindow = GetConsoleWindow();
	_iobuf *fpStdOut;
	freopen_s(&fpStdOut, "CONOUT$", "w", stdout);
	_iobuf *fpStdErr;
	freopen_s(&fpStdErr, "CONOUT$", "w", stderr);
	_iobuf *fpStdIn;
	freopen_s(&fpStdIn, "CONIN$", "r", stdin);
	long style = GetWindowLongA(consoleWindow, GWL_EXSTYLE);
	style |= WS_EX_TOPMOST;
	SetWindowLongA(consoleWindow, GWL_EXSTYLE, style);
	EnableMenuItem(GetSystemMenu(consoleWindow, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void shell_free_console(bool dedicated) // 0x108B2100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shell_free_console@@YAX_N@Z");

	HWND consoleWindow = GetConsoleWindow();
	EnableMenuItem(GetSystemMenu(consoleWindow, TRUE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	if (!dedicated)
	{
		FILE *fpStdOut;
		FILE *fpStdErr;
		FILE *fpStdIn;
		if (stdout)
			fclose(stdout);
		if (stdout)
			fclose(stdout);
		if (stdin)
			fclose(stdin);
		freopen_s(&fpStdOut, "NUL", "a", stdout);
		freopen_s(&fpStdErr, "NUL", "a", stderr);
		freopen_s(&fpStdIn, "NUL", "a", stdin);
		FreeConsole();
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template char const * s_static_string<32>::get_string() const;
template s_static_string<256>::operator char const *() const;
template s_static_string<32>::operator char const *() const;
template void s_static_string<32>::set_wchar(wchar_t const *);

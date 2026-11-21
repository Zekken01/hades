// Stand-ins for the game-side functions the UI host calls, so the real UI host
// (Web/WebRenderer.cpp, Web/Rml/*) can run outside eldorado.exe.

#include <filesystem>
#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "Player/PlayerEmblemRenderer.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Logger.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderer.hpp"

#include "harness.hpp"

#include <Windows.h>

#include <cstdarg>
#include <cstdio>
#include <map>

/* ---------- singleton storage (defined across game sources in the real build) */

template<> Modules::CommandMap *Utils::Singleton<Modules::CommandMap>::m_instance = nullptr;
template<> Utils::Logger *Utils::Singleton<Utils::Logger>::m_instance = nullptr;
template<> CModPackageFileSystemViewManager *Utils::Singleton<CModPackageFileSystemViewManager>::m_instance = nullptr;

/* ---------- logging */

namespace Harness
{
	int g_errors = 0;
	int g_warnings = 0;
	bool g_verbose = false;
	std::map<std::string, std::string> g_variables;
	std::map<std::string, std::string> g_methodResults;
	std::vector<std::string> g_calls;
}

Utils::Logger::Logger()
{
}

void Utils::Logger::Log(Utils::LogTypes, Utils::LogLevel level, std::string format, ...)
{
	char buffer[8192];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
	va_end(args);
	const char *tag = "info";
	if (level == Utils::LogLevel::Error)
	{
		tag = "ERROR";
		Harness::g_errors++;
	}
	else if (level == Utils::LogLevel::Warning)
	{
		tag = "warn";
		Harness::g_warnings++;
	}
	if (level >= Utils::LogLevel::Warning || Harness::g_verbose)
		printf("[%s] %s\n", tag, buffer);
}

namespace Console
{
	void WriteLine(std::string const &)
	{
		// the Logger stub already printed it
	}
}

/* ---------- game state */

bool Modules::CommandMap::GetVariableString(std::string const &name, std::string &value)
{
	auto it = Harness::g_variables.find(name);
	if (it == Harness::g_variables.end())
		return false;
	value = it->second;
	return true;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			// the game's WebScreens add their bridge methods here; the harness answers every
			// bridge call from the test script instead
			void CreateScreens()
			{
			}

			void Show(bool show)
			{
				Web::Browser::WebRenderer::GetInstance()->ShowRenderer(show, true);
				if (Harness::g_verbose)
					printf("[layer] overlay %s\n", show ? "shown" : "hidden");
			}

			void CaptureInput(bool capture, bool pointerCapture)
			{
				if (Harness::g_verbose)
					printf("[layer] capture input=%d pointer=%d\n", capture, pointerCapture);
			}

			void NotifyScreenStateChanged(std::string const &screenId, Web::Ui::ScreenLayer::EScreenState state)
			{
				if (Harness::g_verbose)
					printf("[layer] %s -> %d\n", screenId.c_str(), (int)state);
			}
		}
	}
}

std::shared_ptr<CModPackageFileSystemView> CModPackageFileSystemViewManager::GetView(std::string const &)
{
	return nullptr;
}

bool CModPackageFileSystemView::GetFileEntry(std::string const &, SFileEntry *)
{
	return false;
}

namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CreateRequest()
	{
		return nullptr;
	}
}

namespace Player
{
	namespace Emblems
	{
		bool ParseURL(std::string const &, s_player_emblem_configuration &)
		{
			return false;
		}

		bool PlayerEmblemRenderer::StartRender(s_player_emblem_configuration const &, std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks>)
		{
			return false;
		}
	}
}

namespace Utils
{
	namespace String
	{
		std::wstring WidenString(std::string_view string)
		{
			if (string.empty())
				return {};
			int length = MultiByteToWideChar(CP_UTF8, 0, string.data(), (int)string.size(), nullptr, 0);
			std::wstring out(length, L'\0');
			MultiByteToWideChar(CP_UTF8, 0, string.data(), (int)string.size(), out.data(), length);
			return out;
		}

		std::string ThinString(std::wstring_view wide)
		{
			if (wide.empty())
				return {};
			int length = WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
			std::string out(length, '\0');
			WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), out.data(), length, nullptr, nullptr);
			return out;
		}
	}
}

/* ---------- special members defined in game sources the harness does not build */

namespace Http
{
	CHttpHeaders::CHttpHeaders(Http::CHttpHeaders const &__that) = default;
	CHttpHeaders::~CHttpHeaders() = default;
}

namespace Utils
{
	namespace String
	{
		std::string &TrimInline(std::string &string)
		{
			const char *ws = " \t\r\n";
			string.erase(0, string.find_first_not_of(ws));
			string.erase(string.find_last_not_of(ws) + 1);
			return string;
		}
	}
}

/* ---------- the bridge: canned answers instead of Bridge/Client/ClientFunctions.cpp */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			void RegisterClientFunctions(WebRendererQueryHandler &handler)
			{
				const char *names[] = {
					"show", "hide", "screenState", "command", "setVariables", "ping", "captureInput", "version",
					"mapVariantInfo", "gameVariantInfo", "commands", "sendChat", "chatBoxOpened", "sessionInfo",
					"scoreboard", "scoreboardHide", "stats", "voipSpeaking", "voipConnected", "playerSpeaking",
					"playerVoipLevelChanged", "voipUserJoined", "isMapLoading", "forgeaction", "forgePalette",
					"showlan", "submitDialogResult", "getAssetUrl", "showScoreboard", "modDownloadAction",
					"modDownloadActionSingle", "modDownloadOption",
				};
				for (const char *name : names)
				{
					std::string method = name;
					handler.AddMethod(method, [method](rapidjson::Value const &args, std::string *result) -> QueryError {
						rapidjson::StringBuffer buffer;
						rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
						args.Accept(writer);
						Harness::g_calls.push_back(method + " " + buffer.GetString());
						if (Harness::g_verbose)
							printf("[bridge] %s %s\n", method.c_str(), buffer.GetString());

						if (method == "command" && args.HasMember("command") && args["command"].IsString())
						{
							std::string command = args["command"].GetString();
							auto it = Harness::g_methodResults.find("command:" + command);
							if (it != Harness::g_methodResults.end())
							{
								*result = it->second;
								return QueryError_Ok;
							}
							// "Var" alone reads a variable
							auto var = Harness::g_variables.find(command);
							*result = var != Harness::g_variables.end() ? var->second : "";
							return QueryError_Ok;
						}
						if (method == "getAssetUrl" && args.HasMember("path") && args["path"].IsString())
						{
							// like WebAssetService: the first existing <path>.<fileType> under ui/ (or "")
							const std::string path = args["path"].GetString();
							result->clear();
							if (args.HasMember("fileTypes") && args["fileTypes"].IsArray())
							{
								for (auto &type : args["fileTypes"].GetArray())
									if (type.IsString() && std::filesystem::exists("ui/" + path + "." + type.GetString()))
									{
										*result = "dew://" + path + "." + type.GetString();
										break;
									}
							}
							else
								*result = "dew://" + path;
							return QueryError_Ok;
						}
						auto it = Harness::g_methodResults.find(method);
						if (it != Harness::g_methodResults.end())
						{
							*result = it->second;
							return QueryError_Ok;
						}
						*result = method == "version" ? "0.7.2-harness" : "{}";
						return QueryError_Ok;
					});
				}
			}
		}
	}
}

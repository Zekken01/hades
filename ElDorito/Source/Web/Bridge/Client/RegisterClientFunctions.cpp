/* ---------- headers */

#include "hades/hades.h"

#include "ThirdParty/rapidjson/document.h"
#include "Web/Ui/Screen.hpp"
#include "Web/WebRenderer.hpp"
#include "Voip/VoipClient.hpp"

/* ---------- prototypes */

// Defined in Web/Bridge/Client/ClientFunctions.cpp.
namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				QueryError OnShow(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnHide(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnScreenState(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnCommand(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnSetVariables(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnPing(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnCaptureInput(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVersion(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnMapVariantInfo(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnGameVariantInfo(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnCommands(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnSendChat(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnChatBoxOpened(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnSessionInfo(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnScoreboard(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnScoreboardHide(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnStats(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPSpeakingChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPConnectedChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPPlayerSpeakingChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPPlayerVoipLevelChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPPlayerVoipJoined(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnIsMapLoading(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnForgeAction(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnForgePalette(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnShowLan(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnSubmitDialogResult(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnGetAssetUrl(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnShowScoreboard(rapidjson::Value const &p_Args, std::string *p_Result);
			}
		}
	}
}

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			// The methods the UI's `dew.callMethod` can reach.  Formerly registered on the CEF
			// message router in WebRendererHandler::OnAfterCreated; per-screen methods are added
			// by the WebScreen::OnCreate overrides in ScreenLayer::CreateScreens.
			void RegisterClientFunctions(WebRendererQueryHandler &handler)
			{
				handler.AddMethod("show", ClientFunctions::OnShow);
				handler.AddMethod("hide", ClientFunctions::OnHide);
				handler.AddMethod("screenState", ClientFunctions::OnScreenState);
				handler.AddMethod("command", ClientFunctions::OnCommand);
				handler.AddMethod("setVariables", ClientFunctions::OnSetVariables);
				handler.AddMethod("ping", ClientFunctions::OnPing);
				handler.AddMethod("captureInput", ClientFunctions::OnCaptureInput);
				handler.AddMethod("version", ClientFunctions::OnVersion);
				handler.AddMethod("mapVariantInfo", ClientFunctions::OnMapVariantInfo);
				handler.AddMethod("gameVariantInfo", ClientFunctions::OnGameVariantInfo);
				handler.AddMethod("commands", ClientFunctions::OnCommands);
				handler.AddMethod("sendChat", ClientFunctions::OnSendChat);
				handler.AddMethod("chatBoxOpened", ClientFunctions::OnChatBoxOpened);
				handler.AddMethod("sessionInfo", ClientFunctions::OnSessionInfo);
				handler.AddMethod("scoreboard", ClientFunctions::OnScoreboard);
				handler.AddMethod("scoreboardHide", ClientFunctions::OnScoreboardHide);
				handler.AddMethod("stats", ClientFunctions::OnStats);
				handler.AddMethod("voipSpeaking", ClientFunctions::OnVoIPSpeakingChanged);
				handler.AddMethod("voipConnected", ClientFunctions::OnVoIPConnectedChanged);
				handler.AddMethod("playerSpeaking", ClientFunctions::OnVoIPPlayerSpeakingChanged);
				handler.AddMethod("playerVoipLevelChanged", ClientFunctions::OnVoIPPlayerVoipLevelChanged);
				handler.AddMethod("voipUserJoined", ClientFunctions::OnVoIPPlayerVoipJoined);
				handler.AddMethod("isMapLoading", ClientFunctions::OnIsMapLoading);
				handler.AddMethod("forgeaction", ClientFunctions::OnForgeAction);
				handler.AddMethod("forgePalette", ClientFunctions::OnForgePalette);
				handler.AddMethod("showlan", ClientFunctions::OnShowLan);
				handler.AddMethod("submitDialogResult", ClientFunctions::OnSubmitDialogResult);
				handler.AddMethod("getAssetUrl", ClientFunctions::OnGetAssetUrl);
				handler.AddMethod("showScoreboard", ClientFunctions::OnShowScoreboard);

				// native VoIP (Source/Voip): the voip screen forwards the scoreboard volume slider
				// and the settings screen's "voip-reload"
				handler.AddMethod("voipSetPeerVolume", [](rapidjson::Value const &args, std::string *result) -> QueryError {
					if (!args.IsObject() || !args.HasMember("uid") || !args["uid"].IsString() || !args.HasMember("volume") || !args["volume"].IsNumber())
					{
						*result = "Bad query : \"uid\" (string) and \"volume\" (number) are required";
						return QueryError_BadQuery;
					}
					Voip::SetPeerVolume(args["uid"].GetString(), (float)args["volume"].GetDouble());
					return QueryError_Ok;
				});
				handler.AddMethod("voipReload", [](rapidjson::Value const &, std::string *) -> QueryError {
					Voip::Reload();
					return QueryError_Ok;
				});
			}
		}
	}
}

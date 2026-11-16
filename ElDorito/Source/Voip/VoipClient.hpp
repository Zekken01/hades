#pragma once

// Native VoIP: the C++ replacement for screens/voip/rtc.js.  Joins the game server's
// signaling server (Server/Signaling.cpp, subprotocol "dew-voip"), keeps one WebRTC peer
// connection per player (Opus audio track + negotiated "voip" data channel, perfect
// negotiation like rtc.js so 0.7 browser clients interoperate), and feeds the UI the same
// events the web version did (voip-user-volume, voip-self-volume, voip-user-leave) plus
// voip-peer-speaking / voip-stats for the voip overlay screen.
//
// Every function here is called on the game thread.

#include <string>

namespace Voip
{
	// Server/Signaling.cpp "signal-ready": {"server":"ip:port","password":"..."}
	void OnSignalReady(const std::string &json);

	// VoIP.Update: re-read the VoIP.* variables (connects or disconnects for VoIP.Enabled).
	void ApplySettings();

	// Push-to-talk state from ModuleVoIP::Tick.
	void SetTalking(bool talking);

	// VoIP.ListenToMicrophone: play the microphone back locally.
	void SetListenToMicrophone(bool listen);

	// Scoreboard volume slider: uid is "name|uid", volume 0..1 (0 mutes).
	void SetPeerVolume(const std::string &uid, float volume);

	// Settings changed the microphone or its processing: restart audio and reconnect.
	void Reload();

	// Runs queued work that must happen on the game thread (UI events, bridge methods).
	void Tick();

	void Shutdown();
}

#ifndef __PLAYER_PLAYEREMBLEMDOWNLOAD_HPP__
#define __PLAYER_PLAYEREMBLEMDOWNLOAD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Http
{
	class IHttpRequest;
}
namespace Player
{
	class PlayerEmblemDownload;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	class PlayerEmblemDownload :
		public Utils::Singleton<Player::PlayerEmblemDownload>
	{
	public:
		PlayerEmblemDownload();
		void LoadGenericEmblem(IDirect3DDevice9 *device);
		void Tick();
		void OnEndScene(IDirect3DDevice9 *device);
		void UpdateLocalEmblem();
		void SetLastJoinTime(long time);
		IDirect3DTexture9 *GetPlayerEmblem(long player_index, bool use_generic);
		_inline bool IsAvailable();
		void OnDownloadResponse(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request);
		void OnDownloadComplete(__int32 player_index, std::shared_ptr<Http::IHttpRequest> request, bool success);
		bool OnRecieve(__int32 player_index, char const *buffer, unsigned __int32 length);
	private:
		long server_join_tick; // 0x0
		bool failedInit; // 0x4
		bool emblemUpdate; // 0x5
	};
	static_assert(sizeof(Player::PlayerEmblemDownload) == 8, "Invalid Player::PlayerEmblemDownload size");
}

/* ---------- prototypes */

namespace Player
{
	extern void StartImageDownload(std::string url, __int32 player_index);
	extern void ResetCosmeticSlot(__int32 player_index);
	extern void InvalidateCosmeticSlot(__int32 player_index);
	extern void DXInitEmblem(__int32 player_index);
	extern void DXGenerateEmblem(__int32 player_index);
	extern void CheckDirty(__int32 player_index);
	extern void InitPlayer(__int32 player_index, bool is_customization_biped);
	extern void RetrySlot(__int32 player_index);
}

/* ---------- globals */

/* ---------- public code */

namespace Player
{
	inline bool PlayerEmblemDownload::IsAvailable() // 0x107F0C00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsAvailable@PlayerEmblemDownload@Player@@QAE_NXZ");
		// Player::PlayerEmblemDownload *const this;

		return !failedInit;
	}
}

/* ---------- private code */

#endif // __PLAYER_PLAYEREMBLEMDOWNLOAD_HPP__

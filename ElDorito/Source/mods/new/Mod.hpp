#ifndef __MODS_NEW_MOD_HPP__
#define __MODS_NEW_MOD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "Common/Threading/WaitEvent.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Prefab.hpp"
#include "mods/cache_file_interface.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <atomic>
#include <memory>
#include <string>
#include <thread>

/* ---------- forward declarations */

class IMod;
class Mod;
class WaitEvent;
class c_mod_package;
struct c_cache_file_interface;

/* ---------- constants */

/* ---------- definitions */

class Mod :
	public IMod
{
public:
	public:
	class IClient
	{
	public:
		virtual _inline ~IClient() = default; // 0x107913E0
		virtual void OnModLoadStateChanged(Mod *) = 0;
		IClient(IClient const &); /* compiler_generated() */
		_inline IClient() = default; /* compiler_generated() */
		IClient &operator=(IClient const &); /* compiler_generated() */
	};
	static_assert(sizeof(IClient) == 4, "Invalid IClient size");
	public:
	Mod(IClient *client, EModIndex index, char const *filename);
	virtual ~Mod();
	virtual void AddRef();
	virtual void Release();
	EModIndex GetIndex() const;
	__int32 GetCacheIndex() const;
	virtual bool GetPakIsLoading() const;
	virtual bool GetCacheIsLoading() const;
	virtual EModResult GetError() const;
	virtual char const *GetFilename() const;
	virtual c_mod_package *GetPak(bool wait) const;
	virtual std::shared_ptr<c_cache_file_interface> GetCache(bool wait) const;
	EModResult Load(bool async);
	EModResult LoadCache(__int32 cacheIndex, bool async);
	void Finish();
private:
	EModResult LoadPakBlocking();
	EModResult LoadCacheBlocking(__int32 cacheIndex);
	EModResult FinishLoadPak(EModResult error);
	EModResult FinishLoadCache(EModResult error); template<typename t_function> EModResult BeginLoadAsync(t_function &&function) { if (m_loadThread.joinable()) m_loadThread.detach(); m_loadThread = std::thread(function); return kPending; }  // hades: added for Load/LoadCache
	std::atomic<int> m_refCount; // 0x4
	EModResult m_error; // 0x8
	WaitEvent m_pakLoadEvent; // 0xC
	WaitEvent m_cacheLoadEvent; // 0x10
	std::unique_ptr<c_mod_package> m_pak; // 0x14
	std::shared_ptr<c_cache_file_interface> m_cache; // 0x18
	EModIndex m_index; // 0x20
	IClient *m_client; // 0x24
	__int32 m_cacheIndex; // 0x28
	std::string m_filename; // 0x2C
	std::thread m_loadThread; // 0x48
};
// static_assert(sizeof(Mod) == 80, "Invalid Mod size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_NEW_MOD_HPP__

#ifndef __ELDORITO_HPP__
#define __ELDORITO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

class ElDorito;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class ElDorito :
	public Utils::Singleton<ElDorito>
{
public:
	bool GameHasMenuShown; // 0x0
private:
	bool executeCommandQueue; // 0x1
	bool isDedicated; // 0x2
	bool isBotClient; // 0x3
	bool isHighPriority; // 0x4
	std::string mapsFolder; // 0x8
	bool webDebugging; // 0x24
	bool webDebugLogging; // 0x25
	__int32 webdebugPort; // 0x28
	bool connectToServer; // 0x2C
	std::string serverAddress; // 0x30
	std::string serverPassword; // 0x4C
	std::string instanceName; // 0x68
public:
	static _inline void SetMainThreadID(unsigned __int32 ThreadID);
	static _inline unsigned __int32 GetMainThreadID();
	ElDorito();
	~ElDorito();
	std::string GetDirectory();
	void Initialize();
	void Shutdown();
	void Tick();
	void OnMainMenuShown();
	_inline std::string GetMapsFolder() const;
	_inline bool IsWebDebuggingEnabled() const;
	_inline __int32 GetWebDebugPort() const;
	_inline bool IsWebDebugLoggingEnabled() const;
	_inline bool IsDedicated() const;
	_inline bool IsBotClient() const;
	_inline bool IsHeadless() const;
	_inline bool IsHighPriority() const;
	_inline bool IsConnectingToServer() const;
	_inline std::string GetInstanceName() const;
private:
	static unsigned __int32 MainThreadID;
	static bool (*Video_InitD3D)(bool, bool);
	void setWatermarkText(std::string const &Message);
	void SetMapsFolder(std::string const &path);
};
#pragma pack(pop)
static_assert(sizeof(ElDorito) == 132, "Invalid ElDorito size");

/* ---------- prototypes */

extern bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights);
extern bool EnsureChildProcessTermination();
extern std::string GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord);
extern long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo);
extern __int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow);
extern __int32 InitInstance(HINSTANCE__ *hModule);
extern __int32 ExitInstance();
extern __int32 GetEDVersion();
extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc) noexcept(false);  // hades: the original has an EH frame, which /EHsc drops for a nothrow extern "C" function

/* ---------- globals */

/* ---------- public code */

inline void ElDorito::SetMainThreadID(unsigned __int32 ThreadID) // 0x10966B20
{
	MainThreadID = ThreadID;
}

inline unsigned __int32 ElDorito::GetMainThreadID() // 0x10923830
{
	return MainThreadID;
}

inline std::string ElDorito::GetMapsFolder() const // 0x1074E5C0
{
	return mapsFolder;
}

inline bool ElDorito::IsWebDebuggingEnabled() const // 0x10961AD0
{
	return webDebugging;
}

inline __int32 ElDorito::GetWebDebugPort() const // 0x10C93860
{
	return webdebugPort;
}

inline bool ElDorito::IsWebDebugLoggingEnabled() const // 0x10CC0EA0
{
	return webDebugLogging;
}

inline bool ElDorito::IsDedicated() const // 0x1068FE20
{
	return isDedicated;
}

inline bool ElDorito::IsBotClient() const // 0x109685D0
{
	return isBotClient;
}

inline bool ElDorito::IsHeadless() const // 0x10923850
{
	return isDedicated || isBotClient;
}

inline bool ElDorito::IsHighPriority() const // 0x10A48D10
{
	return isHighPriority;
}

inline bool ElDorito::IsConnectingToServer() const // 0x10CAABD0
{
	return connectToServer;
}

inline std::string ElDorito::GetInstanceName() const // 0x106B4470
{
	return instanceName;
}

/* ---------- private code */

#endif // __ELDORITO_HPP__

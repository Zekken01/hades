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
	unsigned char __pad0[3]; // 0x5
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapsFolder; // 0x8
	bool webDebugging; // 0x24
	bool webDebugLogging; // 0x25
	unsigned char __pad1[2]; // 0x26
	__int32 webdebugPort; // 0x28
	bool connectToServer; // 0x2C
	unsigned char __pad2[3]; // 0x2D
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > serverAddress; // 0x30
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > serverPassword; // 0x4C
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > instanceName; // 0x68
public:
	static _inline void SetMainThreadID(unsigned __int32 ThreadID);
	static _inline unsigned __int32 GetMainThreadID();
	ElDorito();
	~ElDorito();
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetDirectory();
	void Initialize();
	void Shutdown();
	void Tick();
	void OnMainMenuShown();
	_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetMapsFolder() const;
	_inline bool IsWebDebuggingEnabled() const;
	_inline __int32 GetWebDebugPort() const;
	_inline bool IsWebDebugLoggingEnabled() const;
	_inline bool IsDedicated() const;
	_inline bool IsBotClient() const;
	_inline bool IsHeadless() const;
	_inline bool IsHighPriority() const;
	_inline bool IsConnectingToServer() const;
	_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetInstanceName() const;
private:
	static unsigned __int32 MainThreadID;
	static bool (*Video_InitD3D)(bool, bool);
	void setWatermarkText(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &Message);
	void SetMapsFolder(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
};
#pragma pack(pop)
static_assert(sizeof(ElDorito) == 132, "Invalid ElDorito size");

/* ---------- prototypes */

extern bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights);
extern bool EnsureChildProcessTermination();
extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord);
extern long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo);
extern __int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow);
extern __int32 InitInstance(HINSTANCE__ *hModule);
extern __int32 ExitInstance();
extern __int32 GetEDVersion();
extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc);

/* ---------- globals */

/* ---------- public code */

_extern void _sub_10966B20(unsigned __int32);
_inline void ElDorito::SetMainThreadID(unsigned __int32 ThreadID) // 0x10966B20
{
	mangled_x86(MANGLED_TODO, "?SetMainThreadID@ElDorito@@SAXI@Z");
	// unsigned __int32 ThreadID;
	todo("implement");
	_sub_10966B20(ThreadID);
}

_extern unsigned __int32 _sub_10923830();
_inline unsigned __int32 ElDorito::GetMainThreadID() // 0x10923830
{
	mangled_x86(MANGLED_TODO, "?GetMainThreadID@ElDorito@@SAIXZ");
	// procedure flags: nofpo
	todo("implement");
	unsigned __int32 __result = _sub_10923830();
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_1074E5C0(ElDorito const *const);
_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > ElDorito::GetMapsFolder() const // 0x1074E5C0
{
	mangled_x86(MANGLED_TODO, "?GetMapsFolder@ElDorito@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// ElDorito const *const this;
	todo("implement");
	std::string __result = _sub_1074E5C0((ElDorito const *)this);
	return __result;
}

_extern bool _sub_10961AD0(ElDorito const *const);
_inline bool ElDorito::IsWebDebuggingEnabled() const // 0x10961AD0
{
	mangled_x86(MANGLED_TODO, "?IsWebDebuggingEnabled@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_10961AD0((ElDorito const *)this);
	return __result;
}

_extern __int32 _sub_10C93860(ElDorito const *const);
_inline __int32 ElDorito::GetWebDebugPort() const // 0x10C93860
{
	mangled_x86(MANGLED_TODO, "?GetWebDebugPort@ElDorito@@QBEHXZ");
	// ElDorito const *const this;
	todo("implement");
	__int32 __result = _sub_10C93860((ElDorito const *)this);
	return __result;
}

_extern bool _sub_10CC0EA0(ElDorito const *const);
_inline bool ElDorito::IsWebDebugLoggingEnabled() const // 0x10CC0EA0
{
	mangled_x86(MANGLED_TODO, "?IsWebDebugLoggingEnabled@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_10CC0EA0((ElDorito const *)this);
	return __result;
}

_extern bool _sub_1068FE20(ElDorito const *const);
_inline bool ElDorito::IsDedicated() const // 0x1068FE20
{
	mangled_x86(MANGLED_TODO, "?IsDedicated@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_1068FE20((ElDorito const *)this);
	return __result;
}

_extern bool _sub_109685D0(ElDorito const *const);
_inline bool ElDorito::IsBotClient() const // 0x109685D0
{
	mangled_x86(MANGLED_TODO, "?IsBotClient@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_109685D0((ElDorito const *)this);
	return __result;
}

_extern bool _sub_10923850(ElDorito const *const);
_inline bool ElDorito::IsHeadless() const // 0x10923850
{
	mangled_x86(MANGLED_TODO, "?IsHeadless@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_10923850((ElDorito const *)this);
	return __result;
}

_extern bool _sub_10A48D10(ElDorito const *const);
_inline bool ElDorito::IsHighPriority() const // 0x10A48D10
{
	mangled_x86(MANGLED_TODO, "?IsHighPriority@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_10A48D10((ElDorito const *)this);
	return __result;
}

_extern bool _sub_10CAABD0(ElDorito const *const);
_inline bool ElDorito::IsConnectingToServer() const // 0x10CAABD0
{
	mangled_x86(MANGLED_TODO, "?IsConnectingToServer@ElDorito@@QBE_NXZ");
	// ElDorito const *const this;
	todo("implement");
	bool __result = _sub_10CAABD0((ElDorito const *)this);
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B4470(ElDorito const *const);
_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > ElDorito::GetInstanceName() const // 0x106B4470
{
	mangled_x86(MANGLED_TODO, "?GetInstanceName@ElDorito@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// ElDorito const *const this;
	todo("implement");
	std::string __result = _sub_106B4470((ElDorito const *)this);
	return __result;
}

/* ---------- private code */

#endif // __ELDORITO_HPP__

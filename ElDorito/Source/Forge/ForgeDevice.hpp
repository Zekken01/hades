#ifndef __FORGE_FORGEDEVICE_HPP__
#define __FORGE_FORGEDEVICE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

class CForgeDeviceManager;
struct CForgeDeviceObjectProperties;
struct IGameSystem;

/* ---------- constants */

/* ---------- definitions */

struct CForgeDeviceObjectProperties
{
	unsigned short device_flags; // 0x0
	unsigned char trigger_radius; // 0x2
	unsigned char delay_time; // 0x3
	union
	{
		struct
		{
			unsigned char open_time; // 0x0
		} door; // 0x4
		struct
		{
			unsigned char turn_rate; // 0x0
		} gear; // 0x4
	};
	_inline float GetGearTurnRate() const;
	_inline void SetGearTurnRate(float value);
	_inline float GetDoorOpenTime() const;
	_inline void SetDoorOpenTime(float value);
	_inline float GetTriggerRadius() const;
	_inline void SetTriggerRadius(float value);
	_inline float GetDelayTime() const;
	_inline void SetDelayTime(float value);
	unsigned char __pad0[1]; // 0x5
};
static_assert(sizeof(CForgeDeviceObjectProperties) == 6, "Invalid CForgeDeviceObjectProperties size");

class CForgeDeviceManager :
	public Utils::Singleton<CForgeDeviceManager>,
	public IGameSystem
{
public:
	void InitializeDeviceObject(long objectIndex);
	bool IsForgeDevice(long objectIndex);
	EForgeDeviceType GetDeviceType(long objectIndex);
private:
	virtual void InitializeForNewMap();
	virtual void Update();
public:
	_inline CForgeDeviceManager(); /* compiler_generated() */
	virtual _inline ~CForgeDeviceManager(); /* compiler_generated() */
};
static_assert(sizeof(CForgeDeviceManager) == 4, "Invalid CForgeDeviceManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern float _sub_1083D0C0(CForgeDeviceObjectProperties const *const);
_inline float CForgeDeviceObjectProperties::GetGearTurnRate() const // 0x1083D0C0
{
	mangled_x86(MANGLED_TODO, "?GetGearTurnRate@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;
	todo("implement");
	float __result = _sub_1083D0C0((CForgeDeviceObjectProperties const *)this);
	return __result;
}

_extern void _sub_1083F9B0(CForgeDeviceObjectProperties *const, float);
_inline void CForgeDeviceObjectProperties::SetGearTurnRate(float value) // 0x1083F9B0
{
	mangled_x86(MANGLED_TODO, "?SetGearTurnRate@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;
	todo("implement");
	_sub_1083F9B0(this, value);
}

_extern float _sub_1083C030(CForgeDeviceObjectProperties const *const);
_inline float CForgeDeviceObjectProperties::GetDoorOpenTime() const // 0x1083C030
{
	mangled_x86(MANGLED_TODO, "?GetDoorOpenTime@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;
	todo("implement");
	float __result = _sub_1083C030((CForgeDeviceObjectProperties const *)this);
	return __result;
}

_extern void _sub_1083EAE0(CForgeDeviceObjectProperties *const, float);
_inline void CForgeDeviceObjectProperties::SetDoorOpenTime(float value) // 0x1083EAE0
{
	mangled_x86(MANGLED_TODO, "?SetDoorOpenTime@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;
	todo("implement");
	_sub_1083EAE0(this, value);
}

_extern float _sub_1083E7E0(CForgeDeviceObjectProperties const *const);
_inline float CForgeDeviceObjectProperties::GetTriggerRadius() const // 0x1083E7E0
{
	mangled_x86(MANGLED_TODO, "?GetTriggerRadius@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;
	todo("implement");
	float __result = _sub_1083E7E0((CForgeDeviceObjectProperties const *)this);
	return __result;
}

_extern void _sub_10840F90(CForgeDeviceObjectProperties *const, float);
_inline void CForgeDeviceObjectProperties::SetTriggerRadius(float value) // 0x10840F90
{
	mangled_x86(MANGLED_TODO, "?SetTriggerRadius@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;
	todo("implement");
	_sub_10840F90(this, value);
}

_extern float _sub_1083BFE0(CForgeDeviceObjectProperties const *const);
_inline float CForgeDeviceObjectProperties::GetDelayTime() const // 0x1083BFE0
{
	mangled_x86(MANGLED_TODO, "?GetDelayTime@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;
	todo("implement");
	float __result = _sub_1083BFE0((CForgeDeviceObjectProperties const *)this);
	return __result;
}

_extern void _sub_1083EA60(CForgeDeviceObjectProperties *const, float);
_inline void CForgeDeviceObjectProperties::SetDelayTime(float value) // 0x1083EA60
{
	mangled_x86(MANGLED_TODO, "?SetDelayTime@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;
	todo("implement");
	_sub_1083EA60(this, value);
}

/* ---------- private code */

#endif // __FORGE_FORGEDEVICE_HPP__

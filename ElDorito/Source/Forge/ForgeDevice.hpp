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
	_inline CForgeDeviceManager() = default; /* compiler_generated() */
	virtual _inline ~CForgeDeviceManager() = default; /* compiler_generated() */ // 0x108CE1F0
};
static_assert(sizeof(CForgeDeviceManager) == 4, "Invalid CForgeDeviceManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline float CForgeDeviceObjectProperties::GetGearTurnRate() const // 0x1083D0C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetGearTurnRate@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;

	return gear.turn_rate / 40.0f;
}

inline void CForgeDeviceObjectProperties::SetGearTurnRate(float value) // 0x1083F9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetGearTurnRate@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;

	gear.turn_rate = (unsigned char)floorf(value * 40.0f);
}

inline float CForgeDeviceObjectProperties::GetDoorOpenTime() const // 0x1083C030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDoorOpenTime@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;

	return door.open_time / 4.0f;
}

inline void CForgeDeviceObjectProperties::SetDoorOpenTime(float value) // 0x1083EAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetDoorOpenTime@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;

	door.open_time = (unsigned char)floorf(value * 4.0f);
}

inline float CForgeDeviceObjectProperties::GetTriggerRadius() const // 0x1083E7E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetTriggerRadius@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;

	return trigger_radius / 4.0f;
}

inline void CForgeDeviceObjectProperties::SetTriggerRadius(float value) // 0x10840F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetTriggerRadius@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;

	trigger_radius = (unsigned char)floorf(value * 4.0f);
}

inline float CForgeDeviceObjectProperties::GetDelayTime() const // 0x1083BFE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDelayTime@CForgeDeviceObjectProperties@@QBEMXZ");
	// CForgeDeviceObjectProperties const *const this;

	return delay_time / 4.0f;
}

inline void CForgeDeviceObjectProperties::SetDelayTime(float value) // 0x1083EA60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetDelayTime@CForgeDeviceObjectProperties@@QAEXM@Z");
	// float value;

	delay_time = (unsigned char)floorf(value * 4.0f);
}

/* ---------- private code */

#endif // __FORGE_FORGEDEVICE_HPP__

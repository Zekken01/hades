#ifndef __BLAM_GAME_GAME_GLOBALS_HPP__
#define __BLAM_GAME_GAME_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/camera.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct real_point2d;
struct s_ai_globals_definition;
struct s_ai_globals_gravemind_properties;
struct s_camera_globals;
struct s_campaign_metagame_difficulty_multiplier;
struct s_campaign_metagame_globals;
struct s_campaign_metagame_medal_difficulty_multiplier;
struct s_chud_per_character_globals;
struct s_damage_globals_definition;
struct s_damage_globals_group;
struct s_damage_globals_group_armor_modifier;
struct s_game_globals;
struct s_game_globals_camera;
struct s_game_globals_cinematic_anchor;
struct s_game_globals_damage;
struct s_game_globals_difficulty_information;
struct s_game_globals_falling_damage;
struct s_game_globals_grenade;
struct s_game_globals_havok_cleanup_resources;
struct s_game_globals_interface_string_references;
struct s_game_globals_interface_tag_references;
struct s_game_globals_player_character_type;
struct s_game_globals_player_control;
struct s_game_globals_player_information;
struct s_game_globals_player_look_function;
struct s_game_globals_player_representation;
struct s_game_globals_s3d_unknown;
struct s_game_globals_tag_reference;
struct s_global_material_definition;
struct s_global_material_physics_definition;
struct s_global_material_water_drag_properties;
struct s_global_material_water_interaction;
struct s_model_customization_selection;
struct s_sound_globals_definition;
struct s_tag_data;
struct s_tag_reference;
struct s_weapon_first_person_interface_definition;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

struct s_game_globals_tag_reference
{
	s_tag_reference Reference; // 0x0
};
static_assert(sizeof(s_game_globals_tag_reference) == 16, "Invalid s_game_globals_tag_reference size");

struct s_game_globals_havok_cleanup_resources
{
	s_tag_reference ObjectCleanupEffect; // 0x0
};
static_assert(sizeof(s_game_globals_havok_cleanup_resources) == 16, "Invalid s_game_globals_havok_cleanup_resources size");

struct s_sound_globals_definition
{
	s_tag_reference SoundClasses; // 0x0
	s_tag_reference SoundEffects; // 0x10
	s_tag_reference SoundMix; // 0x20
	s_tag_reference SoundCombatDialogueConstants; // 0x30
	s_tag_reference SoundGlobalPropagation; // 0x40
	s_tag_reference GfxUiSounds; // 0x50
};
static_assert(sizeof(s_sound_globals_definition) == 96, "Invalid s_sound_globals_definition size");

struct s_ai_globals_gravemind_properties
{
	float MinimumRetreatTime; // 0x0
	float IdealRetreatTime; // 0x4
	float MaximumRetreatTime; // 0x8
};
static_assert(sizeof(s_ai_globals_gravemind_properties) == 12, "Invalid s_ai_globals_gravemind_properties size");

#pragma pack(push, 4)
struct s_ai_globals_definition
{
	struct GravemindProperty;
	struct Style;
	float Unknown1; // 0x0
	float Unknown2; // 0x4
	float Unknown3; // 0x8
	float DangerBroadlyFacing; // 0xC
	float DangerShootingNear; // 0x10
	float DangerShootingAt; // 0x14
	float DangerExtremelyClose; // 0x18
	float DangerShieldDamage; // 0x1C
	float DangerExtendedShieldDamage; // 0x20
	float DangerBodyDamage; // 0x24
	float DangerExtendedBodyDamage; // 0x28
	s_tag_reference GlobalDialogue; // 0x2C
	float DefaultMissionDialogueSoundEffect; // 0x3C
	float JumpDown; // 0x40
	float JumpStep; // 0x44
	float JumpCrouch; // 0x48
	float JumpStand; // 0x4C
	float JumpStorey; // 0x50
	float JumpTower; // 0x54
	float MaxJumpDownHeightDown; // 0x58
	float MaxJumpDownHeightStep; // 0x5C
	float MaxJumpDownHeightCrouch; // 0x60
	float MaxJumpDownHeightStand; // 0x64
	float MaxJumpDownHeightStorey; // 0x68
	float MaxJumpDownHeightTower; // 0x6C
	real_bounds HoistStepBounds; // 0x70
	real_bounds HoistCrouchBounds; // 0x78
	real_bounds HoistStandBounds; // 0x80
	real_bounds VaultStepBounds; // 0x88
	real_bounds VaultCrouchBounds; // 0x90
	float Unknown4; // 0x98
	float Unknown5; // 0x9C
	float Unknown6; // 0xA0
	float Unknown7; // 0xA4
	c_tag_block<s_ai_globals_gravemind_properties> GravemindProperties; // 0xA8
	float ScaryTargetThreshold; // 0xB4
	float ScaryWeaponThreshold; // 0xB8
	float Unknown8; // 0xBC
	float Unknown9; // 0xC0
	float Unknown10; // 0xC4
	float Unknown11; // 0xC8
	float Unknown12; // 0xCC
	float Unknown13; // 0xD0
	float Unknown14; // 0xD4
	float Unknown15; // 0xD8
	float Unknown16; // 0xDC
	float Unknown17; // 0xE0
	float Unknown18; // 0xE4
	c_tag_block<s_game_globals_tag_reference> Styles; // 0xE8
	float Unknown19; // 0xF4
	float Unknown20; // 0xF8
	float Unknown21; // 0xFC
	float Unknown22; // 0x100
	float Unknown23; // 0x104
	float Unknown24; // 0x108
	float Unknown25; // 0x10C
	float Unknown26; // 0x110
	float Unknown27; // 0x114
	float Unknown28; // 0x118
	float Unknown29; // 0x11C
	float Unknown30; // 0x120
	float Unknown31; // 0x124
	float Unknown32; // 0x128
	float Unknown33; // 0x12C
	float Unknown34; // 0x130
	float Unknown35; // 0x134
	float Unknown36; // 0x138
	float Unknown37; // 0x13C
	float Unknown38; // 0x140
};
#pragma pack(pop)
static_assert(sizeof(s_ai_globals_definition) == 324, "Invalid s_ai_globals_definition size");

struct s_damage_globals_group_armor_modifier
{
	unsigned long Name; // 0x0
	float DamageMultiplier; // 0x4
};
static_assert(sizeof(s_damage_globals_group_armor_modifier) == 8, "Invalid s_damage_globals_group_armor_modifier size");

struct s_damage_globals_group
{
	unsigned long Name; // 0x0
	c_tag_block<s_damage_globals_group_armor_modifier> ArmorModifiers; // 0x4
};
static_assert(sizeof(s_damage_globals_group) == 16, "Invalid s_damage_globals_group size");

#pragma pack(push, 4)
struct s_damage_globals_definition
{
	c_tag_block<s_damage_globals_group> DamageGroups; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_damage_globals_definition) == 12, "Invalid s_damage_globals_definition size");

#pragma pack(push, 4)
struct s_game_globals_camera
{
	s_tag_reference default_unit_camera_track; // 0x0
	s_camera_globals global_defaults; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_camera) == 164, "Invalid s_game_globals_camera size");

struct s_game_globals_player_look_function
{
	float Scale; // 0x0
};
static_assert(sizeof(s_game_globals_player_look_function) == 4, "Invalid s_game_globals_player_look_function size");

struct s_game_globals_player_control
{
	float MagnetismFriction; // 0x0
	float MagnetismAdhesion; // 0x4
	float InconsequentialTargetScale; // 0x8
	real_point2d CrosshairLocation; // 0xC
	float SprintSecondsToStart; // 0x14
	float SprintSecondsToFullSpeed; // 0x18
	float SprintDecayRate; // 0x1C
	float SprintFullSpeedMultiplier; // 0x20
	float SprintPeggedMagnitude; // 0x24
	float SprintPeggedAngularThreshold; // 0x28
	float SprintUnknown1; // 0x2C
	float SprintUnknown2; // 0x30
	float LookDefaultPitchRate; // 0x34
	float LookDefaultYawRate; // 0x38
	float LookPegThreshold; // 0x3C
	float LookYawAccelerationTime; // 0x40
	float LookYawAccelerationScale; // 0x44
	float LookPitchAccelerationTime; // 0x48
	float LookPitchAccelerationScale; // 0x4C
	float LookAutolevelingScale; // 0x50
	float Unknown1; // 0x54
	float Unknown2; // 0x58
	float GravityScale; // 0x5C
	short Unknown5; // 0x60
	short MinimumAutolevelingTicks; // 0x62
	c_tag_block<s_game_globals_player_look_function> LookFunction; // 0x64
};
static_assert(sizeof(s_game_globals_player_control) == 112, "Invalid s_game_globals_player_control size");

struct s_game_globals_difficulty_information
{
	float EasyEnemyDamage; // 0x0
	float NormalEnemyDamage; // 0x4
	float HardEnemyDamage; // 0x8
	float ImpossibleEnemyDamage; // 0xC
	float EasyEnemyVitality; // 0x10
	float NormalEnemyVitality; // 0x14
	float HardEnemyVitality; // 0x18
	float ImpossibleEnemyVitality; // 0x1C
	float EasyEnemyShield; // 0x20
	float NormalEnemyShield; // 0x24
	float HardEnemyShield; // 0x28
	float ImpossibleEnemyShield; // 0x2C
	float EasyEnemyRecharge; // 0x30
	float NormalEnemyRecharge; // 0x34
	float HardEnemyRecharge; // 0x38
	float ImpossibleEnemyRecharge; // 0x3C
	float EasyFriendDamage; // 0x40
	float NormalFriendDamage; // 0x44
	float HardFriendDamage; // 0x48
	float ImpossibleFriendDamage; // 0x4C
	float EasyFriendVitality; // 0x50
	float NormalFriendVitality; // 0x54
	float HardFriendVitality; // 0x58
	float ImpossibleFriendVitality; // 0x5C
	float EasyFriendShield; // 0x60
	float NormalFriendShield; // 0x64
	float HardFriendShield; // 0x68
	float ImpossibleFriendShield; // 0x6C
	float EasyFriendRecharge; // 0x70
	float NormalFriendRecharge; // 0x74
	float HardFriendRecharge; // 0x78
	float ImpossibleFriendRecharge; // 0x7C
	float EasyInfectionForms; // 0x80
	float NormalInfectionForms; // 0x84
	float HardInfectionForms; // 0x88
	float ImpossibleInfectionForms; // 0x8C
	float EasyUnknown; // 0x90
	float NormalUnknown; // 0x94
	float HardUnknown; // 0x98
	float ImpossibleUnknown; // 0x9C
	float EasyRateOfFire; // 0xA0
	float NormalRateOfFire; // 0xA4
	float HardRateOfFire; // 0xA8
	float ImpossibleRateOfFire; // 0xAC
	float EasyProjectileError; // 0xB0
	float NormalProjectileError; // 0xB4
	float HardProjectileError; // 0xB8
	float ImpossibleProjectileError; // 0xBC
	float EasyBurstError; // 0xC0
	float NormalBurstError; // 0xC4
	float HardBurstError; // 0xC8
	float ImpossibleBurstError; // 0xCC
	float EasyTargetDelay; // 0xD0
	float NormalTargetDelay; // 0xD4
	float HardTargetDelay; // 0xD8
	float ImpossibleTargetDelay; // 0xDC
	float EasyBurstSeparation; // 0xE0
	float NormalBurstSeparation; // 0xE4
	float HardBurstSeparation; // 0xE8
	float ImpossibleBurstSeparation; // 0xEC
	float EasyTargetTracking; // 0xF0
	float NormalTargetTracking; // 0xF4
	float HardTargetTracking; // 0xF8
	float ImpossibleTargetTracking; // 0xFC
	float EasyTargetLeading; // 0x100
	float NormalTargetLeading; // 0x104
	float HardTargetLeading; // 0x108
	float ImpossibleTargetLeading; // 0x10C
	float EasyOverchargeChance; // 0x110
	float NormalOverchargeChance; // 0x114
	float HardOverchargeChance; // 0x118
	float ImpossibleOverchargeChance; // 0x11C
	float EasySpecialFireDelay; // 0x120
	float NormalSpecialFireDelay; // 0x124
	float HardSpecialFireDelay; // 0x128
	float ImpossibleSpecialFireDelay; // 0x12C
	float EasyGuidanceVsPlayer; // 0x130
	float NormalGuidanceVsPlayer; // 0x134
	float HardGuidanceVsPlayer; // 0x138
	float ImpossibleGuidanceVsPlayer; // 0x13C
	float EasyMeleeDelayBase; // 0x140
	float NormalMeleeDelayBase; // 0x144
	float HardMeleeDelayBase; // 0x148
	float ImpossibleMeleeDelayBase; // 0x14C
	float EasyMeleeDelayScale; // 0x150
	float NormalMeleeDelayScale; // 0x154
	float HardMeleeDelayScale; // 0x158
	float ImpossibleMeleeDelayScale; // 0x15C
	float EasyUnknown2; // 0x160
	float NormalUnknown2; // 0x164
	float HardUnknown2; // 0x168
	float ImpossibleUnknown2; // 0x16C
	float EasyGrenadeChanceScale; // 0x170
	float NormalGrenadeChanceScale; // 0x174
	float HardGrenadeChanceScale; // 0x178
	float ImpossibleGrenadeChanceScale; // 0x17C
	float EasyGrenadeTimerScale; // 0x180
	float NormalGrenadeTimerScale; // 0x184
	float HardGrenadeTimerScale; // 0x188
	float ImpossibleGrenadeTimerScale; // 0x18C
	float EasyUnknown3; // 0x190
	float NormalUnknown3; // 0x194
	float HardUnknown3; // 0x198
	float ImpossibleUnknown3; // 0x19C
	float EasyUnknown4; // 0x1A0
	float NormalUnknown4; // 0x1A4
	float HardUnknown4; // 0x1A8
	float ImpossibleUnknown4; // 0x1AC
	float EasyUnknown5; // 0x1B0
	float NormalUnknown5; // 0x1B4
	float HardUnknown5; // 0x1B8
	float ImpossibleUnknown5; // 0x1BC
	float EasyMajorUpgradeNormal; // 0x1C0
	float NormalMajorUpgradeNormal; // 0x1C4
	float HardMajorUpgradeNormal; // 0x1C8
	float ImpossibleMajorUpgradeNormal; // 0x1CC
	float EasyMajorUpgradeFew; // 0x1D0
	float NormalMajorUpgradeFew; // 0x1D4
	float HardMajorUpgradeFew; // 0x1D8
	float ImpossibleMajorUpgradeFew; // 0x1DC
	float EasyMajorUpgradeMany; // 0x1E0
	float NormalMajorUpgradeMany; // 0x1E4
	float HardMajorUpgradeMany; // 0x1E8
	float ImpossibleMajorUpgradeMany; // 0x1EC
	float EasyPlayerVehicleRamChance; // 0x1F0
	float NormalPlayerVehicleRamChance; // 0x1F4
	float HardPlayerVehicleRamChance; // 0x1F8
	float ImpossiblePlayerVehicleRamChance; // 0x1FC
	float Unknown; // 0x200
	float Unknown2; // 0x204
	float Unknown3; // 0x208
	float Unknown4; // 0x20C
	float Unknown5; // 0x210
	float Unknown6; // 0x214
	float Unknown7; // 0x218
	float Unknown8; // 0x21C
	float Unknown9; // 0x220
	float Unknown10; // 0x224
	float Unknown11; // 0x228
	float Unknown12; // 0x22C
	float Unknown13; // 0x230
	float Unknown14; // 0x234
	float Unknown15; // 0x238
	float Unknown16; // 0x23C
	float Unknown17; // 0x240
	float Unknown18; // 0x244
	float Unknown19; // 0x248
	float Unknown20; // 0x24C
	float Unknown21; // 0x250
	float Unknown22; // 0x254
	float Unknown23; // 0x258
	float Unknown24; // 0x25C
	float Unknown25; // 0x260
	float Unknown26; // 0x264
	float Unknown27; // 0x268
	float Unknown28; // 0x26C
	float Unknown29; // 0x270
	float Unknown30; // 0x274
	float Unknown31; // 0x278
	float Unknown32; // 0x27C
	float Unknown33; // 0x280
};
static_assert(sizeof(s_game_globals_difficulty_information) == 644, "Invalid s_game_globals_difficulty_information size");

#pragma pack(push, 4)
struct s_game_globals_grenade
{
	short MaximumCount; // 0x0
	short Unknown1; // 0x2
	s_tag_reference ThrowingEffect; // 0x4
	float Unknown2; // 0x14
	float Unknown3; // 0x18
	float Unknown4; // 0x1C
	float Unknown5; // 0x20
	s_tag_reference Equipment; // 0x24
	s_tag_reference Projectile; // 0x34
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_grenade) == 68, "Invalid s_game_globals_grenade size");

struct s_game_globals_interface_string_references
{
	tag_string Name; // 0x0
	s_tag_reference Strings; // 0x20
};
static_assert(sizeof(s_game_globals_interface_string_references) == 48, "Invalid s_game_globals_interface_string_references size");

#pragma pack(push, 4)
struct s_game_globals_interface_tag_references
{
	s_tag_reference Spinner; // 0x0
	s_tag_reference Obsolete; // 0x10
	s_tag_reference ScreenColorTable; // 0x20
	s_tag_reference HudColorTable; // 0x30
	s_tag_reference EditorColorTable; // 0x40
	s_tag_reference DialogColorTable; // 0x50
	s_tag_reference MotionSensorSweepBitmap; // 0x60
	s_tag_reference MotionSensorSweepBitmapMask; // 0x70
	s_tag_reference MultiplayerHudBitmap; // 0x80
	s_tag_reference HudDigitsDefinition; // 0x90
	s_tag_reference MotionSensorBlipBitmap; // 0xA0
	s_tag_reference InterfaceGooMap1; // 0xB0
	s_tag_reference InterfaceGooMap2; // 0xC0
	s_tag_reference InterfaceGooMap3; // 0xD0
	s_tag_reference MainMenuUiGlobals; // 0xE0
	s_tag_reference SinglePlayerUiGlobals; // 0xF0
	s_tag_reference MultiplayerUiGlobals; // 0x100
	s_tag_reference HudGlobals; // 0x110
	c_tag_block<s_game_globals_interface_string_references> UIStrings; // 0x120
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_interface_tag_references) == 300, "Invalid s_game_globals_interface_tag_references size");

#pragma pack(push, 4)
struct s_game_globals_player_information
{
	float WalkingSpeed; // 0x0
	float RunForward; // 0x4
	float RunBackward; // 0x8
	float RunSideways; // 0xC
	float RunAcceleration; // 0x10
	float SneakForward; // 0x14
	float SneakBackward; // 0x18
	float SneakSideways; // 0x1C
	float SneakAcceleration; // 0x20
	float AirborneAcceleration; // 0x24
	real_point3d GrenadeOrigin; // 0x28
	float StunMovementPenalty; // 0x34
	float StunTurningPenalty; // 0x38
	float StunJumpingPenalty; // 0x3C
	real_bounds StunTimeBounds; // 0x40
	real_bounds FirstPersonIdleTimeBounds; // 0x48
	float FirstPersonSkipFraction; // 0x50
	float Unknown1; // 0x54
	s_tag_reference Unknown2; // 0x58
	s_tag_reference Unknown3; // 0x68
	s_tag_reference coop_respawn_effect; // 0x78
	long BinocularsZoomCount; // 0x88
	real_bounds BinocularZoomBounds; // 0x8C
	float Unknown5; // 0x94
	float Unknown6; // 0x98
	s_tag_reference FlashlightOn; // 0x9C
	s_tag_reference FlashlightOff; // 0xAC
	s_tag_reference DefaultDamageResponse; // 0xBC
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_player_information) == 204, "Invalid s_game_globals_player_information size");

#pragma pack(push, 4)
struct s_game_globals_player_representation
{
	unsigned long Name; // 0x0
	c_flags<enum e_player_appearance_flags,long> Flags; // 0x4
	s_tag_reference FirstPersonHands; // 0x8
	s_tag_reference FirstPersonBody; // 0x18
	s_tag_reference ThirdPersonUnit; // 0x28
	long ThirdPersonVariant; // 0x38
	s_tag_reference BinocularsZoomInSound; // 0x3C
	s_tag_reference BinocularsZoomOutSound; // 0x4C
	s_tag_reference Unknown; // 0x5C
	s_game_globals_player_representation(s_game_globals_player_representation &); /* compiler_generated() */
	s_game_globals_player_representation(s_game_globals_player_representation const &); /* compiler_generated() */
	s_game_globals_player_representation(); /* compiler_generated() */
	s_game_globals_player_representation &operator=(s_game_globals_player_representation &); /* compiler_generated() */
	s_game_globals_player_representation &operator=(s_game_globals_player_representation const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_player_representation) == 108, "Invalid s_game_globals_player_representation size");

struct s_game_globals_player_character_type
{
	unsigned long name; // 0x0
	unsigned char flags; // 0x4
	c_tag_block_index<s_game_globals_player_information,char> player_information_block_index; // 0x5
	c_tag_block_index<s_game_globals_player_information,char> player_control_block_index; // 0x6
	c_tag_block_index<s_game_globals_player_information,char> campaign_player_representation_block_index; // 0x7
	c_tag_block_index<s_game_globals_player_representation,char> multiplayer_player_representation_block_index; // 0x8
	c_tag_block_index<s_model_customization_selection,char> multiplayer_armor_customization_block_index; // 0x9
	c_tag_block_index<s_chud_per_character_globals,char> chud_character_globals_block_index; // 0xA
	c_tag_block_index<s_weapon_first_person_interface_definition,char> first_person_weapon_interface_block_index; // 0xB
	s_game_globals_player_character_type(s_game_globals_player_character_type &); /* compiler_generated() */
	_inline s_game_globals_player_character_type(s_game_globals_player_character_type const &__that); /* compiler_generated() */
	s_game_globals_player_character_type(); /* compiler_generated() */
};
static_assert(sizeof(s_game_globals_player_character_type) == 12, "Invalid s_game_globals_player_character_type size");

struct s_game_globals_falling_damage
{
	real_bounds HarmfulFallingDistanceBounds; // 0x0
	s_tag_reference FallingDamage; // 0x8
	s_tag_reference Unknown1; // 0x18
	s_tag_reference SoftLanding; // 0x28
	s_tag_reference HardLanding; // 0x38
	s_tag_reference ScriptDamage; // 0x48
	float MaximumFallingDistance; // 0x58
	s_tag_reference DistanceDamage; // 0x5C
	float Unknown2; // 0x6C
	float Unknown3; // 0x70
	float Unknown4; // 0x74
};
static_assert(sizeof(s_game_globals_falling_damage) == 120, "Invalid s_game_globals_falling_damage size");

struct s_game_globals_s3d_unknown
{
	float Unknown1; // 0x0
	float Unknown2; // 0x4
	float Unknown3; // 0x8
};
static_assert(sizeof(s_game_globals_s3d_unknown) == 12, "Invalid s_game_globals_s3d_unknown size");

struct s_global_material_water_drag_properties
{
	float Unknown1; // 0x0
	float Unknown2; // 0x4
	float Unknown3; // 0x8
	float Unknown4; // 0xC
	float Unknown5; // 0x10
	float Unknown6; // 0x14
	float Unknown7; // 0x18
	float Unknown8; // 0x1C
	float Unknown9; // 0x20
	float Unknown10; // 0x24
};
static_assert(sizeof(s_global_material_water_drag_properties) == 40, "Invalid s_global_material_water_drag_properties size");

#pragma pack(push, 4)
struct s_global_material_physics_definition
{
	unsigned long flags; // 0x0
	float friction; // 0x4
	float restitution; // 0x8
	float density; // 0xC
	c_tag_block<s_global_material_water_drag_properties> drag; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_global_material_physics_definition) == 28, "Invalid s_global_material_physics_definition size");

struct s_global_material_water_interaction
{
	unsigned long SurfaceName; // 0x0
	unsigned long SubmergedName; // 0x4
	short SurfaceIndex; // 0x8
	short SubmergedIndex; // 0xA
};
static_assert(sizeof(s_global_material_water_interaction) == 12, "Invalid s_global_material_water_interaction size");

struct s_global_material_definition
{
	unsigned long Name; // 0x0
	unsigned long ParentName; // 0x4
	short ParentIndex; // 0x8
	c_flags<enum e_global_material_flags,unsigned short> Flags; // 0xA
	unsigned long GeneralArmor; // 0xC
	unsigned long SpecificArmor; // 0x10
	s_global_material_physics_definition physics; // 0x14
	s_tag_reference BreakableSurface; // 0x30
	s_tag_reference SoundSweetenerSmall; // 0x40
	s_tag_reference SoundSweetenerMedium; // 0x50
	s_tag_reference SoundSweetenerLarge; // 0x60
	s_tag_reference SoundSweetenerRolling; // 0x70
	s_tag_reference SoundSweetenerGrinding; // 0x80
	s_tag_reference SoundSweetenerMeleeSmall; // 0x90
	s_tag_reference SoundSweetenerMeleeMedium; // 0xA0
	s_tag_reference SoundSweetenerMeleeLarge; // 0xB0
	s_tag_reference EffectSweetenerSmall; // 0xC0
	s_tag_reference EffectSweetenerMedium; // 0xD0
	s_tag_reference EffectSweetenerLarge; // 0xE0
	s_tag_reference EffectSweetenerRolling; // 0xF0
	s_tag_reference EffectSweetenerGrinding; // 0x100
	s_tag_reference EffectSweetenerMelee; // 0x110
	s_tag_reference WaterRippleSmall; // 0x120
	s_tag_reference WaterRippleMedium; // 0x130
	s_tag_reference WaterRippleLarge; // 0x140
	c_flags<enum e_global_material_sweetener_flags,long> SweetenerInheritanceFlags; // 0x150
	s_tag_reference MaterialEffects; // 0x154
	c_tag_block<s_global_material_water_interaction> WaterInteraction; // 0x164
	float Unknown2; // 0x170
	short Unknown3; // 0x174
	short Unknown4; // 0x176
	s_global_material_definition(s_global_material_definition &); /* compiler_generated() */
	s_global_material_definition(s_global_material_definition const &); /* compiler_generated() */
	s_global_material_definition(); /* compiler_generated() */
	s_global_material_definition &operator=(s_global_material_definition &); /* compiler_generated() */
	s_global_material_definition &operator=(s_global_material_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_global_material_definition) == 376, "Invalid s_global_material_definition size");

struct s_game_globals_cinematic_anchor
{
	s_tag_reference Anchor; // 0x0
	float Unknown1; // 0x10
	float Unknown2; // 0x14
};
static_assert(sizeof(s_game_globals_cinematic_anchor) == 24, "Invalid s_game_globals_cinematic_anchor size");

struct s_campaign_metagame_medal_difficulty_multiplier
{
	float Multiplier; // 0x0
	long AwardedPoints; // 0x4
	long MedalUptime; // 0x8
	long EventName; // 0xC
};
static_assert(sizeof(s_campaign_metagame_medal_difficulty_multiplier) == 16, "Invalid s_campaign_metagame_medal_difficulty_multiplier size");

struct s_campaign_metagame_difficulty_multiplier
{
	float Multiplier; // 0x0
};
static_assert(sizeof(s_campaign_metagame_difficulty_multiplier) == 4, "Invalid s_campaign_metagame_difficulty_multiplier size");

struct s_campaign_metagame_globals
{
	c_tag_block<s_campaign_metagame_medal_difficulty_multiplier> Medals; // 0x0
	c_tag_block<s_campaign_metagame_difficulty_multiplier> Difficulty; // 0xC
	c_tag_block<s_campaign_metagame_difficulty_multiplier> PrimarySkulls; // 0x18
	c_tag_block<s_campaign_metagame_difficulty_multiplier> SecondarySkulls; // 0x24
	long Unknown1; // 0x30
	long DeathPenalty; // 0x34
	long BetrayalPenalty; // 0x38
	long Unknown2; // 0x3C
	float MultikillWindow; // 0x40
	float EMPWindow; // 0x44
	float Unknown3; // 0x48
	float Unknown4; // 0x4C
	float Unknown5; // 0x50
	long FirstWeaponSpree; // 0x54
	long SecondWeaponSpree; // 0x58
	long KillingSpree; // 0x5C
	long KillingFrenzy; // 0x60
	long RunningRiot; // 0x64
	long Rampage; // 0x68
	long Untouchable; // 0x6C
	long Invincible; // 0x70
	long DoubleKill; // 0x74
	long TripleKill; // 0x78
	long Overkill; // 0x7C
	long Killtacular; // 0x80
	long Killtrocity; // 0x84
	long Killimanjaro; // 0x88
	long Killtastrophe; // 0x8C
	long Killpocalypse; // 0x90
	long Killionaire; // 0x94
};
static_assert(sizeof(s_campaign_metagame_globals) == 152, "Invalid s_campaign_metagame_globals size");

#pragma pack(push, 4)
struct s_game_globals_damage
{
	short Index; // 0x0
	short Version; // 0x2
	tag_string Name; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_game_globals_damage) == 36, "Invalid s_game_globals_damage size");

struct s_game_globals
{
	float Unknown1; // 0x0
	float Unknown2; // 0x4
	float Unknown3; // 0x8
	float Unknown4; // 0xC
	float Unknown5; // 0x10
	float Unknown6; // 0x14
	float Unknown7; // 0x18
	float Unknown8; // 0x1C
	float Unknown9; // 0x20
	float Unknown10; // 0x24
	float Unknown11; // 0x28
	float Unknown12; // 0x2C
	float Unknown13; // 0x30
	float Unknown14; // 0x34
	float Unknown15; // 0x38
	float Unknown16; // 0x3C
	float Unknown17; // 0x40
	float Unknown18; // 0x44
	float Unknown19; // 0x48
	float Unknown20; // 0x4C
	float Unknown21; // 0x50
	float Unknown22; // 0x54
	float Unknown23; // 0x58
	float Unknown24; // 0x5C
	float Unknown25; // 0x60
	float Unknown26; // 0x64
	float Unknown27; // 0x68
	float Unknown28; // 0x6C
	float Unknown29; // 0x70
	float Unknown30; // 0x74
	float Unknown31; // 0x78
	float Unknown32; // 0x7C
	float Unknown33; // 0x80
	float Unknown34; // 0x84
	float Unknown35; // 0x88
	float Unknown36; // 0x8C
	float Unknown37; // 0x90
	float Unknown38; // 0x94
	float Unknown39; // 0x98
	float Unknown40; // 0x9C
	float Unknown41; // 0xA0
	float Unknown42; // 0xA4
	float Unknown43; // 0xA8
	long Language; // 0xAC
	c_tag_block<s_game_globals_havok_cleanup_resources> HavokCleanupResources; // 0xB0
	c_tag_block<s_sound_globals_definition> SoundGlobals; // 0xBC
	c_tag_block<s_ai_globals_definition> AIGlobals; // 0xC8
	s_tag_reference AIGlobalsTag; // 0xD4
	c_tag_block<s_damage_globals_definition> DamageTable; // 0xE4
	float Unknown44; // 0xF0
	float Unknown45; // 0xF4
	float Unknown46; // 0xF8
	c_tag_block<s_game_globals_tag_reference> Sounds; // 0xFC
	c_tag_block<s_game_globals_camera> Camera; // 0x108
	c_tag_block<s_game_globals_player_control> PlayerControl; // 0x114
	c_tag_block<s_game_globals_difficulty_information> Difficulty; // 0x120
	c_tag_block<s_game_globals_grenade> Grenades; // 0x12C
	float Unknown47; // 0x138
	float Unknown48; // 0x13C
	float Unknown49; // 0x140
	c_tag_block<s_game_globals_interface_tag_references> InterfaceTags; // 0x144
	float Unknown50; // 0x150
	float Unknown51; // 0x154
	float Unknown52; // 0x158
	float Unknown53; // 0x15C
	float Unknown54; // 0x160
	float Unknown55; // 0x164
	c_tag_block<s_game_globals_player_information> PlayerInformation; // 0x168
	c_tag_block<s_game_globals_player_representation> PlayerRepresentation; // 0x174
	c_tag_block<s_game_globals_player_character_type> player_character_types; // 0x180
	c_tag_block<s_game_globals_falling_damage> PlayerFallingDamage; // 0x18C
	c_tag_block<s_game_globals_s3d_unknown> Unknown60; // 0x198
	c_tag_block<s_global_material_definition> Materials; // 0x1A4
	s_tag_reference MultiplayerGlobals; // 0x1B0
	s_tag_reference SurvivalGlobals; // 0x1C0
	c_tag_block<s_game_globals_cinematic_anchor> CinematicAnchors; // 0x1D0
	c_tag_block<s_campaign_metagame_globals> MetagameGlobals; // 0x1DC
	float Unknown61; // 0x1E8
	float Unknown62; // 0x1EC
	float Unknown63; // 0x1F0
	float Unknown64; // 0x1F4
	float Unknown65; // 0x1F8
	float Unknown66; // 0x1FC
	float Unknown67; // 0x200
	float Unknown68; // 0x204
	float Unknown69; // 0x208
	float Unknown70; // 0x20C
	float Unknown71; // 0x210
	float Unknown72; // 0x214
	float Unknown73; // 0x218
	float Unknown74; // 0x21C
	float Unknown75; // 0x220
	float Unknown76; // 0x224
	float Unknown77; // 0x228
	float Unknown78; // 0x22C
	float Unknown79; // 0x230
	float Unknown80; // 0x234
	float Unknown81; // 0x238
	float Unknown82; // 0x23C
	float Unknown83; // 0x240
	float Unknown84; // 0x244
	float Unknown85; // 0x248
	float Unknown86; // 0x24C
	float Unknown87; // 0x250
	float Unknown88; // 0x254
	float Unknown89; // 0x258
	float Unknown90; // 0x25C
	float Unknown91; // 0x260
	float Unknown92; // 0x264
	float Unknown93; // 0x268
	float Unknown94; // 0x26C
	float Unknown95; // 0x270
	float Unknown96; // 0x274
	float Unknown97; // 0x278
	float Unknown98; // 0x27C
	float Unknown99; // 0x280
	float Unknown100; // 0x284
	float Unknown101; // 0x288
	float Unknown102; // 0x28C
	float Unknown103; // 0x290
	float Unknown104; // 0x294
	float Unknown105; // 0x298
	float Unknown106; // 0x29C
	float Unknown107; // 0x2A0
	float Unknown108; // 0x2A4
	float Unknown109; // 0x2A8
	float Unknown110; // 0x2AC
	float Unknown111; // 0x2B0
	float Unknown112; // 0x2B4
	float Unknown113; // 0x2B8
	float Unknown114; // 0x2BC
	float Unknown115; // 0x2C0
	float Unknown116; // 0x2C4
	float Unknown117; // 0x2C8
	float Unknown118; // 0x2CC
	float Unknown119; // 0x2D0
	float Unknown120; // 0x2D4
	float Unknown121; // 0x2D8
	float Unknown122; // 0x2DC
	float Unknown123; // 0x2E0
	float Unknown124; // 0x2E4
	float Unknown125; // 0x2E8
	float Unknown126; // 0x2EC
	float Unknown127; // 0x2F0
	float Unknown128; // 0x2F4
	float Unknown129; // 0x2F8
	float Unknown130; // 0x2FC
	float Unknown131; // 0x300
	float Unknown132; // 0x304
	float Unknown133; // 0x308
	float Unknown134; // 0x30C
	float Unknown135; // 0x310
	float Unknown136; // 0x314
	float Unknown137; // 0x318
	float Unknown138; // 0x31C
	float Unknown139; // 0x320
	float Unknown140; // 0x324
	float Unknown141; // 0x328
	float Unknown142; // 0x32C
	float Unknown143; // 0x330
	float Unknown144; // 0x334
	float Unknown145; // 0x338
	float Unknown146; // 0x33C
	float Unknown147; // 0x340
	float Unknown148; // 0x344
	float Unknown149; // 0x348
	float Unknown150; // 0x34C
	float Unknown151; // 0x350
	float Unknown152; // 0x354
	float Unknown153; // 0x358
	float Unknown154; // 0x35C
	float Unknown155; // 0x360
	float Unknown156; // 0x364
	float Unknown157; // 0x368
	float Unknown158; // 0x36C
	float Unknown159; // 0x370
	float Unknown160; // 0x374
	float Unknown161; // 0x378
	float Unknown162; // 0x37C
	float Unknown163; // 0x380
	float Unknown164; // 0x384
	float Unknown165; // 0x388
	float Unknown166; // 0x38C
	float Unknown167; // 0x390
	float Unknown168; // 0x394
	float Unknown169; // 0x398
	float Unknown170; // 0x39C
	float Unknown171; // 0x3A0
	float Unknown172; // 0x3A4
	float Unknown173; // 0x3A8
	float Unknown174; // 0x3AC
	float Unknown175; // 0x3B0
	float Unknown176; // 0x3B4
	float Unknown177; // 0x3B8
	float Unknown178; // 0x3BC
	float Unknown179; // 0x3C0
	float Unknown180; // 0x3C4
	float Unknown181; // 0x3C8
	float Unknown182; // 0x3CC
	float Unknown183; // 0x3D0
	float Unknown184; // 0x3D4
	float Unknown185; // 0x3D8
	float Unknown186; // 0x3DC
	float Unknown187; // 0x3E0
	float Unknown188; // 0x3E4
	float Unknown189; // 0x3E8
	float Unknown190; // 0x3EC
	float Unknown191; // 0x3F0
	float Unknown192; // 0x3F4
	float Unknown193; // 0x3F8
	float Unknown194; // 0x3FC
	float Unknown195; // 0x400
	float Unknown196; // 0x404
	float Unknown197; // 0x408
	float Unknown198; // 0x40C
	float Unknown199; // 0x410
	float Unknown200; // 0x414
	float Unknown201; // 0x418
	float Unknown202; // 0x41C
	float Unknown203; // 0x420
	float Unknown204; // 0x424
	float Unknown205; // 0x428
	float Unknown206; // 0x42C
	float Unknown207; // 0x430
	float Unknown208; // 0x434
	float Unknown209; // 0x438
	float Unknown210; // 0x43C
	float Unknown211; // 0x440
	float Unknown212; // 0x444
	float Unknown213; // 0x448
	float Unknown214; // 0x44C
	float Unknown215; // 0x450
	float Unknown216; // 0x454
	float Unknown217; // 0x458
	float Unknown218; // 0x45C
	float Unknown219; // 0x460
	float Unknown220; // 0x464
	float Unknown221; // 0x468
	float Unknown222; // 0x46C
	float Unknown223; // 0x470
	float Unknown224; // 0x474
	float Unknown225; // 0x478
	float Unknown226; // 0x47C
	float Unknown227; // 0x480
	float Unknown228; // 0x484
	float Unknown229; // 0x488
	float Unknown230; // 0x48C
	float Unknown231; // 0x490
	float Unknown232; // 0x494
	float Unknown233; // 0x498
	float Unknown234; // 0x49C
	float Unknown235; // 0x4A0
	float Unknown236; // 0x4A4
	float Unknown237; // 0x4A8
	float Unknown238; // 0x4AC
	float Unknown239; // 0x4B0
	float Unknown240; // 0x4B4
	float Unknown241; // 0x4B8
	float Unknown242; // 0x4BC
	float Unknown243; // 0x4C0
	float Unknown244; // 0x4C4
	float Unknown245; // 0x4C8
	float Unknown246; // 0x4CC
	float Unknown247; // 0x4D0
	float Unknown248; // 0x4D4
	float Unknown249; // 0x4D8
	float Unknown250; // 0x4DC
	float Unknown251; // 0x4E0
	float Unknown252; // 0x4E4
	float Unknown253; // 0x4E8
	float Unknown254; // 0x4EC
	float Unknown255; // 0x4F0
	float Unknown256; // 0x4F4
	float Unknown257; // 0x4F8
	float Unknown258; // 0x4FC
	float Unknown259; // 0x500
	float Unknown260; // 0x504
	float Unknown261; // 0x508
	float Unknown262; // 0x50C
	float Unknown263; // 0x510
	float Unknown264; // 0x514
	s_tag_reference RasterizerGlobals; // 0x518
	s_tag_reference DefaultCameraEffect; // 0x528
	s_tag_reference PodiumDefinition; // 0x538
	s_tag_reference DefaultWind; // 0x548
	s_tag_reference DefaultDamageEffect; // 0x558
	s_tag_reference DefaultCollisionDamage; // 0x568
	unsigned long UnknownMaterial; // 0x578
	short UnknownGlobalMaterialIndex; // 0x57C
	short Unknown265; // 0x57E
	s_tag_reference EffectGlobals; // 0x580
	s_tag_reference GameProgressionGlobals; // 0x590
	s_tag_reference AchievementGlobals; // 0x5A0
	s_tag_reference InputGlobals; // 0x5B0
	float Unknown266; // 0x5C0
	float Unknown267; // 0x5C4
	float Unknown268; // 0x5C8
	float Unknown269; // 0x5CC
	s_tag_data Unknown270; // 0x5D0
	float Unknown271; // 0x5E4
	float Unknown272; // 0x5E8
	float Unknown273; // 0x5EC
	float Unknown274; // 0x5F0
	float Unknown275; // 0x5F4
	c_tag_block<s_game_globals_damage> DamageReportingTypes; // 0x5F8
	float Unknown276; // 0x604
	s_game_globals(s_game_globals &); /* compiler_generated() */
	s_game_globals(s_game_globals const &); /* compiler_generated() */
	s_game_globals(); /* compiler_generated() */
	s_game_globals &operator=(s_game_globals &); /* compiler_generated() */
	s_game_globals &operator=(s_game_globals const &); /* compiler_generated() */
};
static_assert(sizeof(s_game_globals) == 1544, "Invalid s_game_globals size");

/* ---------- prototypes */

extern s_game_globals *game_globals_get();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_GLOBALS_HPP__

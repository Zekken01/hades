# Where Release can behave differently from Debug

Release builds the same code as Debug, so the two only differ where the code depends on how it was compiled. This
list comes from a read-only review of the whole tree (ElDorito, blamlib and hades/), in which a second reviewer
re-checked every candidate. 20 places held up; 16 were ruled out. None of this affects Debug, and none of it is a
problem with the project files.

Almost all of them have the same cause. In Debug, `/RTC1` fills every local variable with `0xCC` bytes before
the function runs. That makes reads of variables the code never set deterministic, and usually harmless. Release
can't use `/RTC1` (it doesn't work with optimisation), so those reads see whatever an earlier function left on the
stack. The fixes are small source changes (usually `= {}` or checking a return value). They would also change the
Debug binary, so they belong in the tree, not in the build settings.

The review found none of the riskier patterns: inline assembly that relies on register contents, code that patches
or reads its own machine code, polling loops the optimiser could hoist, memory probes it could delete, or
incremental-link thunks.

## Normal play (could show up without anything going wrong)

- **Map list, at the end of every maps-folder scan**: `ElDorito/Source/Patches/Maps.cpp:363`. When the maps-folder enumeration ends, levels_enumerate_hook still processes file_reference even though find_files_next did not fill it. Debug's 0xCC fill made that a harmless no-op. In Release the stack slot can still hold the last file from the previous call, so the last .map/.campaign can be added twice, or garbage gets parsed. Skip the name/extension handling when find_files_next returns false.

- **Biped forced airborne (boots off the ground)**: `ElDorito/Source/Patches/BipedPatches.cpp:142`. The force-airborne motor request in biped_update_boots_off_the_ground fills only 3 of its 7 fields, so the flags word at offset 0, the second animation name and the interpolation time are random in Release instead of the constant 0xCC pattern Debug sent. Value-initialise it (`c_motor_request request{};`) so both builds send the same bytes.

- **Audio channel update**: `ElDorito/Source/Patches/Audio.cpp:900`. HALO_CHANNEL_Update passes the address of a 1-byte bool where FMOD writes a 4-byte FMOD_BOOL. Debug's stack-guard check should catch this. In Release the 3 extra bytes silently overwrite whatever /O2 placed next to the bool: padding, another local, or the saved frame pointer. Declare is_playing as FMOD_BOOL.

- **Saved content header (films, saved files)**: `blamlib/source/Blam/saved_games/content_blf.cpp:27`. The content-header constructor leaves most metadata fields unset (id, user id, size, campaign id, difficulty, insertion point, is_survival, map checksum, the rest of the strings), and the initialize hook copies a stack temporary of it into the game's chunk. In Debug those fields are always 0xCC. In Release they hold whatever was left on the stack. Any field the game does not overwrite afterwards (for example is_survival or the checksum) can change from call to call. To get the same result in both builds, zero the object first: memset `this` in the constructor, or zero the chunk in the hook.

- **Font loading result**: `ElDorito/Source/mods/font_package.cpp:293`. fonts_begin_loading_internal (which replaces game 0x5099A0) returns AL from ED's void font_load, called through a bool-returning pointer. Debug happens to return nonzero (a stack-address byte or a refcount). Release's inlined destructor leaves a different, possibly zero, value in AL. If any game caller checks this result, font loading could look failed in Release. Whether one does could not be checked from this tree.

- **`waitfor in_session` in command scripts**: `ElDorito/Source/CommandScript.cpp:287`. `waitfor in_session` stores a lambda that keeps a reference to a local variable (establishTime) of a function that has already returned, so every later check reads and maybe writes a dead stack slot. In Debug, that slot is usually refilled with 0xCC by the debug stack checks, so the script just resumes as soon as a session exists. In the optimised build, the slot holds whatever was left there. If it reads 0 on every tick, the script can stall forever. If it holds a timestamp-like value, the script can wait the wrong amount of time. If it reads 0 while it belongs to a live frame, the timestamp written into it corrupts a local or saved register. Fix: capture establishTime by value with a mutable lambda, or store it in a member.

## Only after an error, or with bad input

- **Map package that fails to open**: `ElDorito/Source/Patches/ModSync.cpp:1147`. If opening the map package fails, main_load_map_internal_hook still verifies and may use the uninitialised 13 KB header. Debug always saw 0xCC and continued with a fixed garbage header. Release sees leftover stack data and may abort or continue with random map_id/map_name. Return false as soon as cache_file_open_package fails.

- **Resource cache header that fails to read**: `ElDorito/Source/Patches/ModSync.cpp:1358`. When a resource-cache header read fails, cache_file_tag_resource_table_read still issues table reads using the unread headers. Debug's 0xCC values make that read fetch nothing. In Release, stale stack values can make it read real data past the end of the file_offsets buffer and corrupt memory. Stop the second loop at the last location whose header was read.

- **Malformed .pak with fewer than 5 sections**: `ElDorito/Source/mods/mod_package_cache.cpp:600`. A .pak whose section table lists fewer than 5 sections leaves some of c_mod_package::m_sections uninitialised for packages built on the stack. Debug sees 0xCC there and rejects the package consistently (always in the updater, and for the first package in enumeration). Release sees leftover stack data and may accept the package, or read metadata, tags or resources from arbitrary offsets. It needs a malformed package.

- **Empty or blank mod name sent by a server**: `ElDorito/Source/mods/mod_system.cpp:530`. For an empty or all-blank mod name (which a server can send), FormatFilename walks below the 32-byte buffer. Debug always hits the 0xCC guard byte and shows a CRT assert without writing anything. Release has no guard: usually the loop just stops, but if the byte below happens to be a whitespace value it is zeroed. That can silently corrupt a neighbouring local or a saved register in GetNewPackageFilename.

- **Font page requested while the font package is closed**: `ElDorito/Source/mods/font_package.cpp:212`. If a font page is requested while the font package file is not open, font_get_package_file_handle returns a check of an uninitialised handle. Debug always sees 0xCCCCCCCC and fails the read the same way each time. Release may skip the read, or queue it on a stale handle left on the stack from an earlier frame, which may now be closed or belong to another file, so glyphs may be missing or wrong. I could not confirm this state ever happens.

- **DirectInput keyboard lost (Input.DirectInput 1 only)**: `ElDorito/Source/Patches/Input.cpp:975`. With Input.DirectInput=1, if GetDeviceState fails the 256-byte key buffer is never written but is still read. Debug then shows every key held. Release shows stale or random key states (phantom or stuck keys). Check the HRESULT, re-Acquire on failure, or zero diKeys first.

- **`Weapon.Offset` on a weapon with no saved offset**: `ElDorito/Source/Patches/Weapon.cpp:412`. When a weapon type is looked up that has a default entry but no saved offset, GetWeaponByType creates a new entry without setting its offset. Debug always filled it with a huge obvious value (-4.3e8). The optimised build fills it with leftover stack bytes, so the offset shown, cached and saved to data/weapon_offsets JSON can be any value, including NaN, and differs between runs. Initialise it (`WeaponInfo newWeapon{};`) to get a zero offset.

## Cosmetic (logs, error text, display only)

- **Desync trace stack capture**: `ElDorito/Source/Patches/DeterminismDebugPatches.cpp:293`. The RNG trace's stack capture hard-codes a skip of 2 frames, assuming RecordRandomSeed is a separate frame. If /O2 inlines it into get_random_seed_address_hook, every logged stack in the desync trace is shifted by one and loses the game function that asked for the seed. Use __declspec(noinline) on RecordRandomSeed, or skip 1.

- **MSAA detection at start-up when the query times out**: `ElDorito/Source/Patches/render_postprocess_patches.cpp:224`. If the start-up MSAA detection query times out (100 ms) or fails, the pixel count is read without ever being set. Debug always read the 0xCCCC fill and got a fixed negative MSAA value. The optimised build reads leftover stack data, so the auto-exposure occlusion scaling on that machine can be off by an arbitrary amount. It cannot divide by zero, because 0 is mapped to 1. Initialise `non_occluded_pixels` to 0, or only compute msaa_level when GetData returned S_OK.

- **"Failed to create window" error box text**: `ElDorito/Source/Patches/Shell.cpp:257`. The 'failed to create window' error box never shows the real Windows error text: FormatMessage is told to allocate its own buffer but is given a char array, so the box shows junk. In Debug the junk was a predictable run of 'Ì' characters. In the optimised build it is random leftover stack bytes and may be empty or cut short. Harmless, because this only appears when window creation has already failed. The fix is to pass `(LPSTR)&ptr` and LocalFree it, or drop FORMAT_MESSAGE_ALLOCATE_BUFFER and pass sizeof(buffer).

- **Team designator with no game engine**: `blamlib/source/Blam/game/engine/game_engine.cpp:98`. game_engine_get_team_designator reads the engine's vtable before checking the engine for null. With a valid engine, both builds behave the same. With no engine (only reachable from the HaloScript player_get_local_team_designator path, which has no engine check of its own), Debug crashes. Release may instead return -1 if the optimiser moves the read after the check. Moving the vtable read inside the `if` makes the two builds match.

- **Server info JSON for an unknown mod**: `ElDorito/Source/Server/InfoServer.cpp:483`. If the session's mod hash is not in the package manager, the lookup result is ignored. The info-server JSON then prints name, author and version from fields of a stack s_entry that were never written. Debug prints a fixed 0xCC junk pattern, while Release prints whatever the stack held before, which could leak up to about 1 KB of old stack bytes. The reads always stop inside the struct at the zeroed std::string members of origin. The fix is to check the return value or zero-initialise the entry with `s_entry packageEntry = {};`.

- **Stats upload for an unknown mod**: `ElDorito/Source/Server/Stats.cpp:532`. If the current mod hash is not found in the package manager, the stats POST sends name, author and version from fields of a stack s_entry that were never written. Debug sends a fixed 0xCC pattern, and Release sends leftover stack bytes, which can leak a small amount of old stack data. Nothing reads past the struct, and the JSON is no worse formed than in Debug. Check the lookup result, or write `s_entry packageEntry = {};`.

- **Mod list "verified" / last-used for old mod_db.json records**: `ElDorito/Source/mods/mod_database.cpp:238`. When mod_db.json has a record without "verified" or "last_used", load() leaves those fields of the stack s_record uninitialised. Debug always gives the first such record verified=true and a fixed huge last-used time (0xCC fill). Release gives leftover stack data, so the 'verified' badge and last-used time in the mod list can change, and the next save() writes the new value back. It is display-only and needs an old or hand-edited database.

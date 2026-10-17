# Building Hades in Visual Studio

In Debug, `hades.sln` builds the same `mtndew.dll` as `build.py`, from Visual Studio or `msbuild`:

| Project | Output | What it is |
|---|---|---|
| `ElDorito` | `build\vs\<Config>\mtndew.dll` | the ElDewrito 0.7.2 mod DLL (also links blamlib's objects) |
| `blamlib` | `build\vs\<Config>\blamlib.lib` | the Blam engine code, compiled with blamlib's own flags |
| `CefProcess` | `build\vs\<Config>\custom_menu.exe` | the CEF helper process for the web UI. It is not part of Build Solution yet (see the end of this file), and `build.py` doesn't build it either |

All output and intermediate files go under `build\vs\`, which `.gitignore` already covers, so a build never touches
tracked files or `build.py`'s own `build\obj`.

## Configurations

- **Debug** is the one to use. It is what 0.7.2 shipped and what `build.py` builds. Every flag matches `build.py`,
  and every prebuilt library in `libs\` has a Debug build.
- **Release** is experimental. It compiles the same code and defines, with Debug's runtime (`/MTd`, `_DEBUG`) and the
  Debug builds of the libraries, using `/O2 /Ob2 /Oi /Gy /Zi /Zc:inline-`, and links with `/INCREMENTAL:NO /OPT:REF
  /OPT:NOICF`. It keeps frame pointers (`/Oy-`), `/GS` and blamlib's `/sdl`. It drops `/RTC1`, blamlib's `/JMC` and
  Edit and Continue (`/ZI`). The DLL is about 8.6 MB instead of 15.6 MB.
  - Dropping `/RTC1` matters. In Debug every local variable starts out as `0xCC` bytes; in Release it holds whatever
    was on the stack. The recovered code reads uninitialised locals in about 20 places, most of them on error
    paths or only cosmetic, and Release can behave differently there. `RELEASE-AUDIT.md`, next to this file, lists
    them. 0.7.2 never shipped an optimised DLL and the reconstructed code has only ever run as Debug,
    so if Release misbehaves in game, go back to Debug.
  - `/OPT:NOICF` keeps identical functions apart, because ElDewrito compares and patches function addresses.
  - `/Zc:inline-` keeps every inline function in the object files. The tree defines
    `c_enum<e_object_type,char>::operator e_object_type` inline in `cseries\enums.inl` but declares it as an ordinary
    function in `objects\objects.hpp`, so files that only see the header need a copy to link against, and an
    optimised build with `/Zc:inline` drops it.
- A classic Release build (`/MT`, `NDEBUG`) doesn't compile. The tree's classes are laid out for the Debug standard
  library, whose containers are bigger than the Release ones, so dozens of size checks fail (`CHttpHeaders`,
  `CForgeUndoManager`, `CommandMap` and others), and the recovered code calls `_wassert` directly, which only exists
  when asserts are on. Getting there needs changes to the tree's source, not to these project files.

## What you need

- Visual Studio 2022 (Community is fine) with the **Desktop development with C++** workload.
- From **Individual components**, add **MSVC v142 - VS 2019 C++ x64/x86 build tools (Latest)**. This is the 14.29
  toolset that `build.py` needs too.
- Windows 10 SDK **10.0.22621.0** (an Individual component). `build.py` and the original build used it, and the projects
  pick it when it's installed. Without it they fall back to the newest SDK you have, which changes the CRT code
  linked into `mtndew.dll`.

Every library is already in `libs\`.

## Build

1. Open `hades.sln`, pick **Debug | x86** (or **Release | x86**), and build the solution (Ctrl+Shift+B). Or, from a
   "Developer Command Prompt for VS 2022":

   ```
   msbuild hades.sln /m /p:Configuration=Debug /p:Platform=x86
   msbuild hades.sln /m /p:Configuration=Release /p:Platform=x86
   ```

2. When `mtndew.dll` links, it's copied to your ElDewrito folder (`N:\Halo\Eldewrito0_7_2\ElDewrito` by default)
   along with `mtndew.pdb`. Debug and Release both copy to the same place, so the game runs whichever you built
   last. Each of the two files is backed up once, as `mtndew.dll.original` and `mtndew.pdb.original`, the first time a
   build replaces it, so the backup holds whatever was in the folder at that moment. If you already copied a
   `build.py` DLL there, put the shipped one back before your first Visual Studio build. To go back to the shipped
   DLL, copy `mtndew.dll.original` over `mtndew.dll` and `mtndew.pdb.original` over `mtndew.pdb`. Close the game before building, or the copy fails.

3. Press F5 on `ElDorito` to start `eldorado.exe -launcher` from that folder with the debugger attached.

## Settings you can change

Create `Hades.user.props` next to `Hades.props`, or pass `/p:Name=Value` to msbuild. Reload the solution after
creating or editing it.

```xml
<Project>
  <PropertyGroup>
    <EldewritoDir>D:\Games\ElDewrito</EldewritoDir>      <!-- where mtndew.dll is copied, and F5 runs from -->
    <HadesLaunchArgs>-launcher -window</HadesLaunchArgs> <!-- eldorado.exe arguments for F5 -->
    <HadesDeploy>false</HadesDeploy>                     <!-- build only, copy nothing; F5 then runs the DLL already in the game folder -->
    <HadesDeployCustomMenu>true</HadesDeployCustomMenu>  <!-- also copy custom_menu.exe (off by default) -->
    <HadesToolset>v143</HadesToolset>                    <!-- VS 2022's own compiler; builds, but won't match -->
    <HadesWindowsSdk>10.0.26100.0</HadesWindowsSdk>      <!-- a different Windows SDK -->
  </PropertyGroup>
</Project>
```

`.gitignore` only covers `build/`. `Hades.user.props` isn't ignored, and neither is the `.vs\` folder Visual Studio
creates next to `hades.sln` or any `*.vcxproj.user` file it writes beside a project. To keep them out of `git status`
without changing `.gitignore`, add these lines to `.git\info\exclude`:

```
/.vs/
*.vcxproj.user
/Hades.user.props
```

If Visual Studio offers to retarget the projects to a newer toolset or SDK, say no. Retargeting rewrites the project
files and changes the build.

## Where the Debug settings come from

`ElDorito` and `blamlib` use `build.py`'s flags, which are the ones measured from the shipped binary:
`/W0 /MTd /Od /Ob0 /ZI /GS /RTC1 /EHsc /std:c++20 /permissive-`, with `/JMC /sdl` and `HADES_STRICT_GS` added for
blamlib. They use exactly `build.py`'s defines (including `MATCHING`), its include order, and the same Windows SDK.
They also use the same libraries, delay-loads (`libcef.dll`, `dbghelp.dll`), resources and `/NODEFAULTLIB`. Like
`build.py`, the link uses a copy of `libcef_dll_wrapper.lib` patched to carry the CEF API hash of the libcef that
0.7.2 ships (see `Hades.targets`). Without the patch, libcef refuses to start.

Where `build.py` doesn't say, the projects follow the original link recorded in `mtndew.pdb`:
`/INCREMENTAL /SUBSYSTEM:CONSOLE /OPT:NOREF /DYNAMICBASE /NXCOMPAT /SAFESEH:NO`.

These differences from `build.py` remain:

- MSBuild adds `/Zc:inline`, `/Gm-`, `/FC` and `/diagnostics:column` by default, and the projects keep them. The
  original MSBuild build had them too. `/Zc:inline` only drops unreferenced inline functions from objects. It doesn't
  change any function's code.
- The DirectX import libraries are the ones the original linked, plus XInput and DirectSound, instead of every
  library in `libs\directx\lib.X86`.
- Objects compile into one shared PDB per project (MSBuild's default), not one PDB per object.

`CefProcess` isn't built by `build.py`. Its Debug configuration uses the original `custom_menu.exe` flags from
`custom_menu.pdb` (`/Zi /O2 /Ob0 /GR-`, `/SUBSYSTEM:WINDOWS /STACK:8194304 /LARGEADDRESSAWARE`, its compatibility
manifest). It adds the tree's include list, `MATCHING`, `/std:c++20` and `/permissive-`, because it includes
`hades/hades.h`.

`CefProcess` doesn't link yet, so Build Solution skips it. `CefProcess\Source\App.hpp` defines `App::AddRef`,
`Release`, `HasOneRef` and `HasAtLeastOneRef` outside the class as `_inline`, and `hades/reverse_engineering.h`
defines `_inline` as nothing. Both `App.cpp` and `main.cpp` include the header, so the link fails with LNK2005.
Once the tree marks them `inline` (or moves them into `App.cpp`), right-click `CefProcess` and choose Build, or add
it back to the solution's build in Configuration Manager. Until then, keep the `custom_menu.exe` that ships with 0.7.2.

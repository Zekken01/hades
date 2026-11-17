# Builds mtndew.dll from this tree, together with the libraries it links that come from the
# submodules under libs/src (libs/CMakeLists.txt) and the test tools under tools/.
#
#   cmake --preset default
#   cmake --build --preset default
#
# or without presets (from the repository root):
#
#   cmake -S . -B build -G "Visual Studio 17 2022" -A Win32 -T v142,host=x86
#   cmake --build build --config Debug
#
# host=x86 picks the 32-bit compiler (bin/Hostx86/x86), which the shipped binary was built
# with: the 64-bit one (CMake's default) emits different code for some compiler-generated
# functions, such as the array copy loops of a defaulted operator=.
#
# Needs Visual Studio 2022 with the MSVC v142 (14.29) x86 toolset and a Windows 10/11 SDK
# (10.0.22621.0, the one the matching build uses, when it is installed). Clone with
# --recursive, or the missing submodules are fetched when CMake configures. build/build.sln
# opens the whole tree in Visual Studio.
#
# Results, in the build directory:
#   mtndew.dll (.pdb, .map)        copy over mtndew.dll in an ElDewrito 0.7.2 install to run
#                                  it (tools/deploy_test.py does that)
#   ui-harness/ui-harness.exe      the UI host outside the game (tools/ui-harness)
#   voip-test/peer_test.exe        a libdatachannel loopback test (tools/voip-test)
#
# Flags (measured from the shipped binary, not chosen - changing them changes the code):
#   /Od /Ob0 /ZI /GS /RTC1 /MTd /std:c++20; blamlib also /JMC /sdl and strict GS.
# Link: dbghelp.dll is delay-loaded; Resources/mtndew.res holds the original's resources
# and manifest; Exports.cpp carries its export table. The UI is RmlUi + Lua, which replaced
# the CEF browser of the shipped binary.
cmake_minimum_required(VERSION 3.26)

# There is one configuration: the flags below are the ones the shipped binary was built with.
set(CMAKE_CONFIGURATION_TYPES Debug CACHE STRING "" FORCE)
# The Windows SDK the matching build uses, when it is installed.
if(NOT CMAKE_SYSTEM_VERSION AND EXISTS "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0")
	set(CMAKE_SYSTEM_VERSION 10.0.22621.0)
endif()

project(hades LANGUAGES CXX)

if(NOT CMAKE_GENERATOR MATCHES "^Visual Studio" OR NOT CMAKE_VS_PLATFORM_NAME STREQUAL "Win32"
		OR NOT MSVC_VERSION EQUAL 1929 OR NOT CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE STREQUAL "x86")
	message(FATAL_ERROR "configure with -G \"Visual Studio 17 2022\" -A Win32 -T v142,host=x86 "
		"(cmake --preset default) in a new build directory; this is ${CMAKE_GENERATOR}, platform "
		"${CMAKE_VS_PLATFORM_NAME}, MSVC ${MSVC_VERSION} (needs 1929, v142), compiler host "
		"'${CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE}' (needs x86)")
endif()

option(HADES_BUILD_TOOLS "Build tools/ui-harness and tools/voip-test" ON)
cmake_host_system_information(RESULT cores QUERY NUMBER_OF_LOGICAL_CORES)
math(EXPR half_cores "(${cores} + 1) / 2")
set(HADES_COMPILE_JOBS ${half_cores} CACHE STRING "cl.exe processes per target (/MP)")

# --- Flags ----------------------------------------------------------------------------
# These replace CMake's defaults instead of adding to them; see the header for where they
# come from.

set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDebug)          # /MTd
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT EditAndContinue)    # /ZI
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_FLAGS "/W0 /GS /EHsc /std:c++20 /permissive-")
set(CMAKE_CXX_FLAGS_DEBUG "/Od /Ob0 /RTC1")
foreach(kind SHARED EXE)
	set(CMAKE_${kind}_LINKER_FLAGS "/machine:X86")
	set(CMAKE_${kind}_LINKER_FLAGS_DEBUG "/DEBUG:FULL /INCREMENTAL")
endforeach()
set(CMAKE_CXX_STANDARD_LIBRARIES "")
# Keep a user-wide vcpkg integration (`vcpkg integrate install`) out of the projects: it
# adds its include and library directories and links every library installed there.
set(CMAKE_VS_GLOBALS VcpkgEnabled=false VCPkgLocalAppDataDisabled=true)

set(HADES_DEFINES
	_WINDOWS _USRDLL WIN32 _DEBUG MINIUPNP_STATICLIB NOMINMAX _CRT_SECURE_NO_WARNINGS
	_WINSOCK_DEPRECATED_NO_WARNINGS MATCHING RMLUI_STATIC_LIB LUNASVG_BUILD_STATIC RMLUI_LUA_AS_CXX
	RTC_STATIC RTC_ENABLE_WEBSOCKET=1 RTC_ENABLE_MEDIA=1)
set(HADES_INCLUDES
	. ElDorito/Source blamlib/source libs/boost-1.76/include libs/detours/include libs/directx/Include
	libs/discord-rpc/include libs/fmod/inc libs/miniupnpc/include libs/oggvorbis/include
	libs/openssl-1.1.0e/include libs/steam/Include libs/websocketpp/include libs/rmlui/include
	libs/lunasvg/include libs/lua-5.4/include libs/freetype/include/freetype2 libs/voip/include)
list(TRANSFORM HADES_INCLUDES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM HADES_INCLUDES REPLACE "/\\.$" "")

# Flags every target compiled from ElDorito/Source shares.
function(hades_target target)
	target_compile_definitions(${target} PRIVATE ${HADES_DEFINES})
	target_include_directories(${target} PRIVATE ${HADES_INCLUDES})
	target_compile_options(${target} PRIVATE /MP${HADES_COMPILE_JOBS})
	# Drops the defines MSBuild adds on its own (_WINDLL, _MBCS); see the file.
	set_target_properties(${target} PROPERTIES VS_USER_PROPS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hades.props")
endfunction()

# --- Libraries from the submodules (libs/CMakeLists.txt) -------------------------------

add_subdirectory(libs)

set(LIBS "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(UI_LIBS
	rmlui/lib/rmlui.lib rmlui/lib/rmlui_debugger.lib rmlui/lib/rmlui_lua.lib freetype/lib/freetyped.lib
	lua-5.4/lib/lua.lib lunasvg/lib/lunasvg.lib lunasvg/lib/plutovg.lib)
set(VOIP_LIBS
	voip/lib/datachannel.lib voip/lib/juice.lib voip/lib/usrsctp.lib voip/lib/srtp2.lib
	voip/lib/mbedtls.lib voip/lib/mbedx509.lib voip/lib/mbedcrypto.lib voip/lib/everest.lib
	voip/lib/p256m.lib voip/lib/opus.lib)
set(PREBUILT_LIBS
	detours/lib.X86/detours.lib discord-rpc/lib/Debug/discord-rpc.lib miniupnpc/lib/miniupnpc.lib
	oggvorbis/lib/Debug/ogg.lib oggvorbis/lib/Debug/vorbis.lib oggvorbis/lib/Debug/vorbisfile.lib
	openssl-1.1.0e/lib/libeay32MTd.lib openssl-1.1.0e/lib/ssleay32MTd.lib)
foreach(list UI_LIBS VOIP_LIBS PREBUILT_LIBS)
	list(TRANSFORM ${list} PREPEND "${LIBS}/")
endforeach()
file(GLOB DIRECTX_LIBS "${LIBS}/directx/lib.X86/*.lib")

# --- mtndew.dll ------------------------------------------------------------------------

file(GLOB_RECURSE ELDORITO_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ElDorito/Source/*.cpp")
file(GLOB_RECURSE BLAMLIB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/blamlib/source/*.cpp")
# The original blamlib was built under `#pragma strict_gs_check(on)` (hades.h turns it on for
# HADES_STRICT_GS) with /JMC and /sdl.
set_source_files_properties(${BLAMLIB_SOURCES} PROPERTIES
	COMPILE_OPTIONS "/JMC;/sdl"
	COMPILE_DEFINITIONS "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING;HADES_STRICT_GS")

add_library(mtndew SHARED ${ELDORITO_SOURCES} ${BLAMLIB_SOURCES})
hades_target(mtndew)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ELDORITO_SOURCES} ${BLAMLIB_SOURCES})
add_dependencies(mtndew hades_deps)
target_link_libraries(mtndew PRIVATE
	${PREBUILT_LIBS} ${UI_LIBS} ${VOIP_LIBS} ${DIRECTX_LIBS}
	kernel32 user32 gdi32 advapi32 shell32 ole32 oleaut32 uuid ws2_32 winhttp wininet iphlpapi psapi
	shlwapi crypt32 winmm dbghelp version comctl32 bcrypt urlmon synchronization dwmapi delayimp)
target_link_options(mtndew PRIVATE
	/SUBSYSTEM:WINDOWS /MAP /MANIFEST:NO /IGNORE:4099 /NODEFAULTLIB:libboost_date_time-vc142-mt-sgd-x32-1_76.lib
	/DELAYLOAD:dbghelp.dll "${CMAKE_CURRENT_SOURCE_DIR}/ElDorito/Source/Resources/mtndew.res")
set_property(TARGET mtndew APPEND PROPERTY LINK_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/ElDorito/Source/Resources/mtndew.res")
# build/mtndew.dll, not build/Debug/mtndew.dll ($<0:> keeps the configuration out of the path).
# DEFINE_SYMBOL "": no mtndew_EXPORTS define, which cl alone would not get either.
set_target_properties(mtndew PROPERTIES
	DEFINE_SYMBOL ""
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<0:>"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<0:>"
	PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<0:>")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT mtndew)

# --- Tools -----------------------------------------------------------------------------

if(HADES_BUILD_TOOLS)
	# The real UI host (Web/WebRenderer.cpp, Web/Rml/*, the bridge registry) outside the game,
	# with stand-ins for the game functions it calls.
	file(GLOB RML_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ElDorito/Source/Web/Rml/*.cpp")
	add_executable(ui-harness
		ElDorito/Source/Web/WebRenderer.cpp
		ElDorito/Source/Web/Bridge/WebRendererQueryHandler.cpp
		ElDorito/Source/Utils/Uri.cpp
		ElDorito/Source/Common/Http/HttpHeaders.cpp
		${RML_SOURCES}
		tools/ui-harness/harness_main.cpp
		tools/ui-harness/harness_stubs.cpp)
	hades_target(ui-harness)
	target_include_directories(ui-harness PRIVATE tools/ui-harness)
	add_dependencies(ui-harness hades_deps)
	target_link_libraries(ui-harness PRIVATE
		${UI_LIBS} "${LIBS}/directx/lib.X86/d3dx9.lib"
		kernel32 user32 gdi32 advapi32 shell32 ole32 psapi d3d9 dbghelp)
	target_link_options(ui-harness PRIVATE
		/SUBSYSTEM:CONSOLE /IGNORE:4099 /NODEFAULTLIB:libboost_date_time-vc142-mt-sgd-x32-1_76.lib)
	set_target_properties(ui-harness PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/ui-harness/$<0:>"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/ui-harness/$<0:>")

	# A two-peer libdatachannel loopback test of the VoIP libraries.
	add_executable(peer_test tools/voip-test/peer_test.cpp)
	target_compile_definitions(peer_test PRIVATE _DEBUG RTC_STATIC RTC_ENABLE_WEBSOCKET=1 RTC_ENABLE_MEDIA=1)
	target_include_directories(peer_test PRIVATE "${LIBS}/voip/include")
	add_dependencies(peer_test hades_deps)
	target_link_libraries(peer_test PRIVATE ${VOIP_LIBS} ws2_32 iphlpapi bcrypt advapi32)
	set_target_properties(peer_test PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/voip-test/$<0:>"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/voip-test/$<0:>")
endif()

# Builds the static x86 libraries mtndew.dll links that are not committed to libs/:
# the UI (Lua, FreeType, lunasvg, RmlUi) and native VoIP (mbedTLS, Opus, libdatachannel).
# Sources are the git submodules under libs/src; libs/patches holds this tree's changes to
# them, applied to a copy. build.py runs this; by hand (from the repository root):
#
#   cmake -S libs -B build/deps -G "Visual Studio 17 2022" -A Win32 -T v142
#   cmake --build build/deps --config Debug --parallel
#
# Everything uses the MultiThreadedDebug CRT, which is what build.py compiles mtndew.dll
# with (/MTd, _DEBUG, _ITERATOR_DEBUG_LEVEL=2); a lib built with another CRT fails to link
# with LNK2038. Optimisation is on (/O2) because the UI runs in a debug game build; debug
# info is embedded (/Z7) so no .pdb files travel with the .lib files.
#
# Results (git-ignored), at the paths build.py links from:
#   libs/lua-5.4    lua.lib (Lua compiled as C++, so lua_error unwinds as a C++ exception)
#   libs/freetype   freetyped.lib (internal zlib, so WOFF works; no png/bzip2/harfbuzz/brotli)
#   libs/lunasvg    lunasvg.lib, plutovg.lib (RmlUi's SVG plugin)
#   libs/rmlui      rmlui.lib (with the SVG plugin), rmlui_debugger.lib, rmlui_lua.lib
#   libs/voip       mbedTLS (DTLS-SRTP on), opus.lib, datachannel.lib and its deps
cmake_minimum_required(VERSION 3.20)
project(hades_deps NONE)

include(ExternalProject)

if(NOT CMAKE_GENERATOR MATCHES "Visual Studio" OR NOT CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
	message(FATAL_ERROR "configure with -G \"Visual Studio 17 2022\" -A Win32 -T v142")
endif()

set(HADES_LIBS "${CMAKE_CURRENT_SOURCE_DIR}")
set(DEP_SRC "${HADES_LIBS}/src")
set(PATCHES "${HADES_LIBS}/patches")
set(LUA_PREFIX "${HADES_LIBS}/lua-5.4")
set(FREETYPE_PREFIX "${HADES_LIBS}/freetype")
set(LUNASVG_PREFIX "${HADES_LIBS}/lunasvg")
set(RMLUI_PREFIX "${HADES_LIBS}/rmlui")
set(VOIP_PREFIX "${HADES_LIBS}/voip")

foreach(dep lua freetype lunasvg rmlui mbedtls opus libdatachannel)
	if(NOT EXISTS "${DEP_SRC}/${dep}/CMakeLists.txt" AND NOT EXISTS "${DEP_SRC}/${dep}/lua.h")
		message(FATAL_ERROR "libs/src/${dep} is empty; run: git submodule update --init --recursive")
	endif()
endforeach()

# ExternalProject reuses this project's generator, platform (Win32) and toolset (v142).
set(COMMON_ARGS
	-DCMAKE_POLICY_DEFAULT_CMP0091=NEW
	-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug
	-DBUILD_SHARED_LIBS=OFF
	-DCMAKE_POLICY_VERSION_MINIMUM=3.5
	-DCMAKE_BUILD_TYPE=Debug
	"-DCMAKE_C_FLAGS_DEBUG=/Z7 /O2 /Ob1"
	"-DCMAKE_CXX_FLAGS_DEBUG=/Z7 /O2 /Ob1")

# A dependency built straight from its submodule.
function(hades_dep name)
	cmake_parse_arguments(arg "" "SOURCE;PREFIX" "ARGS;DEPENDS" ${ARGN})
	ExternalProject_Add(${name}
		SOURCE_DIR "${arg_SOURCE}"
		DOWNLOAD_COMMAND ""
		UPDATE_COMMAND ""
		INSTALL_DIR "${arg_PREFIX}"
		LIST_SEPARATOR |
		CMAKE_ARGS ${COMMON_ARGS} "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>" ${arg_ARGS}
		DEPENDS ${arg_DEPENDS})
endfunction()

# A dependency built from a patched copy of its submodule (libs/patches/<name>.patch).
function(hades_patched_dep name)
	cmake_parse_arguments(arg "" "PREFIX" "ARGS;DEPENDS" ${ARGN})
	ExternalProject_Add(${name}
		SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/${name}"
		DOWNLOAD_COMMAND "${CMAKE_COMMAND}" "-DSOURCE=${DEP_SRC}/${name}" "-DDEST=<SOURCE_DIR>"
			"-DPATCH=${PATCHES}/${name}.patch" -P "${HADES_LIBS}/cmake/copy_and_patch.cmake"
		UPDATE_COMMAND ""
		INSTALL_DIR "${arg_PREFIX}"
		LIST_SEPARATOR |
		CMAKE_ARGS ${COMMON_ARGS} "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>" ${arg_ARGS}
		DEPENDS ${arg_DEPENDS})
	ExternalProject_Add_StepDependencies(${name} download "${PATCHES}/${name}.patch")
endfunction()

# --- UI -------------------------------------------------------------------------------

hades_dep(lua SOURCE "${HADES_LIBS}/cmake/lua" PREFIX "${LUA_PREFIX}"
	ARGS "-DLUA_SOURCE_DIR=${DEP_SRC}/lua")

hades_dep(freetype SOURCE "${DEP_SRC}/freetype" PREFIX "${FREETYPE_PREFIX}"
	ARGS -DFT_DISABLE_ZLIB=ON -DFT_DISABLE_BZIP2=ON -DFT_DISABLE_PNG=ON
		-DFT_DISABLE_HARFBUZZ=ON -DFT_DISABLE_BROTLI=ON)

# lunasvg (with its plutovg submodule) backs RmlUi's SVG plugin: <svg src> and decorator: svg().
hades_patched_dep(lunasvg PREFIX "${LUNASVG_PREFIX}"
	ARGS -DLUNASVG_BUILD_EXAMPLES=OFF -DLUNASVG_DISABLE_LOAD_SYSTEM_FONTS=ON -DUSE_SYSTEM_PLUTOVG=OFF)

hades_patched_dep(rmlui PREFIX "${RMLUI_PREFIX}"
	ARGS "-DCMAKE_PROJECT_INCLUDE=${HADES_LIBS}/cmake/find_threads.cmake"
		"-DCMAKE_PREFIX_PATH=${FREETYPE_PREFIX}|${LUNASVG_PREFIX}"
		"-DLUA_INCLUDE_DIR=${LUA_PREFIX}/include"
		"-DLUA_LIBRARY=${LUA_PREFIX}/lib/lua.lib"
		"-DLUA_LIBRARIES=${LUA_PREFIX}/lib/lua.lib"
		-DRMLUI_LUA_BINDINGS=ON -DRMLUI_LUA_BINDINGS_LIBRARY=lua_as_cxx
		-DRMLUI_FONT_ENGINE=freetype -DRMLUI_SAMPLES=OFF -DRMLUI_PRECOMPILED_HEADERS=OFF
		-DRMLUI_SVG_PLUGIN=ON -DCMAKE_CXX_STANDARD=20
	DEPENDS lua freetype lunasvg)

# --- VoIP -----------------------------------------------------------------------------

# mbedtls.patch turns on MBEDTLS_SSL_DTLS_SRTP, which libdatachannel's media transport needs.
hades_patched_dep(mbedtls PREFIX "${VOIP_PREFIX}"
	ARGS -DENABLE_PROGRAMS=OFF -DENABLE_TESTING=OFF -DMBEDTLS_FATAL_WARNINGS=OFF)

# opus picks its CRT from OPUS_STATIC_RUNTIME, not CMAKE_MSVC_RUNTIME_LIBRARY.
hades_dep(opus SOURCE "${DEP_SRC}/opus" PREFIX "${VOIP_PREFIX}"
	ARGS -DOPUS_BUILD_PROGRAMS=OFF -DOPUS_BUILD_TESTING=OFF -DOPUS_INSTALL_PKG_CONFIG_MODULE=OFF
		-DOPUS_STATIC_RUNTIME=ON)

hades_dep(libdatachannel SOURCE "${DEP_SRC}/libdatachannel" PREFIX "${VOIP_PREFIX}"
	ARGS -DUSE_MBEDTLS=ON -DUSE_NICE=OFF -DNO_EXAMPLES=ON -DNO_TESTS=ON
		"-DCMAKE_PREFIX_PATH=${VOIP_PREFIX}" "-DMbedTLS_ROOT=${VOIP_PREFIX}" -DCMAKE_CXX_STANDARD=20
	DEPENDS mbedtls)

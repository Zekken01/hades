# Builds the static x86 libraries mtndew.dll links that are not committed to libs/:
# the UI (Lua, FreeType, lunasvg, RmlUi) and native VoIP (mbedTLS, Opus, libdatachannel).
# Sources are the git submodules under libs/src; libs/patches holds this tree's changes to
# them, applied to a copy. The top-level CMakeLists.txt includes this directory, and its
# targets depend on hades_deps, so building the tree builds these first. It also builds on
# its own (from the repository root):
#
#   cmake -S libs -B build/deps -G "Visual Studio 17 2022" -A Win32 -T v142
#   cmake --build build/deps --config Debug --parallel
#
# Everything uses the MultiThreadedDebug CRT, which is what mtndew.dll is compiled with
# (/MTd, _DEBUG, _ITERATOR_DEBUG_LEVEL=2); a lib built with another CRT fails to link
# with LNK2038. Optimisation is on (/O2) because the UI runs in a debug game build; debug
# info is embedded (/Z7) so no .pdb files travel with the .lib files.
#
# Results (git-ignored), at the paths mtndew.dll links from:
#   libs/lua-5.4    lua.lib (Lua compiled as C++, so lua_error unwinds as a C++ exception)
#   libs/freetype   freetyped.lib (internal zlib, so WOFF works; no png/bzip2/harfbuzz/brotli)
#   libs/lunasvg    lunasvg.lib, plutovg.lib (RmlUi's SVG plugin)
#   libs/rmlui      rmlui.lib (with the SVG plugin), rmlui_debugger.lib, rmlui_lua.lib
#   libs/voip       mbedTLS (DTLS-SRTP on), opus.lib, datachannel.lib and its deps
#
# A dependency is built again when its submodule moves to another commit, its patch or
# its arguments here change, or one of its installed files is deleted.
cmake_minimum_required(VERSION 3.26)
project(hades_deps NONE)

include(ExternalProject)
find_package(Git REQUIRED)

if(NOT CMAKE_GENERATOR MATCHES "Visual Studio" OR NOT CMAKE_VS_PLATFORM_NAME STREQUAL "Win32")
	message(FATAL_ERROR "configure with -G \"Visual Studio 17 2022\" -A Win32 -T v142")
endif()

set(HADES_LIBS "${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(REPO "${HADES_LIBS}" DIRECTORY)
set(DEP_SRC "${HADES_LIBS}/src")
set(PATCHES "${HADES_LIBS}/patches")
set(LUA_PREFIX "${HADES_LIBS}/lua-5.4")
set(FREETYPE_PREFIX "${HADES_LIBS}/freetype")
set(LUNASVG_PREFIX "${HADES_LIBS}/lunasvg")
set(RMLUI_PREFIX "${HADES_LIBS}/rmlui")
set(VOIP_PREFIX "${HADES_LIBS}/voip")
set(DEPS lua freetype lunasvg rmlui mbedtls opus libdatachannel)

# --- Submodules -----------------------------------------------------------------------

function(submodule_status out)
	execute_process(COMMAND "${GIT_EXECUTABLE}" submodule status --recursive libs/src
		WORKING_DIRECTORY "${REPO}" OUTPUT_VARIABLE status RESULT_VARIABLE result)
	if(NOT result EQUAL 0)
		message(FATAL_ERROR "git submodule status failed in ${REPO}")
	endif()
	set(${out} "${status}" PARENT_SCOPE)
endfunction()

submodule_status(status)
if(status MATCHES "(^|\n)-")  # a submodule is not checked out (a clone made without --recursive)
	message(STATUS "Fetching the submodules under libs/src")
	# core.longpaths: libdatachannel's nested nlohmann/json has test files past MAX_PATH.
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" -c core.longpaths=true submodule update --init --recursive --depth 1 libs/src
		WORKING_DIRECTORY "${REPO}" RESULT_VARIABLE result)
	if(NOT result EQUAL 0)
		message(FATAL_ERROR "could not fetch the submodules; run: git submodule update --init --recursive")
	endif()
	submodule_status(status)
endif()
foreach(dep IN LISTS DEPS)
	if(NOT EXISTS "${DEP_SRC}/${dep}/CMakeLists.txt" AND NOT EXISTS "${DEP_SRC}/${dep}/lua.h")
		message(FATAL_ERROR "libs/src/${dep} is empty; run: git submodule update --init --recursive")
	endif()
endforeach()

# ExternalProject does not notice a submodule moving to another commit. Each dependency's
# commits (its submodule's and the nested ones') go in build/.../<dep>.commits, which its
# steps depend on; the file changes only when a commit does. CMake configures again when a
# submodule's HEAD moves, which rewrites these files.
string(REPLACE "\n" ";" status "${status}")
foreach(dep IN LISTS DEPS)
	set(commits "")
	foreach(line IN LISTS status)
		if(line MATCHES "^.([0-9a-f]+) (libs/src/${dep}(/[^ ]*)?)( |$)")
			string(APPEND commits "${CMAKE_MATCH_1} ${CMAKE_MATCH_2}\n")
		endif()
	endforeach()
	set(file "${CMAKE_CURRENT_BINARY_DIR}/${dep}.commits")
	set(old "")
	if(EXISTS "${file}")
		file(READ "${file}" old)
	endif()
	if(NOT old STREQUAL commits)
		file(WRITE "${file}" "${commits}")
	endif()
endforeach()
execute_process(COMMAND "${GIT_EXECUTABLE}" submodule foreach --recursive --quiet "git rev-parse --absolute-git-dir"
	WORKING_DIRECTORY "${REPO}" OUTPUT_VARIABLE git_dirs OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REPLACE "\n" ";" git_dirs "${git_dirs}")
foreach(dir IN LISTS git_dirs)
	set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${dir}/HEAD")
endforeach()

# --- Dependencies ---------------------------------------------------------------------

# Every dependency builds with this project's generator for Win32 and the v142 toolset, with
# CMake's default 64-bit compiler host even when mtndew.dll is configured with host=x86.
set(COMMON_ARGS
	-DCMAKE_POLICY_DEFAULT_CMP0091=NEW
	-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug
	-DBUILD_SHARED_LIBS=OFF
	-DCMAKE_POLICY_VERSION_MINIMUM=3.5
	-DCMAKE_BUILD_TYPE=Debug
	# Keeps a user-wide vcpkg integration's include and library directories out.
	"-DCMAKE_VS_GLOBALS=VcpkgEnabled=false|VCPkgLocalAppDataDisabled=true"
	"-DCMAKE_C_FLAGS_DEBUG=/Z7 /O2 /Ob1"
	"-DCMAKE_CXX_FLAGS_DEBUG=/Z7 /O2 /Ob1")

# MSBuild does not run a step again because a file it produced is gone. hades_deps_check
# runs before the dependencies build and deletes the install stamp of each one that lost
# an installed file (see OUTPUTS below), so its install step runs again.
function(hades_check_installed name)
	ExternalProject_Get_Property(${name} STAMP_DIR)
	string(REPLACE ";" "\" \"" files "${ARGN}")
	set_property(GLOBAL APPEND_STRING PROPERTY HADES_INSTALL_CHECKS
		"check(${name} \"${STAMP_DIR}\" \"${files}\")
")
endfunction()

# A dependency built straight from its submodule (or, with SOURCE, from a CMake project
# under libs/cmake that builds it). OUTPUTS are installed files, relative to PREFIX; one
# that is missing installs the dependency again.
function(hades_dep name)
	cmake_parse_arguments(arg "" "SOURCE;PREFIX" "ARGS;DEPENDS;OUTPUTS" ${ARGN})
	if(NOT arg_SOURCE)
		set(arg_SOURCE "${DEP_SRC}/${name}")
	endif()
	list(TRANSFORM arg_OUTPUTS PREPEND "${arg_PREFIX}/")
	ExternalProject_Add(${name}
		CMAKE_GENERATOR "${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_PLATFORM Win32
		CMAKE_GENERATOR_TOOLSET v142
		SOURCE_DIR "${arg_SOURCE}"
		DOWNLOAD_COMMAND ""
		UPDATE_COMMAND ""
		INSTALL_DIR "${arg_PREFIX}"
		LIST_SEPARATOR |
		CMAKE_ARGS ${COMMON_ARGS} "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>" ${arg_ARGS}
		BUILD_COMMAND "${CMAKE_COMMAND}" --build <BINARY_DIR> --config $<CONFIG> --parallel
		DEPENDS ${arg_DEPENDS})
	ExternalProject_Add_StepDependencies(${name} configure "${CMAKE_CURRENT_BINARY_DIR}/${name}.commits")
	hades_check_installed(${name} ${arg_OUTPUTS})
endfunction()

# A dependency built from a patched copy of its submodule (libs/patches/<name>.patch).
function(hades_patched_dep name)
	cmake_parse_arguments(arg "" "PREFIX" "ARGS;DEPENDS;OUTPUTS" ${ARGN})
	list(TRANSFORM arg_OUTPUTS PREPEND "${arg_PREFIX}/")
	ExternalProject_Add(${name}
		CMAKE_GENERATOR "${CMAKE_GENERATOR}"
		CMAKE_GENERATOR_PLATFORM Win32
		CMAKE_GENERATOR_TOOLSET v142
		SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/${name}"
		DOWNLOAD_COMMAND "${CMAKE_COMMAND}" "-DSOURCE=${DEP_SRC}/${name}" "-DDEST=<SOURCE_DIR>"
			"-DPATCH=${PATCHES}/${name}.patch" -P "${HADES_LIBS}/cmake/copy_and_patch.cmake"
		UPDATE_COMMAND ""
		INSTALL_DIR "${arg_PREFIX}"
		LIST_SEPARATOR |
		CMAKE_ARGS ${COMMON_ARGS} "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>" ${arg_ARGS}
		BUILD_COMMAND "${CMAKE_COMMAND}" --build <BINARY_DIR> --config $<CONFIG> --parallel
		DEPENDS ${arg_DEPENDS})
	ExternalProject_Add_StepDependencies(${name} download
		"${PATCHES}/${name}.patch" "${CMAKE_CURRENT_BINARY_DIR}/${name}.commits")
	hades_check_installed(${name} ${arg_OUTPUTS})
endfunction()

# --- UI -------------------------------------------------------------------------------

hades_dep(lua SOURCE "${HADES_LIBS}/cmake/lua" PREFIX "${LUA_PREFIX}"
	ARGS "-DLUA_SOURCE_DIR=${DEP_SRC}/lua"
	OUTPUTS lib/lua.lib include/lua.h)
ExternalProject_Add_StepDependencies(lua configure "${HADES_LIBS}/cmake/lua/CMakeLists.txt")

hades_dep(freetype PREFIX "${FREETYPE_PREFIX}"
	ARGS -DFT_DISABLE_ZLIB=ON -DFT_DISABLE_BZIP2=ON -DFT_DISABLE_PNG=ON
		-DFT_DISABLE_HARFBUZZ=ON -DFT_DISABLE_BROTLI=ON
	OUTPUTS lib/freetyped.lib include/freetype2/ft2build.h)

# lunasvg (with its plutovg submodule) backs RmlUi's SVG plugin: <svg src> and decorator: svg().
hades_patched_dep(lunasvg PREFIX "${LUNASVG_PREFIX}"
	ARGS -DLUNASVG_BUILD_EXAMPLES=OFF -DLUNASVG_DISABLE_LOAD_SYSTEM_FONTS=ON -DUSE_SYSTEM_PLUTOVG=OFF
	OUTPUTS lib/lunasvg.lib lib/plutovg.lib include/lunasvg/lunasvg.h)

hades_patched_dep(rmlui PREFIX "${RMLUI_PREFIX}"
	ARGS "-DCMAKE_PROJECT_INCLUDE=${HADES_LIBS}/cmake/find_threads.cmake"
		"-DCMAKE_PREFIX_PATH=${FREETYPE_PREFIX}|${LUNASVG_PREFIX}"
		"-DLUA_INCLUDE_DIR=${LUA_PREFIX}/include"
		"-DLUA_LIBRARY=${LUA_PREFIX}/lib/lua.lib"
		"-DLUA_LIBRARIES=${LUA_PREFIX}/lib/lua.lib"
		-DRMLUI_LUA_BINDINGS=ON -DRMLUI_LUA_BINDINGS_LIBRARY=lua_as_cxx
		-DRMLUI_FONT_ENGINE=freetype -DRMLUI_SAMPLES=OFF -DRMLUI_PRECOMPILED_HEADERS=OFF
		-DRMLUI_SVG_PLUGIN=ON -DCMAKE_CXX_STANDARD=20
	DEPENDS lua freetype lunasvg
	OUTPUTS lib/rmlui.lib lib/rmlui_debugger.lib lib/rmlui_lua.lib include/RmlUi/Core.h)

# --- VoIP -----------------------------------------------------------------------------

# mbedtls.patch turns on MBEDTLS_SSL_DTLS_SRTP, which libdatachannel's media transport needs.
hades_patched_dep(mbedtls PREFIX "${VOIP_PREFIX}"
	ARGS -DENABLE_PROGRAMS=OFF -DENABLE_TESTING=OFF -DMBEDTLS_FATAL_WARNINGS=OFF
	OUTPUTS lib/mbedtls.lib lib/mbedx509.lib lib/mbedcrypto.lib lib/everest.lib lib/p256m.lib
		include/mbedtls/ssl.h)

# opus picks its CRT from OPUS_STATIC_RUNTIME, not CMAKE_MSVC_RUNTIME_LIBRARY.
hades_dep(opus PREFIX "${VOIP_PREFIX}"
	ARGS -DOPUS_BUILD_PROGRAMS=OFF -DOPUS_BUILD_TESTING=OFF -DOPUS_INSTALL_PKG_CONFIG_MODULE=OFF
		-DOPUS_STATIC_RUNTIME=ON
	OUTPUTS lib/opus.lib include/opus/opus.h)

hades_dep(libdatachannel PREFIX "${VOIP_PREFIX}"
	ARGS -DUSE_MBEDTLS=ON -DUSE_NICE=OFF -DNO_EXAMPLES=ON -DNO_TESTS=ON
		"-DCMAKE_PREFIX_PATH=${VOIP_PREFIX}" "-DMbedTLS_ROOT=${VOIP_PREFIX}" -DCMAKE_CXX_STANDARD=20
	DEPENDS mbedtls
	OUTPUTS lib/datachannel.lib lib/juice.lib lib/usrsctp.lib lib/srtp2.lib include/rtc/rtc.hpp)

get_property(checks GLOBAL PROPERTY HADES_INSTALL_CHECKS)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/check_installed.cmake" [[
function(check name stamp_dir)
	foreach(file IN LISTS ARGN)
		if(NOT EXISTS "${file}")
			file(GLOB stamps "${stamp_dir}/${name}-install" "${stamp_dir}/*/${name}-install")
			if(stamps)
				message(STATUS "${file} is missing; installing ${name} again")
				file(REMOVE ${stamps})
			endif()
			return()
		endif()
	endforeach()
endfunction()
]] "${checks}")
add_custom_target(hades_deps_check
	COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/check_installed.cmake" VERBATIM)
foreach(dep IN LISTS DEPS)
	add_dependencies(${dep} hades_deps_check)
endforeach()

# What the targets that link these libraries depend on.
add_custom_target(hades_deps)
add_dependencies(hades_deps ${DEPS})

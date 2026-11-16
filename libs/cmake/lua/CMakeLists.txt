# Lua 5.4 as a static library compiled as C++, so lua_error unwinds as a C++ exception
# through the UI bridge functions instead of longjmp-ing over their destructors.
cmake_minimum_required(VERSION 3.20)
project(lua_as_cxx CXX)

if(NOT LUA_SOURCE_DIR)
	message(FATAL_ERROR "LUA_SOURCE_DIR is not set")
endif()

file(GLOB lua_sources "${LUA_SOURCE_DIR}/*.c")
# Stand-alone interpreter/compiler, the amalgamation and the test hooks are not library code.
list(FILTER lua_sources EXCLUDE REGEX "/(lua|luac|onelua|ltests)\.c$")
set_source_files_properties(${lua_sources} PROPERTIES LANGUAGE CXX)

add_library(lua STATIC ${lua_sources})
target_compile_options(lua PRIVATE /EHsc /W0)

install(TARGETS lua ARCHIVE DESTINATION lib)
install(FILES
	"${LUA_SOURCE_DIR}/lua.h" "${LUA_SOURCE_DIR}/luaconf.h"
	"${LUA_SOURCE_DIR}/lualib.h" "${LUA_SOURCE_DIR}/lauxlib.h"
	DESTINATION include)

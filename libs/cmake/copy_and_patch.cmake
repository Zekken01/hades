# cmake -DSOURCE=<submodule> -DDEST=<copy> -DPATCH=<file.patch> -P copy_and_patch.cmake
#
# Copies a submodule's work tree and applies one of libs/patches/ to the copy, so the
# submodule itself stays clean (a patched submodule blocks `git submodule update`).
foreach(var SOURCE DEST PATCH)
	if(NOT ${var})
		message(FATAL_ERROR "${var} is not set")
	endif()
endforeach()
if(NOT EXISTS "${SOURCE}/.git")
	message(FATAL_ERROR "${SOURCE} is empty; run: git submodule update --init --recursive")
endif()

file(REMOVE_RECURSE "${DEST}")
file(COPY "${SOURCE}/" DESTINATION "${DEST}" PATTERN ".git" EXCLUDE)

find_package(Git REQUIRED)
# The copy lies inside this repository's work tree; the ceiling keeps git from finding
# that repository, so it applies the patch to plain files relative to DEST.
get_filename_component(parent "${DEST}" DIRECTORY)
# --ignore-whitespace: the patches are LF, a checkout made with core.autocrlf is CRLF.
execute_process(
	COMMAND "${CMAKE_COMMAND}" -E env "GIT_CEILING_DIRECTORIES=${parent}"
		"${GIT_EXECUTABLE}" apply --ignore-whitespace --whitespace=nowarn "${PATCH}"
	WORKING_DIRECTORY "${DEST}"
	RESULT_VARIABLE result)
if(NOT result EQUAL 0)
	message(FATAL_ERROR "could not apply ${PATCH} to ${DEST}")
endif()

cmake_minimum_required(VERSION 3.0)

project(deps)

option(DEPS_DOWNLOAD "" ON)
option(DEPS_BUILD "" ON)
option(DEPS_CRT_STATIC "" OFF)

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(BLDDIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")
set(DSTDIR "${CMAKE_CURRENT_BINARY_DIR}/out")

add_custom_target(deps)

if(DEPS_DOWNLOAD)
	message("preparing deps...")
	file(REMOVE_RECURSE ${SRCDIR})
	file(MAKE_DIRECTORY ${SRCDIR})

	file(GLOB SUB "prepare-*.cmake")
	foreach(ITEM ${SUB})
		message(" > processing: ${ITEM}")
		string(REGEX REPLACE ".*prepare-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
		message(" > prepare: ${BASENAME}")
		include(${ITEM})
	endforeach()

	set(DEPS_DOWNLOAD OFF CACHE BOOL "")
endif()

if(DEPS_BUILD)
	message("processing deps...")
	file(MAKE_DIRECTORY ${BLDDIR})

	file(GLOB SUB "build-*.cmake")
	foreach(ITEM ${SUB})
		message(" processing: ${ITEM}")
		string(REGEX REPLACE ".*build-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
		message(" > build: ${BASENAME}")
		include(${ITEM})
	endforeach()

	file(GLOB SUB "depend-*.cmake")
	foreach(ITEM ${SUB})
		message(" processing: ${ITEM}")
		string(REGEX REPLACE ".*depend-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
		message(" > dep: ${BASENAME}")
		include(${ITEM})
	endforeach()

	set(DEPS_BUILD OFF CACHE BOOL "")
endif()



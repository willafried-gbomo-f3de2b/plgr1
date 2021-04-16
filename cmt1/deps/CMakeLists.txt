cmake_minimum_required(VERSION 3.0)

project(deps)

option(DEPS_DOWNLOAD "" ON)
option(DEPS_BUILD "" ON)
option(CRT_STATIC "" OFF)

include(GNUInstallDirs)

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(BLDDIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")
set(DSTDIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out")
set(CPYDIR "${CMAKE_CURRENT_BINARY_DIR}/out")

message("CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("ARCH: ${ARCH}")

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

	# set(DEPS_BUILD OFF CACHE BOOL "")

	add_custom_command(TARGET deps
		COMMAND ${CMAKE_COMMAND} -E echo "copying dep files..."
    	COMMAND ${CMAKE_COMMAND} -D CPYDIR="${CPYDIR}" -D DSTDIR="${DSTDIR}" -D CONFIG=$<CONFIG> -P "${CMAKE_CURRENT_SOURCE_DIR}/copy-deps.cmake"
    	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)
endif()



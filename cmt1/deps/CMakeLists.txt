cmake_minimum_required(VERSION 3.0)

project(deps)

option(DEPS_DOWNLOAD "" ON)

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(BLDDIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")

add_custom_target(deps)

if(DEPS_DOWNLOAD)
	file(REMOVE_RECURSE ${SRCDIR})
	file(MAKE_DIRECTORY ${SRCDIR})

	file(GLOB SUB "prepare-*.cmake")
	foreach(ITEM ${SUB})
		message(" > prepare: processing: ${ITEM}")
		string(REGEX REPLACE ".*prepare-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
		message(" > basename: ${BASENAME}")
		include(${ITEM})
	endforeach()
endif()

file(MAKE_DIRECTORY ${BLDDIR})

file(GLOB SUB "build-*.cmake")
foreach(ITEM ${SUB})
	message(" processing: ${ITEM}")
	string(REGEX REPLACE ".*build-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
	message(" > gen: basename: ${BASENAME}")
	include(${ITEM})
endforeach()

file(GLOB SUB "depend-*.cmake")
foreach(ITEM ${SUB})
	message(" processing: ${ITEM}")
	string(REGEX REPLACE ".*depend-(.+)\\.cmake" "\\1" BASENAME ${ITEM})
	message(" > dep : basename: ${BASENAME}")
	include(${ITEM})
endforeach()


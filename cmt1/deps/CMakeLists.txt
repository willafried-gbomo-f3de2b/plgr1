cmake_minimum_required(VERSION 3.0)

project(deps)


option(DEPS_DOWNLOAD "" ON)

set(THIRDPARTY "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")

add_custom_target(deps)

if(DEPS_DOWNLOAD)

add_custom_command(TARGET deps PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo " >> deleting deps directory... [${THIRDPARTY}] "
	COMMAND ${CMAKE_COMMAND} -E rm -fR thirdparty
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_custom_command(TARGET deps PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo " >> creating deps directory... [${THIRDPARTY}] "
	COMMAND ${CMAKE_COMMAND} -E make_directory ${THIRDPARTY}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_custom_command(TARGET deps PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo " >> cloning deps... "
	COMMAND git clone https://github.com/Matroska-Org/libebml.git
	COMMAND git clone https://github.com/Matroska-Org/libmatroska.git
	WORKING_DIRECTORY ${THIRDPARTY}
	)

add_custom_command(TARGET deps PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo " >> downloading deps... "
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/fetch-sqlite.cmake
	WORKING_DIRECTORY ${THIRDPARTY}
	)

endif()

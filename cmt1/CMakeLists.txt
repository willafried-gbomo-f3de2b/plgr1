cmake_minimum_required(VERSION 3.0)

project(proj1)

option(DEPS_DOWNLOAD "" ON)
option(BUILD_DEPS "" ON)

set(SOURCES 
	main.cpp
	)

add_executable(main ${SOURCES})

add_custom_target(cust)

if(BUILD_DEPS)
	add_subdirectory(deps)
endif()

target_compile_features(main
	PRIVATE cxx_std_17
)

target_include_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/include
)

target_link_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/lib
)

target_link_libraries(main 
	PRIVATE matroska.lib 
)

add_custom_command(TARGET cust PRE_BUILD
	COMMAND dir
)



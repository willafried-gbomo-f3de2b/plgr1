cmake_minimum_required(VERSION 3.0)

project(proj1)

option(DEPS_DOWNLOAD "" ON)
option(DEPS_BUILD "" ON)
option(DEPS_CRT_STATIC "" OFF)

option(CRT_STATIC "" OFF)

set(SOURCES 
	main.cpp
	)

add_executable(main ${SOURCES})

if(BUILD_DEPS OR DEPS_DOWNLOAD)
	add_subdirectory(deps)
	add_dependencies(main deps)

	set(DEPS_DOWNLOAD OFF CACHE BOOL "")
	set(DEPS_BUILD OFF CACHE BOOL "")
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

target_link_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/lib64
)

target_link_libraries(main 
	PRIVATE matroska 
)





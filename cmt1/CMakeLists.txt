cmake_minimum_required(VERSION 3.0)

project(proj1)

option(DEPS_DOWNLOAD "" ON)
option(DEPS_BUILD "" ON)
option(DEPS_CRT_STATIC "" OFF)
option(CRT_STATIC "" OFF)

if (MSVC)
	message(" >  CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

	message(" >  CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")

	message(" >  CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

	message(" >  CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

	message(" >  CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

	message(" >  CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

	if(CRT_STATIC)
		string(APPEND CMAKE_C_FLAGS_DEBUG " /MTd")
		string(APPEND CMAKE_C_FLAGS_RELEASE " /MT")
		string(APPEND CMAKE_CXX_FLAGS_DEBUG " /MTd")
		string(APPEND CMAKE_CXX_FLAGS_RELEASE " /MT")
	else()
		string(APPEND CMAKE_C_FLAGS_DEBUG " /MDd")
		string(APPEND CMAKE_C_FLAGS_RELASE " /MD")
		string(APPEND CMAKE_CXX_FLAGS_DEBUG " /MDd")
		string(APPEND CMAKE_CXX_FLAGS_RELEASE " /MD")
	endif()

	message(" -> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
	message(" -> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
	message(" -> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
	message(" -> CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
	message(" -> CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
	message(" -> CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

set(SOURCES 
	main.cpp
)

add_executable(main ${SOURCES})

if(DEPS_BUILD OR DEPS_DOWNLOAD)
	add_subdirectory(deps)
	#add_dependencies(main deps)

	set(DEPS_DOWNLOAD OFF CACHE BOOL "" FORCE)
	#set(DEPS_BUILD OFF CACHE BOOL "" FORCE)
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





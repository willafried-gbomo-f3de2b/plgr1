cmake_minimum_required(VERSION 3.2)

project(proj1)

# options
option(DEPS_DOWNLOAD "" ON)
option(DEPS_BUILD "" ON)
option(DEPS_STATIC "" OFF)
option(CRT_STATIC "" OFF)

set(ARCH "")
set(ARCHOPT "")
# arch
if(MSVC)
	if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "Win32")
		set(ARCH "32")
		set(ARCHOPT "-A \"Win32\"")
	elseif(${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(ARCH "64")
		set(ARCHOPT "-A \"x64\"")
	endif()
else()
endif()
message(" > ARCH: ${ARCH}")

message(" > CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(" > BUILD_TYPE: ${BUILD_TYPE}")
message(" > BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

message(" >  CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(" >  CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(" >  CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(" >  CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(" >  CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(" >  CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

# msvc crt static/dynamic link option
if (MSVC)
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	string(REGEX REPLACE "/M[DT]d? *" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
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
endif()

# linux debug config
if(UNIX)
	string(REGEX REPLACE "-g *" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	string(REGEX REPLACE "-g *" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
	string(REGEX REPLACE "-g *" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

	string(REGEX REPLACE "-g *" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	string(REGEX REPLACE "-g *" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	string(REGEX REPLACE "-g *" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

	string(APPEND CMAKE_C_FLAGS_DEBUG " -g")
	string(APPEND CMAKE_C_FLAGS_RelWithDebInfo " -g")
	string(APPEND CMAKE_CXX_FLAGS_DEBUG " -g")
	string(APPEND CMAKE_CXX_FLAGS_RelWithDebInfo " -g")
endif()

message(" -> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(" -> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(" -> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(" -> CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(" -> CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(" -> CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

# main target sources
set(SOURCES 
	src/main.cpp
	#src/cfg.cpp
	src/log.cpp
	
)

# declare main target
add_executable(main ${SOURCES})

# dependencies
if(DEPS_BUILD OR DEPS_DOWNLOAD)
	add_subdirectory(deps)
	add_dependencies(main deps)

	set(DEPS_DOWNLOAD OFF CACHE BOOL "" FORCE)
	#set(DEPS_BUILD OFF CACHE BOOL "" FORCE)
endif()

#main target settings
target_compile_features(main
	PRIVATE cxx_std_17
)

target_compile_definitions(main 
	PRIVATE DEPS_STATIC=${DEPS_STATIC}
)

target_include_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/include
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/$<CONFIG>/include

	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/include/upnp
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/$<CONFIG>/include/upnp
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/include/pthread
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/$<CONFIG>/include/pthread
)

target_link_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/lib
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/$<CONFIG>/lib
)

target_link_directories(main 
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/lib64
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/out/$<CONFIG>/lib64
)

if(NOT DEPS_STATIC)
	if(MSVC)
		target_link_libraries(main PRIVATE 
			matroska 
			FLAC 
			sqlite3 
			$<$<CONFIG:Debug>:libupnpd> 
			$<$<CONFIG:Release>:libupnp> 
		)
	else()
		target_link_libraries(main PRIVATE 
			matroska 
			FLAC 
			sqlite3 
			upnp
			pthread
		)
	endif()
else()
	if(MSVC)
		target_link_libraries(main PRIVATE 
			ebml
			matroska 
			FLAC 
			sqlite3 
			$<$<CONFIG:Debug>:pthreadVC3sd> 
			$<$<CONFIG:Release>:pthreadVC3s> 
			$<$<CONFIG:Debug>:ixmlsd> 
			$<$<CONFIG:Release>:ixmls> 
			$<$<CONFIG:Debug>:libupnpsd> 
			$<$<CONFIG:Release>:libupnps> 
			Ws2_32
			Iphlpapi
		)
	else()
		target_link_libraries(main PRIVATE 
			ebml 
			matroska 
			FLAC 
			sqlite3 
			ixml
			upnp
		)
	endif()
endif()





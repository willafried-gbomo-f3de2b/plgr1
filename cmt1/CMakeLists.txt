cmake_minimum_required(VERSION 3.0)

project(proj1)



set(SOURCES 
	main.cpp
	)


add_executable(main ${SOURCES})

add_custom_target(cust)

add_subdirectory(thirdparty)



add_custom_command(TARGET cust PRE_BUILD
	COMMAND dir
	)


project(proj2)

add_library(main2 ${SOURCES})


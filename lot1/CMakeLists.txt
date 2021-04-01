cmake_minimum_required(VERSION 3.0)

#-------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-------------------------------------
project (prj_main)
add_executable (main)
add_library(sep SHARED)
add_library(sepl)



#-------------------------------------
target_sources(main PRIVATE 
main.cpp 
)

target_sources(sep PRIVATE 
sep.cpp 
)

target_sources(sepl PRIVATE 
sep.cpp 
)

#-------------------------------------
# target_compile_features(main PRIVATE 
# cxx_std_17
# )

# target_compile_features(sep PRIVATE 
# cxx_std_17
# )

#-------------------------------------
target_compile_definitions(main 
PRIVATE SEP_EXPORT_NOP
)

target_compile_definitions(sep 
PRIVATE SEP_EXPORT
)

target_compile_definitions(sepl
PRIVATE SEP_EXPORT
)

#target_compile_options(main 
#PRIVATE "/MT")

#-------------------------------------
set_target_properties(main PROPERTIES 
OUTPUT_NAME main
)

#-------------------------------------
add_dependencies(main 
sep
)

#-------------------------------------
target_link_libraries(main 
sep
)



#-------------------------------------
get_target_property (OUT main COMPILE_DEFINITIONS)
message ("COMPILE_DEFINITIONS = ${OUT}")

get_target_property (OUT main COMPILE_OPTIONS)
message ("COMPILE_OPTIONS = ${OUT}")

message ("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message ("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message ("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")

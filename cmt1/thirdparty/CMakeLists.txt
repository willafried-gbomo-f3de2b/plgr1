cmake_minimum_required(VERSION 3.0)

project(deps)

add_custom_target(clone)

add_custom_command(TARGET clone PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -fR ${CMAKE_CURRENT_BINARY_DIR}/libebml
    COMMAND ${CMAKE_COMMAND} -E rm -fR ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    )

add_custom_command(TARGET clone PRE_BUILD
    COMMAND git clone https://github.com/Matroska-Org/libebml.git
    COMMAND git clone https://github.com/Matroska-Org/libmatroska.git
    )


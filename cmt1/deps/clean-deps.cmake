# dep/*

# args: CPYDIR, DSTDIR, CONFIG, PLATFORM

set(TARGETNAME "clean-deps")

add_custom_target(${TARGETNAME})

add_custom_command(TARGET ${TARGETNAME}
    COMMAND ${CMAKE_COMMAND} -E cleaning deps...
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${DSTDIR} 
)




# thirdparty/libebml

message("adding custom target ebml...")
message("SRCDIR: ${SRCDIR}")
message("BLDDIR: ${BLDDIR}")

add_custom_target(deps-libebml)
add_dependencies(deps deps-libebml)

add_custom_command(TARGET deps-libebml
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} dir"
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BLDDIR}/deps-libebml
	WORKING_DIRECTORY ${BLDDIR}
	)

add_custom_command(TARGET deps-libebml
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} gen"
	COMMAND ${CMAKE_COMMAND}  ${SRCDIR}/libebml
	WORKING_DIRECTORY ${BLDDIR}/deps-libebml
	)

add_custom_command(TARGET deps-libebml
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} build"
	COMMAND ${CMAKE_COMMAND} --build . 
	WORKING_DIRECTORY ${BLDDIR}/deps-libebml
	)


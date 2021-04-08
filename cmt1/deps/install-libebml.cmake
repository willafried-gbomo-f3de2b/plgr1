
add_custom_command(TARGET deps-libebml
    COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} install"
    COMMAND ${CMAKE_COMMAND} --install . --prefix ${BLDDIR}/out --config $<CONFIG>
    WORKING_DIRECTORY ${BLDDIR}/deps-libebml
    )

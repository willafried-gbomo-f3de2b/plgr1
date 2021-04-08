
add_custom_command(TARGET deps-libmatroska
    COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} install"
    COMMAND ${CMAKE_COMMAND} --install . --prefix ${BLDDIR}/out --config $<CONFIG>
    WORKING_DIRECTORY ${BLDDIR}/deps-libmatroska
    )

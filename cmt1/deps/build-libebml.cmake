# thirdparty/libebml

add_custom_command(TARGET deps
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} gen"
	COMMAND ${CMAKE_COMMAND} ${THIRDPARTY}/libebml
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)

add_custom_command(TARGET deps
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} build"
	COMMAND ${CMAKE_COMMAND} --build . --target ebml
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)



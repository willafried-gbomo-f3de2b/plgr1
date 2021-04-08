# thirdparty/libmatroska

message("adding custom target libmatroska...")
message("SRCDIR: ${SRCDIR}")
message("BLDDIR: ${BLDDIR}")

add_custom_target(deps-libmatroska)

add_custom_command(TARGET deps-libmatroska
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} dir"
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BLDDIR}/deps-libmatroska
	WORKING_DIRECTORY ${BLDDIR}
	)

add_custom_command(TARGET deps-libmatroska
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} gen"
	COMMAND ${CMAKE_COMMAND}  ${SRCDIR}/libmatroska -D BUILD_SHARED_LIBS=1 -D EBML_DIR=${BLDDIR}/out/lib/cmake/EBML 
	WORKING_DIRECTORY ${BLDDIR}/deps-libmatroska
	)

add_custom_command(TARGET deps-libmatroska
	COMMAND ${CMAKE_COMMAND} -E echo " >> ${BASENAME} build"
	COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
	WORKING_DIRECTORY ${BLDDIR}/deps-libmatroska
	)


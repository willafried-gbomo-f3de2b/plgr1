# thirdparty/deps-libmatroska

set(TARGETNAME "deps-libmatroska")

message("adding custom target libmatroska...")
message("SRCDIR: ${SRCDIR}")
message("BLDDIR: ${BLDDIR}")
message("INSDIR: ${INSDIR}")

add_custom_target(${TARGETNAME})

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo " > ${TARGETNAME}: $<CONFIG>"
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> directory: ${TARGETNAME}"
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BLDDIR}/${TARGETNAME}
	WORKING_DIRECTORY ${BLDDIR}
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> generate: ${TARGETNAME}"
	COMMAND ${CMAKE_COMMAND} ${SRCDIR}/libmatroska -D BUILD_SHARED_LIBS=1 -D EBML_DIR=${INSDIR}/lib/cmake/EBML $<$<BOOL:$<CONFIG>>:"-DBUILD_TYPE=$<CONFIG>">
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> build: ${BASENAME}"
	COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> install: ${BASENAME}"
    COMMAND ${CMAKE_COMMAND} --install . --prefix ${INSDIR} --config $<CONFIG>
    WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)


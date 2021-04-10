# thirdparty/deps-libebml

set(TARGETNAME "deps-libebml")

message("adding custom target ebml...")
message("SRCDIR: ${SRCDIR}")
message("BLDDIR: ${BLDDIR}")

message("CONFIG: ${CONFIG}")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("BUILD_TYPE: ${BUILD_TYPE}")
message("<CONFIG>: $<CONFIG>")

add_custom_target(deps-libebml)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo " CONFIG - ${CONFIG}"
	COMMAND ${CMAKE_COMMAND} -E echo " CMAKE_BUILD_TYPE - ${CMAKE_BUILD_TYPE}"
	COMMAND ${CMAKE_COMMAND} -E echo " BUILD_TYPE - ${BUILD_TYPE}"
	COMMAND ${CMAKE_COMMAND} -E echo " <CONFIG> - $<CONFIG>"
	)

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
	COMMAND ${CMAKE_COMMAND}  ${SRCDIR}/libebml -D BUILD_SHARED_LIBS=1 $<$<BOOL:$<CONFIG>>:"-DCMAKE_BUILD_TYPE=$<CONFIG>">
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> build: ${BASENAME}"
	COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)


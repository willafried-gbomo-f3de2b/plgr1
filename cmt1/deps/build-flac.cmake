# thirdparty/deps-flac

set(TARGETNAME "deps-flac")

message(" > adding custom target ${TARGETNAME} ...")
add_custom_target(${TARGETNAME})

message("SRCDIR: ${SRCDIR}")
message("BLDDIR: ${BLDDIR}")
message("DSTDIR: ${DSTDIR}")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

if(MSVC)
	set(CFLAG "-D CMAKE_C_FLAGS=\"${CMAKE_C_FLAGS}\" -D CMAKE_C_FLAGS_DEBUG=\"${CMAKE_C_FLAGS_DEBUG}\" -D CMAKE_C_FLAGS_RELEASE=\"${CMAKE_C_FLAGS_RELEASE}\"")

	set(CXXFLAG "-D CMAKE_CXX_FLAGS=\"${CMAKE_CXX_FLAGS}\" -D CMAKE_CXX_FLAGS_DEBUG=\"${CMAKE_CXX_FLAGS_DEBUG}\" -D CMAKE_CXX_FLAGS_RELEASE=\"${CMAKE_CXX_FLAGS_RELEASE}\"")
endif()

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
	COMMAND ${CMAKE_COMMAND} ${SRCDIR}/flac -D BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} ${CFLAG} ${CXXFLAG} $<$<BOOL:${CMAKE_BUILD_TYPE}>:"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"> ${ARCHOPT} -D WITH_OGG=OFF -D BUILD_CXXLIBS=OFF -D BUILD_PROGRAMS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_DOCS=OFF -D INSTALL_MANPAGES=OFF
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

add_custom_command(TARGET ${TARGETNAME}
	COMMAND ${CMAKE_COMMAND} -E echo "  >> build: ${BASENAME}"
	COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
	WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

add_custom_command(TARGET ${TARGETNAME}
    COMMAND ${CMAKE_COMMAND} -E echo "  >> install: ${BASENAME}"
    COMMAND ${CMAKE_COMMAND} --install . --prefix ${DSTDIR} --config $<CONFIG>
    WORKING_DIRECTORY ${BLDDIR}/${TARGETNAME}
)

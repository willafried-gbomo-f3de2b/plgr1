# thirdparty/deps-pthreads4w

set(TARGETNAME "deps-pthreads4w")

include(GNUInstallDirs)

message(" > adding custom target ${TARGETNAME} ...")
add_custom_target(${TARGETNAME})

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
	COMMAND ${CMAKE_COMMAND} ${SRCDIR}/pthreads4w -D BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} ${CFLAG} ${CXXFLAG} $<$<BOOL:${CMAKE_BUILD_TYPE}>:"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"> ${ARCHOPT} -D BUILD_TESTING=OFF
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


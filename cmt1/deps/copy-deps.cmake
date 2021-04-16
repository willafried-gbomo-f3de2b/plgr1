# dep/*

# args: CPYDIR, DSTDIR, CONFIG

message("DSTDIR: ${DSTDIR}")
message("CPYDIR: ${CPYDIR}")
message("CONFIG: ${CONFIG}")
if (CPYDIR)
    #message("copying dep files...")
    file(MAKE_DIRECTORY ${CPYDIR}/${CONFIG})

    file(MAKE_DIRECTORY ${CPYDIR}/${CONFIG}/lib)
    file(GLOB_RECURSE SUB "${DSTDIR}/*.lib")
    foreach(ITEM ${SUB})
        file(RELATIVE_PATH REL_ITEM "${DSTDIR}" "${ITEM}")
        message(" ${REL_ITEM}")
        file(COPY ${ITEM} DESTINATION ${CPYDIR}/${CONFIG}/lib)
    endforeach()

    file(MAKE_DIRECTORY ${CPYDIR}/${CONFIG}/bin)
    file(GLOB_RECURSE SUB "${DSTDIR}/*.dll")
    foreach(ITEM ${SUB})
        file(RELATIVE_PATH REL_ITEM "${DSTDIR}" "${ITEM}")
        message(" ${REL_ITEM}")
        file(COPY ${ITEM} DESTINATION ${CPYDIR}/${CONFIG}/bin)
    endforeach()

    message(" copying headers...")
    file(COPY "${DSTDIR}/include" DESTINATION "${CPYDIR}/${CONFIG}")
else()
endif()


add_library(sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite-amalgamation/sqlite3.c
)

target_include_directories(sqlite3
    PUBLIC thirdparty/sqlite-amalgamation
)

include(GNUInstallDirs)

set (PHDR
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite-amalgamation/sqlite3.h $
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite-amalgamation/sqlite3ext.h
)

set_target_properties(sqlite3 
    PROPERTIES PUBLIC_HEADER ${PHDR}
)

install(TARGETS sqlite3
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sqlite3
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
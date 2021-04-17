
add_library(sqlite3
    sqlite3.c
)

target_include_directories(sqlite3
    PUBLIC .
)

include(GNUInstallDirs)

set (PHDR
    sqlite3.h
    sqlite3ext.h
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

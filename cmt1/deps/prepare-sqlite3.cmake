# thirdparty/sqlite3

# sqlite3 amalgamation zip file
set(SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL "https://www.sqlite.org/2021/sqlite-amalgamation-3350500.zip" CACHE STRING "")

# make directory
file(MAKE_DIRECTORY ${SRCDIR}/sqlite3)

# download
message("  >> downloading ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ...")
file(DOWNLOAD ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ${SRCDIR}/sqlite3/sqlite-amalgamation.zip)

# extract
message("  >> extracting...")
file(ARCHIVE_EXTRACT INPUT ${SRCDIR}/sqlite3/sqlite-amalgamation.zip
	DESTINATION ${SRCDIR}/sqlite3
)

# rename
file(GLOB LST "${SRCDIR}/sqlite3/sqlite-amalgamation-*")
foreach(ITEM ${LST})
	if(IS_DIRECTORY ${ITEM})
		#message("ITEM: ${ITEM}")
		#cmake_path(GET ${ITEM} PARENT_PATH DIR)
		#cmake_path(GET ${ITEM} FILE_NAME FN)
		#message("  >> renaming ${FN} -> sqlite-amalgamation")
		file(RENAME ${ITEM} ${SRCDIR}/sqlite3/sqlite-amalgamation)
	endif()
endforeach()

# copy cmake file
message("  >> copy & rename cmake file ...")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.cmake.in DESTINATION ${SRCDIR}/sqlite3)
file(RENAME ${SRCDIR}/sqlite3/sqlite3.cmake.in ${SRCDIR}/sqlite3/CMakeLists.txt)

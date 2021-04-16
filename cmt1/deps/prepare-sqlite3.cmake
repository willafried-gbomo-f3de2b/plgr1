# thirdparty/sqlite3

# sqlite3 amalgamation zip file
set(SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL "https://www.sqlite.org/2021/sqlite-amalgamation-3350400.zip" CACHE STRING "")

# download
message("  >> downloading ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ...")
file(DOWNLOAD ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ${SRCDIR}/sqlite-amalgamation.zip)

# extract
message("  >> extracting...")
file(ARCHIVE_EXTRACT INPUT ${SRCDIR}/sqlite-amalgamation.zip
	DESTINATION ${SRCDIR}
)

# rename
file(GLOB LST "${SRCDIR}/sqlite-amalgamation-*")
foreach(ITEM ${LST})
	if(IS_DIRECTORY ${ITEM})
		#message("ITEM: ${ITEM}")
		#cmake_path(GET ${ITEM} PARENT_PATH DIR)
		#cmake_path(GET ${ITEM} FILE_NAME FN)
		#message("  >> renaming ${FN} -> sqlite-amalgamation")
		file(RENAME ${ITEM} ${SRCDIR}/sqlite-amalgamation)
	endif()
endforeach()

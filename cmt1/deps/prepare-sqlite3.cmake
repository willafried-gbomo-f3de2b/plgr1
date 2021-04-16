# thirdparty/sqlite3

# sqlite3 amalgamation zip file
set(SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL "https://www.sqlite.org/2021/sqlite-amalgamation-3350400.zip" CACHE STRING "")

# download
message("  >> downloading ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ...")
file(DOWNLOAD ${SQLITE3_AMALGAMATION_ZIP_DOWNLOAD_URL} ${SRCDIR}/sqlite-amalgamation.zip)

# extract
file(ARCHIVE_EXTRACT INPUT ${SRCDIR}/sqlite-amalgamation.zip
	DESTINATION ${SRCDIR}
)

# rename
file(GLOB LST "${SRCDIR}/sqlite-amalgamation-*")
foreach(ITEM ${LST})
	message("ITEM: ${ITEM}")
endforeach()

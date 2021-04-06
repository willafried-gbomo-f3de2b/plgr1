# thirdparty/sqlite

message("  >>> downloading sqlite... ")
file(DOWNLOAD https://www.sqlite.org/2021/sqlite-amalgamation-3350400.zip ${THIRDPARTY}/sqlite-download.zip)

file(REMOVE_RECURSE ${OUT} ${THIRDPARTY}/sqlite-amalgamation)

message("  >>> extracting sqlite... ")
file(ARCHIVE_EXTRACT 
	INPUT ${THIRDPARTY}/sqlite-download.zip
	DESTINATION ${THIRDPARTY}
	)

file(GLOB OUT ${THIRDPARTY}/sqlite-amalgamation-*)
message("  >>> renaming sqlite directory... [sqlite-amalgamation]")
file(RENAME ${OUT} ${THIRDPARTY}/sqlite-amalgamation)


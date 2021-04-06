# thirdparty/sqlite

message("  >>> downloading sqlite... ")
file(DOWNLOAD https://www.sqlite.org/2021/sqlite-amalgamation-3350400.zip sqlite-download.zip)

message("  >>> extracting sqlite... ")
file(ARCHIVE_EXTRACT 
	INPUT sqlite-download.zip
	DESTINATION .
	)

file(GLOB OUT sqlite-amalgamation-*)
message("  >>> renaming sqlite directory... [${OUT}] => [sqlite-amalgamation]")
file(RENAME ${OUT} sqlite-amalgamation)


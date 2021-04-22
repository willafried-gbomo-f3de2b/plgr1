# dependencies

# deps/thirdparty/flac
add_dependencies(deps dep-flac)
add_dependencies(dep-flac clean-deps)

# deps/thirdparty/libebml
add_dependencies(deps dep-libebml)
add_dependencies(dep-libebml clean-deps)

# deps/thirdparty/sqlite3
add_dependencies(deps dep-sqlite3)
add_dependencies(dep-sqlite3 clean-deps)


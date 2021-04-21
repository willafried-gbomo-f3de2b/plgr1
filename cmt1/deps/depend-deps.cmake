# dependencies

# deps/thirdparty/flac
add_dependencies(deps deps-flac)
add_dependencies(deps-flac clean-deps)

# deps/thirdparty/libebml
add_dependencies(deps deps-libebml)
add_dependencies(deps-libebml clean-deps)

# deps/thirdparty/sqlite3
add_dependencies(deps deps-sqlite3)
add_dependencies(deps-sqlite3 clean-deps)


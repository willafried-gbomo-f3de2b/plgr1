# thirdparty/pupnp

add_dependencies(deps dep-pupnp)

if(MSVC)
    add_dependencies(dep-pupnp dep-pthreads4w)
endif()

add_dependencies(dep-pupnp clean-deps)



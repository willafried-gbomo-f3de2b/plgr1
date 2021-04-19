# thirdparty/pupnp

add_dependencies(deps deps-pupnp)

if(MSVC)
    add_dependencies(deps-pupnp deps-pthreads4w)
endif()

add_dependencies(deps-pupnp clean-deps)



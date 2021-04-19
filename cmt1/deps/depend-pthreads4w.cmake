# thirdparty/pthreads4w

if(MSVC)
    add_dependencies(deps deps-pthreads4w)
    add_dependencies(deps-pthreads4w clean-deps)
endif()


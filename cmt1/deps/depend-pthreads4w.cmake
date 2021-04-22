# thirdparty/pthreads4w

if(MSVC)
    add_dependencies(deps dep-pthreads4w)
    add_dependencies(dep-pthreads4w clean-deps)
endif()


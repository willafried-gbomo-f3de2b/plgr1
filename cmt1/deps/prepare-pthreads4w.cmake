# thirdparty/pthreads4w

if(MSVC)
	execute_process(COMMAND git clone https://github.com/Vollstrecker/pthreads4w.git
		WORKING_DIRECTORY ${SRCDIR}
	)
endif()


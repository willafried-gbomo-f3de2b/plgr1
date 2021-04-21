# thirdparty/pupnp

execute_process(COMMAND git clone https://github.com/pupnp/pupnp.git
	WORKING_DIRECTORY ${SRCDIR}
)

execute_process(COMMAND git checkout 138a67329ec7365eb0d8b10b447da62184cd9019
	WORKING_DIRECTORY ${SRCDIR}/pupnp
	# '2021/4/1
)


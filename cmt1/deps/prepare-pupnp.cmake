# thirdparty/pupnp

execute_process(COMMAND git clone https://github.com/pupnp/pupnp.git
	WORKING_DIRECTORY ${SRCDIR}
)

execute_process(COMMAND git checkout 332fa8879e457487fc3c8800c4461d74fcb29527
	WORKING_DIRECTORY ${SRCDIR}/pupnp
)


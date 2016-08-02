
default:    gridftp_checkaccess

gridftp_checkaccess: gridftp_checkaccess.c
	gcc ${CFLAGS} -o $@ $@.c

bindatecallout: $<.c
	gcc -o $< $@.c
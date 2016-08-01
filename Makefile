
default:    authzcallout

authzcallout: authzcallout.c
	gcc -o $@ $@.c

bindatecallout: $<.c
	gcc -o $< $@.c
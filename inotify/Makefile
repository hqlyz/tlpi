OBJ = error_functions.o demo_inotify.o

demo_inotify: $(OBJ)
	cc -o demo_inotify $(OBJ)

error_functions.o: ../lib/error_functions.h
	cc -c ../lib/error_functions.c

demo_inotify.o: ../lib/tlpi_hdr.h

.PHONY: clean
clean: 
	rm $(OBJ)
OBJECTS=master.o 
MODULE_DIR=./modules
MODULE_OBJ=module_register.o cmd_exec.o

#M4ster: $(OBJECTS) 	
#	gcc -g3 -o M4ster $(OBJECTS)

#master.o: master.c master.h 
#	gcc -g3 -o master.o -c master.c -l

M4ster: master.c master.h
	gcc -g3 -o M4ster master.c -L/root/hacking_proj/c2/M4ster/src/modules -lmodule -Wl,-rpath=/root/hacking_proj/c2/M4ster/src/modules

.PHONY:
	clean
	del

clean:
	rm -f $(OBJECTS)

del:
	rm -f M4ster $(OBJECTS)

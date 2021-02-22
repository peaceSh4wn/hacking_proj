MODULE_OBJ=module_register.o cmd_exec.o

libmodule.so: $(MODULE_OBJ)
	gcc -shared $(MODULE_OBJ) -o libmodule.so

module_register.o: module_register.c module_register.h cmd_exec.h
	gcc -g3 -c -fPIC module_register.c

cmd_exec.o: cmd_exec.c cmd_exec.h
	gcc -g3 -c -fPIC cmd_exec.c 

.PHONY:
	clean

clean:
	-rm -f *.o

del:
	rm -f *.o *.so

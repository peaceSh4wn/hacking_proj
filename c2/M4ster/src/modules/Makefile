MODULE_OBJ=cmd_exec.o

module.o: module_register.c module_register.h $(MODULE_OBJ)
	gcc -g3 -o module.o -c module_register.c $(MODULE_OBJ)

cmd_exec.o: cmd_exec.c cmd_exec.h
	gcc -g3 -o cmd_exec.o -c cmd_exec.c 

.PHONY:
	clean

clean:
	rm -f *.o

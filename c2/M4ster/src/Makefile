OBJECTS=master.o 
MODULE_DIR=./modules
MODULE_OBJ=cmd_exec.o

M4ster: $(OBJECTS) 	
	gcc -g3 -o M4ster $(OBJECTS)

master.o: master.c master.h usage.h module.o
	gcc -g3 -o master.o -c master.c module.o 

modules.o: module_register.c module_register.h $(MODULE_OBJ)
	gcc -g3 -o modules.o -c module_register.c $(MODULE_OBJ)

cmd_exec.o:
	gcc -g3 -o cmd_exec.o -c -I$(MODULE_DIR)/cmd_exec.h \
							 -I$(MODULE_DIR)/cmd_exec.c

.PHONY:
	clean

clean:
	rm -f $(OBJECTS)

del:
	rm -f M4ster $(OBJECTS)

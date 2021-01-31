OBJECTS = main.o module_init.o

Cli3nt: $(OBJECTS)
	gcc -g3 -o Cli3nt $(OBJECTS)

main.o: client.c client.h module_init.h
	gcc -g3 -o main.o -c client.c 

module_init.o: module_init.c module_init.h
	gcc -g3 -o module_init.o -c module_init.c

.PHONY:
	clean

clean:
	rm -f $(OBJECTS)

del:
	rm -f Cli3nt $(OBJECTS)

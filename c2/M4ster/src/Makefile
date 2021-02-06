OBJECTS = master.o

M4ster: $(OBJECTS) 	
	gcc -g3 -o M4ster $(OBJECTS)

master.o: master.c master.h usage.h
	gcc -g3 -o master.o -c master.c 

.PHONY:
	clean

clean:
	rm -f $(OBJECTS)

del:
	rm -f M4ster $(OBJECTS)

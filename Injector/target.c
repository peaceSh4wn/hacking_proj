#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void function() {
	int i;
	for (i = 0; i < 10; i++) {
		sleep(1);
	}
	puts("good bye~");
}

int main(int argc, char const **argv) {
	puts("welcome!");
	sleep(1);
	char *ptr = malloc(0x100);
	puts("what's your name");
	read(0, ptr, 0x20);

	printf("nice to meet you %s\n", ptr);
	function();
	return 0;
}	

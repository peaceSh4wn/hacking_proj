#include "client.h"
#include "module_init.h"

void usage() {
	printf(USAGE_STR);	
}

static inline int input_gardian(int argc, char **argv)
{
	if (argc != 3) {
		usage();
		exit(0);
	}	
}

int init_client(int argc, char **argv)
{
	int i;
	for(i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
		
		/* module initilize in */
		module_init(argv[i], &i, argv);
	}
}

int do_it()
{
	
}

int close_client()
{
	
}

int main(int argc, char **argv)
{
	int sock_fd, sock_len;
	
	input_gardian(argc, argv);
	
	init_client(argc, argv);

	do_it();

	close_client();

	return 0;
}

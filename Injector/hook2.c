#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

#if defined(RTLD_NEXT)
#	define REAL_LIBC RTLD_NEXT
#else
#	define REAL_LIBC ((void *) -1L)
#endif

#define FN(ptr, type, name, args) ptr = (type (*)args)dlsym(REAL_LIBC, name)

typedef int (*SLEEP)(unsigned int);
static int sleep_times = 0;

int sleep(unsigned int t) {
	static void *handle = NULL;
	static SLEEP true_sleep = NULL;
	sleep_times++;
	if (!handle) {
		handle = dlopen("libc.so.6", RTLD_LAZY);
		true_sleep = (SLEEP)dlsym(handle, "sleep");
	}
	printf("sleep has been call for %d times\n", sleep_times);
	return true_sleep(t);
}

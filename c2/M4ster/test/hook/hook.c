#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int(*SLEEP)(unsigned int t);
static int sleep_time = 0;

int sleep(unsigned int t)
{
    static void *handle = NULL;
    static SLEEP true_sleep = NULL;
    sleep_time++;
    if (!handle) {
        handle = dlopen("libc.so.6", RTLD_LAZY);
        true_sleep = (SLEEP)dlsym(handle, "sleep");
    }
    printf("sleep has been called for %d times\n", sleep_time);
    return true_sleep(t);
}
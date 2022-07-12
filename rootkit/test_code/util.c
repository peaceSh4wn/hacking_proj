#include "common.h"

struct sym_hook {
	void *addr;

	unsigned char o[T_SIZE];
	unsigned char n[T_SIZE];

	struct list_head list;
};

void hook_start(void *tg) {

}

void hook_end(void *tg) {}
void hook_pause(void *tg) {}
void hook_resume(void *tg) {}

LIST_HEAD(hook_syms);



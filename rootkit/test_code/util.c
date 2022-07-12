#include "common.h"

struct sym_hook {
	void *addr;

	unsigned char o[T_SIZE];
	unsigned char n[T_SIZE];
	struct list_head list;
}

unsigned long disable_wp(void) {

	unsigned long cr0;

	preempt_disable();
	barrier();

	cr0 = read_cr0();
	write_cr0(cr0 & ~X86_CR0_WP);

	return cr0;
}

void restore_wp(unsigned long o_cr0) {
	write_cr0(o_cr0);

	barrier();
	preempt_disable();
}

void hook_start(void *tg, void *new) {
	struct sym_hook *s;
	unsigned char o_code[T_SIZE], n_code[T_SIZE];

	// for x86_64
	unsigned long o_cr0;

	memcpy(n_code, "\x48\xb8\x00\x00\x00\x00\x00\x00\x00\x00\xff\xe0", T_SIZE);	
	*(unsigned long *)&n_code[2] = (unsigned long)new;
	memcpy(o_code, tg, T_SIZE);
	
	o_cr0 = disable_wp();
	
	memcpy(tg, n_code, T_SIZE);
	restore_wp(o_cr0);

	s = kmalloc(sizeof(*s), GFP_KERNEL);
	if (!s) 
		return;

	s->addr = tg;
	memcpy(s->o, o_code, T_SIZE);
	memcpy(s->n, n_code, T_SIZE);

	list_add(&s->list, &hook_syms);
}

void hook_end(void *tg) {
	struct sym_hook *s;

	list_for_each_entry (s, &hook_syms, list) {
		if (tg == s->addr) {
			unsigned long o_cr0 = disable_wp();

			memcpy(tg, s->o, T_SIZE);

			restore_wp(o_cr0);

			list_del(&s->list);
			kfree(s);
			break;
		}
	}
}

void hook_pause(void *tg) {
	struct sym_hook *s;

	list_for_each_entry (s, &hook_syms, list) {
		if (tg == s->addr) {
			unsigned long o_cr0 = disable_wp();
			memcpy(tg, s->o, T_SIZE);
			restore_wp(o_cr0);
			break;
		}
	}
}

void hook_resume(void *tg) {
	struct sym_hook *s;

    list_for_each_entry (s, &hook_syms, list) {
        if (tg == s->addr) {
            unsigned long o_cr0 = disable_wp();
            memcpy(tg, s->n, T_SIZE);
            restore_wp(o_cr0);
            break;
        }
    }
}




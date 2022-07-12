#include "common.h"

unsigned long *st = NULL;

unsigned long *find_st(void) {
	unsigned long *stt;
	unsigned long i;
	for (i = (unsigned long int)sys_close; i < ULONG_MAX; i+= sizeof(void *)) {
		stt = (unsigned long *)i;
		if (stt[__NR_close] == (unsigned long)sys_close) {
			return stt;
		}
	}
	return NULL;
}

static int __init start(void) {
	printk(KERN_ALERT "[+] module inserted\n");
#if 1
	st = find_st();
	if (NULL != st) {
		printk(KERN_ALERT "we find it %p\n", st);
#if 1
		sys_r = (unsigned long *)st[__NR_read];
		printk(KERN_ALERT "sys_read %p\n", sys_r);

		sys_w = (unsigned long *)st[__NR_write];
		printk(KERN_ALERT "sys_write %p\n", sys_w);
		
		hook_start(sys_r, n_sys_r);
#endif
	}
#endif
	return 0;
}

static void __exit end(void) {
#if 1
	hook_end(sys_r);
#endif
	printk(KERN_ALERT "[-] bye~\n");
}

module_init(start);
module_exit(end);

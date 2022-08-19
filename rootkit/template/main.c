#include "common.h"

static int __init start(void) {
	printk(KERN_ALERT "[+] module inserted\n");
	return 0;
}

static void __exit end(void) {
	printk(KERN_ALERT "[-] bye~\n");
}

module_init(start);
module_exit(end);

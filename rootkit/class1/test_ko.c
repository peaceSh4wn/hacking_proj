#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SHAWN");
MODULE_DESCRIPTION("basic kernel module");
MODULE_VERSION("0.01");

static int __init example_init(void) {
	printk(KERN_ALERT "hello, world\n");
	return 0;
}

static void __exit example_exit(void) {
	printk(KERN_ALERT "Goodbye, world\n");
}

module_init(example_init);
module_exit(example_exit);

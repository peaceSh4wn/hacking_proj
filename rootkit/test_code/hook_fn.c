#include "common.h"

extern unsigned long *st;

//unsigned long *sys_r;
//unsigned long *sys_w;
asmlinkage long (*sys_r)(unsigned int fd, char __user *buf, size_t count);
asmlinkage long (*sys_w)(unsigned int fd, char __user *buf, size_t count);

void hook_write(unsigned int *fd, const char __user *buf, size_t *count) {
	printk(KERN_ALERT "do nothing write\n");
}

void hook_read(unsigned int *fd, const char __user *buf, size_t *count) {
	printk(KERN_ALERT "do nothing read\n");
}

asmlinkage long n_sys_r(unsigned int fd, char __user *buf, size_t count) {
	long ret;

	void *bb;

	bb = kmalloc(count, GFP_KERNEL);
	if (!bb) {
		printk(KERN_ALERT "kmalloc failed\n");
	} else {
		if(copy_from_user(bb, buf, count)) {
			printk(KERN_ALERT "copy from user failed\n");
			kfree(bb);
		} else {
			//printk(KERN_ALERT "we got here\n");
			kfree(bb);
		}
	}

	hook_pause(sys_r);
	ret = sys_r(fd, buf, count);
	hook_resume(sys_r);

	return ret;
}

asmlinkage long n_sys_w(unsigned int fd, char __user *buf, size_t count) {
    long ret;

    void *bb;

    bb = kmalloc(count, GFP_KERNEL);
    if (!bb) {
        printk(KERN_ALERT "kmalloc failed\n");
    } else {
        if(copy_from_user(bb, buf, count)) {
            printk(KERN_ALERT "copy from user failed\n");
            kfree(bb);
        } else {
            //printk(KERN_ALERT "we got here\n");
            kfree(bb);
        }
    }

    hook_pause(sys_w);
    ret = sys_w(fd, buf, count);
    hook_resume(sys_w);

    return ret;
}

void hookrw_start(void) {
	if (st != NULL) {
		sys_r = st[__NR_read];
		ALERT("sys_read %p\n", sys_r);

		sys_w = st[__NR_write];
		ALERT("sys_write %p\n", sys_w);

		hook_start(sys_r, n_sys_r);

	} else {
		ALERT("symbol table isn't find right now\n");
	}
}

void hookrw_end(void) {
	if (st != NULL) {
		hook_end(sys_r);		
	} else {
		ALERT("symbol table isn't find right now\n");
	}
}

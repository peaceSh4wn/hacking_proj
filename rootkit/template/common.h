#ifndef __COMMON_H_
#define __COMMON_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/fs.h>

#define ALERT(...) printk(KERN_ALERT __VA_ARGS__)

#endif

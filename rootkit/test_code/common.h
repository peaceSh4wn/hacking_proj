#ifndef __COMMON_H_
#define __COMMON_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/fs.h>

//  12 for x86_64
#define T_SIZE 16

unsigned long disable_wp(void);
void restore_wp(unsigned long);

void hook_start(void *, void *);
void hook_end(void *);
void hook_pause(void *);
void hook_resume(void *);

void hook_rw(void);

void hook_write(unsigned int *fd, const char __user *buf, size_t *count);
void hook_read (unsigned int *fd, const char __user *buf, size_t *count);

asmlinkage long n_sys_r(unsigned int fd, char __user *buf, size_t count);
asmlinkage long n_sys_w(unsigned int fd, char __user *buf, size_t count);

unsigned long *sys_r;
unsigned long *sys_w;

#endif

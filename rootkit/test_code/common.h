#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/fs.h>

#define T_SIZE 16

void hook_start(void *);
void hook_end(void *);
void hook_pause(void *);
void hook_resume(void *);

void hook_rw(void);

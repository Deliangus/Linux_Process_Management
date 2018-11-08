<<<<<<< HEAD
=======
/*
  A kernel module to list process by their names. Print when loading the module.
  In the terminal, compile this module with "make" and load it with "sudo insmod process.ko". 
  Check the result of printk by “dmesg”
  Unload it with "sudo rmmod process.ko".
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct definition
#include <asm/unistd.h>
#include <linux/list.h>
#include <linux/init_task.h>
#include <linux/kernel.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif

// Initialization of module
int __init init_MyKernelModule(void);

// Exit of module
void __exit exit_MyKernelModule(void);
>>>>>>> a8e1d3b0db86cfc1525c95e67f3f8b6f2fc9c792

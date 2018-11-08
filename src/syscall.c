/*
  A kernel module to list process by their names. Print when loading the module.
  In the terminal, compile this module with "make" and load it with "sudo insmod process.ko". 
  Check the result of printk by “dmesg”
  Unload it with "sudo rmmod process.ko".
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct definition
#include <asm/unistd.h>
#include <linux/list.h>
#include <linux/init_task.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif


// Initialization of module
int __init init_MyKernelModule(void)
{
  printk("Process List Lookup Module Init.\n");
  print_task_by_name();
  return 0;
}

// Exit of module
void __exit exit_MyKernelModule(void)
{
  printk("Process List Lookup Module Exit.\n");
  return;
}

module_init(init_MyKernelModule);
module_exit(exit_MyKernelModule);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A kernel module to list process by their names");

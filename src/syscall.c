#include "syscall.h"

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

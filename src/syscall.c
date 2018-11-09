#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>

struct process{
	char * name;
	int pid;
}

struct process[512] process_List;

static unsigned long syscall_getProcess(const struct process* user_List)
{
	struct task_struct * p;
	int counter = 0;

	p = NULL;
	p = &init_task;
	for_each_process(p)
	{
		process_List[counter].pid = p -> pid;
		process_List[counter].name = p ->com;
		counter++;
		if(counter>= 512)
		{
			printk("process_List Overflow.\n");
		}
	}

	if(copy_to_user(user_list,&process_List,sizeof(struct process)*counter));

	return 0;
}
static int init_syscall(void)
{
        printk(KERN_INFO "Custom syscall loaded\n");
        replace_syscall(SYSCALL_NI, (ulong)lkm_syscall);
        return 0;
}

static void cleanup_syscall(void)
{
        page_read_write((ulong)syscall_table);
        syscall_table[SYSCALL_NI] = (ulong)original_syscall;
        page_read_only((ulong)syscall_table);
        printk(KERN_INFO "Syscall at offset %d : %p\n", SYSCALL_NI, (void *)syscall_table[SYSCALL_NI]);
        printk(KERN_INFO "Custom syscall unloaded\n");
}

module_init(init_syscall);
module_exit(cleanup_syscall);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yuxiang Luo");

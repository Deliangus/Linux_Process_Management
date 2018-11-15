#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>

#include "../data_type.h"

#define SYS_CALL_TABLE "sys_call_table"
#define SYSCALL_NI __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"

static unsigned long *syscall_table = NULL;

static void *original_syscall = NULL;

static struct process process_List[512];

static unsigned long syscall_getProcess(const struct process* user_List)
{
	struct task_struct * p;
	int counter = 1;
	unsigned long status;

	p = NULL;
	p = &init_task;
	for_each_process(p)
	{
		process_List[counter].pid = p -> pid;
		strcpy(process_List[counter].name,p ->comm);
		//process_List[counter].name[16] = '\0';
		counter++;
		if(counter>= 512)
		{
			printk("process_List Overflow.\n");
		}
	}

	process_List[0].pid = counter;
	strcpy(process_List[0].name,PROCESS_LIST_HEAD);
	
	status = copy_to_user((void*)user_List,(void*)&process_List,sizeof(struct process)*512);

	if(status)
	{
		return -EFAULT;
	}

	return status;
}

static int is_syscall_table(unsigned long *p)
{
        return ((p != NULL) && (p[__NR_close] == (unsigned long)sys_close));
}

static int page_read_write(unsigned long address)
{
        unsigned int level;
        pte_t *pte = lookup_address(address, &level);

        if(pte->pte &~ _PAGE_RW)
                pte->pte |= _PAGE_RW;
        return 0;
}

static int page_read_only(unsigned long address)
{
        unsigned int level;
        pte_t *pte = lookup_address(address, &level);
        pte->pte = pte->pte &~ _PAGE_RW;
        return 0;
}

static void install_syscall(unsigned long repalce_Index,unsigned long replace_funcion)
{
	syscall_table = (unsigned long*)kallsyms_lookup_name(SYS_CALL_TABLE);

	if(is_syscall_table(syscall_table))
	{
		page_read_write((unsigned long)syscall_table);

        	original_syscall = (void *)(syscall_table[repalce_Index]);

		syscall_table[repalce_Index] = replace_funcion;

		page_read_only((unsigned long)syscall_table);
	}
}

static int init_syscall(void)
{
        install_syscall(SYSCALL_NI, (unsigned long)syscall_getProcess);
		printk(KERN_INFO "Custom syscall loaded\n");
        return 0;
}

static void cleanup_syscall(void)
{
        page_read_write((unsigned long)syscall_table);
        syscall_table[SYSCALL_NI] = (unsigned long)original_syscall;
        page_read_only((unsigned long)syscall_table);
        printk(KERN_INFO "Syscall at offset %d : %p\n", SYSCALL_NI, (void *)syscall_table[SYSCALL_NI]);
        printk(KERN_INFO "Custom syscall unloaded\n");
}

module_init(init_syscall);
module_exit(cleanup_syscall);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yuxiang Luo");

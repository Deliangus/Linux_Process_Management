#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>

#define SYS_CALL_TABLE "sys_call_table"
#define SYSCALL_NI __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"

static ulong *syscall_table = NULL;

static void *original_syscall = NULL;

struct process{
	char * name;
	int pid;
}

struct process[512] process_List;

static unsigned long syscall_getProcess(const struct process* user_List)
{
	struct task_struct * p;
	int counter = 1;

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

	process_List[0].pid = counter;
	process_list[0].name = PROCESS_LIST_HEAD;
	
	ulong status = copy_to_user(user_list,&process_List,sizeof(struct process)*counter);

	return status;
}

static int is_syscall_table(ulong *p)
{
        return ((p != NULL) && (p[__NR_close] == (ulong)sys_close));
}

static int page_read_write(ulong address)
{
        uint level;
        pte_t *pte = lookup_address(address, &level);

        if(pte->pte &~ _PAGE_RW)
                pte->pte |= _PAGE_RW;
        return 0;
}

static int page_read_only(ulong address)
{
        uint level;
        pte_t *pte = lookup_address(address, &level);
        pte->pte = pte->pte &~ _PAGE_RW;
        return 0;
}

static void install_syscall(ulong repalce_Index,ulong replace_funcion)
{
	syscall_table = (ulong*)kallsyms_lookup_name(SYS_CALL_TABLE);

	if(is_syscall_table(syscall_table))
	{
		page_read_write((ulong)syscall_table);

        original_syscall = (void *)(syscall_table[repalce_Index]);

		syscall_table[repalce_Index] = replace_funcion;

		page_read_only((ulong)syscall_table);
	}
}

static int init_syscall(void)
{
        install_syscall(SYSCALL_NI, (ulong)syscall_getProcess);
		printk(KERN_INFO "Custom syscall loaded\n");
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

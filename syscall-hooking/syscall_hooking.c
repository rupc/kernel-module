/**
 * @file syscall_hooking.c
 * @brief variation of syscall hooking via dynamic loading kernel module. It locates sys_call_table and intercept system call invoked.
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/hugetlb.h>

#define SEARCH_BASE ffffffff81000000
#define SEARCH_OFFSET ffffffffa1000000

#define SYSTABLE_LOC ffffffff81a001c0 /* My system */

/* const sys_call_ptr_t sys_call_table; */
unsigned long **sys_call_table;

unsigned long **locate_sys_call_table(void)
{
    unsigned long temp;
    unsigned long *p;
    unsigned long **sys_table;

    for (temp = SEARCH_BASE; temp < SEARCH_OFFSET; temp+=sizeof(void *)) {
        p = (unsigned long *)temp;

        if ( p[__NR_close] == (unsigned long)sys_close) {
            sys_table = (unsigned long **)p;
            return &sys_table[0];
        }

    }
    return NULL;
}

asmlinkage long (*original_call)(const char __user *, int, umode_t);

asmlinkage long sys_our_open(const char __user *filename, int flags, umode_t mode) {
    printk("open system call\n");
    return (original_call(filename, flags, mode));
}


int syscall_hooking_init(void)
{
    unsigned long cr0;

    if ((sys_call_table = locate_sys_call_table()) == NULL) {
        printk("Can't find sys_call_table\n");
    }
    return 0;
}

void syscall_hooking_cleanup(void)
{
    return;
}
    
module_init(syscall_hooking_init);
module_exit(syscall_hooking_cleanup);
MODULE_LICENSE("GPL");
    

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
#include <asm/syscall.h>
#include <asm/unistd.h>

#define SEARCH_BASE ffffffff81000000
#define SEARCH_OFFSET ffffffffa1000000

#define SYSTABLE_LOC ffffffff81a001c0 /* My system */

const sys_call_ptr_t sys_call_table;

}
int syscall_hooking_init(void)
{
    return 0;
}

void syscall_hooking_cleanup(void)
{
    return;
}
    
module_init(syscall_hooking_init);
module_exit(syscall_hooking_cleanup);
MODULE_LICENSE("GPL");
    

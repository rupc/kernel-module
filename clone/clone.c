/**
 * @file clone.c
 * @brief test kernel thread
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#define _GNU_SOURCE
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
/* #include <asm/unistd.h> */

#define SYSTHREAD_STK_SIZE (PAGE_SIZE * 2)

void *systhread_stack;

int systhread_work(void * args) {
    struct task_struct *task;
    task = current;
    printk("pid %d ppid %d tgid %d\n", task->pid, task->real_parent->pid, task->tgid);
    return 0;
}

int clone_init(void)
{
    struct task_struct *task;
    pid_t kt;
    task = current;

    printk("%d\n", (int)SYSTHREAD_STK_SIZE);
    printk("%d[%d]\n", task->pid, task->tgid);

    systhread_stack = kmalloc(SYSTHREAD_STK_SIZE, GFP_KERNEL);

    kt = kernel_thread(systhread_work, 0, CLONE_VM | CLONE_FS | CLONE_FILES);

    if (!systhread_stack) {
        printk("error\n");
    }
    printk("%d %d\n", kt, sizeof(systhread_stack));
    return 0;
}

void clone_cleanup(void)
{
    kfree(systhread_stack);
    return;
}
    
module_init(clone_init);
module_exit(clone_cleanup);
MODULE_LICENSE("GPL");
    

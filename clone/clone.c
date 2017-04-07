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
    task = current;
    printk("%d\n", (int)SYSTHREAD_STK_SIZE);
    printk("%d[%d]\n", task->pid, task->tgid);

    systhread_stack = kmalloc(SYSTHREAD_STK_SIZE, GFP_KERNEL);

    clone(systhread_work, systhread_stack, CLONE_VM | CLONE_FS | CLONE_FILES, 0);

    if (!systhread_stack) {
        printk("error\n");
    }
    printk("%d\n", sizeof(systhread_stack));
    kfree(systhread_stack);
    return 0;
}

void clone_cleanup(void)
{
    return;
}
    
module_init(clone_init);
module_exit(clone_cleanup);
MODULE_LICENSE("GPL");
    

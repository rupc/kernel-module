/**
 * @file kthread.c
 * @brief playing with kthread APIs
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/time.h> 

#define MAX_NAME 64

static struct task_struct *systhread;

static void print_task_info(struct task_struct *task) 
{
    printk("\n%8s%8s%8s%8s%12s%8s\n",
            "pid", "tgid", "ppid",
            "state", "priority", "policy");
    printk("%8d%8d%8d%8d%12d%8d\n",
            task->pid, task->tgid,
            task->parent->pid, task->state,
            task->prio, task->policy);
}

int thread_fn(void *args)
{
    unsigned long j0,j1;
    int delay = 60*HZ;
    j0 = jiffies;
    j1 = j0 + delay;

    printk(KERN_INFO "In Thread Function");
    print_task_info(current);

    while (time_before(jiffies, j1))
        schedule();

    return 0;
}

int kthread_jiffies (void)
{

    char our_thread[MAX_NAME]="systhread1";

    printk(KERN_INFO "In Init Function");
    print_task_info(current);

    systhread = kthread_create(thread_fn,NULL,our_thread);
    
    if((systhread))
    {
        printk(KERN_INFO "in init");
        wake_up_process(systhread);
    }

    return 0;
}

struct task_struct *changing_thread;

int task_state_change(void *args)
{
    printk("In task_state_change\n");
    print_task_info(current);
    return 0;
}

static void kthread_task_state_change(void)
{
    char tname[MAX_NAME] = "thread2";

    changing_thread = 
        kthread_create(task_state_change, 
                NULL, tname);

    printk("In parent thread\n");
    print_task_info(current);
    if (changing_thread) {
        wake_up_process(changing_thread);
    }

}



int __init kthread_init(void)
{
    /* kthread_jiffies(); */
    kthread_task_state_change();
    return 0;
}

void __exit kthread_cleanup(void)
{
    /* if (!kthread_stop(systhread) {
        printk("thread stopped\n");
    } */

    if(!kthread_stop(changing_thread)) 
        printk("thread stopped\n");
    
    return;
}
    
module_init(kthread_init);
module_exit(kthread_cleanup);
MODULE_LICENSE("GPL");
    

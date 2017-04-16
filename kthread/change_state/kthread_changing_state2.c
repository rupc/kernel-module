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

struct task_struct *changing_thread;

int task_state_change(void *args)
{
    return 0;
}

static void kthread_task_state_change(void)
{
    char tname[MAX_NAME] = "thread2";

    changing_thread = 
        kthread_create(task_state_change, 
                NULL, tname);

    printk("In parent thread");
    print_task_info(current);

    printk("Before wake up");
    print_task_info(changing_thread);
    if (changing_thread) {
        wake_up_process(changing_thread);
    }
    printk("After wake up");
    print_task_info(changing_thread);


    printk("After set_task_state(INTERRUPTIBLE)");
    set_task_state(changing_thread, TASK_UNINTERRUPTIBLE);
    print_task_info(changing_thread);

    schedule();
    printk("After schedule()\n");
    print_task_info(changing_thread);
}



int __init kthread_init(void)
{
    kthread_task_state_change();
    return 0;
}

void __exit kthread_cleanup(void)
{

    if(!kthread_stop(changing_thread)) 
        printk("thread stopped\n");
    
    return;
}
    
module_init(kthread_init);
module_exit(kthread_cleanup);
MODULE_LICENSE("GPL");
    

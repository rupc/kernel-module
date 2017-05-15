/**
 * @file hello_task.c
 * @brief practice task api
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/workqueue.h>



int hello_task_init(void)
{
    /* struct task_struct *task;
    struct list_head *list; */
    /* struct task_struct *my_parent = current->parent; */

    /* list_for_each(list, &current->children) {
      task = list_entry(list, struct task_struct, sibling);
      printk("%ld on_cpu[%d]\n", task->state, task->on_cpu);
    } */

    printk("sizeof(struct task struct *) %ld\n", sizeof(struct task_struct *));
    printk("sizeof(struct work_sturct *) %ld\n", sizeof(struct work_struct *));

    printk("sizeof(struct task_struct) %ld\n", sizeof(struct task_struct));
    printk("sizeof(struct work_sturct) %ld\n", sizeof(struct work_struct));
    /* for_each_process(task) {
        [>printk("%s[%d]\n", task->comm, task->pid);<]
        [>printk("%s[%d]:%ld on_cpu[%d]\n", task->comm, task->pid, task->state, task->on_cpu);<]
        [>printk("%s[%d]:%ld cpu_allowed[%d]\n", task->comm, task->pid, task->state, task->nr_cpus_allowed);<]
    } */
    return 0;
}

void hello_task_cleanup(void)
{
    return;
}
    
module_init(hello_task_init);
module_exit(hello_task_cleanup);
MODULE_LICENSE("GPL");
    

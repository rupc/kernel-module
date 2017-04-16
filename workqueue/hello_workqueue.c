#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>

#define printd() \
    printk(KERN_ALERT "workqueue_test: %s %d\n", __FUNCTION__, __LINE__); 

struct workqueue_struct *my_workqueue;
struct work_struct mywork1;
struct work_struct mywork2;

static void flexsc_work1_handler(void *args);
static void flexsc_work2_handler(void *args);

extern void destory_workqueue(struct workqueue_struct *wq);

static void basic_workqueue(void)
{
    my_workqueue = create_workqueue("flexsc_workqueue");
    /* statically made work. Not fit for kernel module */
    /* DECLARE_WORK(flexsc_work1, flexsc_work1_handler); */
    /* DECLARE_WORK(flexsc_work2, flexsc_work2_handler); */

    /* Declare two work dynamically */
    INIT_WORK(&mywork1, flexsc_work1_handler);
    INIT_WORK(&mywork2, flexsc_work2_handler);

    /* Put a work into workqueue */
    queue_work(my_workqueue, &mywork1);
    printk("after queuing work1\n");

    /* Put a work into workqueue */
    queue_work(my_workqueue, &mywork2);
    printk("after queuing work2\n");
    

    schedule_work(&mywork1);
    schedule_work(&mywork2);

    /* show_workqueue_state(); */
    
}



static int __init hello_workqueue_init(void)
{
    printd();
    basic_workqueue();
    return 0;
}

static void __exit hello_workqueue_cleanup(void)
{
    flush_workqueue(my_workqueue);
    destroy_workqueue(my_workqueue);
    return;
}

static void flexsc_work2_handler(void *args)
{
    printk("dinka - closer!\n");
}

static void flexsc_work1_handler(void *args)
{
    printk("my heart is go on!\n");
}
    
module_init(hello_workqueue_init);
module_exit(hello_workqueue_cleanup);
MODULE_LICENSE("GPL");

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>

struct workqueue_struct *keventd_wq;
struct work_struct mywork1;
struct work_struct mywork2;

static void flexsc_work1_handler(void *args);
static void flexsc_work2_handler(void *args);

extern void destory_workqueue(struct workqueue_struct *wq);

static int __init hello_workqueue_init(void)
{
    keventd_wq = create_workqueue("flexsc_workqueue");

    /* DECLARE_WORK(flexsc_work1, flexsc_work1_handler); */
    /* DECLARE_WORK(flexsc_work2, flexsc_work2_handler); */

    INIT_WORK(&mywork1, flexsc_work1_handler);
    INIT_WORK(&mywork2, flexsc_work2_handler);

    /* queue_work(keventd_wq, flexsc_work1); */
    /* printk("after queuing work1\n"); */

    /* queue_work(keventd_wq, flexsc_work2); */
    /* printk("after queuing work2\n"); */

    queue_work(keventd_wq, &mywork1);
    printk("after queuing work1\n");

    queue_work(keventd_wq, &mywork2);
    printk("after queuing work2\n");
    
    schedule_work(&mywork1);
    schedule_work(&mywork2);

    return 0;
}

static void __exit hello_workqueue_cleanup(void)
{
    flush_workqueue(keventd_wq);
    destroy_workqueue(keventd_wq);
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

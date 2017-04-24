#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/types.h>

#define printd() \
    printk(KERN_ALERT "workqueue_test: %s %d\n", __FUNCTION__, __LINE__); 

struct workqueue_struct *my_workqueue;
struct work_struct mywork1;
struct work_struct mywork2;

static void flexsc_work1_handler(struct work_struct *work);
static void flexsc_work2_handler(struct work_struct *work);

extern void destory_workqueue(struct workqueue_struct *wq);

static void flexsc_work2_handler(struct work_struct *work)
{
    printk("dinka - closer!\n");
}

static void flexsc_work1_handler(struct work_struct *work)
{
    printk("my heart is go on!\n");
}
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

/* Note that worker thread function prototype
 * 
 * typedef void (*work_func_t)(struct work_struct *work); 
 *
*/

static int cnt = 0;
void syswork_thread(struct work_struct *work)
{
    /* printk("work's data: %d\n", (int64_t)(work->data)); */
    if (cnt % 100 == 0) {
        printk("%d\n", cnt++);
        
    }
    ++cnt;
}

struct workqueue_struct *cwqueue;

void modern_wq(void)
{
    unsigned long num = 5;
    unsigned long *pnum = &num;
    const int nwork = 6;
    int i;

    #define MAX_WORK 100000
    #define MAX_WORKER 1 
    static struct work_struct sys_work[MAX_WORK];

    cwqueue = alloc_workqueue("hello_queue", WQ_MEM_RECLAIM, MAX_WORKER);

    for (i = 0; i < MAX_WORK; i++) {
        INIT_WORK(&sys_work[i], syswork_thread);
        /* sys_work[i].data = ,cc; */

        /* set_work_data(&sys_work[i], pnum++, 0); */

        /* queue_work_on(5, cwqueue, &sys_work[i]); */
    }
    for (i = 0; i < MAX_WORK; i++) {
        /* queue_work(cwqueue, &sys_work[i]); */
        queue_work_on(0, cwqueue, &sys_work[i]);
    }

}


static int __init hello_workqueue_init(void)
{
    printd();
    /* basic_workqueue(); */
    modern_wq();
    return 0;
}

static void __exit hello_workqueue_cleanup(void)
{
    /* flush_workqueue(my_workqueue);
    destroy_workqueue(my_workqueue); */
    printk("Module Exit: hello_workqueue \n");
    destroy_workqueue(cwqueue);

    return;
}

    
module_init(hello_workqueue_init);
module_exit(hello_workqueue_cleanup);
MODULE_LICENSE("GPL");

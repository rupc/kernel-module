#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kfifo.h>

void hello_queue(void)
{
    struct kfifo fifo;
    int ret;

    ret = kfifo_alloc(&fifo, PAGE_SIZE, GFP_KERNEL);
    if (ret) {
        return ret;
    }

    printk(KERN_EMERG "size of TASK_SIZE is %ld\n", TASK_SIZE);
    printk(KERN_EMERG "size of PAGE_SIZE is %ld\n", PAGE_SIZE);
    printk(KERN_EMERG "size of BITS_PER_LONG is %d\n", BITS_PER_LONG);
    printk(KERN_EMERG "size of BITS_PER_LONG is %d\n", BITS_PER_LONG);
    printk(KERN_EMERG "size of L1_CACHE_BYTES %d\n", L1_CACHE_BYTES);
}
int hello_queue_init(void)
{
    hello_queue();
    return 0;
}

void hello_queue_cleanup(void)
{
    return;
}
    
module_init(hello_queue_init);
module_exit(hello_queue_cleanup);
MODULE_LICENSE("MIT");

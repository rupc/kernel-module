#include <linux/kernel.h>
#include <linux/module.h>

int hello_mmap_init(void)
{
    printk(KERN_EMERG "hello mmap!\n");
    return 0;
}

void hello_mmap_cleanup(void)
{
    return;
}
    
module_init(hello_mmap_init);
module_exit(hello_mmap_cleanup);
MODULE_LICENSE("GNU GPL v3.0");
    

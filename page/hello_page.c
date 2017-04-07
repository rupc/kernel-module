#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gfp.h> // __get_free_pages

unsigned long page;
#define REQUESTED_PAGES 3
int hello_page_init(void)
{
    page = __get_free_pages(GFP_KERNEL, REQUESTED_PAGES);
    if (!page) {
        return -ENOMEM;
    }
    printk(KERN_EMERG "%lx\n", page);
    printk(KERN_EMERG "%d\n", sizeof(long));
    return 0;
}

void hello_page_cleanup(void)
{
    free_pages(page, REQUESTED_PAGES);
    return;
}
    
module_init(hello_page_init);
module_exit(hello_page_cleanup);
MODULE_LICENSE("GPL");
    

/**
 * @file hello_cache.c
 * @brief Template to build normal kernel module. It contains Makefile, some source file
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/cache.h>



int hello_cache_init(void)
{
    printk("%d\n", L1_CACHE_BYTES);
    return 0;
}

void hello_cache_cleanup(void)
{
    return;
}
    
module_init(hello_cache_init);
module_exit(hello_cache_cleanup);
MODULE_LICENSE("GPL");
    

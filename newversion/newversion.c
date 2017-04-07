/**
 * @file newversion.c
 * @brief test on 4.9
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>



int newversion_init(void)
{
    printk(KERN_EMERG "hello world!\n");
    return 0;
}

void newversion_cleanup(void)
{
    return;
}
    
module_init(newversion_init);
module_exit(newversion_cleanup);
MODULE_LICENSE("GPL");
    

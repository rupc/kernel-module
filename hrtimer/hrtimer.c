/**
 * @file hrtimer.c
 * @brief Template to build normal kernel module. It contains Makefile, some source file
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>


int hrtimer_init(void)
{
    return 0;
}

void hrtimer_cleanup(void)
{
    return;
}
    
module_init(hrtimer_init);
module_exit(hrtimer_cleanup);
MODULE_LICENSE("GPL");
    

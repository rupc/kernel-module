/**
 * @file jiffies.c
 * @brief Template to build normal kernel module. It contains Makefile, some source file
 * @author Yongrae Jo
 * @version 1.0
 * @date 2017
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list stupid_timer;

void stupid_timer_cb(unsigned long data) 
{
    printk("current jiffies: %ld\n", jiffies);
}

/* jiffies defined in linux/timer.h is global variable
 * jiffies is updated by +1 every 4ms(250Hz)
 * */
int jiffies_init(void)
{
    int ret;
    setup_timer(&stupid_timer, stupid_timer_cb, 0);

    ret = mod_timer(&stupid_timer, jiffies + msecs_to_jiffies(200));

    if (ret) {
        printk("Stupid timer got error :(\n");
    }

    return 0;
}

void jiffies_cleanup(void)
{
    int ret;
    
    ret = del_timer(&stupid_timer);

    if (ret) {
        printk("Stupid timer got destroyed\n");
    }

    printk("Stupid timer uninstalled\n");

    return;
}
    
module_init(jiffies_init);
module_exit(jiffies_cleanup);
MODULE_LICENSE("GPL");
    

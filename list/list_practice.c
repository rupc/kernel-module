#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

struct fox {
    unsigned long tail_length;
    unsigned long weight;
    bool is_fantastic;
    struct list_head list;
};

int list_practice_init(void)
{
    struct fox *red_fox;
    red_fox = kmalloc(sizeof(*red_fox), GFP_KERNEL);
    red_fox->tail_length = 40;
    red_fox->weight = 6;
    red_fox->is_fantastic = false;
    /* get pointer as argument */
    INIT_LIST_HEAD(&red_fox->list);

    struct fox blue_fox = {
        .tail_length = 30,
        .weight = 3,
        .is_fantastic = true,
        /* get the normal variable as argument */
        .list = LIST_HEAD_INIT(blue_fox.list),
    };
    /* declaration of list head */
    LIST_HEAD(fox_list);

    /* add an element at head */
    list_add(&red_fox->list, &fox_list);
    list_add(&blue_fox.list, &fox_list);

    struct fox yellow_fox = {
        .tail_length = 10,
        .weight = 10,
        .is_fantastic = false,
        .list = LIST_HEAD_INIT(yellow_fox.list),
    };

    list_add_tail(&yellow_fox.list, &fox_list);

    if (list_empty(&fox_list) == 0) {
        printk(KERN_EMERG "list has something in it!\n");
    } else {
        printk(KERN_EMERG "list is empty!\n");
    }

    struct list_head *iterator;
    struct fox *f;

    /* Iteration of kernel list */
    list_for_each(iterator, &fox_list) {
        f = list_entry(iterator, struct fox, list);
        printk(KERN_EMERG "%ld\n", f->tail_length);
    }

    list_for_each_entry(f, &fox_list, list) {
        printk(KERN_EMERG "list_for_each_entry : %ld\n", f->weight);
    }

    list_for_each_entry_reverse(f, &fox_list, list) {
        printk(KERN_EMERG "list_for_each_entry_reverse : %ld\n", f->weight);
    }

    /* list_add(&blue_fox.list, red_fox->list); */

    /* struct *fox_indicator; */
    printk(KERN_EMERG "hello list practice module!\n");

    return 0;
}

void list_practice_cleanup(void)
{
    return;
}
    
module_init(list_practice_init);
module_exit(list_practice_cleanup);
MODULE_LICENSE("MIT");

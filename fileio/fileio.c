#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <asm/uaccess.h>

int fd;
loff_t pos = 0;
struct file *flip;
mm_segment_t old_fs;

struct file* open_in_module(char *name, int flags, int perms)
{
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    if ( (flip = filp_open(name, flags, perms)) < 0) {
        return NULL;
    }
    return flip;
}

int close_in_module(struct file *flip)
{
    if (flip) {
        filp_close(flip, NULL);
        pos = 0;
        set_fs(old_fs);
        return 0;
    }
    return -1;
}
int write_in_module(struct file *flip, char *data, int count)
{
    if (flip) {
        return vfs_write(flip, data, count, &pos);
    }
    return -1;
}

int read_in_module(struct file *flip, char *data, int count)
{
    if (flip) {
        return vfs_read(flip, data, count, &pos);
    }
    return -1;
}

int fw_module_init(void)
{
    struct file *fp;
    printk(KERN_EMERG "File write test module\n");
    if ( (fp = open_in_module("/root/test.txt", O_CREAT | O_RDWR, 0644)) == NULL) {
        printk("<0> file create error\n");
        return -1;
    }

    if (write_in_module(fp, "test string from kernel module\n", 31) < 0) {
        printk(KERN_EMERG "file write error\n");
        return -1;
    }

    if (close_in_module(fp) < 0) {
        printk(KERN_EMERG "file close error\n");
        return -1;
    }
    return 0;
}

void fw_module_cleanup(void)
{
    printk(KERN_EMERG "Module ended\n");
}

module_init(fw_module_init);
module_exit(fw_module_cleanup);   
MODULE_LICENSE("GPL");

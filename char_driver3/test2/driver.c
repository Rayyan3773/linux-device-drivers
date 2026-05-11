#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>

int base_minor=0;
char* devname="mychardev";
int count = 1;
dev_t devnum;

static struct class* class=NULL;
static struct device* device=NULL;
static struct cdev mycdev;

static int device_open(struct inode* inode, struct file* file){
pr_info("%s\n", __func__);

if((file->f_flags & O_ACCMODE) == O_RDONLY){
	pr_info("opened file in read only mode\n");
}
else if((file->f_flags & O_ACCMODE) == O_WRONLY){
	pr_info("opened file in write only mode");
}
else if((file->f_flags & O_ACCMODE) == O_RDWR){
	pr_info("opened file in read write mode");
}
if (file->f_flags & O_CREAT) {
        pr_info( "Create if it does not exist");
    }

    if (file->f_flags & O_EXCL) {
        pr_info( "Provide exclusive access");
    }

    if (file->f_flags & O_TRUNC) {
        pr_info( "Truncate the file to zero size first");
    }

    if (file->f_flags & O_APPEND) {
        pr_info( "Append to the file (don't overwrite)");
    }

    if (file->f_flags & O_NONBLOCK) {
        pr_info( "Access methods are non-blocking");
    }
    if (file->f_flags & O_SYNC) {
        pr_info( "O_SYNC");
    }

    pr_info("File Offset:%llu\n", file->f_pos);
    return 0;
}

static ssize_t device_read(struct file* file, char __user* buffer, size_t length, loff_t* offset){
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_write(struct file* file, const char __user* buffer, size_t length, loff_t* offset){
	pr_info("%s\n", __func__);
	return length;
}

static int device_release(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
	return 0;
}

struct file_operations fops={
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};

static int test_init(void){
	class=class_create("myclass");
	if(!alloc_chrdev_region(&devnum, base_minor, count, devname)){
			printk("device number registered\n");
			printk("major number assigned: %d\n", MAJOR(devnum));

			device=device_create(class, NULL, devnum, NULL, devname);
			cdev_init(&mycdev, &fops);
			mycdev.owner = THIS_MODULE;
			cdev_add(&mycdev, devnum, count);
			}
	else{
	printk("device number reg failed");

	}
	return 0;

	}


static void test_exit(void){
device_destroy(class, devnum);
class_destroy(class);
cdev_del(&mycdev);
unregister_chrdev_region(devnum, count);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("this is a dummy driver to explain struct file");





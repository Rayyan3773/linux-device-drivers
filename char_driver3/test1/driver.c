#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor=0;
char* devname="mychardev";
int count =1;
dev_t devnum;

static struct class* class;
static struct device* device;
static struct cdev mycdev;

static int device_open(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
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

struct file_operations dev_fops={
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_init(void){
	class = class_create("myclass");
	
	if(!alloc_chrdev_region(&devnum, base_minor, count, devname)){
		printk("Device num registered\n");
		printk("Major num assigned: %d\n", MAJOR(devnum));

		device=device_create(class, NULL, devnum, NULL, devname);
		cdev_init(&mycdev, &dev_fops); //file operations are being set
		mycdev.owner = THIS_MODULE; // manually set owner
		cdev_add(&mycdev, devnum, count);
	}
	else{
		printk("device number reg failed\n");
	}
	return 0;
}

static void test_exit(void){
	printk("this is exit seq\n");
	device_destroy(class, devnum);
	class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devnum, count);
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("rayyanbaig");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("use of cdev_init vs cdev_alloc");



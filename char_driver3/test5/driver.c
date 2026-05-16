#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/fs.h>


int baseminor =0;
int count=1;
char*devname= "mychardev";
dev_t devnum;

static struct class* class;
static struct device* device;
static struct cdev mycdev;



static int device_open(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
	return 0;
}

static int device_release(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_read(struct file*file, char __user* buffer, size_t length, loff_t* offset){
	char k_buffer[10] = "kernel";
	int retval;
	retval = copy_to_user(buffer, k_buffer, 7);
	pr_info("%s: copy to user retruned: %d\n", __func__, retval);
	pr_info("%s: kernel_bufffer: %s \t length: %lu \t offet: %llu\n", __func__, k_buffer, length, *offset);
	return 0;
}

static ssize_t device_write(struct file*file, const char __user* buffer, size_t length, loff_t* offset){
	char k_buffer[100] = {0};
	int retval;
	
	retval = copy_from_user(k_buffer, buffer, length);
	pr_info("%s: copy from user returned: %d\n", __func__, retval);
	pr_info("%s: kernel_buffer: %s \t length: %lu \t offset:%llu\n", __func__, k_buffer, length, *offset);
	return length;
}

struct file_operations fops={
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};

static int __init test_init(void){
	class=class_create("myclass");

	if(!alloc_chrdev_region(&devnum, baseminor, count, devname)){
		printk("device number registered\n");
		printk("major number assigned: %d\n", MAJOR(devnum));

		device = device_create(class, NULL, devnum, NULL, devname);
		cdev_init(&mycdev, &fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devnum, count);
	}
	else{
		printk("device reg failed\n");
	}
	return 0;
}

static void __exit test_exit(void){
	printk("exit seq initiated\n");
	device_destroy(class, devnum);
	class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devnum, count);
}
module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");


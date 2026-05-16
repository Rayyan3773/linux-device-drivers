#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>

int base_minor = 0;
char* devname = "mychardev";
int count =1;
dev_t devnum;

static struct class* class = NULL;
static struct device* device = NULL;
static struct cdev mycdev;

static int device_open(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_read(struct file* file, char __user* buffer, size_t length, loff_t* offset){
	pr_info("%s:count:%lu \t offset:%llu\n", __func__, length, *offset);
	//pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_write(struct file* file, const char __user* buffer, size_t length, loff_t* offset){
	char k_buffer[100] = {0};
	int retval;
	pr_info("%s: kernel buffer:%p\t User buffer:%p\n", __func__, k_buffer, buffer);
	retval = copy_from_user(k_buffer, buffer, length);
	pr_info("%s: copy from user returned: %d\n", __func__, retval);
	pr_info("%s: kernel buffer: %s\t count:%lu \t offset:%llu\n", __func__, k_buffer, length, *offset);
	//pr_info("%s\n", __func__);
	return length;
}

static int device_release(struct inode* inode, struct file* file){
	pr_info("%s\n", __func__);
	return 0;
}

struct file_operations fops ={
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};

static int __init test_init(void){
	class = class_create("myclass");

	if(!alloc_chrdev_region(&devnum, base_minor, count, devname)){
		printk("device numgistered\n");
		printk("Major numbigned: %d\n", MAJOR(devnum));

		device = device_create(class, NULL, devnum, NULL, devname);
		cdev_init(&mycdev, &fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devnum, count);

	}
	else{
		printk("device reg failed");
	}
	return 0;
}

static void __exit test_exit(void){
	device_destroy(class, devnum);
	class_destroy(class);

	cdev_del(&mycdev);
	unregister_chrdev_region(devnum, count);

}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ex: copy_from_user");


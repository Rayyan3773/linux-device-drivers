#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor = 0;
char* devname = "mychardev";
int count = 1;
dev_t devnum;

static struct class* class=NULL;
static struct device* device=NULL;
static struct cdev mycdev;

static int device_open(struct inode* inode, struct file* file){
	pr_info("%s File: %p inode: %p\n", __func__, file, inode); //to check the file and inode numbers, 
								   //when we call the userapp multiple times: the file number might change, but the inode number will remain same
								   //as file is closed through release function the file changes, but inode internally points to the same location of file
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
	.read = device_read,
	.open = device_open,
	.write = device_write,
	.release = device_release
};


static int test_init(void){
	class = class_create("myclass");

	if(!alloc_chrdev_region(&devnum, base_minor, count, devname)){
		printk("device num registered\n");
		printk("major num assigned: %d\n", MAJOR(devnum));

		device = device_create(class, NULL, devnum, NULL, devname);

		cdev_init(&mycdev, &fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devnum, count);
	}
	else{
		printk("device num reg failed");
	}

	return 0;
}

static void test_exit(void){
	printk("start of exit seq\n");
	device_destroy(class, devnum);
	class_destroy(class);

	cdev_del(&mycdev);
	unregister_chrdev_region(devnum, count);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EXAMPLE FOR STRUCT INODE VS STRUCT FILE");


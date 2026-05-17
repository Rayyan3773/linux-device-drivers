#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>


int baseminor = 0;
int count =1;
char* devname= "msg";
dev_t devnum;

static struct class* class = NULL;
static struct device* device = NULL;
static struct cdev mycdev;

#define MAX_SIZE 1024
char kernel_buffer[MAX_SIZE];
int buffer_index;


static int device_open(struct inode* inode, struct file* file)
{
	pr_info("%s\n", __func__);
	file -> f_pos=0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode* inode, struct file*file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_read(struct file* file, char __user* user_buffer, size_t read_count, loff_t* offset)
{
	int retval;

	pr_info("%s read offset: %lld\n", __func__, *offset);
	if(buffer_index + read_count > MAX_SIZE){
		pr_err("%s: buffer_index: %d \t read_count: %lu \t max size: %d\n", __func__, buffer_index, read_count, MAX_SIZE);
		return -ENOSPC;
	}

	retval = copy_to_user(user_buffer, kernel_buffer+*offset, read_count);
	pr_info("%s: copy to user returned: %d\n", __func__, retval);
	
	*offset += read_count; //updating offset
	
	return read_count;
}

static ssize_t device_write(struct file* file, const char __user* user_buffer, size_t write_count, loff_t* offset)
{
	int retval;

	pr_info("%s write offset: %lld\n", __func__, *offset);
	if(buffer_index + write_count > MAX_SIZE){
		pr_err("%s: buffer_index: %d \t write_count: %lu \t max size: %d\n", __func__, buffer_index, write_count, MAX_SIZE);
		return -ENOSPC;
	}

	retval = copy_from_user(kernel_buffer + buffer_index, user_buffer, write_count);
	pr_info("%s: copy from user returned: %d\n", __func__, retval);
	pr_info("%s: kernel_buffer: %s\n", __func__, kernel_buffer);

	buffer_index += write_count;
	*offset += write_count; // updating offset
	return write_count;
}


struct file_operations fops={
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write
};


static int __init test_init(void){
	class = class_create("myclass");

	if(!alloc_chrdev_region(&devnum, baseminor, count, devname)){
		printk("device number registered\n");
		printk("major number assigned: %d\n", MAJOR(devnum));

		device = device_create(class, NULL, devnum, NULL, devname);
		cdev_init(&mycdev, &fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devnum, count);
	}
	else{
		printk("device num reg failed\n");
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



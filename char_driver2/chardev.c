#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>

int base_minor=0;
char *devname="chardev";
int count=1;
dev_t devnum;

static struct class *class;
static struct device *device;

static int __init test_init(void){
	class = class_create("myclass");

	if(!alloc_chrdev_region(&devnum, base_minor, count, devname)){
		printk("Device Number registered\n");
		printk("Major num assigned: %d\n", MAJOR(devnum));
		device=device_create(class, NULL, devnum, NULL, devname);
	}
	else{
		printk("Device not registered");
	}
	return 0;
}

static void __exit test_exit(void){
	printk("this is exit seq\n");
	unregister_chrdev_region(devnum, count);
	device_destroy(class, devnum);
	class_destroy(class);
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("rayyanbaig");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("everything consolidated device number, device file, class, device");


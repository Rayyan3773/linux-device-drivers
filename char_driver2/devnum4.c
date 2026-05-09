#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/delay.h>

int base_minor =0;
int count =0;
char *dev_name="mychardev";
dev_t devnum;

module_param(base_minor, int, 0);
module_param(count, int, 0);
module_param(dev_name, charp,0);

static int test_init(void){
	int i=0;

	printk("Minor num: %d\n", base_minor);
	printk("Count: %d\n", count);
	printk("Device Name: %s\n", dev_name);

	for(i=0; i<512; i++){
		if(!alloc_chrdev_region(&devnum, base_minor, count, dev_name)){
			printk("Device number registered");
			printk("Major num received: %d\n", MAJOR(devnum));
		}
		else{
			printk("Device number not registered");
			return -1;
		}
		msleep(1000);
	}
	return 0;
}


static void test_exit(void){
	unregister_chrdev_region(devnum, count);
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("rayyanbaig");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("put the alloc_chrdev_region to test out the max number of major number allowed");

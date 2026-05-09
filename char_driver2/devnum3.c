#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

int base_minor=0;
char* dev_name="mychardev";
int count=1;
dev_t devnum;

module_param(base_minor, int, 0);
module_param(count, int, 0);
module_param(dev_name, charp, 0);


static int test_init(void){
	printk("Minor num: %d\n", base_minor);
	printk("Count: %d\n", count);
	printk("device name: %s\n", dev_name);

	if(!alloc_chrdev_region(&devnum, base_minor, count, dev_name)){
		printk("Device number registered\n");
		printk("Major number received: %d\n", MAJOR(devnum));
	}
	else{
		printk("Device number registration failed\n");
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
MODULE_DESCRIPTION("test driver: asking kernel fro using specific device numbers (like reserving devnum) ");


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

int major_num=120;
int minor_num=0;
char* dev_name="mychardev";
int count=1;
dev_t devnum;

module_param(major_num, int, 0);
module_param(minor_num, int, 0);
module_param(count, int, 0);
module_param(dev_name, charp, 0);


static int test_init(void){
	devnum=MKDEV(major_num, minor_num);
	printk("Major num: %d\n", MAJOR(devnum));
	printk("Minor num: %d\n", MINOR(devnum));
	printk("Count: %d\n", count);
	printk("device name: %s\n", dev_name);

	if(!register_chrdev_region(devnum, count, dev_name)){
		printk("Device number registered\n");
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

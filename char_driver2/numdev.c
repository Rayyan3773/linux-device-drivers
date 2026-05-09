#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>

static int test_init(void){
	dev_t devnum=10;
	printk("Device num: %u\n", devnum);
	printk("Major num: %d\n", MAJOR(devnum));
	printk("Minor num: %d\n", MINOR(devnum));

	devnum = MKDEV(120,3);
	printk("Device num: %u\n", devnum);
	printk("Major num: %d\n", MAJOR(devnum));
	printk("Minor num: %d\n", MINOR(devnum));

	return 0;
}

static void test_exit(void){
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("rayyanbaig");
MODULE_DESCRIPTION("this is dev num test file");
MODULE_LICENSE("GPL");

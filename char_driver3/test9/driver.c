#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");

static int __init test_init(void){
	dev_t devnum;
	char buffer[20];

	devnum=MKDEV(120,30);
	printk("devnum: %s\n", format_dev_t(buffer, devnum));
	buffer[0] = '\0';
	printk("print_dev_t returned: %d\t device number: %s\n", print_dev_t(buffer, devnum),buffer);

	return 0;
}
static void __exit test_exit(void){
}

module_init(test_init);
module_exit(test_exit);

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/device.h>

static struct class *class;

static int test_init(void){
	class= class_create("myclass");
	return 0;
}

static void test_exit(void){
	class_destroy(class);
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("rayyanbaig");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("this is a test for class_create and class_destroy");

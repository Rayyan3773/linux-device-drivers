#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/delay.h>

static struct class *class;
static struct device *device1, *device2;
dev_t dev1, dev2;

static int test_init(void){
	dev1=MKDEV(200,1);
	dev2=MKDEV(200,2);

	class = class_create("myclass");
	device1=device_create(class, NULL, dev1,NULL,  "mydevice%d", 1);
	device2=device_create(class, NULL, dev2,NULL,  "mydevice%d", 2);

	return 0;
}

static void test_exit(void){
	device_destroy(class, dev1);
	device_destroy(class, dev2);
	class_destroy(class);
}

module_init(test_init);
module_exit(test_exit);


MODULE_AUTHOR("rayyanbaig");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("test on device_create and device destroy");

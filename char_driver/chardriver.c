#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int my_char_file_open(struct inode *char_test_inode, struct file *my_char_file){
	printk(KERN_NOTICE "my char file is open now\n");
	return 0;
}

static int my_char_file_close(struct inode* char_test_inode, struct file* my_char_file){
	printk(KERN_NOTICE "my char file is close now\n");
	return 0;
}

static ssize_t my_char_file_read(struct file* my_char_file, char __user* buffer, size_t length, loff_t* my_char_offset){
	printk(KERN_NOTICE "my char file is being read\n");
	return 0;
}

static ssize_t my_char_file_write(struct file *my_char_file, const char __user *buffer, size_t length, loff_t *my_char_offset){
	printk(KERN_NOTICE "my char file is in write\n"); 
	return length; //DO NO CHANGE TO 0, IT THE WRITE SYSCALL WITH TAKE HUGE NUMBER AND NEVER END
}




static const struct file_operations my_char_file_operations ={
	.owner = THIS_MODULE,
	.open = my_char_file_open,
	.release = my_char_file_close,
	.read = my_char_file_read,
	.write = my_char_file_write,
	
};

static int __init entry_fun(void){
	printk(KERN_NOTICE "hello world from init module\n");
	register_chrdev(200, "Test Char Driver", &my_char_file_operations);
	return 0;
}

static void __exit exit_fun(void){
	printk("good bye from exit module\n");
	unregister_chrdev(200, "Test Char Driver");
}


module_init(entry_fun);
module_exit(exit_fun);

MODULE_AUTHOR("rayyan");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple hello world module");


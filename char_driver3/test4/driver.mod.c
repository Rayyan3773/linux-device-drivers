#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xe486c4b7, "device_create" },
	{ 0xd5f66efd, "cdev_init" },
	{ 0x8ea73856, "cdev_add" },
	{ 0x1595e410, "device_destroy" },
	{ 0xa1dacb42, "class_destroy" },
	{ 0x4e54d6ac, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x546c19d9, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xf64ac983, "__copy_overflow" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x653aa194, "class_create" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9f222e1e,
	0xe486c4b7,
	0xd5f66efd,
	0x8ea73856,
	0x1595e410,
	0xa1dacb42,
	0x4e54d6ac,
	0x0bc5fb0d,
	0xbd03ed67,
	0x546c19d9,
	0xa61fd7aa,
	0x092a35a2,
	0xf64ac983,
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x653aa194,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"alloc_chrdev_region\0"
	"device_create\0"
	"cdev_init\0"
	"cdev_add\0"
	"device_destroy\0"
	"class_destroy\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"__ref_stack_chk_guard\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"__copy_overflow\0"
	"__stack_chk_fail\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"class_create\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "90BFF22CCAC72125A0C69B7");

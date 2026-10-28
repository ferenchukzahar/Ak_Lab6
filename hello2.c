// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/bug.h>
#include "hello1.h"

MODULE_AUTHOR("Zakhar Ferenchuk");
MODULE_DESCRIPTION("Hello2 module - BUG_ON implementation");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to print Hello, world!");

static int __init hello2_init(void)
{
	uint i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Warning: count is %u\n", count);
	}

	/* Завдання 1.I: Замість pr_err повертаємо BUG_ON */
	BUG_ON(count > 10);

	for (i = 0; i < count; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
}

module_init(hello2_init);
module_exit(hello2_exit);

// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/bug.h>
#include "hello1.h"

MODULE_AUTHOR("Zakhar Ferenchuk");
MODULE_DESCRIPTION("Hello1 module - memory fault simulation");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(event_list);
static int print_counter = 0;

void print_hello(void)
{
	struct hello_event *event;

	event = kmalloc(sizeof(*event), GFP_KERNEL);
	
	/* Завдання 1.II: Примусова імітація помилки "начебто kmalloc повернув 0" на 5-му виклику */
	print_counter++;
	if (print_counter == 5) {
		pr_info("Simulating kmalloc failure for event 5\n");
		event = NULL;
	}

	if (!event) {
		pr_err("Memory allocation failed (simulated)\n");
	} else {
		event->time_before = ktime_get();
	}

	pr_info("Hello, world!\n");

	if (event) {
		event->time_after = ktime_get();
	}

	/* Аварія (OOPS) відбудеться тут, якщо event == NULL */
	list_add_tail(&event->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *cursor, *tmp;

	list_for_each_entry_safe(cursor, tmp, &event_list, list) {
		ktime_t duration = ktime_sub(cursor->time_after, cursor->time_before);
		pr_info("Time taken: %lld ns\n", ktime_to_ns(duration));
		list_del(&cursor->list);
		kfree(cursor);
	}
}

module_init(hello1_init);
module_exit(hello1_exit);

// SPDX-License-Identifier: Dual BSD/GPL
#ifndef HELLO1_H
#define HELLO1_H

#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/list.h>

struct hello_event {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

void print_hello(void);

#endif

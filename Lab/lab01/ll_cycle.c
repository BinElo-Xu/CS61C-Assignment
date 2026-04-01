#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node *tortoise = head, *hare = head;
    if (!hare) {
	return 0;
    }

    if (!hare->next) {
	return 0;
    }

    while (hare->next) {
	if (!hare->next->next) {
	    return 0;
	}
	hare = hare->next->next;
	tortoise = tortoise->next;
	if (hare == tortoise) {
	    return 1;
	}
    }
    return 0;
}

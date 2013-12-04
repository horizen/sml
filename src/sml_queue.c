/*
 * queue.c
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */


#include "sml_queue.h"

void sml_queue_sort(sml_queue_t *h, int (*cmp)(const sml_queue_t*, const sml_queue_t*))
{
	sml_queue_t *q = sml_queue_first(h);
	if(q == sml_queue_last(h))
		return;
	sml_queue_t *prev, *next;
	for(q = sml_queue_next(q); q != sml_queue_head(h); q = next) {
		prev = sml_queue_prev(q);
		next = sml_queue_next(q);
		sml_queue_remove(q);
		while(prev != sml_queue_head(h)) {
			if(cmp(prev, q) <= 0)
				break;
			prev = sml_queue_prev(prev);
		}
		sml_queue_insert_after(prev, q);
	}
}


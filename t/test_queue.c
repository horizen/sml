/*
 * test_queue.c
 *
 *  Created on: 2013年10月24日
 *      Author: yw
 */

#include <sml_config.h>
#include "sml_queue.h"
#include "mutest.h"

typedef struct node
{
	int data;
	sml_queue q;
}node;

int cmp(const sml_queue *a, const sml_queue *b) {
	node *aa = sml_queue_data(a, node, q);
	node *bb = sml_queue_data(b, node, q);
	return aa->data - bb->data;
}

void mu_test_sml_queue()
{
	sml_queue head;
	sml_queue_init(&head);
	sml_queue *q;
	for(int i=0; i < 40; i++) {
		node *val= (node *)malloc(sizeof(node));
		val->data = i;
		if(i & 1) {
			sml_queue_insert_tail(&head, &(val->q));
		}
		else {
			sml_queue_insert_head(&head, &(val->q));
		}
	}
	q = sml_queue_first(&head);
	int j = 38, k = 1;
	while(q != sml_queue_head(&head)) {
		node *val = sml_queue_data(q, node, q);
		mu_check(val->data == j);
		//printf("%d ", val->data);
		if(j == 0) break;
		j -= 2;
		q = sml_queue_next(q);
	}
	q = sml_queue_next(q);
	while(q != sml_queue_head(&head)) {
		node *val = sml_queue_data(q, node, q);
		mu_check(val->data == k);
		//printf("%d ", val->data);
		k += 2;
		q = sml_queue_next(q);
	}
	sml_queue_sort(&head, cmp);
	q = sml_queue_first(&head);
	j = 0;
	while(q != sml_queue_head(&head)) {
		node *val = sml_queue_data(q, node, q);
		mu_check(val->data == j);
		j++;
		//printf("%d ", val->data);
		q = sml_queue_next(q);
	}
	q = sml_queue_first(&head);
	while(q != sml_queue_head(&head)) {
		node *val = sml_queue_data(q, node, q);
		free(val);
		q = sml_queue_next(q);
	}
}

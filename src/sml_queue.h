/*
 * queue.h
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */

#include "sml_config.h"

#ifndef SML_QUEUE_H_
#define SML_QUEUE_H_

typedef struct sml_queue_s {
	struct sml_queue_s *prev;
	struct sml_queue_s *next;
}sml_queue_t;

#define sml_queue_init(q)				\
	(q)->prev = q;						\
	(q)->next = q

#define sml_queue_empty(q)				\
	(q == (q)->prev)

#define sml_queue_insert_tail(h, v)		\
	(h)->prev->next = v;				\
	(v)->prev = (h)->prev;				\
	(v)->next = h;						\
	(h)->prev = v

#define sml_queue_insert_head(h, v)		\
	(h)->next->prev = v;				\
	(v)->next = (h)->next;				\
	(v)->prev = h;						\
	(h)->next = v

#define sml_queue_insert_after	sml_queue_insert_head

#define sml_queue_first(h)	(h)->next
#define sml_queue_last(h)	(h)->prev
#define sml_queue_head(h)	(h)
#define sml_queue_next(q)	(q)->next
#define sml_queue_prev(q)	(q)->prev

#define sml_queue_remove(x)				\
	(x)->next->prev = (x)->prev;		\
	(x)->prev->next = (x)->next

/* split from q and h2 is the head of new queue
 */
#define sml_queue_split(h1, q, h2)		\
	(h2)->prev = (h1)->prev;			\
	(h1)->prev->next = h2;				\
	(h2)->next = q;						\
	(h1)->prev = (q)->prev;				\
	(q)->prev->next = h1;				\
	(q)->prev = h2

#define sml_queue_data(q, type, member)	\
	(type *)((u_char*)q - offsetof(type, member))

void sml_queue_sort(sml_queue_t *q, int (*cmp)(const sml_queue_t *, const sml_queue_t *));


#endif /* SML_QUEUE_H_ */

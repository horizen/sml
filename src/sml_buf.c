/*
 * sml_buf.c
 *
 *  Created on: 2013年12月4日
 *      Author: yw
 */

#include "sml_buf.h"

int sml_buf_init(sml_buf_t *buf, size_t size)
{
	// size + 1 for c string traing '\0'
	buf->start = calloc(size + 1, 1);
	if(buf->start == NULL) {
		return -1;
	}
	buf->end = buf->start + size;
	buf->pos = buf->start;
	buf->last = buf->pos;
	return 0;
}

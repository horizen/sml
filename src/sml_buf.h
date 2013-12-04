/*
 * sml_buf.h
 *
 *  Created on: 2013年12月4日
 *      Author: yw
 */

#ifndef SML_BUF_H_
#define SML_BUF_H_

#include "sml_config.h"

typedef struct sml_buf_s
{
	u_char *start;
	u_char *end;
	u_char *pos;
	u_char *last;
}sml_buf_t;

int sml_buf_init(sml_buf_t *buf, size_t size);
#endif /* SML_BUF_H_ */

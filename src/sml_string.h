/*
 * string.h
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */
#ifndef SML_STRING_H_
#define SML_STRING_H_

#include "sml_config.h"

typedef struct sml_string{
	size_t len;
	u_char *data;
}sml_string;

#define sml_str_init(str) 	{ sizeof(str) - 1, (u_char *)str }
#define sml_null_str		{ 0, NULL }
#define sml_str_set(str, text)			\
	(str)->len = sizeof(text) - 1;		\
	(str)->data = (u_char *)text
#define sml_set_null(str)				\
	(str)->len = 0; (str)->data = NULL

#define sml_tolower(c)      		(u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define sml_toupper(c)      		(u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#define sml_strcmp(s1, s2)			strcmp((const char*)s1, (const char*)s2)
#define sml_strncmp(s1, s2, n)			strncmp((const char*)s1, (const char*)s2, n)


#define sml_strstr(s1, s2)  		strstr((const char *) s1, (const char *) s2)
#define sml_strlen(s)       		strlen((const char *) s)

#define sml_strchr(s1, c)   		strchr((const char *) s1, (int) c)

#define sml_memzero(buf, n)       	(void) memset(buf, 0, n)
#define sml_memset(buf, c, n)     	(void) memset(buf, c, n)

#define sml_memcpy(dst, src, n)   	(void) memcpy(dst, src, n)
#define sml_cpymem(dst, src, n)   	(((u_char *) memcpy(dst, src, n)) + (n))

#define sml_memmove(dst, src, n)   	(void) memmove(dst, src, n)
#define sml_movemem(dst, src, n)   	(((u_char *) memmove(dst, src, n)) + (n))

#define sml_memcmp(s1, s2, n)  		memcmp((const char *) s1, (const char *) s2, n)

sml_int sml_strcasecmp(const u_char *s1, const u_char *s2);
sml_int sml_strncasecmp(const u_char *s1, const u_char *s2, size_t n);

sml_int sml_atoi(const u_char *str, size_t n, sml_int *val);
sml_int sml_atof(const u_char *str, size_t n, double *val);

#endif /* SML_STRING_H_ */

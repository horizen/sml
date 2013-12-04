/*
 * string.c
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */

#include "sml_config.h"
#include "sml_string.h"

sml_int_t sml_strcasecmp(const u_char *s1, const u_char *s2)
{
    sml_uint_t  c1, c2;

    while(1) {
        c1 = (sml_uint_t) *s1++;
        c2 = (sml_uint_t) *s2++;

        c1 = sml_toupper(c1);
        c2 = sml_toupper(c2);

        if (c1 == c2) {
            if (c1) {
                continue;
            }
            return 0;
        }
        return c1 - c2;
    }
    return 0;
}

sml_int_t sml_strncasecmp(const u_char *s1, const u_char *s2, size_t n)
{
    sml_uint_t  c1, c2;

    while (n--) {
        c1 = (sml_uint_t) *s1++;
        c2 = (sml_uint_t) *s2++;

        c1 = sml_toupper(c1);
        c2 = sml_toupper(c2);

        if (c1 == c2) {
            if (c1) {
                continue;
            }
            return 0;
        }
        return c1 - c2;
    }
    return 0;
}

sml_int_t sml_atoi(const u_char *str, size_t n, sml_int_t *value)
{
    sml_int_t  ret = 0;
    if (n == 0) {
        return SML_ERROR;
    }
    sml_int_t flag = 0;
    if(str[0] == '-' || str[0] == '+') {
    	flag = (str[0] == '-');
    	str++;
    	n--;
    }
    for(ret = 0; n--; str++) {
        if (*str < '0' || *str > '9') {
            return SML_ERROR;
        }
        ret = ret * 10 + (*str - '0');
    }
    if (flag) {
        *value = -ret;
    } else {
        *value = ret;
    }
    return 0;
}

sml_int_t sml_atof(const u_char *str, size_t n, double *value)
{
    double ret;
    sml_uint_t  dot, divnum;
    if (n == 0) {
        return SML_ERROR;
    }
    sml_int_t flag = 0;
    if(str[0] == '-' || str[0] == '+') {
        flag = (str[0] == '-');
        str++;
        n--;
    }
    for (ret = 0, dot = 0, divnum = 0; n--; str++) {
        if (*str == '.') {
            if (dot) {
                return SML_ERROR;
            }
            dot = 1;
            continue;
        }
        if (*str < '0' || *str > '9') {
            return SML_ERROR;
        }
        ret = ret * 10 + (*str - '0');
        divnum += dot;
    }
    while (divnum--) {
        ret /= 10;
    }

    if (flag) {
        *value = -ret;
    } else {
        *value = ret;
    }
    return 0;
}


//kmp next array
int sml_kmp_next(const u_char *str, size_t size, int *next)
{
	if(next == NULL || str == NULL) {
		return -1;
	}
	int i, k;
	next[0] = -1;
	i = 0;
	while(i < size - 1) {
		k = next[i];
		while(k != -1 && str[i] != str[k]) {
			k = next[k];
		}
		next[i + 1] = k + 1;
		i++;
	}
	return 0;
}

u_char *sml_kmp_strstr(const u_char *src, size_t size, const char *pat)
{
	int i, j, len;
	int *next;
	len = strlen(pat);
	next = malloc(len * sizeof(int));
	sml_kmp_next((const u_char*)pat, len, next);
	i = j = 0;
	while(i < size && j < len) {
		while(j != -1 && src[i] != pat[j]) {
			j = next[j];
		}
		i++;
		j++;
	}
	free(next);
	if(j >= len) {
		return (u_char*)src + i - len;
	}
	return NULL;
}

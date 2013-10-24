/*
 * string.c
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */

#include "sml_config.h"
#include "sml_string.h"

sml_int sml_strcasecmp(const u_char *s1, const u_char *s2)
{
    sml_uint  c1, c2;

    while(1) {
        c1 = (sml_uint) *s1++;
        c2 = (sml_uint) *s2++;

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
}

sml_int sml_strncasecmp(const u_char *s1, const u_char *s2, size_t n)
{
    sml_uint  c1, c2;

    while (n--) {
        c1 = (sml_uint) *s1++;
        c2 = (sml_uint) *s2++;

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

sml_int sml_atoi(const u_char *str, size_t n, sml_int *value)
{
    sml_int  ret = 0;
    if (n == 0) {
        return SML_ERROR;
    }
    sml_int flag = 0;
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

sml_int sml_atof(const u_char *str, size_t n, double *value)
{
    double ret;
    sml_uint  dot, divnum;
    if (n == 0) {
        return SML_ERROR;
    }
    sml_int flag = 0;
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

/*
 * test_string.c
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */

#include "sml_string.h"
#include "sml_config.h"
#include "mutest.h"

void mu_test_sml_string_null() {
	sml_str_t str = sml_null_str;
	mu_check((str.len == 0) && (str.data == NULL));
}

void mu_test_sml_string_init() {
	sml_str_t str = sml_str_init("string test");
	mu_check((str.len == 11) && (!strcmp((char*)str.data, "string test")));
}

void mu_test_sml_string_set() {
	sml_str_t str = sml_str_init("string test");
	sml_str_set(&str, "another string");
	mu_check((str.len == 14) && (!strcmp((char*)str.data, "another string")));
}

void mu_test_sml_string_setnull() {
	sml_str_t str = sml_str_init("string test");
	sml_set_null(&str);
	mu_check((str.len == 0) && (str.data == NULL));
}

void mu_test_sml_strcmp() {
	sml_str_t str = sml_str_init("test sml_strcmp");
	sml_str_t str1 = sml_str_init("test SML_STRCMP");
	mu_check(!sml_strcmp(str.data, "test sml_strcmp"));
	mu_check(sml_strcmp(str.data, "test sml_strcmpa") != 0);
	mu_check(sml_strcmp(str.data, str1.data) != 0);
}

void mu_test_sml_strncmp() {
	sml_str_t str = sml_str_init("test sml_strcmp");
	sml_str_t str1 = sml_str_init("test SML_STRCMP");
	mu_check(!sml_strncmp(str.data, str1.data, 4));
	mu_check(!sml_strncmp(str.data, "test sml_strncmp", 12));
}
void mu_test_sml_strcasecmp() {
	sml_str_t str = sml_str_init("test sml_strcmp");
	sml_str_t str1 = sml_str_init("test SML_STRCMP");
	mu_check(!sml_strcasecmp(str.data, str1.data));
}
void mu_test_sml_strncasecmp() {
	sml_str_t str = sml_str_init("test sml_strcmp");
	mu_check(!sml_strncasecmp(str.data, (u_char*)"TEST", 4));
}

void mu_test_sml_toupper() {
	char *p = "abce";
	sml_str_t str= sml_str_init("ab");
	sml_str_t *pstr = &str;
	mu_check(sml_toupper(p[0]) == 'A');
	mu_check(sml_toupper(pstr->data[1]) == 'B');
}

void mu_test_sml_tolower() {
	char *p = "ABD";
	sml_str_t str= sml_str_init("AB");
	sml_str_t *pstr = &str;
	mu_check(sml_tolower(p[2]) == 'd');
	mu_check(sml_tolower(pstr->data[1]) == 'b');
}

void mu_test_sml_strstr() {
	sml_str_t str = sml_str_init("test");
	char *p = sml_strstr(str.data, "es");
	mu_check((u_char *)p == (str.data + 1));
	p = sml_strstr(str.data, "ts");
	mu_check((u_char *)p == NULL);
}

void mu_test_sml_atoi() {
	int tag, val;
	tag = sml_atoi((u_char*)"-2345", 5, &val);
	mu_check((tag == 0) && (val == -2345));

	tag = sml_atoi((u_char*)"24445", 5, &val);
	mu_check((tag == 0) && (val == 24445));

	tag = sml_atoi((u_char*)"+2345", 5, &val);
	mu_check((tag == 0) && val == 2345);

	tag = sml_atoi((u_char*)"-23 45", 6, &val);
	mu_check(tag == SML_ERROR);
}

void mu_test_sml_atof() {
	int tag;
	double val1;
	tag = sml_atof((u_char*)"-23.45", 6, &val1);
	mu_check((tag == 0) && ((val1 - -23.45) < 10e-7));

	tag = sml_atof((u_char*)"244.45", 6, &val1);
	mu_check((tag == 0) && ((val1 - 244.45) < 10e-7));

	tag = sml_atof((u_char*)"-23 45", 6, &val1);
	mu_check(tag == SML_ERROR);

	tag = sml_atof((u_char*)"2.44.45", 7, &val1);
	mu_check(tag == SML_ERROR);

	tag = sml_atof((u_char*)"+2.4445", 7, &val1);
	mu_check((tag == 0) && ((val1 == 2.4445) < 10e-7));
}


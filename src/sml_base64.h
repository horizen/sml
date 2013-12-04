/*
 * sml_base64.h
 *
 *  Created on: 2013年10月24日
 *      Author: yw
 */

#ifndef SML_BASE64_H_
#define SML_BASE64_H_

#include "sml_string.h"
#include "sml_config.h"

void sml_encode_base64(sml_str_t *dst, sml_str_t *src);
sml_int_t sml_decode_base64(sml_str_t *dst, sml_str_t *src);



#endif /* SML_BASE64_H_ */

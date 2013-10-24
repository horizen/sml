/*
 * sml_base64.h
 *
 *  Created on: 2013年10月24日
 *      Author: yw
 */

#ifndef BASE64_H_
#define BASE64_H_

#include "sml_string.h"
#include "sml_config.h"

void sml_encode_base64(sml_string *dst, sml_string *src);
void sml_decode_base64(sml_string *dst, sml_string *src);



#endif /* BASE64_H_ */
/*
 * sml_config.h
 *
 *  Created on: 2013年10月23日
 *      Author: yw
 */

#ifndef SML_CONFIG_H_
#define SML_CONFIG_H_

#include<sml_linux_config.h>
#define SML_ERROR -1

// Define integer types with known size: int32_t, uint32_t, int64_t, uint64_t.
// If this doesn't work then insert compiler-specific definitions here:
#if defined(__GNUC__) || (defined(_MSC_VER) && _MSC_VER >= 1600)
  // Compilers supporting C99 or C++0x have stdint.h defining these integer types
  #include <stdint.h>
  #define INT64_SUPPORTED // Remove this if the compiler doesn't support 64-bit integers
#elif defined(_WIN16) || defined(__MSDOS__) || defined(_MSDOS) 
  // 16 bit systems use long int for 32 bit integer.
  typedef   signed long int int32_t;
  typedef unsigned long int uint32_t;
#elif defined(_MSC_VER)
  // Older Microsoft compilers have their own definition
  typedef   signed __int32  int32_t;
  typedef unsigned __int32 uint32_t;
  typedef   signed __int64  int64_t;
  typedef unsigned __int64 uint64_t;
  #define INT64_SUPPORTED // Remove this if the compiler doesn't support 64-bit integers
#else
  // This works with most compilers
  typedef signed int          int32_t;
  typedef unsigned int       uint32_t;
  typedef long long           int64_t;
  typedef unsigned long long uint64_t;
  #define INT64_SUPPORTED // Remove this if the compiler doesn't support 64-bit integers
#endif

typedef int32_t         sml_uint;
typedef uint32_t        sml_int;

typedef int64_t         sml_int64;
typedef uint64_t        sml_uint64;

#endif /* SML_CONFIG_H_ */

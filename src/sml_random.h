/*
 * random.h
 *
 *  Created on: 2013年10月24日
 *      Author: ys
 */

#ifndef SML_RANDOM_H_
#define SML_RANDOM_H_

#include "sml_config.h"

/* glibc rand algo */
#define sml_random_init srand
int sml_random_int (int min, int max);

/* Mersenne Twister random algo */
#define SML_MERS_N   624
#define SML_MERS_M   397
#define SML_MERS_R   31
#define SML_MERS_U   11
#define SML_MERS_S   7
#define SML_MERS_T   15
#define SML_MERS_L   18
#define SML_MERS_A   0x9908B0DF
#define SML_MERS_B   0x9D2C5680
#define SML_MERS_C   0xEFC60000

void sml_mers_random_init(sml_uint_t seed);
//void sml_mers_random_initbyarray(const sml_uint_t seeds[], size_t n);
int sml_mers_random_int(int min, int max);
double sml_mers_random_float();


/* The Mother random algo */
void sml_mother_random_init(sml_uint_t seed);
int sml_mother_random_int(int min, int max);
double sml_mother_random_float();

/* combined Mersenne and Mother random algo */
void sml_combined_random_init(sml_uint_t seed);
int sml_combined_random_int(int min, int max);
double sml_combined_random_float();

#endif /* SML_RANDOM_H_ */

#include "sml_random.h"

/* glibc rand */
int sml_random_int (int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

/* Mersenne Twister algorithm */
static sml_uint_t mt[SML_MERS_N];
static sml_int_t mti;

static sml_uint_t sml_mers_random()
{
    sml_uint_t y;

    if (mti >= SML_MERS_N) {
        //Generate SML_MERS_N words at one time
        const sml_uint_t LOWER_MASK = (1LU << SML_MERS_R) - 1;       // Lower SML_MERS_R bits
        const sml_uint_t UPPER_MASK = 0xFFFFFFFF << SML_MERS_R;      // Upper (32 - SML_MERS_R) bits
        static const sml_uint_t mag01[2] = {0, SML_MERS_A};

        int kk;
        for (kk=0; kk < SML_MERS_N-SML_MERS_M; kk++) {    
            y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
            mt[kk] = mt[kk+SML_MERS_M] ^ (y >> 1) ^ mag01[y & 1];}

        for (; kk < SML_MERS_N-1; kk++) {    
            y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
            mt[kk] = mt[kk+(SML_MERS_M-SML_MERS_N)] ^ (y >> 1) ^ mag01[y & 1];}      

        y = (mt[SML_MERS_N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[SML_MERS_N-1] = mt[SML_MERS_M-1] ^ (y >> 1) ^ mag01[y & 1];
        mti = 0;
    }

    y = mt[mti++];
    y ^=  y >> SML_MERS_U;
    y ^= (y << SML_MERS_S) & SML_MERS_B;
    y ^= (y << SML_MERS_T) & SML_MERS_C;
    y ^=  y >> SML_MERS_L;

    return y;
}

void sml_mers_random_init(sml_uint_t seed)
{
	int i;
    const sml_uint_t factor = 1812433253UL;
    mt[0]= seed;
    for (mti = 1; mti < SML_MERS_N; mti++) {
        mt[mti] = (factor * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
    }
    
    for (i = 0; i < 37; i++) {
        mt[i] = sml_mers_random();
    }
}

/* output a random float number between [0, 1) */
double sml_mers_random_float()
{
    return (double) sml_mers_random() * (1. / (65536. * 65536.));
}

/* output a random number between [min, max] */
int sml_mers_random_int(int min, int max) 
{
    if (min >= max) {
        if (min == max) return min;
        else return 0x80000000;
    }

    return (int)(sml_mers_random_float() * (double)(sml_uint_t)(max - min + 1) + min);
}



/* The Mother random algorithm */
static sml_uint_t x[5];

static sml_uint_t sml_mother_random()
{
    sml_uint64_t sum;
    sum = (sml_uint64_t)2111111111UL * (sml_uint64_t)x[3] +
        (sml_uint64_t)1492 * (sml_uint64_t)(x[2]) +
        (sml_uint64_t)1776 * (sml_uint64_t)(x[1]) +
        (sml_uint64_t)5115 * (sml_uint64_t)(x[0]) +
        (sml_uint64_t)x[4];
    x[3] = x[2];  x[2] = x[1];  x[1] = x[0];
    x[4] = (sml_uint_t)(sum >> 32);                  // Carry
    x[0] = (sml_uint_t)sum;                          // Low 32 bits of sum
    return x[0];
} 

/* this function initializes the random number generator */
void sml_mother_random_init (sml_uint_t seed)
{
    int i;
    sml_int_t s = seed;
    // make random numbers and put them into the buffer
    for (i = 0; i < 5; i++) {
        s = s * 29943829 - 1;
        x[i] = s;
    }
    // randomize some more
    for (i=0; i<19; i++) sml_mother_random();
} 

/* output a float number between [0, 1) */
double sml_mother_random_float() 
{
    return (double)sml_mother_random() * (1./(65536.*65536.));
}

/* output a number between [min, max] */
int sml_mother_random_int(int min, int max) 
{
    if (max <= min) {
        if (max == min) return min; 
        else return 0x80000000;
    }
    // Assume 64 bit integers supported. Use multiply and shift method
    sml_uint_t interval;                  // Length of interval
    sml_uint64_t longran;                 // Random bits * interval
    sml_uint_t iran;                      // Longran / 2^32

    interval = (sml_uint_t)(max - min + 1);
    longran  = (sml_uint64_t)sml_mother_random() * interval;
    iran = (sml_uint_t)(longran >> 32);

    // Convert back to signed and return result
    return (int)iran + min;
}


/* combined Mersenne Sister and Mother */

/* init combined random */
void sml_combined_random_init(sml_uint_t seed)
{
    sml_mers_random_init(seed);
    sml_mother_random_init(seed + 1);
}

/* output a float number between [0, 1) */
double sml_combined_random_float()
{
    double r = sml_mers_random_float() + sml_mother_random_float();
    if(r >= 1.) r -= 1.;
    return r;
}

/* output a number between [min, max] */
int sml_combined_random_int(int min, int max)
{
    int interval = max - min + 1;
    if(interval <= 0) {
        return 0x80000000;
    }
    int r = (int)(interval * sml_combined_random_float());
    if(r >= interval) r -= 1;
    return r + min;
}

/* test
typedef int (*prand)(int, int);
static double x2cal(int n, prand func)
{
    int i;
    int a[6] = {0};
    for (i = 0; i < n; i++) {
        a[func(0,5)]++;
    }
    printf("\n");
    double v, sum = 0;
    for (i = 0; i < 6; i++) {
        printf("%d ", a[i]);
        sum += (double)((double)a[i] * a[i] * 6.0);
    }
    v = sum / n - n;
    return v;
}
int main()
{
    int i;
    sml_mers_random_init((unsigned int)time(NULL));
    int cas = 30, n = 2000;
    while(cas--) {
        double v = x2cal(n, sml_mers_random_int);
        printf("%.4f ", v);
        n += 2000;
    }
    printf("\n");

	sml_mother_random_init((unsigned int )time(NULL));
    cas = 30, n = 2000;
    while(cas--) {
        double v = x2cal(n, sml_mers_random_int);
        printf("%.4f ", v);
        n += 2000;
    }
    printf("\n");
    
	sml_combined_random_init((unsigned int )time(NULL));
    cas = 30, n = 2000;
    while(cas--) {
        double v = x2cal(n, sml_combined_random_int);
        printf("%.4f ", v);
        n += 2000;
    }
    printf("\n");

	return 0;
}
*/

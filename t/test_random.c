#include "sml_config.h"
#include "sml_random.h"
#include "mutest.h"

typedef int (*prand)(int, int);
static double x2cal(int n, prand func)
{
	int i;
    int a[6] = {0};
    for (i = 0; i < n; i++) {
        a[func(0,5)]++;
    }

    double v, sum = 0;
    for (i = 0; i < 6; i++) {
        sum += (double)((double)a[i] * a[i] * 6.0);
    }
    v = sum / n - n;
    return v;
}
void mu_test_sml_random_glibc() {
    sml_random_init((unsigned int)time(NULL));
    int cas = 30, n = 2000;

    while(cas--) {
        double v = x2cal(n, sml_random_int);
        mu_check(v < 15.09 && v > 0.5543);
        n += 2000;
    }
}

void mu_test_sml_random_mers() {
    sml_mers_random_init((unsigned int)time(NULL));
    int cas = 30, n = 2000;

    while(cas--) {
        double v = x2cal(n, sml_mers_random_int);
        mu_check(v < 15.09 && v > 0.5543);
        n += 2000;
    }
}

void mu_test_sml_random_mother() {
    sml_mother_random_init((unsigned int)time(NULL));
    int cas = 30, n = 2000;

    while(cas--) {
        double v = x2cal(n, sml_mother_random_int);
        mu_check(v < 15.09 && v > 0.5543);
        n += 2000;
    }
}

void mu_test_sml_random_combined() {
    sml_combined_random_init((unsigned int)time(NULL));
    int cas = 30, n = 2000;

    while(cas--) {
        double v = x2cal(n, sml_combined_random_int);
        mu_check(v < 15.09 && v > 0.5543);
        n += 2000;
    }
}

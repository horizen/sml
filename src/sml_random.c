#include <stdlib.h>
#include "sml_random.h"
#include "sml_types.h"

sml_int sml_random_int (sml_int min, sml_int max) {
	return (rand() % (max - min + 1) + min);
}

#ifndef OCTAL_C
#define OCTAL_C

MU_TEST_SUITE(octal);

#include "../lib/octal.h"
#include <string.h>

/*
 * string.h	- strcmp
 */

MU_TEST(test_to_octal);

MU_TEST_SUITE(octal) {
	MU_RUN_TEST(test_to_octal);
}

MU_TEST(test_to_octal) {
	mu_check(!strcmp("1", (char *)to_octal(1, NULL, 0)));
}

#endif /* OCTAL_C */

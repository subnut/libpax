#include "test.h"

#include "../lib/octal.h"

MU_TEST(test_to_octal);
MU_TEST_SUITE(octal);

MU_TEST_SUITE(octal) {
	MU_RUN_TEST(test_to_octal);
}

MU_TEST(test_to_octal) {
	mu_check(!strcmp("1", (char *)to_octal(1, NULL, 0)));
}

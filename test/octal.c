#include "minunit.h"
#include "../lib/octal.h"

/* Test-suites (declarations) */
MU_TEST_SUITE(octal);

static void (*suites[])(void) = {
	&octal,
};

int main(void) {
	for (size_t i = 0; i < (sizeof suites/sizeof suites[0]); i++)
		MU_RUN_SUITE(suites[i]);
	MU_REPORT();
	return MU_EXIT_CODE;
}

/* Tests (declarations) */
MU_TEST(test_to_octal);

/* Test-suites */
MU_TEST_SUITE(octal) {
	MU_RUN_TEST(test_to_octal);
}

/* Tests */
MU_TEST(test_to_octal) {
	mu_check(!strcmp("1", (char *)to_octal(1, NULL, 0)));
}

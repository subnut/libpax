#include "minunit.h"
#include "../lib/octal.h"

MU_TEST(test_to_octal) {
	mu_check(!strcmp("1", (char *)to_octal(1, NULL, 0)));
}

int
main(void) {
	MU_RUN_TEST(test_to_octal);
	return MU_EXIT_CODE;
}

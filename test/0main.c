#include "minunit.h"

#include "octal.c"

static void (*suites[])(void) = {
	&octal,
};

int main(void) {
	for (size_t i = 0; i < (sizeof suites/sizeof suites[0]); i++)
		MU_RUN_SUITE(suites[i]);

	MU_REPORT();
	return MU_EXIT_CODE;
}

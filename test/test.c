#include "test.h"

int
main(void) {
	MU_RUN_SUITE(octal);
	MU_REPORT();
	return MU_EXIT_CODE;
}

#include "testing.h"

unsigned long int t_indent;
unsigned long int num_assert,	num_assert_failed;
unsigned long int num_test,	num_test_failed;
unsigned long int num_suite,	num_suite_failed;
bool t_pass, t_pass_assert,
     t_pass_test, t_pass_suite = true;

TEST(t) { ASSERT(1 == 1); }

int main(void) {
	RUN_TEST(t);
	RUN_TESTSUITE(octal);
	return T_EXITCODE;
}

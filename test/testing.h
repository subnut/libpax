#ifndef TESTING_H
#define TESTING_H

#ifndef TEST_VERBOSE
#define TEST_VERBOSE 0
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long int t_indent;
extern unsigned long int num_assert,	num_assert_failed;
extern unsigned long int num_test,	num_test_failed;
extern unsigned long int num_suite,	num_suite_failed;
extern bool t_pass, t_pass_assert,
       t_pass_test, t_pass_suite;

/*
 * stdbool.h	- bool
 * stdio.h	- printf, fprintf, stdout, stderr
 * stdlib.h	- EXIT_SUCCESS, EXIT_FAILURE
 * string.h	- strchr
 */

#define T_EXITCODE (t_pass ? EXIT_SUCCESS : EXIT_FAILURE)
#define T_PASSFAIL (t_pass ? "PASS" : "FAIL")
#define T_PRINT_PASSFAIL() _MACRO(puts(T_PASSFAIL);)
#define T_PRINT_REPORT() _MACRO(\
		if (num_assert_failed) printf("%li out of %li assertions failed\n", num_assert_failed, num_assert);\
		if (num_test_failed)   printf("%li out of %li tests failed\n", num_test_failed, num_test);\
		if (num_suite_failed)  printf("%li out of %li testsuites failed\n", num_suite_failed, num_suite);\
		T_PRINT_PASSFAIL();\
)

#define TESTSUITE(funcname) void testsuite_##funcname(void)
#define TEST(funcname)      void test_##funcname(void)

#define RUN_TEST(testname) _MACRO(\
		extern TEST(testname);\
		num_test++; t_pass_test = true;\
		test_##testname();\
		if (!t_pass_test) {num_test_failed++; t_pass = t_pass_suite = false;}\
		_LOG_TEST(t_pass_test, testname);\
)
#define RUN_TESTSUITE(suitename) _MACRO(\
		extern TESTSUITE(suitename);\
		num_suite++; t_pass_suite = true;\
		t_indent++; testsuite_##suitename(); t_indent--;\
		if (!t_pass_suite) num_suite_failed++;\
		_LOG_SUITE(t_pass_suite, suitename);\
)

#define FAIL(msg) _MACRO(\
		t_pass = false;\
		fprintf(stderr, "FAIL %s:"__FILE__":"__LINE__": %s\n", _OGNAME(__func__), msg);\
)

#define ASSERT(x) _MACRO(_ASSERT(x); _LOG_ASSERT(x);)
#define ASSERT_STR(a,b) _MACRO(\
		if (a == NULL) {\
			num_assert_failed++; t_pass_test = false; t_pass_suite = false;\
			fprintf(stderr, "");\
		};\
		_ASSERT(!strcmp(a,b));\
)
/* TODO: Complete ASSERT_STR, ASSERT_FLOAT */

#define _ASSERT(assertion) _MACRO(\
		num_assert++;\
		t_pass_assert = (assertion);\
		if (!t_pass_assert) {num_assert_failed++; t_pass_test = false; t_pass_suite = false;}\
)

#define _OGNAME(fname) \
	( strchr(fname, '_') + 1 != fname+strlen(fname) \
	? strchr(fname, '_') + 1 \
	: fname \
	)

#define _LOG_ASSERT(stmt) _MACRO(\
		bool pass = t_pass_assert;\
		if(!pass || TEST_VERBOSE) fprintf(\
			(pass ? stdout : stderr),\
			"%s (ASSERT)\t%s:"__FILE__":%i -- %s\n",\
			(pass ? "PASS" : "FAIL"),\
			_OGNAME(__func__),\
			__LINE__, #stmt\
		);\
)

#define _LOG_TEST(pass, name) _MACRO(\
		if(!pass || TEST_VERBOSE) fprintf(\
			(pass ? stdout : stderr),\
			"%s ( TEST )\t%s\n", (pass ? "PASS" : "FAIL"), #name\
		);\
)
#define _LOG_SUITE(pass, name) _MACRO(\
		if(!pass || TEST_VERBOSE) fprintf(\
			(pass ? stdout : stderr),\
			"%s %s\n", (pass ? "PASS" : "FAIL"), #name\
		);\
)

/* https://stackoverflow.com/questions/154136 */
#define _MACRO(code) do { code } while(0)

#endif /* TESTING_H */

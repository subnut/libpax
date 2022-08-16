#ifndef TEST_H
#define TEST_H

#include "minunit.h"
#undef MU_TEST_SUITE
#define MU_TEST_SUITE(suite) void suite(void)

/* test_octal.c */
MU_TEST_SUITE(octal);

#endif /* TEST_H */

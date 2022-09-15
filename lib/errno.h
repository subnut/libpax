#define _POSIX_C_SOURCE 200809L
#ifndef ERRNO_H
#define ERRNO_H

#include <errno.h>
#include <limits.h>

#define ERETURN(err) ERETURNVAL(err, -1)
#define ERETURNVAL(err, val) do { errno = err; return val; } while(0)

void libpax_perror(const char *);
const char *libpax_strerror(int);
enum {
	_E__MAX = SCHAR_MIN,	// SCHAR_MIN = -128
	E_NULL,
	E_NAME,
};

#endif /* ERRNO_H */

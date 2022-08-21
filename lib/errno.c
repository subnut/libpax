#define _POSIX_C_SOURCE 200809L
#include "errno.h"

#include <stdio.h>
#include <string.h>

/*
 * stdio.h	- stderr, f*
 * string.h	- strerror
 */

static const char *errno_desc[] = {
	/* E_NULL */	"Unexpected NULL pointer",
	/* E_NAME */	"Name contains invalid character",
};

void
libpax_perror(const char *msg)
{
	flockfile(stderr);
	if (msg != NULL && msg[0] != '\0')
		fprintf(stderr, "%s: ", msg);
	fputs(libpax_strerror(errno), stderr);
	fflush(stderr);
	funlockfile(stderr);
}

const char *
libpax_strerror(int errnum)
{
	if (errnum > -1) return strerror(errnum);
	else             return errno_desc[-errnum];
}

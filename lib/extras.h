#define _POSIX_C_SOURCE 200809L
#ifndef EXTRAS_H
#define EXTRAS_H

#define not(cond) \
	(!(cond))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"

#define free(ptr) \
	do { free(ptr); ptr = NULL; } while (0)

static inline
int fcopy(FILE *restrict in, FILE *restrict out, size_t length, size_t bufsz) {
	char *buf = NULL;
	size_t copied = 0;
	if (in == NULL || out == NULL)
		ERETURN(E_NULL);
	if (length < 0 || bufsz <= 0)
		ERETURN(EINVAL);
	if (length == 0)
		return 0;
	if ((buf = calloc(bufsz, sizeof(char))) == NULL)
		return -1;

	int rc = 0;
	flockfile(in);
	flockfile(out);
	size_t rem, chunks;
	while ((rem = length - copied) > 0) {
		chunks = rem > bufsz ? bufsz : rem;
		memset(buf, 0, bufsz * sizeof(char));
		if (fread(buf, sizeof(char), chunks, in) != chunks) goto fail;
		if (fwrite(buf, sizeof(char), chunks, out) != chunks) goto fail;
		copied += chunks;
	}
exit:	funlockfile(out);
	funlockfile(in);
	free(buf);
	return rc;

fail:	rc = -1;
	goto exit;
}

#endif /* EXTRAS_H */

/* Needed for errno.h values other than EDOM/EILSEQ/ERANGE */
#define _POSIX_C_SOURCE 200809L
#include "octal.h"

#include <errno.h>
#include <stdlib.h>
#include "extras.h"

/*
 * errno.h	- errno, EINVAL, EOVERFLOW
 * stdlib.h	- calloc
 * extras.h	- not
 */

bool
is_octal(const uint8_t *s, size_t n)
{
	for (size_t i = 0; i < n; i++)
		if not(s[i] >= '0' && s[i] <= '7')
			return false;
	return true;
}


/*
 * Returns the non-negative integer value of the octal number stored in *str.
 * In case of error, sets errno and returns the negative of errno.
 * NOTE: *str must be no longer than 21 digits.
 */
int64_t
un_octal(const uint8_t *str, size_t len)
{
	if (len > 21)
		return -(errno = EOVERFLOW);
	if not(is_octal(str, len))
		return -(errno = EINVAL);

	/* Trim extra zeroes from the left */
	while (*str == '0')
		str++, len--;

	int64_t result = 0;
	for (size_t i = 0; i < len; i++)
		result = (result << 3) | (str[i] - '0');

	return result;
}

/*
 * Returns a pointer to *buffer containing the octal form of integer.
 *
 * If *buffer is set to NULL, then it allocates a buffer of suitable size,
 * which needs to be freed by the caller.
 *
 * If given buffer is too small, it sets errno = EOVERFLOW and returns NULL.
 * In case of other errors, sets errno and returns NULL.
 */
uint8_t *
to_octal(uint64_t integer, uint8_t *buffer, size_t buflen) {
	size_t len = 0;
	while (integer >> len)
		len++;
	len++;	// For the trailing NUL

	if (buflen < len && buffer != NULL)
		return errno = EOVERFLOW,
		       NULL;
	if (buffer == NULL)
		if ((buffer = calloc(len, sizeof(uint8_t))) == NULL)
			return NULL;

	buffer[--len] = '\0';
	for (; len; integer >>= 3)
		buffer[--len] = '0' + (07 & integer);

	return buffer;
}
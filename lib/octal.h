#ifndef OCTAL_H
#define OCTAL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * stdbool.h	- bool
 * stddef.h	- size_t
 * stdint.h	- uint8_t
 */

bool is_octal(const uint8_t *, size_t);
int64_t un_octal(const uint8_t *, size_t);
uint8_t *to_octal(uint64_t, uint8_t *, size_t, bool);

#endif /* OCTAL_H */

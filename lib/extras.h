#ifndef EXTRAS_H
#define EXTRAS_H

#define not(cond) \
	(!(cond))

#define free(ptr) \
	do { free(ptr); ptr = NULL; } while (0)

static inline
int ctoi(char c) {
	return (c >= '0' && c <= '9')
		? c - '0'
		: -1
		;
}

#endif /* EXTRAS_H */

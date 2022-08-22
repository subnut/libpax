#define _POSIX_C_SOURCE 200809L
#ifndef CPIO_H
#define CPIO_H

#include <cpio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

/*
 * cpio.h	- MAGIC
 * stdio.h	- FILE
 * stdbool.h	- bool
 * stdint.h	- uint8_t
 * sys/stat.h	- struct stat
 */

#define TRAILER \
	"TRAILER!!!"

struct cpio_header {
	uint8_t  c_magic[6];	// "070707"
	uint8_t  c_dev[6];
	uint8_t  c_ino[6];
	uint8_t  c_mode[6];
	uint8_t  c_uid[6];
	uint8_t  c_gid[6];
	uint8_t  c_nlink[6];
	uint8_t  c_rdev[6];
	uint8_t  c_mtime[11];
	uint8_t  c_namesize[6];	// including the trailing NUL
	uint8_t  c_filesize[11];
};
struct cpio_record {
	uint32_t  dev;
	uint32_t  ino;
	uint16_t  mode;	// Max is 177777
	uint32_t  uid;
	uint32_t  gid;
	uint32_t  nlink;
	uint32_t  rdev;
	uint64_t  mtime;
	uint32_t  namesize;	// includes the trailing NUL
	uint64_t  filesize;
	char      filename[0777777];
	/*
	 * NOTE: char is okay because POSIX.1-2017 mandates CHAR_BIT = 8
	 * See limits.h
	 */
};
struct cpio_entry {
	struct cpio_record *rec;
	FILE *fp;
};

/*
 * Difference between header, record and file
 * ------------------------------------------
 *  header - The on-disk data structure describing an archive entry, minus c_name.
 *  record - The header with its entries converted to their native values (eg. octal to decimal).
 *           Also contains an additional entry (filename) that corresponds to the on-disk c_name.
 *  entry  - A single struct describing a single Archive Entry (ie. metadata + data).
 *           Contains only pointers.
 */

/* Create */
struct cpio_header *new_cpio_header(void);
struct cpio_record *new_cpio_record(void);

/* Read */
int	cpio_read_record(FILE *, struct cpio_record *); // TODO
int	cpio_read_entry(FILE *, struct cpio_entry *); // TODO

/* Write */
int	cpio_write_trailer(FILE *);
int	cpio_write_record(const struct cpio_record *, FILE *);
int	cpio_write_entry(const struct cpio_entry *, FILE *, size_t);
int	cpio_write_file(const char *, FILE *, size_t); // TODO: TESTME

/* Helpers */
void	cpio_header_to_record(const struct cpio_header *restrict, struct cpio_record *restrict);
void	cpio_header_from_record(struct cpio_header *restrict, const struct cpio_record *restrict);
bool	cpio_header_isvalid(const struct cpio_header *); // TODO

/* Setters */
int	cpio_record_set_filename(struct cpio_record *, const char *);
int	cpio_record_set_stat(struct cpio_record *, const struct stat *); // TODO

#endif /* CPIO_H */

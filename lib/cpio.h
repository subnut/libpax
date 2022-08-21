#ifndef CPIO_H
#define CPIO_H

#include <cpio.h>
#include <stdio.h>
#include <stdint.h>

/*
 * cpio.h	- MAGIC
 * stdio.h	- FILE
 * stdint.h	- uint8_t
 */

#define TRAILER \
	"TRAILER!!!"

struct cpio_header {
	uint8_t c_magic[6];	// "070707"
	uint8_t c_dev[6];
	uint8_t c_ino[6];
	uint8_t c_mode[6];
	uint8_t c_uid[6];
	uint8_t c_gid[6];
	uint8_t c_nlink[6];
	uint8_t c_rdev[6];
	uint8_t c_mtime[11];
	uint8_t c_namesize[6];	// including the trailing NUL
	uint8_t c_filesize[11];
};
struct cpio_metadata {
	uint32_t dev;
	uint32_t ino;
	uint16_t mode;	// Max is 177777
	uint32_t uid;
	uint32_t gid;
	uint32_t nlink;
	uint32_t rdev;
	uint64_t mtime;
	uint32_t namesize;
	uint64_t filesize;
};
struct cpio_record {
	struct cpio_metadata meta;
	uint8_t *c_filename;	// includes the trailing NUL
	uint8_t *c_data;
};

int	cpio_write_trailer(FILE *);
int	cpio_write_record(const struct cpio_record *, FILE *);
void	cpio_header_to_metadata(const struct cpio_header *restrict, struct cpio_metadata *restrict);
void	cpio_metadata_to_header(const struct cpio_metadata *restrict, struct cpio_header *restrict);
int	cpio_record_set_filename(struct cpio_record *restrict, const char *restrict);

struct cpio_header *new_cpio_header(void);
struct cpio_record *new_cpio_record(void);

#if 0
void free_cpio_record(struct cpio_record *restrict);
void free_cpio_header(struct cpio_header *restrict);
#endif

#endif /* CPIO_H */

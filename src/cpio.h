#ifndef CPIO_H
#define CPIO_H

#include <cpio.h>
#include <stdint.h>

struct cpio_record {
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
	uint8_t *c_filename;	// includes the trailing NUL
	uint8_t *c_data;
};

const struct cpio_record cpio_END = {
	.c_magic = MAGIC,
	.c_namesize = "000013",
	.c_filename = (uint8_t*)"TRAILER!!!",
};

#endif /* CPIO_H */

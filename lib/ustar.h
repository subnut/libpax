#ifndef USTAR_H
#define USTAR_H

#include <stdint.h>

/* SIZE: 512 bytes */
struct ustar_header {
	uint8_t  name[100];	// offset: 0
	uint8_t  mode[8];	// offset: 100
	uint8_t  uid[8];	// offset: 108
	uint8_t  gid[8];	// offset: 116
	uint8_t  size[12];	// offset: 124
	uint8_t  mtime[12];	// offset: 136
	uint8_t  chksum[8];	// offset: 148
	uint8_t  typeflag[1];	// offset: 156
	uint8_t  linkname[100];	// offset: 157
	uint8_t  magic[6];	// offset: 257
	uint8_t  version[2];	// offset: 263
	uint8_t  uname[32];	// offset: 265
	uint8_t  gname[32];	// offset: 297
	uint8_t  devmajor[8];	// offset: 329
	uint8_t  devminor[8];	// offset: 337
	uint8_t  prefix[155];	// offset: 345
	uint8_t  _padding[12];	// offset: 500
};

/* Two consecutive headers filled with binary zeroes */
const uint8_t ustar_EOF[1024] = {0};

#endif /* USTAR_H */

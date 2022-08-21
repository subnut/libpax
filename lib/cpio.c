#define _POSIX_C_SOURCE 200809L
#include "cpio.h"

#include <cpio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"

/*
 * cpio.h	- MAGIC
 * errno.h	- errno
 * stdbool.h	- bool
 * stdio.h	- FILE, flockfile, funlockfile
 * stdlib.h	- calloc, free
 * string.h	- strncpy
 * errno.h	- ERETURN
 */

#include "errno.h"
#include "octal.h"
#include "extras.h"

struct cpio_header *
new_cpio_header(void)
{
	struct cpio_header *data = calloc(sizeof(struct cpio_header), 1);
	if (data == NULL) return data;
	memset(data, '0', sizeof(struct cpio_header));
	memcpy(data, MAGIC, strlen(MAGIC));
	return data;
}

struct cpio_record *
new_cpio_record(void)
{
	struct cpio_record *data = calloc(sizeof(struct cpio_record), 1);
	if (data == NULL) return data;
	memset(data, 0, sizeof(struct cpio_record));
	data->filename = NULL;
	return data;
}

void
free_cpio_header(struct cpio_header *data)
{
	if (data == NULL) return;
	free(data);
}

void
free_cpio_record(struct cpio_record *data)
{
	if (data == NULL) return;
	if (data->filename != NULL)
		free(data->filename);
	free(data);
}

int
cpio_write_trailer(FILE *fp)
{
	struct cpio_record rec = {0};
	cpio_record_set_filename(&rec, TRAILER);
	return cpio_write_record(&rec, fp);
}

void
cpio_header_to_record(const struct cpio_header *restrict head, struct cpio_record *restrict rec)
{
#define COPY(param) \
	rec->param = un_octal(head->c_##param, sizeof(head->c_##param))
	COPY(dev);
	COPY(ino);
	COPY(mode);
	COPY(uid);
	COPY(gid);
	COPY(nlink);
	COPY(rdev);
	COPY(mtime);
	COPY(namesize);
	COPY(filesize);
#undef COPY
}

void
cpio_header_from_record(struct cpio_header *restrict head, const struct cpio_record *restrict rec)
{
#define COPY(param) \
	to_octal(rec->param, head->c_##param, sizeof(head->c_##param), false)
	COPY(dev);
	COPY(ino);
	COPY(mode);
	COPY(uid);
	COPY(gid);
	COPY(nlink);
	COPY(rdev);
	COPY(mtime);
	COPY(namesize);
	COPY(filesize);
#undef COPY
	memcpy(head->c_magic, MAGIC, sizeof(head->c_magic));
}

int
cpio_record_set_filename(struct cpio_record *restrict rec, const char *restrict name)
{
	char *dup;
	size_t len;

	if (rec == NULL || name == NULL)
		ERETURN(E_NULL);

	if ((len = strlen(name) + 1) > 0777777)	// +1 for the NUL byte
		ERETURN(EOVERFLOW);

	/*
	 * POSIX-1.2017 says -
	 *
	 * 	All characters shall be represented in the ISO/IEC 646:1991 standard
	 * 	IRV. For maximum portability between implementations, names should be
	 * 	selected from characters represented by the portable filename character
	 * 	set as octets with the most significant bit zero.
	 *
	 * So, we reject any names with the MSB set.
	 */
	for (int i = 0; i < strlen(name); i++)
		if (name[i] >> 7)
			ERETURN(E_NAME);

	if ((dup = strdup(name)) == NULL)
		return -1;	// errno already set by strdup

	if (rec->filename != NULL)
		free(rec->filename);

	rec->namesize = len;
	rec->filename = dup;
	return 0;
}

int
cpio_write_record(const struct cpio_record *rec, FILE *fp)
{
	if (rec == NULL || fp == NULL)
		ERETURN(E_NULL);

	struct cpio_header header;
	cpio_header_from_record(&header, rec);

#define WRITE(ptr, size, nmemb) \
	if (fwrite(ptr, size, nmemb, fp) < nmemb) return -1
	flockfile(fp);
	WRITE(&header, sizeof(header), 1);
	WRITE(rec->filename, sizeof(rec->filename[0]), rec->namesize);
	/* WRITE(rec->c_data, sizeof(rec->c_data[0]), rec->meta.filesize); */
	funlockfile(fp);
#undef WRITE

	return 0;
}

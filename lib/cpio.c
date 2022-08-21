#define _POSIX_C_SOURCE 200809L
#include "cpio.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "octal.h"

/*
 * errno.h	- errno
 * stdio.h	- flockfile, funlockfile
 * stdlib.h	- calloc
 * string.h	- strncpy
 */

struct cpio_header *
new_cpio_header(void)
{
	struct cpio_header *data = calloc(sizeof(struct cpio_header), 1);
	memset(data, '0', sizeof(struct cpio_header));
	memcpy(data, MAGIC, strlen(MAGIC));
	return data;
}

void
cpio_header_to_metadata(const struct cpio_header *restrict head, struct cpio_metadata *restrict meta)
{
#define COPY(param) \
	meta->param = un_octal(head->c_##param, sizeof(head->c_##param))
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
cpio_metadata_to_header(const struct cpio_metadata *restrict meta, struct cpio_header *restrict head)
{
#define COPY(param) \
	to_octal(meta->param, head->c_##param, sizeof(head->c_##param), false)
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
		return (errno = E_NULL),
		       -1;

	if ((len = strlen(name) + 1) > 0777777)	// +1 for the NUL byte
		return (errno = EOVERFLOW),
		       -1;

	if ((dup = strdup(name)) == NULL)
		return -1;	// errno already set by strdup

	if (rec->filename != NULL)
		free(rec->filename);

	rec->filename = dup;
	rec->namesize = len;
	return 0;
}

int
cpio_write_record(const struct cpio_record *rec, FILE *fp)
{
	if (rec == NULL || fp == NULL)
		return -(errno = EINVAL);

	struct cpio_header header;
	cpio_metadata_to_header(&rec->meta, &header);

#define WRITE(ptr, size, nmemb) \
	if (fwrite(ptr, size, nmemb, fp) < nmemb) return -errno
	flockfile(fp);
	WRITE(&header, sizeof(header), 1);
	WRITE(rec->c_filename, sizeof(rec->c_filename[0]), rec->meta.namesize);
	WRITE(rec->c_data, sizeof(rec->c_data[0]), rec->meta.filesize);
	funlockfile(fp);
#undef WRITE

	return 0;
}

int
cpio_write_trailer(FILE *fp)
{
	struct cpio_record rec = {0};
	cpio_record_set_filename(&rec, TRAILER);
	return cpio_write_record(&rec, fp);
}

#define _POSIX_C_SOURCE 200809L
#include "cpio.h"

#include <cpio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "errno.h"

/*
 * cpio.h	- MAGIC
 * errno.h	- errno
 * stdbool.h	- bool
 * stdio.h	- FILE, flockfile, funlockfile
 * stdlib.h	- calloc, free
 * string.h	- strncpy
 * errno.h	- ERETURN
 * sys/stat.h	- lstat, struct stat
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
	return data;
}

int
cpio_write_trailer(FILE *fp)
{
	struct cpio_record rec = {0};
	if (cpio_record_set_filename(&rec, TRAILER) == -1) return -1;
	return cpio_write_record(&rec, fp);
}

int
cpio_write_file(const char *fname, FILE *fp, size_t iobufsz)
{
	if (fname == NULL || fp == NULL)
		ERETURN(E_NULL);

	FILE *file;
	if ((file = fopen(fname, "r")) == NULL)
		return -1;

	int rc = 0;

	struct stat stat = {0};
	if (lstat(fname, &stat) == -1)
		goto fail;

	struct cpio_record rec = {0};
	struct cpio_entry ent = {
		.rec = &rec,
		.fp = file,
	};

	cpio_record_set_stat(&rec, &stat);
	if (cpio_record_set_filename(&rec, fname) == -1) goto fail;
	if (cpio_write_entry(&ent, fp, iobufsz) == -1) goto fail;

	int saved_errno;
exit:	saved_errno = errno;
	fclose(file);
	errno = saved_errno;
	return rc;

fail:	rc = -1;
	goto exit;
}

int
cpio_write_record(const struct cpio_record *rec, FILE *fp)
{
	if (rec == NULL || fp == NULL)
		ERETURN(E_NULL);

	struct cpio_header header;
	if (cpio_header_from_record(&header, rec) == -1)
		return -1;

	flockfile(fp);
#define WRITE(ptr, size, nmemb) \
	if (fwrite(ptr, size, nmemb, fp) < nmemb) goto fail
	WRITE(&header, sizeof(header), 1);
	WRITE(rec->filename, sizeof(rec->filename[0]), rec->namesize);
#undef WRITE
	funlockfile(fp); return 0;
fail:	funlockfile(fp); return -1;
}

int
cpio_write_entry(const struct cpio_entry *ent, FILE *fp, size_t iobufsz)
{
	if (iobufsz < 1)
		ERETURN(EINVAL);

	if (fp == NULL || ent == NULL || ent->rec == NULL
			|| (ent->rec->filesize > 0 && ent->fp == NULL))
		ERETURN(E_NULL);

	flockfile(fp);
	if (cpio_write_record(ent->rec, fp) == -1) goto fail;
	if (fcopy(ent->fp, fp, ent->rec->filesize, iobufsz) == -1) goto fail;
	funlockfile(fp); return 0;
fail:	funlockfile(fp); return -1;
}

int
cpio_record_set_filename(struct cpio_record *rec, const char *name)
{
	if (rec == NULL || name == NULL)
		ERETURN(E_NULL);

	size_t len;
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

	rec->namesize = len;
	memcpy(rec->filename, name, len);
	return 0;
}

int
cpio_header_to_record(const struct cpio_header *restrict head, struct cpio_record *restrict rec)
{
#define COPY(param) \
	rec->param = un_octal(head->c_##param, sizeof(head->c_##param)); \
	if (rec->param == -1) return -1
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
	return 0;
}

int
cpio_header_from_record(struct cpio_header *restrict head, const struct cpio_record *restrict rec)
{
#define COPY(param) \
	to_octal(rec->param, head->c_##param, sizeof(head->c_##param), false); \
	if (head->c_##param == NULL) return -1
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
	return 0;
}

void
cpio_record_set_stat(struct cpio_record *rec, const struct stat *stat)
{
#define COPY(param) \
	rec->param = stat->st_##param
	COPY(dev);
	COPY(ino);
	COPY(mode);
	COPY(uid);
	COPY(gid);
	COPY(nlink);
	COPY(rdev);
#undef COPY
	rec->mtime = stat->st_mtim.tv_sec;
	rec->filesize = stat->st_size;
}

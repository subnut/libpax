.POSIX:
.SILENT: clean test tests
include ../config.mk

all: test
test: 0main
	0main
	rm -f 0main *.o

CFLAGS	= -Wall -Wpedantic -Wno-unused-variable	# NOTE: POSIX-incompatible
LDFLAGS	= -L.. -l$(NAME) -lrt -lm		# NOTE: -l$(LIBNAME) won't work
CURL	= curl -L

.SUFFIXES:
.SUFFIXES: .c
.c: minunit.h
	@$(CC) $(CFLAGS:  = ) -o $@ $< $(LDFLAGS:  = )

MINUNIT_REF = b15ad0ae28f1a7a43881ea17defb0a4367d9582d
MINUNIT_URL = https://github.com/siu/minunit/raw/$(MINUNIT_REF)/minunit.h
minunit.h: ; $(CURL) $(MINUNIT_URL) > $@
update:
	rm -f minunit.h
	$(MAKE) $(MAKEFLAGS) minunit.h

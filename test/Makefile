.POSIX:
.SUFFIXES:
.SUFFIXES: .c
.c: ; @$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

CFLAGS	= -Wall -Wpedantic -static
LDFLAGS	= -L../lib -lpax -lrt -lm

CURL	= curl -L
TESTS	= test_octal

test: minunit.h $(TESTS)
	@for test in $(TESTS); do \
		echo "## $$test"; \
		$$test; \
	done
	@rm -f $(TESTS)

MINUNIT_URL = https://github.com/siu/minunit/raw/master/minunit.h
minunit.h: ; $(CURL) $(MINUNIT_URL) > $@
update:
	rm -f minunit.h
	$(MAKE) $(MAKEFLAGS) CURL="$(CURL)" minunit.h

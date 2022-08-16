.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o
.c.o: ; @$(CC) $(CFLAGS) -c $< $(LDFLAGS)
all: test

clean: ; @rm -f *.o test
test: tests
	@tests
	@rm -f tests *.o

CFLAGS	= -Wall -Wpedantic -Wno-unused-variable
LDFLAGS	= -L../lib -lpax -lrt -lm

CURL	= curl -L
TESTS	= test_octal

tests: $(TESTS:=.o)
tests: minunit.h
tests: test.o test.h
tests: ; @$(CC) $(CFLAGS) -o $@ test.o $(TESTS:=.o) $(LDFLAGS)

MINUNIT_REF = b15ad0ae28f1a7a43881ea17defb0a4367d9582d
MINUNIT_URL = https://github.com/siu/minunit/raw/$(MINUNIT_REF)/minunit.h
minunit.h: ; $(CURL) $(MINUNIT_URL) > $@
update:
	rm -f minunit.h
	$(MAKE) $(MAKEFLAGS) minunit.h

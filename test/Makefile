.POSIX:
.SILENT: clean test tests main
include ../config.mk

all: test
test: main ; main ; rm -f main *.o
clean: ; rm -f main *.o; cd tests && $(MK) clean

CFLAGS	= -Wall -Wpedantic -Wno-unused-variable	# NOTE: POSIX-incompatible
LDFLAGS	= -L.. -l$(NAME) -lrt -lm		# NOTE: -l$(LIBNAME) won't work

../$(LIBNAME).a: ; @cd .. && $(MK) -s lib
main: main.o testing.h ../$(LIBNAME).a
	cd tests && $(MK)
	$(CC) $(CFLAGS) -o $@ main.o tests/*.o $(LDFLAGS)

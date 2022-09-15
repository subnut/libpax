.POSIX:
include ../config.mk
all: pax
clean: ; rm -f *.o pax

IFLAGS	= -I..
LDFLAGS	= -L.. -l$(LIB)

# pax needs the library for linking to it
pax: ../$(LIBNAME).a
../$(LIBNAME).a:
	@cd .. && $(MK) -s "$(LIBNAME).a"

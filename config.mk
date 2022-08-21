.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o
.c.o: ; $(CC) $(CFLAGS:  = ) -c $< $(IFLAGS:  = )
.c:   ; $(CC) $(CFLAGS:  = ) -o $@ $< $(IFLAGS:  = ) $(LDFLAGS:  = )

NAME	= pax
ARFLAGS	= -rcs
IFLAGS	=

EXE	= $(NAME)
LIB	= $(NAME)
LIBNAME	= lib$(LIB)

# NOTE: These aren't POSIX-compatible
CFLAGS	= -fPIC -Wall -Wpedantic
CP	= cp -r

# Command aliases
MK	= $(MAKE) MAKEFLAGS="$(MAKEFLAGS)"

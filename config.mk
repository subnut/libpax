.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o
.c.o: ; $(CC) $(CFLAGS:  = ) -c $<
.c:   ; $(CC) $(CFLAGS:  = ) -o $@ $< $(LDFLAGS:  = )

NAME	= pax
ARFLAGS	= -rcs

# NOTE: These aren't POSIX-compatible
CFLAGS	= -fPIC -Wall -Wpedantic

# NOTE: Changing these will break things
LIBNAME	= lib$(NAME)
EXENAME	= $(NAME)

# Command aliases
MK	= $(MAKE) MAKEFLAGS="$(MAKEFLAGS)"

.POSIX:
.c.o: ; $(CC) $(CFLAGS:  = ) -c $<

ARFLAGS	= -rcs
NAME	= pax

EXENAME	= $(NAME)
LIBNAME	= lib$(NAME)

# NOTE: These CFLAGS aren't POSIX-compatible
CFLAGS	= -fPIC -Wall -Wpedantic

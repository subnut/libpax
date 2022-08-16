.POSIX:
include ../config.mk
lib: alib

# NOTE: sharedlib isn't POSIX-compatible
all: lib solib
clean: ; rm -f *.o $(LIBNAME).*

alib: $(LIBNAME).a
solib: $(LIBNAME).so

OBJS = octal.o
$(LIBNAME).a: $(OBJS)
$(LIBNAME).so: $(OBJS)

$(LIBNAME).a: ; $(AR) $(ARFLAGS) $@ $(OBJS)
$(LIBNAME).so: ;  $(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)

octal.o: octal.h

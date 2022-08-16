.POSIX:
include ../config.mk
lib: alib

# NOTE: sharedlib isn't POSIX-compatible
all: lib solib
clean: ; rm -f *.o $(LIBNAME).*

alib: $(LIBNAME).a
solib: $(LIBNAME).so
dylib: $(LIBNAME).dylib

OBJS = octal.o
$(LIBNAME).a: $(OBJS)
$(LIBNAME).so: $(OBJS)
$(LIBNAME).dylib: $(OBJS)

$(LIBNAME).a: ; $(AR) $(ARFLAGS) $@ $?
$(LIBNAME).so: ;  $(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)
$(LIBNAME).dylib: ;  $(CC) $(CFLAGS) -shared -dynamiclib -o $@ $(OBJS) $(LDFLAGS)

octal.o: octal.h

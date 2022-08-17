.POSIX:
include ../config.mk
lib: alib
clean: ; rm -f *.o $(LIBNAME).*

OBJS = octal.o

alib: $(LIBNAME).a
solib: $(LIBNAME).so
dylib: $(LIBNAME).dylib

$(LIBNAME).a: $(OBJS)
$(LIBNAME).so: $(OBJS)
$(LIBNAME).dylib: $(OBJS)

$(LIBNAME).a: ; $(AR) $(ARFLAGS) $@ $?
$(LIBNAME).so: ;  $(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)
$(LIBNAME).dylib: ;  $(CC) $(CFLAGS) -shared -dynamiclib -o $@ $(OBJS) $(LDFLAGS)

octal.o: octal.h

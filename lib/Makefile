.POSIX:
include ../config.mk
lib: alib
clean: ; rm -f *.o $(LIBNAME).*

OBJS = cpio.o errno.o octal.o

alib: $(LIBNAME).a
solib: $(LIBNAME).so
dylib: $(LIBNAME).dylib

$(LIBNAME).a: $(OBJS)
$(LIBNAME).so: $(OBJS)
$(LIBNAME).dylib: $(OBJS)

$(LIBNAME).a: ; $(AR) $(ARFLAGS) $@ $?
$(LIBNAME).so: ;  $(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)
$(LIBNAME).dylib: ;  $(CC) $(CFLAGS) -shared -dynamiclib -o $@ $(OBJS) $(LDFLAGS)

# Every .c depends upon its .h
cpio.o: cpio.h
errno.o: errno.h
octal.o: octal.h

# Additional dependencies
extras.h: errno.h
cpio.o: errno.o
cpio.o: octal.o
cpio.o: extras.h
octal.o: errno.o
octal.o: extras.h

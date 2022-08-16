.POSIX:
.SILENT: bin clean test
include config.mk

CP = ln -f
MK = $(MAKE) -s $(MAKEFLAGS)

posix: bin lib
linux: posix solib
macos: posix dylib

bin: ; cd bin && $(MK) $@ && $(CP) $(EXENAME) ..
test: lib ; cd test && $(MK) $@
lib: alib

alib solib: ; @cd lib && $(MK) $@ && $(CP) $(LIBNAME).$(@:lib=) ..
dylib:      ; @cd lib && $(MK) $@ && $(CP) $(LIBNAME).$@ ..

clean:
	rm -f $(EXENAME)
	rm -f $(LIBNAME).*
	cd bin && $(MAKE) $(MAKEFLAGS) -s clean
	cd lib && $(MAKE) $(MAKEFLAGS) -s clean

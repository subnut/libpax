.POSIX:
include config.mk

posix: bin lib
linux: posix solib
clean: ; rm -f $(EXENAME) $(LIBNAME).*

lib: alib
bin: ; @cd bin && $(MAKE) $(MAKEFLAGS) $@ && mv -f $(EXENAME) ..
alib solib: ; @cd lib && $(MAKE) $(MAKEFLAGS) $@ && mv -f $(LIBNAME).$(@:lib=) ..

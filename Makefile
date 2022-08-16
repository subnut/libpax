.POSIX:
.SILENT: clean
include config.mk

posix: bin lib
linux: posix solib

lib: alib
bin: ; @cd bin && $(MAKE) $(MAKEFLAGS) $@ && mv -f $(EXENAME) ..
alib solib: ; @cd lib && $(MAKE) $(MAKEFLAGS) $@ && mv -f $(LIBNAME).$(@:lib=) ..

clean:
	rm -f $(EXENAME)
	rm -f $(LIBNAME).*
	cd bin && $(MAKE) $(MAKEFLAGS) -s clean
	cd lib && $(MAKE) $(MAKEFLAGS) -s clean

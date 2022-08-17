.POSIX:
.SILENT: test
include config.mk

CP = ln -f

posix: bin lib
linux: posix solib
macos: posix dylib

bin: ; cd bin && $(MK) $@ && $(CP) $(EXENAME) ..
test: lib ; cd test && $(MK) $@
lib: alib

alib:  $(LIBNAME).a
solib: $(LIBNAME).so
dylib: $(LIBNAME).dylib

$(LIBNAME).a $(LIBNAME).so $(LIBNAME).dylib :
	cd lib && $(MK) $@ && $(CP) $@ ..

clean:
	rm -f $(EXENAME) $(LIBNAME).*
	cd bin && $(MK) clean
	cd lib && $(MK) clean

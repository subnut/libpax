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
	@echo "cd lib && $(MAKE) $@ && $(CP) $@ .."
	@cd lib && $(MK) $@ && $(CP) $@ ..

clean:
	rm -f $(EXENAME) $(LIBNAME).*
	@echo "cd bin && $(MAKE) $@"
	@cd bin && $(MK) clean
	@echo "cd lib && $(MAKE) $@"
	@cd lib && $(MK) clean

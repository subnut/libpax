.POSIX:
.SILENT: test
include config.mk
all: posix
test: lib ; cd test && $(MK) $@

posix: bin lib
linux: posix solib
macos: posix dylib

lib: alib
bin: $(EXE)
$(EXE): lib
	@echo "cd bin && $(MAKE) pax && $(CP) pax ../$(EXE)"
	@      cd bin && $(MK)   pax && $(CP) pax ../$(EXE)

alib:  $(LIBNAME).a
solib: $(LIBNAME).so
dylib: $(LIBNAME).dylib

$(LIBNAME).a $(LIBNAME).so $(LIBNAME).dylib :
	@echo "cd lib && $(MAKE) $@ && $(CP) $@ .."
	@      cd lib && $(MK)   $@ && $(CP) $@ ..

clean:
	rm -f $(EXE) $(LIBNAME).*
	@echo "cd bin && $(MAKE) clean"
	@      cd bin && $(MK)   clean
	@echo "cd lib && $(MAKE) clean"
	@      cd lib && $(MK)   clean

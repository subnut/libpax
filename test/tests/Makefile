.POSIX:
all: ; echo *.test | sed s/test$$/o/g | xargs $(MAKE) $(MAKEFLAGS)
clean: ; rm -f *.o

.SUFFIXES:
.SUFFIXES: .o .test
.test.o: ; cp $< $(<:test=c); trap 'rm $(<:test=c)' EXIT; $(CC) $(CFLAGS) -c $(<:test=c) -I../..

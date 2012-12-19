%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: distclean pbsplit pbsplit.man

pbsplit: pbsplit.o xsum.o
	$(CC) $(LDFLAGS) -o $@ $^

pbsplit.o: pbsplit.c xsum.h
xsum.o: xsum.c xsum.h

clean:
	rm -f *.o 

distclean: clean
	rm -f pbsplit

%.o: %.c
	gcc -c -o $@ $<

all: clean xsum

xsum: xsum.o
	cc -o $@ $^

clean:
	rm -f *.o
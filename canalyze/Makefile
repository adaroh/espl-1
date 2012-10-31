%.o: %.c
	gcc -c -o $@ $<

all: clean fortune

fortune: fortune.o
	cc -o $@ $^

clean:
	rm -f *.o

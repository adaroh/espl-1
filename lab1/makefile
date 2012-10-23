%.o: %.c
	cc -c -o $@ $<
 
all: clean invert
 
clean:
	rm -f *.o
 
invert: invert.o
	cc -o $@ $^
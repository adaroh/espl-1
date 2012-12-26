CC=gcc
CFLAGS=-O -g -m32


all: encbc decbc

# TODO: add rule for encbc
encbc: secret-elf-b secret-elf-c
	$(CC) $(CFLAGS) -o $@ $^

decbc: secret-elf-a secret-elf-c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f encbc decbc testbc


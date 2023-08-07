CC=gcc
CFLAGS=-Wall
INSTALL_DIR=/usr/bin
MAN_DIR=/usr/share/man/man1

all: cumsay

cumsay: cum.c
	$(CC) $(CFLAGS) -o cumsay cum.c

install: cumsay
	cp cumsay $(INSTALL_DIR)/
	cp cumsay.1 $(MAN_DIR)/

uninstall:
	rm -f $(INSTALL_DIR)/cumsay
	rm -f $(MAN_DIR)/cumsay.1

clean:
	rm -f cumsay


CC=gcc
CFLAGS=-Wall
INSTALL_DIR=/usr/bin

all: cumsay

cumsay: cum.c
	$(CC) $(CFLAGS) -o cumsay cum.c

install: cumsay
	cp cumsay $(INSTALL_DIR)/

uninstall:
	rm -f $(INSTALL_DIR)/cumsay

clean:
	rm -f cumsay

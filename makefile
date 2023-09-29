CC=gcc
CFLAGS=-Wall -Werror -O2 
DEBUGFLAGS=-Wall -Werror -Wextra -fsanitize=address,undefined
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

debug:
	$(CC) -o cumsay cum.c $(DEBUGFLAGS)

clean:
	rm -f cumsay


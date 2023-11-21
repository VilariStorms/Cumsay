bin_PROGRAMS = cumsay
cumsay_SOURCES = cum.c cum.h
man_MANS = cumsay.1
EXTRA_DIST = cumsay.1
AM_CFLAGS = -Wall -Werror -O2
AM_LDFLAGS = 
debug: clean
	$(MAKE) all AM_CFLAGS='$(AM_CFLAGS) -g -O0 -fsanitize=address -fsanitize=undefined'

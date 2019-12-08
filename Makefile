CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -O2 -Isrc

PREFIX = /usr/local

EXE = rot

HDRS = src/rot.h
SRCS = src/rot.c main.c
OBJS = $(SRCS:.c=.o)


$(EXE):  $(HDRS) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: install
install:  $(EXE)
	mv -f $(EXE) $(PREFIX)/bin

$(OBJS): $(HDRS) $(SRCS) Makefile


.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE)

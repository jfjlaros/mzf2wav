CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -static

EXEC = mzf2wav
MAIN = ../mzf2wav.c
OBJS = ../physical.o ../methods.o ../args.o ../wav.o

all: $(EXEC)

.cc.o:
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) core

distclean: clean
	rm -f $(EXEC)

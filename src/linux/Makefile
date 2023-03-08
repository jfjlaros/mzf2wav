CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -static

EXEC = mzf2wav
MAIN = ../mzf2wav.c
OBJS = ../argparse.o ../methods.o ../wav.o ../write.o

all: $(EXEC)

.cc.o:
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) core

distclean: clean
	rm -f $(EXEC)

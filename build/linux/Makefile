CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O2 -static

EXEC := mzf2wav
PTH := ../../src
MAIN := $(PTH)/mzf2wav.c
OBJS := argparse.o methods.o mzf.o wav.o write.o

all: $(EXEC)

%.o: $(PTH)/%.c $(PTH)/%.h
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) core

distclean: clean
	rm -f $(EXEC)

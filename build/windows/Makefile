CC := x86_64-w64-mingw32-gcc
CFLAGS := -Wall -Wextra -pedantic -O2 -static

EXEC := mzf2wav.exe
PTH := ../../src
MAIN := $(PTH)/mzf2wav.c
OBJS := argparse.o methods.o mzf.o wav.o write.o

all: $(EXEC)

%.o: $(PTH)/%.c $(PTH)/%.h
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)

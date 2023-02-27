CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -static

EXEC = mzf2wav.exe
MAIN = ../mzf2wav.c
OBJS = ../physical.obj ../methods.obj ../args.obj ../wav.obj 

all: $(EXEC)

%.obj: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)

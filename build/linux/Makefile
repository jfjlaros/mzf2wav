CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O2 -static

EXEC := mzf2wav
PTH := ../../src
MAIN := $(PTH)/mzf2wav.c
OBJS := argparse.o methods.o mzf.o wav.o write.o


all: $(EXEC)

$(EXEC): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: $(PTH)/%.c $(PTH)/%.h
	$(CC) $(CFLAGS) -c $<

../../docs/cli.rst: ../../docs/cli_template.rst_ $(EXEC)
	cp $< $@ && ./$(EXEC) -h >> $@

clean:
	rm -f $(OBJS) core

distclean: clean
	rm -f $(EXEC)

doc: ../../docs/cli.rst

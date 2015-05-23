// Defenitions.
#define DEFAULT_LONG_UP       21 // Normal mode.
#define DEFAULT_LONG_DOWN     21
#define DEFAULT_SHORT_UP      11
#define DEFAULT_SHORT_DOWN    11

#define FAST_LONG_UP          11 // Fastest in normal mode.
#define FAST_LONG_DOWN        21
#define FAST_SHORT_UP         11
#define FAST_SHORT_DOWN       12

#define TURBO_2_LONG_UP       11 // Turbo 2x.
#define TURBO_2_LONG_DOWN     11
#define TURBO_2_SHORT_UP      5
#define TURBO_2_SHORT_DOWN    6

#define TURBO_3_LONG_UP       7  // Turbo 3x.
#define TURBO_3_LONG_DOWN     7
#define TURBO_3_SHORT_UP      3
#define TURBO_3_SHORT_DOWN    4

#define TURBO_FAST_LONG_UP    3  // Fastest in turbo mode.
#define TURBO_FAST_LONG_DOWN  7
#define TURBO_FAST_SHORT_UP   3
#define TURBO_FAST_SHORT_DOWN 4

// Prototypes.
void outb(int, int),
     writewavheader(void),
     setheader(void);

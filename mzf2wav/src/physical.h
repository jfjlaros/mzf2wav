#include "wav.h"

// Defenitions.
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;

// Prototypes.
void reversepol(void),      // Reverse polarity.
     gap(int),              // i short pulses.
     tapemark(int),         // i long, i short and two long pulses.
     writecs(word),         // Write the checksum.
     setspeed(int);         // Define the waveform.
word writebyte(byte),       // Write a byte and count the ones. 
     getfilesize(byte *);   // Get the file size.
int assert(byte *, word);   // See if the MZF file is valid.

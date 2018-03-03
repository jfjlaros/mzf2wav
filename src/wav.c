#include <stdio.h>
#include "wav.h"
#include "physical.h"

// Externs.
extern FILE *OUT;

// Global variables.
dword fs = 0;
// Numbers are little endian.
byte header[44] = { 'R', 'I', 'F', 'F',   // File description header.
                    0x0, 0x0, 0x0, 0x0,   // Filesize - 8.
                    'W', 'A', 'V', 'E',   // "WAVE" Description header.
                    'f', 'm', 't', ' ',   // "fmt " Description header.
                    0x10, 0x0, 0x0, 0x0,  // Size of WAVE section chunck.
                    0x1, 0x0,             // Wave type format.
                    0x1, 0x0,             // Mono or stereo.
                    0x44, 0xac, 0x0, 0x0, // Sample rate.
                    0x44, 0xac, 0x0, 0x0, // Bytes per second.
                    0x1, 0x0,             // Block alignment.
                    0x8, 0x0,             // Bits per sample.
                    'd', 'a', 't', 'a',   // "data" Description header.
                    0x0, 0x0, 0x0, 0x0 }; // Size of data chunk.


// Public functions.
void outb(int value, int port) {
  fprintf(OUT, "%c", value);
}//outb

// Write the WAV header.
void writewavheader(void) {
  int i = 0;

  for (i = 0; i < 44; i++)
    fprintf(OUT, "%c", header[i]);
}//writewavheader

// Set the filesizes in the WAV header. 
void setheader(void) {
  dword temp = fs;
  int i = 0;

  fseek(OUT, 4, SEEK_SET);
  fprintf(OUT, "%c", (temp & 0xff) + 36);
  fseek(OUT, 40, SEEK_SET);
  fprintf(OUT, "%c", temp & 0xff);
  temp >>= 8;
  for (i = 1; i < 4; i++) {
    fseek(OUT, 4 + i, SEEK_SET);
    fprintf(OUT, "%c", temp & 0xff);
    fseek(OUT, 40 + i, SEEK_SET);
    fprintf(OUT, "%c", temp & 0xff);
    temp >>= 8;
  }//for
}//setheader

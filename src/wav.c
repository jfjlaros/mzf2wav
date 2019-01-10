#include <stdio.h>
#include "wav.h"
#include "physical.h"

// Externs.
extern FILE *OUT;

// Global variables.
dword fs = 0;
int divider = 1;

// Numbers are little endian.
byte header[44] = {
  'R', 'I', 'F', 'F',       // File description header.
  0x00, 0x00, 0x00, 0x00,   // Filesize - 8.
  'W', 'A', 'V', 'E',       // "WAVE" Description header.
  'f', 'm', 't', ' ',       // "fmt " Description header.
  0x10, 0x00, 0x00, 0x00,   // Size of WAVE section chunk.
  0x01, 0x00,               // Wave type format.
  0x01, 0x00,               // Mono or stereo.
  0x44, 0xad, 0x00, 0x00,   // Sample rate.
  0x44, 0xad, 0x00, 0x00,   // Bytes per second.
  0x01, 0x00,               // Block alignment.
  0x08, 0x00,               // Bits per sample.
  'd', 'a', 't', 'a',       // "data" Description header.
  0x00, 0x00, 0x00, 0x00 }; // Size of data chunk.


// Public functions.
void setbitrate(uint32_t bitrate) {
  int i;

  for (i = 0; i < 4; i++) {
    header[i + 24] = bitrate >> (8 * i) & 0xff;
    header[i + 28] = bitrate >> (8 * i) & 0xff;
  }
  divider = 44100 / bitrate;
}

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

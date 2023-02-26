#include "wav.h"

uint8_t const header_[] = {
  'R', 'I', 'F', 'F',       // File description header.
  0x00, 0x00, 0x00, 0x00,   // Filesize - 8.
  'W', 'A', 'V', 'E',       // "WAVE" Description header.
  'f', 'm', 't', ' ',       // "fmt " Description header.
  0x10, 0x00, 0x00, 0x00,   // Size of WAVE section chunk.
  0x01, 0x00,               // Wave type format.
  0x01, 0x00,               // Mono or stereo.
  0x00, 0x00, 0x00, 0x00,   // Sample rate.
  0x00, 0x00, 0x00, 0x00,   // Bytes per second.
  0x01, 0x00,               // Block alignment.
  0x08, 0x00,               // Bits per sample.
  'd', 'a', 't', 'a',       // "data" Description header.
  0x00, 0x00, 0x00, 0x00};  // Size of data chunk.


void writeInt_(FILE *output, uint32_t const data) {
  for (size_t i = 0; i < sizeof(data); ++i) {
    fprintf(output, "%c", data >> 8 * i);
  }
}


void writeBit(FILE *output, bool const bit, bool const invert) {
  uint8_t const zero = 0x30;
  uint8_t const one = 0xd0;

  if (bit != invert) {
    fprintf(output, "%c", one);
    return;
  }
  fprintf(output, "%c", zero);
}

void writeHeader(FILE *output) {
  for (uint8_t i = 0; i < sizeof(header_); ++i) {
    fprintf(output, "%c", header_[i]);
  }
}

void updateHeader(FILE *output, uint32_t const size, uint32_t const bitrate) {
  // File size.
  fseek(output, 4, SEEK_SET);
  writeInt_(output, size + 36);

  // Sample rate and bytes per second.
  fseek(output, 24, SEEK_SET);
  writeInt_(output, bitrate);
  writeInt_(output, bitrate);

  // Data size.
  fseek(output, 40, SEEK_SET);
  writeInt_(output, size);
}

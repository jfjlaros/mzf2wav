#include "wav.h"
#include "physical.h"

int waveScale = 1;

// Numbers are little endian.
uint8_t header[] = {
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
  0x00, 0x00, 0x00, 0x00};  // Size of data chunk.

uint8_t const zero = 0x30;
uint8_t const one = 0xd0;


void setBitrate(uint32_t bitrate) {
  for (int i = 0; i < 4; ++i) {
    header[i + 24] = bitrate >> (8 * i) & 0xff;
    header[i + 28] = bitrate >> (8 * i) & 0xff;
  }
  waveScale = 44100 / bitrate;  // TODO: return this value.
}

void writeBit(FILE *output, bool const bit, bool const invert) {
  if (bit != invert) {
    fprintf(output, "%c", one);
    return;
  }
  fprintf(output, "%c", zero);
}

void writeHeader(FILE *output) {  // TODO: combine with next function?
  for (uint8_t i = 0; i < 44; ++i) {
    fprintf(output, "%c", header[i]);
  }
}

void setHeader(FILE *output, uint32_t const size) {
  fseek(output, 4, SEEK_SET);
  uint32_t size_ = size;
  fprintf(output, "%c", (size_ & 0xff) + 36);
  fseek(output, 40, SEEK_SET);
  fprintf(output, "%c", size_ & 0xff);
  size_ >>= 8;
  for (uint8_t i = 1; i < 4; ++i) {
    fseek(output, 4 + i, SEEK_SET);
    fprintf(output, "%c", size_ & 0xff);
    fseek(output, 40 + i, SEEK_SET);
    fprintf(output, "%c", size_ & 0xff);
    size_ >>= 8;
  }
}

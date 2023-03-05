#include "physical.h"

Waveform const waveforms[] = {
  //{{464, 494}, {240, 264}},   // Normal mode.
  {{480, 494}, {260, 264}},   // TODO: should be the one above.
  {{248, 474}, {248, 271}},   // Fastest in normal mode.
  {{248, 248}, {113, 136}},   // Turbo 2x.
  {{158, 158}, { 68,  91}},   // Turbo 3x.
  {{ 68, 158}, { 68,  91}}};  // Fastest in turbo mode.


uint16_t pulse_(uint32_t const duration, uint16_t const bitrate) {
  return duration * bitrate / 1000000;
}

void writeLongPulse_(FILE *output, uint32_t *size, WaveCfgPtr wfc) {
  uint16_t const up = pulse_(wfc->wave.longPulse.up, wfc->bitrate);
  for (uint16_t i = 0; i < up; ++i) {
    writeBit(output, false, wfc->invert);
  }
  uint16_t const down = pulse_(wfc->wave.longPulse.down, wfc->bitrate);
  for (uint16_t i = 0; i < down; ++i) {
    writeBit(output, true, wfc->invert);
  }
  *size += up + down;
}

void writeShortPulse_(FILE *output, uint32_t *size, WaveCfgPtr wfc) {
  uint16_t const up = pulse_(wfc->wave.shortPulse.up, wfc->bitrate);
  for (uint16_t i = 0; i < up; ++i) {
    writeBit(output, false, wfc->invert);
  }
  uint16_t const down = pulse_(wfc->wave.shortPulse.down, wfc->bitrate);
  for (uint16_t i = 0; i < down; ++i) {
    writeBit(output, true, wfc->invert);
  }
  *size += up + down;
}


void writeGap(FILE *output, uint32_t *size, int const n, WaveCfgPtr wfc) {
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, wfc);
  }
}

void writeTapeMark(
    FILE *output, uint32_t *size, int const n, WaveCfgPtr wfc) {
  for (int i = 0; i < n; ++i) {
    writeLongPulse_(output, size, wfc);
  }
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, wfc);
  }
  writeLongPulse_(output, size, wfc);
  writeLongPulse_(output, size, wfc);
}

uint16_t writeByte(
    FILE *output, uint32_t *size, uint8_t const data, WaveCfgPtr wfc) {
  uint16_t ones = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    if (data & 0x80 >> i) {
      writeLongPulse_(output, size, wfc);
      ++ones;
    }
    else {
      writeShortPulse_(output, size, wfc);
    }
  }
  writeLongPulse_(output, size, wfc);

  return ones;
}

void writeChecksum(
    FILE *output, uint32_t *size, uint16_t const checksum,
    WaveCfgPtr wfc) {
  writeByte(output, size, checksum >> 8, wfc);
  writeByte(output, size, checksum, wfc);
  writeLongPulse_(output, size, wfc);
}

uint16_t getImageSize(uint8_t const *const image) {
  return image[0x12] | image[0x13] << 8;
}

int checkImage(uint8_t const *const image, uint16_t const size) {  // TODO
  uint16_t imageSize = getImageSize(image);

  if (imageSize + 0x80 != size) {
    if (size - imageSize > 0x200)
      return 2;
    if (size < imageSize)
      return 2;
    return 1;
  }
  return 0;
}

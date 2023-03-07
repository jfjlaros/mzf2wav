#include "physical.h"


void writeLongPulse_(FILE *output, uint32_t *size, PCP pulseConfig) {
  for (uint16_t i = 0; i < pulseConfig->longPulse.up; ++i) {
    writeBit(output, false, pulseConfig->invert);
  }
  for (uint16_t i = 0; i < pulseConfig->longPulse.down; ++i) {
    writeBit(output, true, pulseConfig->invert);
  }
  *size += pulseConfig->longPulse.up + pulseConfig->longPulse.down;
}

void writeShortPulse_(FILE *output, uint32_t *size, PCP pulseConfig) {
  for (uint16_t i = 0; i < pulseConfig->shortPulse.up; ++i) {
    writeBit(output, false, pulseConfig->invert);
  }
  for (uint16_t i = 0; i < pulseConfig->shortPulse.down; ++i) {
    writeBit(output, true, pulseConfig->invert);
  }
  *size += pulseConfig->shortPulse.up + pulseConfig->shortPulse.down;
}


Pulse toPulse(Pulse const pulse, uint32_t const bitrate) {  // TODO: move?
  Pulse pulse_ = {
    pulse.up * bitrate / 1000000, pulse.down * bitrate / 1000000};
  return pulse_;
}

void writeGap(FILE *output, uint32_t *size, int const n, PCP pulseConfig) {
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, pulseConfig);
  }
}

void writeTapeMark(
    FILE *output, uint32_t *size, int const n, PCP pulseConfig) {
  for (int i = 0; i < n; ++i) {
    writeLongPulse_(output, size, pulseConfig);
  }
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, pulseConfig);
  }
  writeLongPulse_(output, size, pulseConfig);
  writeLongPulse_(output, size, pulseConfig);
}

uint16_t writeByte(
    FILE *output, uint32_t *size, uint8_t const data, PCP pulseConfig) {
  uint16_t ones = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    if (data & 0x80 >> i) {
      writeLongPulse_(output, size, pulseConfig);
      ++ones;
    }
    else {
      writeShortPulse_(output, size, pulseConfig);
    }
  }
  writeLongPulse_(output, size, pulseConfig);

  return ones;
}

void writeChecksum(
    FILE *output, uint32_t *size, uint16_t const checksum,
    PCP pulseConfig) {
  writeByte(output, size, checksum >> 8, pulseConfig);
  writeByte(output, size, checksum, pulseConfig);
  writeLongPulse_(output, size, pulseConfig);
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

#include "physical.h"

Waveform const waveforms_[] = {
  {{21, 21}, {11, 11}, false},   // Normal mode.
  {{11, 21}, {11, 12}, false},   // Fastest in normal mode.
  {{11, 11}, { 5,  6}, false},   // Turbo 2x.
  {{ 7,  7}, { 3,  4}, false},   // Turbo 3x.
  {{ 3,  7}, { 3,  4}, false}};  // Fastest in turbo mode.


void writeLongPulse_(FILE *output, uint32_t *size, Waveform const *const waveform) {
  for (int i = 0; i < waveform->longPulse.up; ++i) {
    writeBit(output, false, waveform->invert);
  }
  for (int i = 0; i < waveform->longPulse.down; ++i) {
    writeBit(output, true, waveform->invert);
  }
  *size += waveform->longPulse.up + waveform->longPulse.down;
}

void writeShortPulse_(FILE *output, uint32_t *size, Waveform const *const waveform) {
  for (int i = 0; i < waveform->shortPulse.up; ++i) {
    writeBit(output, false, waveform->invert);
  }
  for (int i = 0; i < waveform->shortPulse.down; ++i) {
    writeBit(output, true, waveform->invert);
  }
  *size += waveform->shortPulse.up + waveform->shortPulse.down;
}


void writeGap(FILE *output, uint32_t *size, int const n, Waveform const *const waveform) {
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, waveform);
  }
}

void writeTapeMark(
    FILE *output, uint32_t *size, int const n, Waveform const *const waveform) {
  for (int i = 0; i < n; ++i) {
    writeLongPulse_(output, size, waveform);
  }
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, waveform);
  }
  writeLongPulse_(output, size, waveform);
  writeLongPulse_(output, size, waveform);
}

uint16_t writeByte(
    FILE *output, uint32_t *size, uint8_t const data, Waveform const *const waveform) {
  uint16_t ones = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    if (data & 1 << (7 - i)) {
      writeLongPulse_(output, size, waveform);
      ++ones;
    }
    else {
      writeShortPulse_(output, size, waveform);
    }
  }
  writeLongPulse_(output, size, waveform);

  return ones;
}

void writeChecksum(
    FILE *output, uint32_t *size, uint16_t const checksum, Waveform const *const waveform) {
  writeByte(output, size, checksum >> 8, waveform);
  writeByte(output, size, checksum, waveform);
  writeLongPulse_(output, size, waveform);
}

void configureWaveform(
    Waveform *waveform, Speed const speed, int const bitrate,
    bool const invert, int const correction) {
  *waveform = waveforms_[speed];
  waveform->invert = invert;

  if (speed == fastNormal) {
    waveform->longPulse.up += correction;
    waveform->longPulse.down += correction;
    waveform->shortPulse.up += correction;
    waveform->shortPulse.down += correction;
  }
  if (speed == fastTurbo) {
    waveform->longPulse.down += correction;
    waveform->shortPulse.down += correction;
  }

  int const scale = 44100 / bitrate;
  waveform->longPulse.up /= scale;
  waveform->longPulse.down /= scale;
  waveform->shortPulse.up /= scale;
  waveform->shortPulse.down /= scale;
}

uint16_t getImageSize(uint8_t const *const image) {
  return image[0x12] | image[0x13] << 8;
}

int checkImage(uint8_t const *const image, uint16_t const size) {
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

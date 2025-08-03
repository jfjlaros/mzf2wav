#include "write.h"


static void writeLongPulse_(FILE *const output, uint32_t *size, PCP pulseConfig) {
  for (uint16_t i = 0; i < pulseConfig->longPulse.high; ++i) {
    writeBit(output, false, pulseConfig->invert);
  }
  for (uint16_t i = 0; i < pulseConfig->longPulse.low; ++i) {
    writeBit(output, true, pulseConfig->invert);
  }
  *size += pulseConfig->longPulse.high + pulseConfig->longPulse.low;
}

static void writeShortPulse_(FILE *const output, uint32_t *size, PCP pulseConfig) {
  for (uint16_t i = 0; i < pulseConfig->shortPulse.high; ++i) {
    writeBit(output, false, pulseConfig->invert);
  }
  for (uint16_t i = 0; i < pulseConfig->shortPulse.low; ++i) {
    writeBit(output, true, pulseConfig->invert);
  }
  *size += pulseConfig->shortPulse.high + pulseConfig->shortPulse.low;
}


void writeGap(
    FILE *const output, uint32_t *const size, int const n, PCP pulseConfig) {
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, pulseConfig);
  }
}

void writeTapeMark(
    FILE *const output, uint32_t *const size, int const n, PCP pulseConfig) {
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
    FILE *const output, uint32_t *const size, uint8_t const data,
    PCP pulseConfig) {
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
    FILE *const output, uint32_t *const size, uint16_t const checksum,
    PCP pulseConfig) {
  writeByte(output, size, checksum >> 8, pulseConfig);
  writeByte(output, size, checksum, pulseConfig);
  writeLongPulse_(output, size, pulseConfig);
}

#include "physical.h"

// Normal mode.
uint8_t const defaultLongUp = 21;
uint8_t const defaultLongDown = 21;
uint8_t const defaultShortUp = 11;
uint8_t const defaultShortDown = 11;

// Fastest in normal mode.
uint8_t const fastLongUp = 11;
uint8_t const fastLongDown = 21;
uint8_t const fastShortUp = 11;
uint8_t const fastShortDown = 12;

// Turbo 2x.
uint8_t const turbo2LongUp = 11;
uint8_t const turbo2LongDown = 11;
uint8_t const turbo2ShortUp = 5;
uint8_t const turbo2ShortDown = 6;

// Turbo 3x.
uint8_t const turbo3LongUp = 7;
uint8_t const turbo3LongDown = 7;
uint8_t const turbo3ShortUp = 3;
uint8_t const turbo3ShortDown = 4;

// Fastest in turbo mode.
uint8_t const turboFastLongUp = 3;
uint8_t const turboFastLongDown = 7;
uint8_t const turboFastShortUp = 3;
uint8_t const turboFastShortDown = 4;

// Long wave.
static int longUp = 0;
static int longDown = 0;

// Short wave.
static int shortUp = 0;
static int shortDown = 0;

// Corrections.
int fastCorrection = 0;
int turboCorrection = 0;


void writeLongPulse_(FILE *output, uint32_t *size, bool const invert) {
  for (int i = 0; i < longUp; ++i) {
    writeBit(output, false, invert);
  }
  for (int i = 0; i < longDown; ++i) {
    writeBit(output, true, invert);
  }
  *size += longUp + longDown;
}

void writeShortPulse_(FILE *output, uint32_t *size, bool const invert) {
  for (int i = 0; i < shortUp; ++i) {
    writeBit(output, false, invert);
  }
  for (int i = 0; i < shortDown; ++i) {
    writeBit(output, true, invert);
  }
  *size += shortUp + shortDown;
}


void writeGap(FILE *output, uint32_t *size, int const n, bool const invert) {
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, invert);
  }
}

void writeTapeMark(FILE *output, uint32_t *size, int const n, bool const invert) {
  for (int i = 0; i < n; ++i) {
    writeLongPulse_(output, size, invert);
  }
  for (int i = 0; i < n; ++i) {
    writeShortPulse_(output, size, invert);
  }
  writeLongPulse_(output, size, invert);
  writeLongPulse_(output, size, invert);
}

void writeChecksum(FILE *output, uint32_t *size, uint16_t const checksum, bool const invert) {
  uint16_t checksum_ = checksum;

  checksum_ &= 0xffff;
  for (uint8_t i = 0; i < 2; ++i) {
    for (uint8_t j = 0; j < 8; ++j) {
      if (checksum_ & 0x8000) {
        writeLongPulse_(output, size, invert);
      }
      else {
        writeShortPulse_(output, size, invert);
      }
      checksum_ <<= 1;
    }
    writeLongPulse_(output, size, invert);
  }
  writeLongPulse_(output, size, invert);
}

void setSpeed(Speed const speed) {
  switch (speed) {
    case normal:
      longUp = defaultLongUp;
      longDown = defaultLongDown;
      shortUp = defaultShortUp;
      shortDown = defaultShortDown;
      break;
    case fastNormal:
      longUp = fastLongUp + fastCorrection;
      longDown = fastLongDown + fastCorrection;
      shortUp = fastShortUp + fastCorrection;
      shortDown = fastShortDown + fastCorrection;
      break;
    case turbo2:
      longUp = turbo2LongUp;
      longDown = turbo2LongDown;
      shortUp = turbo2ShortUp;
      shortDown = turbo2ShortDown;
      break;
    case turbo3:
      longUp = turbo3LongUp;
      longDown = turbo3LongDown;
      shortUp = turbo3ShortUp;
      shortDown = turbo3ShortDown;
      break;
    case fastTurbo:
      longUp = turboFastLongUp;
      longDown = turboFastLongDown + turboCorrection;
      shortUp = turboFastShortUp;
      shortDown = turboFastShortDown + turboCorrection;
      break;
  }
  longUp = longUp / waveScale;
  longDown = longDown / waveScale;
  shortUp = shortUp / waveScale;
  shortDown = shortDown / waveScale;
}

uint16_t writeByte(FILE *output, uint32_t *size, uint8_t const data, bool const invert) {
  uint16_t ones = 0;
  uint8_t data_ = data;

  for (uint8_t i = 0; i < 8; ++i) {
    if (data_ & 0x80) {
      writeLongPulse_(output, size, invert);
      ++ones;
    }
    else
      writeShortPulse_(output, size, invert);
    data_ <<= 1;
  }
  writeLongPulse_(output, size, invert);

  return ones;
}

uint16_t getFileSize(uint8_t const *const image) {  // TODO rename to imageSize
  return image[0x12] | (image[0x13] << 8);
}

int checkImage(uint8_t const *const image, uint16_t const size) {
  uint16_t imageSize = getFileSize(image);

  if (imageSize + 0x80 != size) {
    if (size - imageSize > 0x200)
      return 2;
    if (size < imageSize)
      return 2;
    return 1;
  }
  return 0;
}

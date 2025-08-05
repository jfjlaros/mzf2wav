#include "methods.h"

uint16_t const headerTapeMarkLength_ = 40;
uint16_t const bodyTapeMarkLength_ = 20;

uint8_t const headerSize = 128;


static void writeLeader_(
    FILE *const output, uint32_t *const size, PCP pulseConfig,
    uint16_t const gapLength, uint16_t const tapeMarkLength) {
  writeGap(output, size, gapLength, pulseConfig);
  writeTapeMark(output, size, tapeMarkLength, pulseConfig);
}

static void writeHeader_(
    FILE *const output, uint32_t *const size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  for (uint8_t i = 0; i < headerSize; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}

static void writeBody_(
    FILE *const output, uint32_t *const size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  uint16_t const end = imageSize(image) + headerSize;
  for (uint16_t i = headerSize; i < end; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}


uint32_t conventionalFormat(
    FILE *const output, IMGP image, PCP pulseConfig) {
  uint16_t const gapLength = 256;
  uint32_t size = 0;

  uint16_t headerGapLength = 22000;
  writeLeader_(
    output, &size, pulseConfig, headerGapLength, headerTapeMarkLength_);
  writeHeader_(output, &size, image, pulseConfig);
  writeGap(output, &size, gapLength, pulseConfig);
  writeHeader_(output, &size, image, pulseConfig);

  uint16_t bodyGapLength = 11000;
  writeLeader_(output, &size, pulseConfig, bodyGapLength, bodyTapeMarkLength_);
  writeBody_(output, &size, image, pulseConfig);
  writeGap(output, &size, gapLength, pulseConfig);
  writeBody_(output, &size, image, pulseConfig);

  return size;
}

uint32_t fastFormat(FILE *const output, IMGP image, PCP pulseConfig) {
  uint32_t size = 0;

  uint16_t headerGapLength = 4000;
  writeLeader_(
    output, &size, pulseConfig, headerGapLength, headerTapeMarkLength_);
  writeHeader_(output, &size, image, pulseConfig);

  uint16_t bodyGapLength = 5000;
  writeLeader_(output, &size, pulseConfig, bodyGapLength, bodyTapeMarkLength_);
  writeBody_(output, &size, image, pulseConfig);

  return size;
}

uint32_t turboFormat(
    FILE *const output, IMGP image, PCP pulseConfig, PCP turboConfig) {
  uint8_t turboLoader[turboLoaderSize];
  prepareLoader(turboLoader, image);

  uint32_t size = fastFormat(output, turboLoader, pulseConfig);
  size += fastFormat(output, image, turboConfig);

  return size;
}

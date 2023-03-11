#include "methods.h"


void writeLeader_(
    FILE *const output, uint32_t *const size, PCP pulseConfig,
    uint16_t const gapLength, uint16_t const tapeMarkLength) {
  writeGap(output, size, gapLength, pulseConfig);
  writeTapeMark(output, size, tapeMarkLength, pulseConfig);
}

void writeHeader_(
    FILE *const output, uint32_t *const size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  for (uint8_t i = 0; i < 128; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}

void writeBody_(
    FILE *const output, uint32_t *const size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  uint16_t const end = imageSize(image) + 128;
  for (uint16_t i = 128; i < end; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}


uint32_t conventionalFormat(
    FILE *const output, IMGP image, PCP pulseConfig) {
  uint32_t size = 0;

  writeLeader_(output, &size, pulseConfig, 22000, 40);
  writeHeader_(output, &size, image, pulseConfig);
  writeGap(output, &size, 256, pulseConfig);
  writeHeader_(output, &size, image, pulseConfig);

  writeLeader_(output, &size, pulseConfig, 11000, 20);
  writeBody_(output, &size, image, pulseConfig);
  writeGap(output, &size, 256, pulseConfig);
  writeBody_(output, &size, image, pulseConfig);

  return size;
}

uint32_t fastFormat(FILE *const output, IMGP image, PCP pulseConfig) {
  uint32_t size = 0;

  writeLeader_(output, &size, pulseConfig, 4000, 40);
  writeHeader_(output, &size, image, pulseConfig);

  writeLeader_(output, &size, pulseConfig, 5000, 20);
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

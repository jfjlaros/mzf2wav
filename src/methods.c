#include <string.h>

#include "methods.h"


void writeLeader_(
    FILE *output, uint32_t *size, PCP pulseConfig,
    uint16_t const gapLength, uint16_t const tapeMarkLength) {
  writeGap(output, size, gapLength, pulseConfig);
  writeTapeMark(output, size, tapeMarkLength, pulseConfig);
}

void writeHeader_(
    FILE *output, uint32_t *size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  for (uint8_t i = 0; i < 128; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}

void writeBody_(
    FILE *output, uint32_t *size, IMGP image, PCP pulseConfig) {
  uint16_t checkSum = 0;
  uint16_t const end = getImageSize(image) + 128;
  for (uint16_t i = 128; i < end; ++i) {
    checkSum += writeByte(output, size, image[i], pulseConfig);
  }
  writeChecksum(output, size, checkSum, pulseConfig);
}


uint32_t fastTransfer(FILE *output, IMGP image, PCP pulseConfig) {
  uint32_t size = 0;

  writeLeader_(output, &size, pulseConfig, 4000, 40);
  writeHeader_(output, &size, image, pulseConfig);

  writeLeader_(output, &size, pulseConfig, 5000, 20);
  writeBody_(output, &size, image, pulseConfig);

  return size;
}

uint32_t conventionalTransfer(FILE *output, IMGP image, PCP pulseConfig) {
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

uint32_t turboTransfer(
    FILE *output, IMGP image, PCP pulseConfig) {
  uint8_t program_[turboLoaderSize];
  memcpy(program_, turboLoader, turboLoaderSize);

  // Name.
  memcpy(program_ + 1, image + 1, 17);
  // Comment.
  memcpy(program_ + 31, image + 31, 97);
  // Info.
  memcpy(program_ + 205, image + 18, 13);

  uint32_t size = fastTransfer(output, program_, pulseConfig);
  //Waveform waveform_ = makeWaveform(  // TODO
  //  secondStageSpeed, 42000, waveform->invert, 0);
  //size += fastTransfer(output, image, &waveform_);

  return size;
}

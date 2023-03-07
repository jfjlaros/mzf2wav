#include <string.h>

#include "methods.h"

// Turbo loader in MZF format.
uint8_t const program_[] = {
  0x01,                                                  // Program type.

  0x0d, 0x0d, 0x0d, 0x0d, 0x0d,                          // Room for the
  0x0d, 0x0d, 0x0d, 0x0d, 0x0d,                          // image name.
  0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,

  0x5a, 0x00,                                            // File size.
  0x00, 0xd4,                                            // Load address.
  0x00, 0xd4,                                            // Execution address.
  '[', 't', 'u', 'r', 'b', 'o', ']',                     // The first 7 bytes.

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Room for comment.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // minus 7 bytes.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,

  0xcd, 0x00,                                            // End Header.

  // Begin Program.
  0x3e, 0x08,       // D400: LD A, 08h
  0xd3, 0xce,       // D402: OUT (0ceh), A  ; Set video mode?

  0xe5,             // D404: PUSH HL

  0x21, 0x00, 0x00, // D405: LD HL, 0000h
  0xd3, 0xe4,       // D408: OUT (0e4h), A  ; Bank switch to ROM?

  0x7e,             // D40A: LD A, (HL)
  0xd3, 0xe0,       // D40B: OUT (0e0h), A  ; Bank switch to RAM?

  0x77,             // D40D: LD (HL), A
  0x23,             // D40E: INC HL

  0x7c,             // D40F: LD A, H
  0xfe, 0x10,       // D410: CP 10h
  0x20, 0xf4,       // D412: JR NZ, f4h    ; Jump 0xf4 forward if A != 0x10

  0x3a, 0x4b, 0xd4, // D414: LD A, (d44bh)
  0x32, 0x4b, 0x0a, // D417: LD (0a4bh), A ; (0x0a4b) = (0xd44b)
  0x3a, 0x4c, 0xd4, // D41A: LD A, (d44ch)
  0x32, 0x12, 0x05, // D41D: LD (0512h), A ; (0xd44c) = (0x0512)
  0x21, 0x4d, 0xd4, // D420: LD HL, d44dh
  0x11, 0x02, 0x11, // D423: LD DE, 1102h
  0x01, 0x0d, 0x00, // D426: LD BC, 000dh
  0xed, 0xb0,       // D429: LDIR          ; Copy 0x0d bytes from (HL) to (DE)

  0xe1,             // D42B: POP HL

  0x7c,             // D42C: LD A, H
  0xfe, 0xd4,       // D42D: CP d4h
  0x28, 0x12,       // D42F: JR Z, 12h     ; Jump to label #1 if A == 0xd4

  0x2a, 0x04, 0x11, // D431: LD HL, (1104h)
  0xd9,             // D434: EXX           ; BC/DE/HL <-> BC'/DE'/HL'
  0x21, 0x00, 0x12, // D435: LD HL, 1200h
  0x22, 0x04, 0x11, // D438: LD (1104h), HL
  0xcd, 0x2a, 0x00, // D43B: CALL 002ah    ; Read data subroutine.
  0xd3, 0xe4,       // D43E: OUT (0e4h), A ; Bank switch to ROM?
  0xc3, 0x9a, 0xe9, // D440: JP e99ah      ; Jump to 0xe99a

  0xcd, 0x2a, 0x00, // D443: CALL (002ah)  ; Label #1 (read data sub).
  0xd3, 0xe4,       // D446: OUT (0e4h), A ; Bank switch to ROM?
  0xc3, 0x24, 0x01, // D448: JP (0124h)
  // End program.

  0x15, 0x01,       // D44B:

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      // Room for the address information
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // + the first 7 bytes of comment.
};


uint32_t fastTransfer(
    FILE *output, uint8_t const *const image, PCP pulseConfig) {
  uint32_t bytesWritten = 0;

  writeGap(output, &bytesWritten, 4000, pulseConfig);
  writeTapeMark(output, &bytesWritten, 40, pulseConfig);

  // Header.
  uint16_t checkSum = 0;
  for (uint8_t i = 0; i < 128; ++i) {
    checkSum += writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  writeGap(output, &bytesWritten, 5000, pulseConfig);
  writeTapeMark(output, &bytesWritten, 20, pulseConfig);

  // Body.
  uint16_t imageSize = getImageSize(image) + 128;
  checkSum = 0;
  for (uint16_t i = 128; i < imageSize; ++i) {
    checkSum += writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  return bytesWritten;
}

uint32_t conventionalTransfer(
    FILE *output, uint8_t const *const image, PCP pulseConfig) {
  uint32_t bytesWritten = 0;

  writeGap(output, &bytesWritten, 22000, pulseConfig);
  writeTapeMark(output, &bytesWritten, 40, pulseConfig);

  // Header.
  uint16_t checkSum = 0;
  for (uint8_t i = 0; i < 128; ++i) {
    checkSum += writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  writeGap(output, &bytesWritten, 256, pulseConfig);

  // Copy of the header.
  for (uint8_t i = 0; i < 128; ++i) {
    writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  writeGap(output, &bytesWritten, 11000, pulseConfig);
  writeTapeMark(output, &bytesWritten, 20, pulseConfig);

  // Body.
  uint16_t imageSize = getImageSize(image) + 128;
  checkSum = 0;
  for (uint16_t i = 128; i < imageSize; ++i) {
    checkSum += writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  writeGap(output, &bytesWritten, 256, pulseConfig);

  // Copy of the body.
  for (uint16_t i = 128; i < imageSize; ++i) {
    writeByte(output, &bytesWritten, image[i], pulseConfig);
  }
  writeChecksum(output, &bytesWritten, checkSum, pulseConfig);

  return bytesWritten;
}

uint32_t turboTransfer(
    FILE *output, uint8_t const *const image, PCP pulseConfig) {
  //Speed secondStageSpeed = turbo2;  // TODO: remove

  uint8_t program[sizeof(program_)];
  memcpy(program, program_, sizeof(program_));

  // Name.
  memcpy(program + 1, image + 1, 17);
  // Comment.
  memcpy(program + 31, image + 31, 97);
  // Info.
  memcpy(program + 205, image + 18, 13);

  uint32_t bytesWritten = fastTransfer(output, program, pulseConfig);
  //Waveform waveform_ = makeWaveform(  // TODO
  //  secondStageSpeed, 42000, waveform->invert, 0);
  //bytesWritten += fastTransfer(output, image, &waveform_);

  return bytesWritten;
}

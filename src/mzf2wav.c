#include <stdio.h>
#include <stdlib.h> // Just to remove a warning (malloc).
#include <string.h>
#include "methods.h"
#include "args.h"

extern uint32_t fileSize; // TODO
extern int waveScale; // TODO
bool invert = false;  // TODO

int bitrate = 44356; // TODO Should be 44100

// Global variables.
FILE *OUT = NULL;
Speed firstStageSpeed = normal;
char *filename = NULL,
     *outfile = NULL;
void (*method)(uint8_t const *const, Waveform *const) = fastTransfer;


// Read the file into memory.
uint8_t *readfile(FILE *IN) {
  uint8_t *image = (uint8_t *)malloc(2),
       *temp = NULL;
  uint16_t i = 0,
       t = 0;

  if (!image)
    return NULL;
  while (fread(&image[i], 1, 1, IN)) {
    temp = (uint8_t *)realloc((uint8_t *)image, i + 2);
    if (!temp) {
      free(image);
      return NULL;
    }
    image = temp;
    i++;
  }
  if (!memcmp(image, "MZF1", 4)) {
    memmove(image, image + 4, i);
    i -= 4;
  }
  t = checkImage(image, i);
  if (t) {
    printf("The MZF file size does not match the image size.\n");
    if (t > 1) {
      printf("This is not a valid MZF file.\n");
      free(image);
      return NULL;
    }
  }
  return image;
}

int main(int argc, char **argv) {
  FILE *IN = NULL;
  uint8_t *image = NULL;
  int i = 0;

  setvars(argc, argv);

  IN = fopen(filename, "rb");
  if (!IN) {
    printf("Unable to open file: %s for reading.\n\n", argv[1]);
    error(2);
  }

  image = readfile(IN);
  if (!image) {
    printf("Out of memory or assertion error.\n\n");
    fclose(IN);
    error(3);
  }
  OUT = fopen(outfile, "wb");
  if (!OUT) {
    printf("Error: unable to open output file: %s for writing.\n", outfile);
    free(image);
    fclose(IN);
    error(6);
  }

  while (fread(&image[i], 1, 1, IN))
    i++;

  writeHeader(OUT);

  Waveform waveform;
  configureWaveform(&waveform, firstStageSpeed, 42000, invert, 0);  // TODO.
  method(image, &waveform);

  updateHeader(OUT, fileSize, bitrate);

  fclose(OUT);
  free(image);
  fclose(IN);

  return 0;
}

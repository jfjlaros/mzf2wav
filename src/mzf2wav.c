#include <stdlib.h>
#include <string.h>

#include "argparse.h"

unsigned int fileSize_(FILE *handle) {
  fseek(handle, 0, SEEK_END);
  unsigned int size = ftell(handle);
  rewind(handle);
  return size;
}

void stripTag_(uint8_t *image, unsigned int *size) {
  if (!memcmp(image, "MZF1", 4)) {
    *size -= 4;
    memmove(image, image + 4, *size);
  }
}

uint16_t scale_(uint16_t const length, uint32_t const bitrate) {
  return length * bitrate / 1000000;
}

Pulse scalePulse_(Pulse const pulse, uint32_t const bitrate) {
  Pulse scaled = {scale_(pulse.up, bitrate), scale_(pulse.down, bitrate)};
  return scaled;
}


bool mzf2wav(Options const *const options) {
  // Load image.
  FILE *input = fopen(options->input, "rb");
  if (!input) {
    printf("Unable to open file \"%s\" for reading.\n", options->input);
    return false;
  }
  unsigned int size = fileSize_(input);
  uint8_t image[size];
  fread(image, 1, size, input);
  fclose(input);

  stripTag_(image, &size);

  /*
  if (size != imageSize(image) + 128) {
    printf("MZF file size does not match header data.")
    return false;
  }
  */

  // Transfer file.
  FILE *output = fopen(options->output, "wb");
  if (!output) {
    printf("Unable to open file \"%s\" for writing.\n", options->output);
    return false;
  }

  writeHeader(output);

  PulseConfig pulseConfig = {
    scalePulse_(options->normal.longPulse, options->bitrate),
    scalePulse_(options->normal.shortPulse, options->bitrate),
    options->invert};

  uint32_t size_ = 0;
  switch (options->method) {
    case conventional:
      size_ = conventionalTransfer(output, image, &pulseConfig);
      break;
    case fast:
      size_ = fastTransfer(output, image, &pulseConfig);
      break;
    case turbo:
      size_ = fastTransfer(output, image, &pulseConfig);
      // TODO.
      break;
  }
  updateHeader(output, size_, 44356);

  fclose(output);

  return true;
}


int main(int argc, char **argv) {
  Options options = argParse(argc, argv);
  if (options.version) {
    printf(version);
    return 0;
  }
  if (options.error || !mzf2wav(&options)) {
    printf(usage, argv[0]);
    return 1;
  }
}

#include <stdlib.h>
#include <string.h>

#include "argparse.h"


unsigned int fileSize_(FILE *handle) {
  fseek(handle, 0, SEEK_END);
  unsigned int size = ftell(handle);
  rewind(handle);
  return size;
}

uint16_t scale_(uint16_t const length, uint32_t const bitrate) {
  return length * bitrate / 1000000;
}

PulseConfig makePulseConfig_(
    uint16_t const *const cfg, uint32_t const bitrate, bool const invert) {
  PulseConfig pulseConfig = {
    {scale_(cfg[0], bitrate), scale_(cfg[1], bitrate)},
    {scale_(cfg[2], bitrate), scale_(cfg[3], bitrate)}, invert};
  return pulseConfig;
}


bool mzf2wav(Options const *const options) {
  // Load MZF image.
  FILE *input = fopen(options->input, "rb");
  if (!input) {
    printf("Unable to open file \"%s\" for reading.\n", options->input);
    return false;
  }
  uint32_t size = fileSize_(input);
  uint8_t image[size];
  fread(image, 1, size, input);
  fclose(input);

  // Sanitise and check image.
  sanitiseImage(image, &size);
  if (!checkImage(image, size)) {
    printf("Invalid MZF file.\n");
    return false;
  }

  // Write WAV file.
  FILE *output = fopen(options->output, "wb");
  if (!output) {
    printf("Unable to open file \"%s\" for writing.\n", options->output);
    return false;
  }

  writeHeader(output);

  PulseConfig pulseConfig = makePulseConfig_(
    options->normal, options->bitrate, options->invert);
  PulseConfig turboConfig = makePulseConfig_(
    options->turbo, options->bitrate, options->invert);

  uint32_t size_ = 0;
  switch (options->method) {
    case conventional:
      size_ = conventionalTransfer(output, image, &pulseConfig);
      break;
    case fast:
      size_ = fastTransfer(output, image, &pulseConfig);
      break;
    case turbo:
      size_ = turboTransfer(output, image, &pulseConfig, &turboConfig);
      break;
  }
  updateHeader(output, size_, options->bitrate);

  fclose(output);

  return true;
}


int main(int const argc, char *const *const argv) {
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

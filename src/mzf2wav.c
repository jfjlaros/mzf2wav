#include <stdlib.h>
#include <string.h>

#include "argparse.h"

unsigned int fileSize_(FILE *handle) {
  fseek(handle, 0, SEEK_END);
  unsigned int size = ftell(handle);
  rewind(handle);
  return size;
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

  // Dirty MZF1 magic tag hack.
  if (!memcmp(image, "MZF1", 4)) {
    size -= 4;
    memmove(image, image + 4, size);
  }

  // TODO: checkImage()

  // Transfer file.
  FILE *output = fopen(options->output, "wb");
  if (!output) {
    printf("Unable to open file \"%s\" for writing.\n", options->output);
    return false;
  }

  writeHeader(output);
  //Waveform waveform = makeWaveform(
  //  options->initial.speed, 44000, options->invert, 0);
  PulseConfig pulseConfig = {
    toPulse(options->normal[0], options->bitrate),
    toPulse(options->normal[1], options->bitrate),
    options->invert};
  //WaveFormConfig wfc = {
  //  options->normal, options->invert, 44000};
  uint32_t size_ = options->method(output, image, &pulseConfig);
  updateHeader(output, size_, 44356);

  fclose(output);

  return true;
}


int main(int argc, char **argv) {
  Options options = argParse(argc, argv);
  if (options.error || !mzf2wav(&options)) {
    printf(usage, argv[0]);
    return 1;
  }
}

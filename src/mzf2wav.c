#include <stdlib.h>
#include <string.h>

#include "argparse.h"

char const usage_[] =
  "usage: %s [-c] [-t] [-p] [-b BITRATE] [-n SPEED] [-s SPEED] "
  "[-N FMT] [-S FMT] MZF WAV\n\n"
  "positional arguments:\n"
  "  MZF          input file in MZF format\n"
  "  WAV          input file in WAV format\n\n"
  "options:\n"
  "  -h           display help information and exit\n"
  "  -v           display version information and exit\n"
  "  -c           conventional mode\n"
  "  -t           turbo mode\n"
  "  -p           invert polarity\n"
  "  -b BITRATE   bit rate (dafault: 44100)\n"
  "  -n SPEED     normal mode speed 0 or 1 (default: 0)\n"
  "  -s SPEED     turbo mode speed 0, 1 or 2 (default: 0)\n"
  "  -N FMT       custom waveform for normal mode\n"
  "  -S FMT       custom waveform for turbo mode\n\n"
  "FMT: long_high,long_low,short_high,short_low\n";

char const version_[] =
  "MZF2WAV version 2.0.0\n"
  "Copyright (c) 2003-2023 Jeroen F.J. Laros <jlaros@fixedpoint.nl>\n"
  "Homepage: https://mzf2wav.readthedocs.io\n";


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
      size_ = conventionalFormat(output, image, &pulseConfig);
      break;
    case fast:
      size_ = fastFormat(output, image, &pulseConfig);
      break;
    case turbo:
      size_ = turboFormat(output, image, &pulseConfig, &turboConfig);
      break;
  }
  updateHeader(output, size_, options->bitrate);

  fclose(output);

  return true;
}


int main(int const argc, char *const *const argv) {
  Options options = argParse(argc, argv);
  if (options.help) {
    printf(usage_, argv[0]);
    return 0;
  }
  if (options.version) {
    printf(version_);
    return 0;
  }
  if (options.error || !mzf2wav(&options)) {
    printf(usage_, argv[0]);
    return 1;
  }
}

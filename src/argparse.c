#include "argparse.h"

#include <stdlib.h>
#include <string.h>
#include <getopt.h>

uint16_t const normalDefaults_[][4] = {
  {464, 494, 240, 264},   // Normal mode.
  {248, 474, 248, 271}};  // Fastest in normal mode.
uint16_t const turboDefaults_[][4] = {
  {248, 248, 113, 136},   // Turbo 2x.
  {158, 158,  68,  91},   // Turbo 3x.
  { 68, 158,  68,  91}};  // Fastest in turbo mode.

Options const default_ = {
  NULL, NULL, fast, false, 44100, {0}, {0}, false, false, false};


static size_t parseInt_(char const *const text, size_t const range) {
  size_t idx = strtoul(text, NULL, 10);
  if (idx >= range) {
    return 0;
  }
  return idx;
}

static void customPulses_(uint16_t *const pulses, char *const text) {
  char *p = text;
  for (size_t i = 0; i < 4 && *p; ++i, ++p) {
    pulses[i] = strtoul(p, &p, 10);
  }
}


Options argParse(int const argc, char *const *const argv) {
  Options options = default_;
  size_t const size = sizeof(normalDefaults_[0]);
  memcpy(options.normal, normalDefaults_[0], size);
  memcpy(options.turbo, turboDefaults_[0], size);

  int opt;
  while ((opt = getopt(argc, argv, "hvctpb:n:s:N:S:")) != -1) {
    switch (opt) {
      case 'h':
        options.help = true;
        return options;
      case 'v':
        options.version = true;
        return options;
      case 'c':
        options.method = conventional;
        break;
      case 't':
        options.method = turbo;
        break;
      case 'p':
        options.invert = true;
        break;
      case 'b':
        options.bitrate = atoi(optarg);
        break;
      case 'n':
        memcpy(options.normal, normalDefaults_[parseInt_(optarg, 2)], size);
        break;
      case 's':
        memcpy(options.turbo, turboDefaults_[parseInt_(optarg, 3)], size);
        break;
      case 'N':
        customPulses_(options.normal, optarg);
        break;
      case 'S':
        customPulses_(options.turbo, optarg);
        break;
      default:
        options.error = true;
        return options;
    }
  }

  if (optind != argc - 2) {
    options.error = true;
    return options;
  }
  options.input = argv[optind];
  options.output = argv[optind + 1];

  return options;
}

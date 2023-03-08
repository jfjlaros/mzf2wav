#include <stdlib.h>
#include <unistd.h>

#include "argparse.h"

PulsePair const normalDefaults_[] = {
  //{{464, 494}, {240, 264}},   // Normal mode.
  {{480, 494}, {260, 264}},   // TODO: should be the one above.
  {{248, 474}, {248, 271}}};  // Fastest in normal mode.
PulsePair const turboDefaults_[] = {
  {{248, 248}, {113, 136}},   // Turbo 2x.
  {{158, 158}, { 68,  91}},   // Turbo 3x.
  {{ 68, 158}, { 68,  91}}};  // Fastest in turbo mode.

Options const default_ = {
  NULL, NULL, normalDefaults_[0], turboDefaults_[0],
  44356, false, fast, NULL};

char const usage[] =
  "usage: %s [-c] [-t] [-p] [-b BITRATE] [-n SPEED] [-s SPEED]\n"
  "  [-N FMT] [-S FMT] MZF WAV\n\n"
  "positional arguments:\n"
  "  MZF          input file in MZF format\n"
  "  WAV          input file in WAV format\n\n"
  "options:\n"
  "  -c           conventional mode\n"
  "  -t           turbo mode\n"
  "  -p           reverse polarity\n"
  "  -b BITRATE   bitrate (dafault: 44000)\n"
  "  -n SPEED     normal mode speed 0 or 1 (default: 0)\n"
  "  -s SPEED     turbo mode speed 0, 1 or 2 (default: 0)\n"
  "  -N FMT       custom waveform for normal mode\n"
  "  -S FMT       custom waveform for turbo mode\n\n"
  "FMT: long_up,long_down,short_up,short_down\n";


bool parse_(uint16_t *result, char **p) {
  *result = strtoul(*p, p, 10);
  return **p;
}

PulsePair customPulsePair_(char *const text) {
  PulsePair pair;
  uint16_t* arr[4] = {
    &pair.longPulse.up, &pair.longPulse.down,
    &pair.shortPulse.up, &pair.shortPulse.down};

  char* p = text;
  for (size_t i = 0; i < 4 && parse_(arr[i], &p); ++i, ++p);

  return pair;
}


Options argParse(int argc, char **argv) {
  Options options = default_;

  int opt;
  while ((opt = getopt(argc, argv, "i:t:1:2:b:pcw")) != -1) {
    switch (opt) {
      case 'i':
        options.normal = normalDefaults_[atoi(optarg)];
        break;
      case 't':
        options.turbo = turboDefaults_[atoi(optarg)];
        break;
      case '1':
        options.normal = customPulsePair_(optarg);
        break;
      case '2':
        options.turbo = customPulsePair_(optarg);
        break;
      case 'b':
        options.bitrate = atoi(optarg);
        break;
      case 'p':
        options.invert = true;
        break;
      case 'c':
        options.method = conventional;
        break;
      case 'w':
        options.method = turbo;
        break;
      default:
        options.error = true;
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

#include <stdlib.h>
#include <unistd.h>

#include "argparse.h"

Pulses const normalDefaults_[] = {
  //{{464, 494}, {240, 264}},   // Normal mode.
  {{480, 494}, {260, 264}},   // TODO: replace with the one above.
  {{248, 474}, {248, 271}}};  // Fastest in normal mode.
Pulses const turboDefaults_[] = {
  {{248, 248}, {113, 136}},   // Turbo 2x.
  {{158, 158}, { 68,  91}},   // Turbo 3x.
  {{ 68, 158}, { 68,  91}}};  // Fastest in turbo mode.

Options const default_ = {
  NULL, NULL, fast, false, 44356, normalDefaults_[0], turboDefaults_[0],
  false, false};

char const usage[] =
  "usage: %s [-c] [-t] [-p] [-b BITRATE] [-n SPEED] [-s SPEED]\n"
  "  [-N FMT] [-S FMT] MZF WAV\n\n"
  "positional arguments:\n"
  "  MZF          input file in MZF format\n"
  "  WAV          input file in WAV format\n\n"
  "options:\n"
  "  -h           display help information and exit\n"
  "  -v           display version information and exit\n"
  "  -c           conventional mode\n"
  "  -t           turbo mode\n"
  "  -p           reverse polarity\n"
  "  -b BITRATE   bitrate (dafault: 44000)\n"
  "  -n SPEED     normal mode speed 0 or 1 (default: 0)\n"
  "  -s SPEED     turbo mode speed 0, 1 or 2 (default: 0)\n"
  "  -N FMT       custom waveform for normal mode\n"
  "  -S FMT       custom waveform for turbo mode\n\n"
  "FMT: long_up,long_down,short_up,short_down\n";

char const version[] =
  "MZF2WAV version 2.0.0\n"
  "Copyright (c) 2003-2023 Jeroen F.J. Laros <jlaros@fixedpoint.nl>\n"
  "Homepage: https://mzf2wav.readthedocs.io\n";


Pulses customPulses_(char *const text) {
  Pulses pair = {{0, 0}, {0, 0}};

  uint16_t *arr[] = {
    &pair.longPulse.up, &pair.longPulse.down,
    &pair.shortPulse.up, &pair.shortPulse.down};
  char *p = text;
  for (size_t i = 0; i < 4 && *p; ++i, ++p) {
    *arr[i] = strtoul(p, &p, 10);
  }

  return pair;
}


Options argParse(int argc, char **argv) {
  Options options = default_;

  int opt;
  while ((opt = getopt(argc, argv, "hvctp:b:n:s:N:S:")) != -1) {
    switch (opt) {
      case 'h':
        options.error = true;
        break;
      case 'v':
        options.version = true;
        break;
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
        options.normal = normalDefaults_[atoi(optarg)];  // TODO: range check
        break;
      case 's':
        options.turbo = turboDefaults_[atoi(optarg)];    // TODO: range check
        break;
      case 'N':
        options.normal = customPulses_(optarg);
        break;
      case 'S':
        options.turbo = customPulses_(optarg);
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

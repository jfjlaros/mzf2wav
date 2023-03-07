#include <stdlib.h>
#include <unistd.h>

#include "argparse.h"

// TODO: precalculate using bitrate.
Pulse const normalDefaults_[][2] = {
  //{{464, 494}, {240, 264}},   // Normal mode.
  {{480, 494}, {260, 264}},   // TODO: should be the one above.
  {{248, 474}, {248, 271}}};  // Fastest in normal mode.
Pulse const turboDefaults_[][2] = {
  {{248, 248}, {113, 136}},   // Turbo 2x.
  {{158, 158}, { 68,  91}},   // Turbo 3x.
  {{ 68, 158}, { 68,  91}}};  // Fastest in turbo mode.

Options const default_ = {
  NULL, NULL, {normalDefaults_[0][0], normalDefaults_[0][1]},
  {turboDefaults_[0][0], turboDefaults_[0][1]},
  44356, false, fastTransfer, NULL};

char const usage[] =
  "Usage: %s <-i n> <-t n> <-1 n> <-2 n> <-b n> <-c> <-s> <-w> <-p> in out\n"
  " -i normal speed mode (0 or 1), default = 0.\n"
  " -t turbo speed mode (0, 1 or 2), default = 0.\n"
  " -1 correction for fast normal mode (-50 to 50).\n"  // TODO: replace
  " -2 correction for fast turbo mode (-50 to 50).\n"   // TODO: replace
  " -b bitrate.\n"
  " -p reverse polarity.\n"
  " -c conventional writing mode.\n"
  " -w turbo writing mode.\n";


/*
void parseWaveform_(Waveform *waveform, char const *const str) {
  char *p = str;
}
*/


Options argParse(int argc, char **argv) {
  Options options = default_;

  int opt;
  while ((opt = getopt(argc, argv, "i:t:1:2:b:pcw")) != -1) {
    switch (opt) {
      case 'i':
        options.normal[0] = normalDefaults_[atoi(optarg)][0];
        options.normal[1] = normalDefaults_[atoi(optarg)][1];
        break;
      case 't':
        //options.turbo = turboDefaults_[atoi(optarg)];
        break;
      case '1':
        //options.normal = normalDefaults[atoi(optarg)];
        break;
      case '2':
        //options.turbo = turboDefaults[atoi(optarg)];
        break;
      case 'b':
        options.bitrate = atoi(optarg);
        break;
      case 'p':
        options.invert = true;
        break;
      case 'c':
        options.method = conventionalTransfer;
        break;
      case 'w':
        options.method = turboTransfer;
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

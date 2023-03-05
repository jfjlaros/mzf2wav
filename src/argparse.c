#include <stdlib.h>
#include <unistd.h>

#include "argparse.h"

Options const default_ = {
  NULL, NULL, {0, 0}, {0, 0}, 0, false, fastTransfer, NULL};

char const usage[] =
  "Usage: %s <-i n> <-t n> <-1 n> <-2 n> <-b n> <-c> <-s> <-w> <-p> in out\n"
  " -i initial speed mode (0, 1, 2, 3 or 4), default = 0.\n"
  " -t turbo speed mode (0, 1, 2, 3 or 4), default = 2.\n"
  " -1 correction for fast initial mode (-50 to 50).\n"
  " -2 correction for fast turbo mode (-50 to 50).\n"
  " -b bitrate.\n"
  " -p reverse polarity.\n"
  " -c conventional writing mode.\n"
  " -w turbo writing mode.\n";


Options argParse(int argc, char **argv) {
  Options options = default_;

  int opt;
  while ((opt = getopt(argc, argv, "i:t:1:2:b:pcw")) != -1) {
    switch (opt) {
      case 'i':
        options.initial.speed = atoi(optarg);
        break;
      case 't':
        options.turbo.speed = atoi(optarg);
        break;
      case '1':
        options.initial.correction = atoi(optarg);
        break;
      case '2':
        options.turbo.correction = atoi(optarg);
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

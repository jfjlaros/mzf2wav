#include "methods.h"

typedef struct {  // TODO: check types.
  char const *input;
  char const *output;
  Pulse normal[2];
  Pulse turbo[2];
  int bitrate;
  bool invert;
  uint32_t (*method)(FILE *, uint8_t const *const, PCP);

  bool error;
} Options;

extern char const usage[];


/*! Parse command line arguments.
 *
 * \param argc
 * \param argv
 *
 * \return
 */
Options argParse(int argc, char **argv);

#include "methods.h"

typedef struct {  // TODO: check types.
  Speed speed;
  int correction;
} WaveConfig;

typedef struct {  // TODO: check types.
  char const *input;
  char const *output;
  WaveConfig initial;
  WaveConfig turbo;
  int bitrate;
  bool invert;
  uint32_t (*method)(FILE *, uint8_t const *const, WaveCfgPtr);

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

#include "methods.h"

typedef enum {conventional, fast, turbo} Method;

typedef struct {
  Pulse longPulse;
  Pulse shortPulse;
} PulsePair;

typedef struct {  // TODO: check types.
  char const *input;
  char const *output;
  PulsePair normal;
  PulsePair turbo;
  int bitrate;
  bool invert;
  //uint32_t (*method)(FILE *, uint8_t const *const, PCP);
  Method method;

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

#include "methods.h"

typedef enum {conventional, fast, turbo} Method;

typedef struct {
  Pulse longPulse;
  Pulse shortPulse;
} Pulses;

typedef struct {
  char const *input;
  char const *output;

  Method method;
  bool invert;
  int bitrate;
  Pulses normal;
  Pulses turbo;

  bool error;
  bool version;
} Options;

extern char const usage[];
extern char const version[];


/*! Parse command line arguments.
 *
 * \param argc
 * \param argv
 *
 * \return
 */
Options argParse(int argc, char **argv);

#include "methods.h"

typedef enum {conventional, fast, turbo} Method;

typedef struct {
  char const *input;   //!< Input file.
  char const *output;  //!< Output file.

  Method method;       //!< Transfer method.
  bool invert;         //!< Invert polarity.
  uint32_t bitrate;    //!< Bit rate.
  uint16_t normal[4];  //!< Normal mode pulses.
  uint16_t turbo[4];   //!< Turbo mode pulses.

  bool error;          //!< Error.
  bool version;        //!< Version.
} Options;

extern char const usage[];    // Usage string.
extern char const version[];  // Version string.


/*! Parse command line arguments.
 *
 * \param [in] argc Argument count.
 * \param [in] argv Argument vector.
 *
 * \return Parsed options.
 */
Options argParse(int const argc, char *const *const argv);

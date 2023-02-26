#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/*! Write one bit.
 *
 * \param output Output file.
 * \param bit Bit.
 * \param invert Invert polarity.
 */
void writeBit(FILE *output, bool const bit, bool const invert);

/*! Write the WAV header.
 *
 * \param output Output file.
 */
void writeHeader(FILE *output);

/*! Update the WAV header.
 *
 * \param output Output file.
 * \param size File size.
 * \param bitrate Bitrate.
 */
void updateHeader(FILE *output, uint32_t const size, uint32_t const bitrate);

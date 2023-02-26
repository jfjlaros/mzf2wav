#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

extern int waveScale;

/*! Set WAV bitrate.
 *
 * \param bitrate Bitrate.
 */
void setBitrate(uint32_t bitrate);

/*! Write one bit.
 *
 * \param output Output file.
 * \param bit Bit.
 * \param invert Invert polarity.
 */
void writeBit(FILE *output, bool const bit, bool const invert);

/*! Write a WAV header.
 *
 * \param output Output file.
 */
void writeHeader(FILE *output);

/*! Set filesizes in the WAV header.
 *
 * \param output Output file.
 * \param size File size.
 */
void setHeader(FILE *output, uint32_t const size);

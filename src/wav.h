#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/*! Write one bit.
 *
 * \param [out] output Output file.
 * \param [in] bit Bit.
 * \param [in] invert Invert polarity.
 */
void writeBit(FILE *const output, bool const bit, bool const invert);

/*! Write the WAV header.
 *
 * \param [out] output Output file.
 */
void writeHeader(FILE *const output);

/*! Update the WAV header.
 *
 * \param [out] output Output file.
 * \param [in] size File size.
 * \param [in] bitrate Bitrate.
 */
void updateHeader(
  FILE *const output, uint32_t const size, uint32_t const bitrate);

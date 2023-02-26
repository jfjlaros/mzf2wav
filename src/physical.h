#include "wav.h"

typedef enum {
  normal, fastNormal, turbo2, turbo3, fastTurbo
} Speed;

extern int fastCorrection;
extern int turboCorrection;

/*! Write a gap of n short pulses.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param n Number of pulses.
 * \param invert Invert polarity.
 */
void writeGap(FILE *output, uint32_t *size, int const n, bool const invert);

/*! Write a tape mark of n long pulses, n short pulses and one long pulse.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param n Number of pulses.
 * \param invert Invert polarity.
 */
void writeTapeMark(FILE *output, uint32_t *size, int const, bool const invert);

/*! Write a checksum.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param checksum Checksum.
 * \param invert Invert polarity.
 */
void writeChecksum(FILE *output, uint32_t *size, uint16_t const checksum, bool const invert);

/*! Define the waveform to use.
 *
 * \param speed Speed.
 */
void setSpeed(Speed const speed);

/*! Write a byte and count the ones for the checksum.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param data Data.
 * \param invert Invert polarity.
 *
 * \return Number of ones in `data`.
 */
uint16_t writeByte(FILE *output, uint32_t *size, uint8_t const data, bool const invert);

/*! Get the file size.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param image MZF image.
 *
 * \return Size of `image`.
 */
uint16_t getFileSize(uint8_t const *const image);

/*! See if the MZF file is valid.
 *
 * \param image MZF image.
 * \param size Image size.
 *
 * \return TODO
 */
int checkImage(uint8_t const *const image, uint16_t const size);

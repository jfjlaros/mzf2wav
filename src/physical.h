#include "wav.h"

typedef struct {
  uint16_t up;
  uint16_t down;
} Pulse;

typedef struct {
  Pulse longPulse;
  Pulse shortPulse;
  bool invert;
} PulseConfig;

typedef PulseConfig const *const PCP;


Pulse toPulse(Pulse const pulse, uint32_t const bitrate);

/*! Write a gap of `n` short pulses.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] pulseConfig Pulse config.
 */
void writeGap(FILE *output, uint32_t *size, int const n, PCP pulseConfig);

/*! Write a tape mark of `n` long pulses, `n` short pulses and one long pulse.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] pulseConfig Pulse config.
 */
void writeTapeMark(
  FILE *output, uint32_t *size, int const n, PCP pulseConfig);

/*! Write a byte and count the number of ones for the checksum.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] data Data.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of ones in `data`.
 */
uint16_t writeByte(
  FILE *output, uint32_t *size, uint8_t const data, PCP pulseConfig);

/*! Write a checksum.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] checksum Checksum.
 * \param [in] pulseConfig Pulse config.
 */
void writeChecksum(
  FILE *output, uint32_t *size, uint16_t const checksum, PCP pulseConfig);

/*! Get the image size.
 *
 * \param [in] image MZF image.
 *
 * \return Size of `image`.
 */
uint16_t getImageSize(uint8_t const *const image);

/*! See if the MZF file is valid.
 *
 * \param [in] image MZF image.
 * \param [in] size Image size.
 *
 * \return TODO
 */
int checkImage(uint8_t const *const image, uint16_t const size);

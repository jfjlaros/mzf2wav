#include "wav.h"

typedef struct {
  uint16_t high;  //!< Pulse high count.
  uint16_t low;   //!< Pulse low count.
} Pulse;

typedef struct {
  Pulse longPulse;   //!< Long pulse.
  Pulse shortPulse;  //!< Short pulse.
  bool invert;       //!< Invert polarity.
} PulseConfig;

typedef PulseConfig const *const PCP;  //!< Constant pulse config pointer.


/*! Write a gap of `n` short pulses.
 *
 * \param [out] output Output file.
 * \param [in,out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] pulseConfig Pulse config.
 */
void writeGap(
  FILE *const output, uint32_t *const size, int const n, PCP pulseConfig);

/*! Write a tape mark of `n` long pulses, `n` short pulses and one long pulse.
 *
 * \param [out] output Output file.
 * \param [in,out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] pulseConfig Pulse config.
 */
void writeTapeMark(
  FILE *const output, uint32_t *const size, int const n, PCP pulseConfig);

/*! Write a byte and count the number of ones for the checksum.
 *
 * \param [out] output Output file.
 * \param [in,out] size Size of `output`.
 * \param [in] data Data.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of ones in `data`.
 */
uint16_t writeByte(
  FILE *const output, uint32_t *const size, uint8_t const data,
  PCP pulseConfig);

/*! Write a checksum.
 *
 * \param [out] output Output file.
 * \param [in,out] size Size of `output`.
 * \param [in] checksum Checksum.
 * \param [in] pulseConfig Pulse config.
 */
void writeChecksum(
  FILE *const output, uint32_t *const size, uint16_t const checksum,
  PCP pulseConfig);

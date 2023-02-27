#include "physical.h"

extern Speed secondStageSpeed;  // TODO: remove

/*! Fast file transfer.
 *
 * \param image MZF image.
 * \param waveform Waveform.
 */
void fastTransfer(uint8_t const *const image, Waveform const *const waveform);

/*! Conventional file transfer.
 *
 * \param image MZF image.
 * \param waveform Waveform.
 */
void conventionalTransfer(
  uint8_t const *const image, Waveform const *const waveform);

/*! Turbo file transfer.
 *
 * \param image MZF image.
 * \param waveform Waveform.
 */
void turboTransfer(uint8_t const *const image, Waveform const *const waveform);

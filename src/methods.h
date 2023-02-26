#include "physical.h"

extern Speed secondStageSpeed;

/*! Fast file transfer.
 *
 * \param image MZF image.
 * \param invert Invert polarity.
 */
void fastTransfer(uint8_t const *const image, bool const invert);

/*! Conventional file transfer.
 *
 * \param image MZF image.
 * \param invert Invert polarity.
 */
void conventionalTransfer(uint8_t const *const image, bool const invert);

/*! Turbo file transfer.
 *
 * \param image MZF image.
 * \param invert Invert polarity.
 */
void turboTransfer(uint8_t const *const image, bool const invert);

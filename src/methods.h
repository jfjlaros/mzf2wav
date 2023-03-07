#include "physical.h"

/*! Fast file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t fastTransfer(
  FILE *output, uint8_t const *const image, PCP pulseConfig);

/*! Conventional file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t conventionalTransfer(
  FILE *output, uint8_t const *const image, PCP pulseConfig);

/*! Turbo file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t turboTransfer(
  FILE *output, uint8_t const *const image, PCP pulseConfig);

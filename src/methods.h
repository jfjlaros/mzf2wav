#include "physical.h"

extern Speed secondStageSpeed;  // TODO: remove

/*! Fast file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param wfc Waveform config.
 *
 * \return Number of bytes written.
 */
uint32_t fastTransfer(
  FILE *output, uint8_t const *const image, WaveCfgPtr wfc);

/*! Conventional file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param wfc Waveform config.
 *
 * \return Number of bytes written.
 */
uint32_t conventionalTransfer(
  FILE *output, uint8_t const *const image, WaveCfgPtr wfc);

/*! Turbo file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param wfc Waveform config.
 *
 * \return Number of bytes written.
 */
uint32_t turboTransfer(
  FILE *output, uint8_t const *const image, WaveCfgPtr wfc);

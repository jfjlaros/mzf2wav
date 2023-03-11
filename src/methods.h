#include "mzf.h"
#include "write.h"


/*! Fast file transfer.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t fastTransfer(FILE *const output, IMGP image, PCP pulseConfig);

/*! Conventional file transfer.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t conventionalTransfer(
  FILE *const output, IMGP image, PCP pulseConfig);

/*! Turbo file transfer.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 * \param [in] turboConfig Pulse config for turbo mode.
 *
 * \return Number of bytes written.
 */
uint32_t turboTransfer(
  FILE *output, IMGP image, PCP pulseConfig, PCP turboConfig);

#include "mzf.h"
#include "write.h"


/*! Write using the conventional format.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t conventionalFormat(
  FILE *const output, IMGP image, PCP pulseConfig);

/*! Write using the fast format.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t fastFormat(FILE *const output, IMGP image, PCP pulseConfig);

/*! Write using the turbo format.
 *
 * \param [out] output Output file.
 * \param [in] image MZF image.
 * \param [in] pulseConfig Pulse config.
 * \param [in] turboConfig Pulse config for turbo mode.
 *
 * \return Number of bytes written.
 */
uint32_t turboFormat(
  FILE *output, IMGP image, PCP pulseConfig, PCP turboConfig);

#include "write.h"

typedef uint8_t const *const IMGP;

/*! See if the MZF file is valid.
 *
 * \param [in] image MZF image.
 * \param [in] size Image size.
 *
 * \return TODO
 */
int checkImage(IMGP image, uint16_t const size);

/*! Fast file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t fastTransfer(FILE *output, IMGP image, PCP pulseConfig);

/*! Conventional file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t conventionalTransfer(FILE *output, IMGP image, PCP pulseConfig);

/*! Turbo file transfer.
 *
 * \param output Output file.
 * \param image MZF image.
 * \param pulseConfig Pulse config.
 *
 * \return Number of bytes written.
 */
uint32_t turboTransfer(FILE *output, IMGP image, PCP pulseConfig);

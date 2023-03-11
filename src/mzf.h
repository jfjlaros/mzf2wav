#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t const *const IMGP;    //!< Constant image pointer.

extern size_t const turboLoaderSize;  //!< Size of the turbo loader image.


/*! Sanitise an MZF image and change its size accordingly.
 *
 * \param [in,out] image MZF image.
 * \param [in,out] size Image size.
 */
void sanitiseImage(uint8_t *const image, uint32_t *const size);

/*! Determine the size of an MZF image from its header.
 *
 * \param [in] image MZF image.
 *
 * \return Size of MZF image.
 */
uint16_t imageSize(IMGP image);

/*! Check whether the MZF file is valid.
 *
 * \param [in] image MZF image.
 * \param [in] size Image size.
 *
 * \return `true` if `image` is valid, `false` otherwise.
 */
bool checkImage(IMGP image, uint16_t const size);

/*! Prepare a turbo loader image for a given MZF image.
 *
 * \param [out] loader Buffer for MZF turbo loader image.
 * \param [in] image MZF image.
 */
void prepareLoader(uint8_t *const loader, IMGP image);

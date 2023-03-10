#include <stddef.h>
#include <stdint.h>

typedef uint8_t const *const IMGP;

extern uint8_t const turboLoader[];
extern size_t const turboLoaderSize;


/*
 */
uint16_t getImageSize(IMGP image);

/*! See if the MZF file is valid.
 *
 * \param [in] image MZF image.
 * \param [in] size Image size.
 *
 * \return TODO
 */
int checkImage(IMGP image, uint16_t const size);

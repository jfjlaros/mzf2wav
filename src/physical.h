#include "wav.h"

typedef struct {
  uint8_t up;
  uint8_t down;
} Pulse;

typedef struct {
  Pulse longPulse;
  Pulse shortPulse;
  bool invert;
} Waveform;

typedef enum {
  normal, fastNormal, turbo2, turbo3, fastTurbo
} Speed;


/*! Write a gap of `n` short pulses.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param n Number of pulses.
 * \param waveform Waveform.
 */
void writeGap(
  FILE *output, uint32_t *size, int const n, Waveform const *const waveform);

/*! Write a tape mark of `n` long pulses, `n` short pulses and one long pulse.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param n Number of pulses.
 * \param waveform Waveform.
 */
void writeTapeMark(
  FILE *output, uint32_t *size, int const, Waveform const *const waveform);

/*! Write a byte and count the number of ones for the checksum.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param data Data.
 * \param waveform Waveform.
 *
 * \return Number of ones in `data`.
 */
uint16_t writeByte(
  FILE *output, uint32_t *size, uint8_t const data,
  Waveform const *const waveform);

/*! Write a checksum.
 *
 * \param output Output file.
 * \param size Size of `output`.
 * \param checksum Checksum.
 * \param waveform Waveform.
 */
void writeChecksum(
  FILE *output, uint32_t *size, uint16_t const checksum,
  Waveform const *const waveform);

/*! Define the waveform to use.
 *
 * \param waveForm Waveform.
 * \param waveScale Wave scaling factor.
 * \param speed Speed.
 * \param bitrate Bitrate.
 * \param invert Invert waveform.
 * \param correction Wave correction.
 */
void configureWaveform(
    Waveform *waveform, Speed const speed, int const bitrate,
    bool const invert, int const correction);

/*! Get the image size.
 *
 * \param image MZF image.
 *
 * \return Size of `image`.
 */
uint16_t getImageSize(uint8_t const *const image);

/*! See if the MZF file is valid.
 *
 * \param image MZF image.
 * \param size Image size.
 *
 * \return TODO
 */
int checkImage(uint8_t const *const image, uint16_t const size);

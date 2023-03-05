#include "wav.h"

typedef struct {
  uint16_t up;
  uint16_t down;
} Pulse;

typedef struct {
  Pulse longPulse;
  Pulse shortPulse;
} Waveform;

typedef struct {
  Waveform wave;
  bool invert;
  uint32_t bitrate;
} WaveFormConfig;

typedef WaveFormConfig const* const WaveCfgPtr;

typedef enum {
  normal, fastNormal, turbo2, turbo3, fastTurbo
} Speed;

extern Waveform const waveforms[];


/*! Write a gap of `n` short pulses.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] wfc Waveform config.
 */
void writeGap(FILE *output, uint32_t *size, int const n, WaveCfgPtr wfc);

/*! Write a tape mark of `n` long pulses, `n` short pulses and one long pulse.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] n Number of pulses.
 * \param [in] wfc Waveform config.
 */
void writeTapeMark(
  FILE *output, uint32_t *size, int const n, WaveCfgPtr wfc);

/*! Write a byte and count the number of ones for the checksum.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] data Data.
 * \param [in] wfc Waveform config.
 *
 * \return Number of ones in `data`.
 */
uint16_t writeByte(
  FILE *output, uint32_t *size, uint8_t const data, WaveCfgPtr wfc);

/*! Write a checksum.
 *
 * \param [out] output Output file.
 * \param [out] size Size of `output`.
 * \param [in] checksum Checksum.
 * \param [in] wfc Waveform config.
 */
void writeChecksum(
  FILE *output, uint32_t *size, uint16_t const checksum, WaveCfgPtr wfc);

/*! Get the image size.
 *
 * \param [in] image MZF image.
 *
 * \return Size of `image`.
 */
uint16_t getImageSize(uint8_t const *const image);

/*! See if the MZF file is valid.
 *
 * \param [in] image MZF image.
 * \param [in] size Image size.
 *
 * \return TODO
 */
int checkImage(uint8_t const *const image, uint16_t const size);

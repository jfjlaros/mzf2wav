#include <errno.h>
#include <stdio.h>
#include <stdlib.h> // Just to remove a warning (exit).
#include "args.h"
#include "methods.h"

extern Speed firstStageSpeed;
extern char *filename,
            *outfile;
extern void (*method)(uint8_t const *const, Waveform *const);
extern bool invert;
extern int waveScale; // TODO
extern int bitrate;

// Private function prototypes.
int chtoi(char *), // Convert the first char of a string to an integer.
    stoi(char *);  // Convert a string to an integer.

// Private functions.
// Convert the first char of a string to an integer and check the boundries.
int chtoi(char *string) {
  int temp = 0;

  if (!string)
    return -1;
  temp = (int)string[0] - 48;
  if ((temp < 0) || (temp > 4))
    return -1;
  return temp;
}//chtoi

// Convert a string to an integer and check the boundries.
int stoi(char *string) {
  int i = 0,
      m = 1,
      temp = 0,
      ret = 0;

  if (!string)
    return -100;
  if (string[0] == '-') {
    m = -1;
    i++;
  }//if

  while (string[i]) {
    temp = (int)string[i] - 48;
    if ((temp < 0) || (temp > 9))
      return -100;
    ret *= 10;
    ret += temp;
    i++;
  }//while
  if (ret > 50)
    return -100;
  return m * ret;
}//stoi

// Public functions.
// Print usage and return an error code.
void error(int i) {
  printf("Usage: mzf2wav <-i n> <-t n> <-1 n> <-2 n> <-b n> <-c> <-s> <-w> <-p> in out\n"
         " -i sets initial speed mode (0, 1, 2, 3 or 4), default = 0.\n"
         " -t sets turbo speed mode (0, 1, 2, 3 or 4), default = 2.\n"
         " -1 sets correction for fast initial mode (-50 to 50).\n"
         " -2 sets correction for fast turbo mode (-50 to 50).\n"
         " -b sets bit rate.\n"
         " -c sets conventional writing mode.\n"
         " -s sets fast writing mode (default).\n"
         " -w sets turbo writing mode.\n"
         " -p reverse polarity.\n");
  exit(i);
}//error

// Set the configuration variables.
int setvars(int argc, char **argv) {
  char *endptr;
  int temp = 0,
      i = 1;

  while (i < argc) {
    if (argv[i][0] == '-')
      switch (argv[i][1]) {
        case 'i':                                   // Initial write speed.
          temp = chtoi(argv[i + 1]);
          if (temp == -1) {
            printf("No valid initial speed given.\n");
            error(1);
          }//if
          firstStageSpeed = temp;
          i++;
          break;
        case 't':                                   // Turbo write speed.
          temp = chtoi(argv[i + 1]);
          if (temp == -1) {
            printf("No valid turbo speed given.\n");
            error(1);
          }//if
          secondStageSpeed = temp;
          i++;
          break;
        case '1':                                   // Initial fast correction.
          temp = stoi(argv[i + 1]);
          if (temp == -100) {
            printf("No valid fast initial correction given.\n");
            error(1);
          }//if
          //fastCorrection = temp;
          i++;
          break;
        case '2':                                   // Initial fast correction.
          temp = stoi(argv[i + 1]);
          if (temp == -100) {
            printf("No valid fast turbo correction given.\n");
            error(1);
          }//if
          //turboCorrection = temp;
          i++;
          break;
        case 'b':                                   // Bit rate.
          errno = 0;
          temp = strtol(argv[i + 1], &endptr, 10);
          if (errno) {
            printf("No valid bit rate given.\n");
            error(1);
          }//if
          //waveScale = setBitrate((uint32_t)temp);
          bitrate = temp;
          waveScale = 44100 / temp;
          i++;
          break;
        case 'c':
          method = conventionalTransfer;
          break;
        case 's':
          method = fastTransfer;
          break;
        case 'w':
          method = turboTransfer;
          break;
        case 'p':
          //reversePolarity();
          invert = true;
          break;
        default:
          printf("Unknown option: %s\n", argv[i]);
          error(1);
      }//switch
    else
      if (!filename)
        filename = argv[i];
      else
        outfile = argv[i];
    i++;
  }//while
  if (!filename) {
    printf("No filename given.\n");
    error(1);
  }//if
  if (!outfile) {
    printf("No output filename given.\n");
    error(1);
  }//if

  return 0;
}//setvars

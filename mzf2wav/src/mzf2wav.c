/*
 * mzf2wav by: Jeroen F. J. Laros.
 *
 * Last change on: Sep 11 2003.
 * 
 * This program is freeware and may be used without paying any registration 
 * fees. It may be distributed freely provided it is done so using the 
 * original, unmodified version. Usage of parts of the source code is granted, 
 * provided the author is referenced. For private use only. Re-selling or any 
 * commercial use of this program or parts of it is strictly forbidden. The
 * author is not responsible for any damage or data loss as a result of using 
 * this program.
 */
#include <stdio.h>
#include <stdlib.h> // Just to remove a warning (malloc).
#include "methods.h"
#include "args.h"

// Global variables.
FILE *OUT = NULL;
int speed_1 = 0;
char *filename = NULL,
     *outfile = NULL;
void (*method)(byte *) = trans;

//Private function prototypes.
byte *readfile(FILE *); // Read the file into memory.

// Read the file into memory.
byte *readfile(FILE *IN) {
  byte *image = (byte *)malloc(2),
       *temp = NULL;
  word i = 0,
       t = 0;

  if (!image)
    return NULL;
  while (fread(&image[i], 1, 1, IN)) {
    temp = (byte *)realloc((byte *)image, i + 2);
    if (!temp) {
      free(image);
      return NULL;
    }//if
    image = temp;
    i++;
  }//while
  t = assert(image, i);
  if (t) {
    printf("The MZF file size does not match the image size.\n");
    if (t > 1) {
      printf("This is not a valid MZF file.\n");
      free(image);
      return NULL;
    }//if
  }//if
  return image;
}//readfile

// Main.
int main(int argc, char **argv) {
  FILE *IN = NULL;
  byte *image = NULL;
  int i = 0;
  
  setvars(argc, argv);

  IN = fopen(filename, "rb");
  if (!IN) {
    printf("Unable to open file: %s for reading.\n\n", argv[1]);
    error(2);
  }//if
  
  image = readfile(IN);
  if (!image) {
    printf("Out of memory or assertion error.\n\n");
    fclose(IN);
    error(3);
  }//if
  OUT = fopen(outfile, "wb");
  if (!OUT) {
    printf("Error: unable to open output file: %s for writing.\n", outfile);
    free(image);
    fclose(IN);
    error(6);
  }//if

  while (fread(&image[i], 1, 1, IN))
    i++;

  setspeed(speed_1);
  
  writewavheader();
  method(image);
  setheader();

  fclose(OUT);
  free(image);
  fclose(IN);
  
  return 0;
}//main

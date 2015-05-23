#!/bin/sh

cp Makefile.linux ../Makefile
cd ..
make release
make realclean
rm Makefile
echo If all is well, the executable is in: linux/release

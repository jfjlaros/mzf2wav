@echo off

copy Makefile.Windows ..\Makefile
cd ..
nmake release
nmake realclean
del Makefile
cd w32
echo If all is well, the executable and belongings are in:
echo w32\release

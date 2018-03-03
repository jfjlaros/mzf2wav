# MZF2WAV
There are several ways to transfer the
[downloadable MZF-files](https://sharpmz.org/) to your MZ or directly to your
data recorder:

- Directly connect the data recorder to your PC and use the PC-interface.
- Connect your MZ or your data recorder to the soundcard of your PC.

The first method is described on the page
[PC tape interface](https://sharpmz.org/mztape.htm) and also enables you to
receive files from your data recorder.

The second method is described on the page
[File transfer / Data transfer problem](https://sharpmz.org/mz-700/filetrans.htm).
Karl Walpuski describes the transfer from the MZ to the PC using the program
tapeload.exe, but if you use a WAV-player-program like the Windows Mediaplayer
and you have connected your MZ or data recorder to the output connector of your
PC soundcard, then you can transfer your files into the other direction. In
this case, of course, you do not need tapeload.exe, but you need a converter
program which converts your MZF-files (or M12, or MZT; simple rename the file
to MZF) to a WAV-file which can be transmitted directly.

If you decide to use an audio recorder to interface between an MZ and your PC,
think first about all problems you can get by doing this. And, be sure, there
are a lot of problems waiting for you! Please read the article:
[Using an audio recorder](https://sharpmz.org/mz-700/usetape2.htm) first before
you decide. At a first sight using an audio recorder looks very user-friendly
and simple to do (e.g., only a standard stereo cinch cable is needed and a
transfer program). But, sooner or later you'll get a knowledge about why data
recorders exist. ;-)

We also know, and so, a program to transfer MZF-files to the MZ is in progress
by the author Jeroen F.J. Laros. It will work on all Wins and Linux.

This article describes a converter MZF to WAV. It is written by Jeroen F.J.
Laros from Netherlands. There are other converters available in the internet (I
saw e.g., a Japanese MZF2WAV-program, a Czech TransManger, Adler's MZ-800
emulator contains also such a converter) but this version is very simple to use
and allows several baud rates.

![The help screen of MZF2WAV](doc/mzf2wavs1.gif)

Simply type

    mzf2wav inputfile outputfile

in the Windows-DOS prompt (The program will not work under plain DOS!) and a
WAV-file containing your program will be written with the standard speed of
1200 baud. `inputfile` is the name of your MZF-file (e.g., `myprog.mzf`) and
`outputfile` is the name of the new WAV-file (e.g., `myprog.wav`). Use path
information for all files if required. Change the BAT-file for your purposes if
you prefer to use it.

All options shown in the screenshot above are optional and described in the
author's manual.

Download it now (PDF, 41kb, 6 pages) - you'll need it.

Download this utility now (25kb, all Windows). The sourcecode is included.
Download this utility now (14kb, LINUX). The sourcecode is included.

The MZ-80B is not supported, because your MZ-80B reads or writes using 1800
bauds (MZ-80K, MZ-80A, MZ-700, and MZ-800, and some other Japanese types of
MZs, all use 1200 baud).

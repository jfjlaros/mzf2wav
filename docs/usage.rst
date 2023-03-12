Usage
=====

The following command converts an MZF image named ``image.mzf`` to a WAV file
named ``image.wav``:

::

    mzf2wav image.mzf image.wav


Modes of operation
------------------

MZF2WAV supports different writing techniques that can shorten the loading
time considerably. Please see the tape_ data processing page for more
background information.

Conventional mode
~~~~~~~~~~~~~~~~~

In this mode, everything is done according to the Sharp MZ series
conventions. A long gap is 22000 pulses, a short gap is 11000 pulses. The
header and body are written twice to allow for errors. This mode can be
selected using the ``-c`` command line option.

Fast mode
~~~~~~~~~

In this mode, the long gap is 4000 pulses and the short gap is 5000 pulses.
Both the header and the MZF image body are written once. This is the default
mode.

Turbo mode
~~~~~~~~~~

In this mode, a turbo loader is written using fast sending mode, which
enables the MZ to operate at higher speeds. The MZF image is then sent using
fast sending mode, but now at a higher speed. This mode can be selected using
the ``-t`` command line option.


Speeds
------

Apart from increasing the pulse frequency, the waveforms themselves can be
altered in order to increase speed.

For conventional and fast mode, two predefined waveform configurations are
available that can be selected using the ``-n`` command line option.

For turbo mode, three predefined waveform configurations are available that
can be selected using the ``-s`` command line option. This option can be
combined with the ``-n`` option to also write the turbo loader at a higher
speed. For example:

::

    mzf2wav -t -n 1 -s 2 image.mzf image.wav


Pulse customisation
~~~~~~~~~~~~~~~~~~~

Next to the predefined waveform configurations, it is possible to make custom
waveform configurations using the ``-N`` (conventional and fast mode) and
``-S`` (turbo mode) options. For example:

::

    mzf2wav -t -N 480,494,260,264 -S 248,248,113,140 image.mzf image.wav

The pulse configuration consists of four comma separated values giving the
length of the long pulse up, long pulse down, short pulse up and short pulse
down times in microseconds.


Polarity
--------

The polarity can be inverted using the ``-p`` option.


Bit rate
--------

The bit rate is set using the ``-b`` option.


Related software
----------------

Please check out MZF2WAVGUI_, a graphical user interface for this project
(Windows only). There is also a nice tutorial_ on how to use this software to
directly connect to an MZ.


.. _MZF2WAVGUI: https://github.com/rickyelqasem/MZF2WAVGUI
.. _tutorial: https://www.youtube.com/watch?v=iwD3-5ENyE8
.. _tape: https://web.archive.org/web/20201127232159/https://original.sharpmz.org/mz-700/tapeproc.htm

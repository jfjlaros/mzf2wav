Usage
=====

The following command converts an MZF image named ``image.mzf`` to a WAV file
named ``image.wav``:

::

    mzf2wav image.mzf image.wav


Operation modes
---------------

Conventional sending mode
~~~~~~~~~~~~~~~~~~~~~~~~~

This is the safest (and slowest) way to transfer an image, everything is done
according to the Sharp MZ series conventions: A long gap is 22000 pulses, a
short gap is 11000 pulses. The header and body are transferred twice to allow
for errors.

Fast sending mode
~~~~~~~~~~~~~~~~~

This is the easiest way to transfer a file. In this mode the long gap (a tape
marker) is 4000 pulses and the short gap is 5000 pulses. Both the header and
the MZF image body are transferred once.

Turbo sending mode
~~~~~~~~~~~~~~~~~~

In this mode, the turbo loader is transferred using fast sending mode, this
turbo loader enables the MZ to operate at higher transfer speeds. The MZF
image is then sent using fast sending mode, but now at a higher speed.

The speed at which the turbo loader is transferred is controlled with the
``-i`` option, the speed at which the MZF image is sent is controlled with the
``-t`` option.


Speeds
------

Apart from increasing the pulse frequency, the waveforms themselves can be
altered in order to increase speed. The "fast waveform" was found by minimising
the high and the low states of the pulses independently.

At this time, five speeds are implemented:

- Speed 0: normal speed with normal waveforms.
- Speed 1: normal speed with fast waveforms.
- Speed 2: 2x speed with normal waveforms.
- Speed 3: 3x speed with normal waveforms.
- Speed 4: 3x speed with fast waveforms.

These speeds can be set for all operation modes, although some combinations may
not work. The most commonly used speeds are: speed 0 or 1 for initial speed
mode and speed 2 or higher for turbo speed mode.

If multiple images are transferred, using speed 3 or 4 with fast sending mode
may be preferred.

Corrections
~~~~~~~~~~~

Because the waveforms used by speeds 1 and 4 may not always work, two
correction factors for these speeds are implemented, controlled with the ``-1``
and ``-2`` options.


Polarity
--------

The polarity can be revered with the ``-p`` option.


Related software
----------------

Please check out MZF2WAVGUI_, a graphical user interface for this project
(Windows only). There is also a nice tutorial_ on how to use this software to
directly connect to an MZ.


.. _operation modes: https://github.com/jfjlaros/mzput#operation-modes
.. _MZF2WAVGUI: https://github.com/rickyelqasem/MZF2WAVGUI
.. _tutorial: https://www.youtube.com/watch?v=iwD3-5ENyE8

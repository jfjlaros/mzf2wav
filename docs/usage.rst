Usage
=====

.. figure:: ../doc/mzf2wavs1.gif
   :alt: The help screen of MZF2WAV

   The help screen of MZF2WAV

To convert an MZF image named ``image.mzf`` to a WAV file named ``image.wav``,
run the following command:

::

    mzf2wav image.mzf image.wav

The program recognises the following options:

+----------+-----------------------------------------------------------+
| option   | description                                               |
+==========+===========================================================+
| ``-i``   | sets initial speed mode (0, 1, 2, 3 or 4), default = 0.   |
+----------+-----------------------------------------------------------+
| ``-t``   | sets turbo speed mode (0, 1, 2, 3 or 4), default = 2.     |
+----------+-----------------------------------------------------------+
| ``-1``   | sets correction for fast initial mode (-50 to 50).        |
+----------+-----------------------------------------------------------+
| ``-2``   | sets correction for fast turbo mode (-50 to 50).          |
+----------+-----------------------------------------------------------+
| ``-b``   | sets bit rate.                                            |
+----------+-----------------------------------------------------------+
| ``-c``   | sets conventional writing mode.                           |
+----------+-----------------------------------------------------------+
| ``-s``   | sets fast writing mode (default).                         |
+----------+-----------------------------------------------------------+
| ``-w``   | sets turbo writing mode.                                  |
+----------+-----------------------------------------------------------+
| ``-p``   | reverse polarity.                                         |
+----------+-----------------------------------------------------------+

For a full explanation of the different modes of operation, see the section
`operation modes`_ of the MZPut documentation.


Related software
----------------

Please check out MZF2WAVGUI_, a graphical user interface for this project
(Windows only). There is also a nice tutorial_ on how to use this software to
directly connect to an MZ.


.. _operation modes: https://github.com/jfjlaros/mzput#operation-modes
.. _MZF2WAVGUI: https://github.com/rickyelqasem/MZF2WAVGUI
.. _tutorial: https://www.youtube.com/watch?v=iwD3-5ENyE8

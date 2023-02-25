Installation
============

Binaries
--------

The latest binaries_ for modern systems can be found in the latest release on
GitHub.

There are old binaries for Linux_ and Windows_ available. After unzipping the
archive, the binary for Linux can be found in ``mzf2wav/src/linux/release``,
for Windows it can be found in ``mzf2wav\src\w32\release``.


From source
-----------

Retrieve the source code with Git.

::

    git clone https://github.com/jfjlaros/mzf2wav.git

To compile for Linux:

::

    cd mzf2wav/src/linux
    sh build.sh

For Windows, use:

::

    cd mzf2wav\src\w32
    build.bat

The binary will be placed in the ``release`` subdirectory.


.. _binaries: https://github.com/jfjlaros/mzf2wav/releases/latest
.. _Linux: https://web.archive.org/web/20170831235756/https://www.sharpmz.org/download/mzf2wav.zip
.. _Windows: https://web.archive.org/web/20170831235756/https://www.sharpmz.org/download/mzf2wav32.zip

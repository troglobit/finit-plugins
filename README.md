Finit Plugin Repository
=======================

This repository is for external plugins not part of mainline [Finit][].

> **Note:** contributions to this repo are expected to follow the coding
> style of 1) an existing plugin, or 2) coding style of Finit.  It is
> also expected that contributions are tested against the latest release
> of Finit, or current mainline.  Please describe your changes, or what
> a new plugin does (code is not self documenting) in the PR and also
> describe how you have verified the change or tested a new plugin.

Finit v4.4, and later, is required for these plugins.  Earlier versions
of Finit did not export all required header files.  Loading of external
plugins is supported as of Finit v4.4 from (in order) `/usr/lib/finit`
and `/usr/local/lib/finit`.  This in addition to the main search path
for native plugins (`/lib/finit`).


Build & Install
---------------

This assumes Finit header files are installed in `/usr/include/finit`.

    ./autogen.sh
    ./configure --prefix=/usr
    make
    sudo make install

The build system is based on GNU autotools so it honors the `DESTDIR`
environment variable.


Disclaimer
----------

All boiler-plate files, e.g., build system files, are copyright free and
in the public domain.  Each plugin, however, is copyright the respective
author(s), and they are all licensed under the same [MIT license][] as
[Finit][], due to runtime linking.

[Finit]:       https://github.com/troglobit/finit
[MIT license]: https://en.wikipedia.org/wiki/MIT_License

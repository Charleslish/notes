# zlib API headers

These are unmodified `zlib.h` and `zconf.h` from zlib v1.3.1:

- https://github.com/madler/zlib/blob/v1.3.1/zlib.h
- https://github.com/madler/zlib/blob/v1.3.1/zconf.h

The copyright and redistribution license are preserved in the headers.
The provided PNG implementation uses the system zlib runtime for compression,
decompression, and CRCs. These headers declare that API; no zlib implementation
or PNG library is bundled. The course container supplies `libz.so.1` but not its
development headers, so these files allow building without package installation.

Students do not modify or include these headers in their solution files.

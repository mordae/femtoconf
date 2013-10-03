#!/usr/bin/make -f

lib += libfemtoconf.so.0

libfemtoconf.so.0 = -Wl,-h,libfemtoconf.so.0 femtoconf.c

# EOF

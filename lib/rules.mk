#!/usr/bin/make -f

lib += libfconf.so.0

libfconf.so.0 = -Wl,-h,libfconf.so.0 fconf.c

# EOF

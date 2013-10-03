#!/usr/bin/make -f

tests = t-link t-load

$(foreach t,${tests},$(eval ${t} = ../libfconf.so ${t}.c cutest.h))
check += ${tests}

# EOF

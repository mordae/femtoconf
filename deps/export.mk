#!/usr/bin/make -f

dist:
	git clone .git ${package}-${version}
	rm -rf ${package}-${version}/.git
	tar -cvpzf ${package}-${version}.tar.gz ${package}-${version}
	rm -rf ${package}-${version}

# EOF

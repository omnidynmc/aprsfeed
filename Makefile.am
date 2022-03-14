EXTRA_DIST = include/*.h \
             include/openframe/*.h \
             etc/opentest.conf \
             libraries/openframe/include/openframe/*.h \
             libraries/openframe/src/*.cpp \
             libraries/openframe/src/Makefile.in \
             modules/*/*.h \
             modules/*/*.cpp \
             modules/*/Makefile.in \
             modules/Makefile.in

SUBDIRS = src modules

buildall:
	cd libraries/openframe && ./configure --disable-mysql && make install
	cd libraries/openstats && ./configure && make install
	cd libraries/stomp && ./configure && make install
	make install

makeall:
	cd libraries/openframe && make install
	cd libraries/openstats && make install
	cd libraries/stomp && make install
	make install

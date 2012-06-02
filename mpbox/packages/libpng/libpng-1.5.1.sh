#!/bin/sh

libpng-1.5.1_perform() {
	tar xvf ${MP_SOURCE_PATH}/libpng-1.5.1.tar.bz2
	cd libpng-1.5.1
	./configure --prefix=/usr --target=${MP_TC_TARGET_TRI} --host=${MP_TC_TARGET_TRI}
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
	
}

#!/bin/bash

zlib-1.2.5_perform() {
	tar xvf ${MP_SOURCE_PATH}/zlib-1.2.5.tar.bz2
	cd zlib-1.2.5
	CC="${MP_TC_TARGET_TRI}-gcc" ./configure --prefix=/usr
	CC="${MP_TC_TARGET_TRI}-gcc" make
	CC="${MP_TC_TARGET_TRI}-gcc" make DESTDIR=${MP_TMP_INSTALL_PATH} install
	mkdir ${MP_TMP_INSTALL_PATH}/lib
	mv -v ${MP_TMP_INSTALL_PATH}/usr/lib/libz.so* ${MP_TMP_INSTALL_PATH}/lib
	ln -sfv /lib/libz.so.1.2.5 ${MP_TMP_INSTALL_PATH}/usr/lib/libz.so
}

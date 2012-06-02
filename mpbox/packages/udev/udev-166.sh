#!/bin/bash

udev-166_perform() {
	tar xvf ${MP_SOURCE_PATH}/udev-166.tar.bz2
	cd udev-166
	./configure --prefix=/usr --target=${MP_TC_TARGET_TRI} --host=${MP_TC_TARGET_TRI} --sysconfdir=/etc --sbindir=/sbin --with-rootlibdir=/lib --libexecdir=/lib/udev --disable-extras --disable-introspection
	make 
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}

#! /bin/bash

mpfr-3.0.0_perform() {
	tar xvf /source/mpfr-3.0.0.tar.bz2 -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/mpfr-3.0.0
	./configure --prefix=/usr --enable-shared --target=${MP_TC_TARGET_TRI} --host=${MP_TC_TARGET_TRI} --build=${MP_TC_HOST_TRI} --with-gmp=${MP_PATH}/targets/current/rootfs/
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}

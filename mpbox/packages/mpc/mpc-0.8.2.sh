#!/bin/bash

mpc-0.8.2_perform() {
	tar xvf /source/mpc-0.8.2.tar.gz -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/mpc-0.8.2
	LDFLAGS="-Wl,-rpath,${MP_TC_SYSROOT_PATH}/usr/lib" ./configure --prefix=/usr --enable-shared --target=${MP_TC_TARGET_TRI} --with-gmp=${MP_TC_SYSROOT_PATH}/usr --with-mpfr=${MP_TC_SYSROOT_PATH}/usr/
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install

}

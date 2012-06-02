#! /bin/bash

gmp-5.0.1_perform() {
	tar xvf /source/gmp-5.0.1.tar.bz2 -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/gmp-5.0.1
	CPPFLAGS="-fexceptions" ./configure --prefix=/usr --target=${MP_TC_TARGET_TRI} --enable-shared --enable-cxx --host=${MP_TC_TARGET_TRI} --build=${MP_TC_HOST_TRI}
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}


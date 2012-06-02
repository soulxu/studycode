#! /bin/bash

tc-gmp-5.0.1_1_perform() {
	tar xvf /source/gmp-5.0.1.tar.bz2 -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/gmp-5.0.1
	CPPFLAGS="-fexceptions" ./configure --prefix=${MP_TC_INSTALL_PATH} --disable-shared --enable-cxx
	make
	make install
}


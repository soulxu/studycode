#! /bin/bash

tc-mpfr-3.0.0_1_perform() {
	tar xvf /source/mpfr-3.0.0.tar.bz2 -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/mpfr-3.0.0
	LDFLAGS="-Wl,-rpath,${MP_TC_INSTALL_PATH}/lib" ./configure --prefix=${MP_TC_INSTALL_PATH} --with-gmp=${MP_TC_INSTALL_PATH} --disable-shared
	make
	make install
}

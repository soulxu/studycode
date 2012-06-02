#!/bin/bash

tc-mpc-0.8.2_1_perform() {
	tar xvf /source/mpc-0.8.2.tar.gz -C ${MP_BUILD_PATH}
	cd ${MP_BUILD_PATH}/mpc-0.8.2
	LDFLAGS="-Wl,-rpath,${MP_TC_INSTALL_PATH}/lib" ./configure --prefix=${MP_TC_INSTALL_PATH} --with-gmp=${MP_TC_INSTALL_PATH} --with-mpfr=${MP_TC_INSTALL_PATH} --disable-shared
	make
	make install

}

#!/bin/bash

tc-gcc-4.5.2_1_perform() {
	tar xvf /source/gcc-4.5.2.tar.bz2 -C ${MP_BUILD_PATH}
	mkdir ${MP_BUILD_PATH}/gcc-build
	cd ${MP_BUILD_PATH}/gcc-build

	# can not use --with-abi= it's doesn't work. i don't know why

	../gcc-4.5.2/configure --prefix=${MP_TC_INSTALL_PATH} --target=${MP_TC_TARGET_TRI} --enable-languages=c,c++ --with-sysroot=${MP_TC_SYSROOT_PATH} --enable-shared --enable-c99 --enable-long-long --with-mpfr=${MP_TC_INSTALL_PATH} --with-gmp=${MP_TC_INSTALL_PATH} --with-mpc=${MP_TC_INSTALL_PATH} --disable-multilib --disable-nls --enable-threads=posix --enable-__cxa_atexit --with-local-prefix=${MP_TC_SYSROOT_PATH} ${MP_TC_GCC_CPU_PARAM}

	make
	make install
}

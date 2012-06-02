#! /bin/bash

gcc-4.5.2_perform() {
	tar xvf ${MP_SOURCE_PATH}/gcc-4.5.2.tar.bz2
	mkdir gcc-build
	cd gcc-build
	../gcc-4.5.2/configure --prefix=/usr --libexecdir=/usr/lib --build=${MP_TC_HOST_TRI} --host=${MP_TC_HOST_TRI} --target=${MP_TC_TARGET_TRI} --enable-languages=c,c++ --with-sysroot=${MP_TC_SYSROOT_PATH} --enable-shared --enable-c99 --enable-long-long --with-mpfr=${MP_TC_INSTALL_PATH} --with-gmp=${MP_TC_INSTALL_PATH} --with-mpc=${MP_TC_INSTALL_PATH} --disable-multilib --disable-nls --enable-threads=posix --enable-__cxa_atexit --with-local-prefix=${SYSROOT_DIR} ${MP_TC_GCC_CPU_PARAM}
	make 
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}

#! /bin/bash

tc-static-gcc-4.5.2_1_perform() {
	tar xvf /source/gcc-4.5.2.tar.bz2 -C ${MP_BUILD_PATH}
	mkdir ${MP_BUILD_PATH}/gcc-build
	cd ${MP_BUILD_PATH}/gcc-build

# --enable-shared can generate libgcc_eh, glibc needs libgcc_eh
# --without-headers , gcc will not use include file from sysroot. if set --with-headers=xxx, we must install glibc headers, libgcc need the headers

	AR=ar LDFLAGS="-Wl,-rpath,${MP_TC_INSTALL_DIR}/lib" ../gcc-4.5.2/configure --prefix=${MP_TC_INSTALL_PATH} --build=${MP_TC_HOST_TRI} --host=${MP_TC_HOST_TRI} --target=${MP_TC_TARGET_TRI} --with-sysroot=${MP_TC_SYSROOT_PATH} --disable-nls --disable-shared --with-mpfr=${MP_TC_INSTALL_PATH} --with-gmp=${MP_TC_INSTALL_PATH} --with-mpc=${MP_TC_INSTALL_PATH} --with-newlib --disable-threads --enable-languages=c --without-headers --disable-libmudflap --disable-threads --disable-libssp --disable-libgomp --disable-multilib --with-local-prefix=${MP_TC_SYSROOT_PATH} ${MP_TC_GCC_CPU_PARAM}

	make all-gcc 
	make all-target-libgcc
	make install 

}

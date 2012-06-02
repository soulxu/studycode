#!/bin/bash

tc-binutils-2.21_1_perform() {
	tar xvf ${MP_SOURCE_PATH}/binutils-2.21.tar.bz2 -C ${MP_BUILD_PATH}
	mkdir ${MP_BUILD_PATH}/binutils-build
	cd ${MP_BUILD_PATH}/binutils-build
	../binutils-2.21/configure --prefix=${MP_TC_INSTALL_PATH} --target=${MP_TC_TARGET_TRI} --with-sysroot=${MP_TC_SYSROOT_PATH} --disable-nls --enable-shared --disable-multilib
	make configure-host
	make
	make install
	cp ${MP_BUILD_PATH}/binutils-2.21/include/libiberty.h ${MP_TC_SYSROOT_PATH}/usr/include
}

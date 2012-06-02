#!/bin/bash

tc-linux-header-2.6.36_1_perform() {
	tar xvf ${MP_SOURCE_PATH}/linux-2.6.36-20110112.tar.gz
	cd linux-2.6.36
	make mrproper
	cp config_mini6410_n43 .config
	make ARCH=${MP_TC_CPU_ARCH} headers_check
	make ARCH=${MP_TC_CPU_ARCH} INSTALL_HDR_PATH=${MP_TMP_INSTALL_PATH} headers_install
	mkdir -p ${MP_TC_SYSROOT_PATH}/usr/
	cp -rv ${MP_TMP_INSTALL_PATH}/* ${MP_TC_SYSROOT_PATH}/usr/
}

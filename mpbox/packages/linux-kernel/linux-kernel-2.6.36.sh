#!/bin/bash

linux-kernel-2.6.36_perform() {
	tar xvf ${MP_SOURCE_PATH}/linux-2.6.36-20110112.tar.gz
	cd linux-2.6.36
	make mrproper
	cp config_mini6410_n43 .config
	make -j5 ARCH=${MP_TC_CPU_ARCH} CROSS_COMPILE="${MP_TC_TARGET_TRI}-"
	make ARCH=${MP_TC_CPU_ARCH} CROSS_COMPILE="${MP_TC_TARGET_TRI}-" INSTALL_MOD_PATH=${MP_TMP_INSTALL_PATH} modules_install
	make ARCH=${MP_TC_CPU_ARCH} CROSS_COMPILE="${MP_TC_TARGET_TRI}-" INSTALL_HDR_PATH=${MP_TMP_INSTALL_PATH}/usr headers_install
	if [ ! -d ${MP_TMP_INSTALL_PATH}/boot/ ]; then
		mkdir ${MP_TMP_INSTALL_PATH}/boot/
	fi
	cp arch/arm/boot/zImage ${MP_TMP_INSTALL_PATH}/boot/bzImage
}

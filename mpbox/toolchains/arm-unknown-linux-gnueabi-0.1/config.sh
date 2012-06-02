MP_TC_NAME=arm-unknown-linux-gnueabi-0.1
# global
MP_TC_HOST_TRI="${MACHTYPE}"
MP_TC_BUILD_TRI="${MACHTYPE}"
MP_TC_TARGET_TRI="arm-unknown-linux-gnueabi"
MP_TC_CPU_ARCH="arm"
MP_TC_INSTALL_PATH=/opt/${MP_TC_TARGET_TRI}
MP_TC_SYSROOT_PATH=${MP_TC_INSTALL_PATH}/${MP_TC_TARGET_TRI}/sysroot
MP_TC_GCC_CPU_PARAM=""
#MP_TC_GCC_CPU_PARAM="--with-float=softfp --with-fpu=vfp --with-cpu=arm1176jzf-s --with-tune=arm1176jzf-s"

ARM_ARCH="armv6"

#package list
MP_BUILD_PACKAGES "tc-linux-header" "2.6.36_1"
MP_BUILD_PACKAGES "tc-binutils" "2.21_1"
MP_BUILD_PACKAGES "tc-gmp" "5.0.1_1"
MP_BUILD_PACKAGES "tc-mpfr" "3.0.0_1"
MP_BUILD_PACKAGES "tc-mpc" "0.8.2_1"
MP_BUILD_PACKAGES "tc-static-gcc" "4.5.2_1"
MP_BUILD_PACKAGES "tc-glibc" "2.13_1"
MP_BUILD_PACKAGES "tc-gcc" "4.5.2_1"



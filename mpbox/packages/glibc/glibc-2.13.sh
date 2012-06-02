#!/bin/bash

glibc-2.13_perform() {
  tar xvf /source/glibc-2.13.tar.bz2 -C ${MP_BUILD_PATH}
  tar xvf /source/glibc-ports-2.13.tar.bz2 -C ${MP_BUILD_PATH}/glibc-2.13

  cd ${MP_BUILD_PATH}/glibc-2.13

  mkdir ${MP_BUILD_PATH}/glibc-build
  cd ${MP_BUILD_PATH}/glibc-build

  echo "libc_cv_forced_unwind=yes" > config.cache
  echo "libc_cv_c_cleanup=yes" >> config.cache
  echo "libc_cv_cc_with_libgcc_eh=no" >> config.cache


  AS=${MP_TC_TARGET_TRI}-as LD=${MP_TC_TARGET_TRI}-ld CC=${MP_TC_TARGET_TRI}-gcc AR=${MP_TC_TARGET_TRI}-ar RANLIB=${MP_TC_TARGET_TRI}-ranlib CFLAGS="-g -O2" ../glibc-2.13/configure --prefix=/usr --host=${MP_TC_TARGET_TRI} --build=${MP_TC_HOST_TRI} --target=${MP_TC_TARGET_TRI} --disable-profile --enable-add-ons --enable-kernel=2.6.0 --with-binutils=${MP_TC_INSTALL_PATH}/bin --with-headers=${MP_TC_SYSROOT_PATH}/usr/include --cache-file=config.cache

  make -j4
  make install_root=${MP_TMP_INSTALL_PATH} install

}

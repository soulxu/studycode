#!/bin/bash

busybox-1.18.4_perform() {
	tar xvf ${MP_SOURCE_PATH}/busybox-1.18.4.tar.bz2
	cd busybox-1.18.4
	cp ${PKG_PATH}/config-1.18.4 ./.config
	make ARCH=${MP_TC_CPU_ARCH} CROSS_COMPILE="${MP_TC_TARGET_TRI}-" install

	cd _install
	for f in $(find .); do
		if [ "$f" == "." -o "$f" == ".." -o -d $f ]; then
			continue
		fi
		install -D $f ${MP_TMP_INSTALL_PATH}/$f
	done
	cd -
}

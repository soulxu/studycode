#! /bin/sh

tslib-1.4_perform() {
	tar xvf ${MP_SOURCE_PATH}/tslib-1.4.tar.gz
	cd tslib-1.4
	./autogen.sh || echo "aa"
	./configure --prefix=/usr --host=${MP_TC_TARGET_TRI} --target=${MP_TC_TARGET_TRI}
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}

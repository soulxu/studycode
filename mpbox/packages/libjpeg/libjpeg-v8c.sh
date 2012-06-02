#!/bin/bash

libjpeg-v8c_perform() {
	tar xvf ${MP_SOURCE_PATH}/jpegsrc.v8c.tar.gz
	cd jpeg-8c
	./configure --prefix=/usr --target=${MP_TC_TARGET_TRI} --host=${MP_TC_TARGET_TRI}
	make
	make DESTDIR=${MP_TMP_INSTALL_PATH} install
}

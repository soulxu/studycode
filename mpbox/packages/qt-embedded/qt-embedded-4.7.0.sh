#! /bin/sh

qt-embedded-4.7.0_perform() {
	tar xvf ${MP_SOURCE_PATH}/qt-everywhere-opensource-src-4.7.0.tar.gz
	cd qt-everywhere-opensource-src-4.7.0
	cp ${PKG_PATH}/linux-arm-unknown-gnueabi-g++ ./mkspecs/qws/ -a
	./configure -embedded arm -xplatform qws/linux-arm-unknown-gnueabi-g++ -system-zlib -system-libpng -system-libjpeg -no-phonon-backend -no-phonon -no-multimedia -opensource -little-endian -prefix "/usr/share/Trolltech/Qt-4.7.0" -libdir "/usr/lib" -headerdir "/usr/include" -bindir "/usr/bin" -sysconfdir "/etc"
	make -j4
	make INSTALL_ROOT=${MP_TMP_INSTALL_PATH} install
}

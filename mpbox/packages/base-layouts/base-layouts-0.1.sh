#!/bin/bash

base-layouts-0.1_perform() {
	mkdir -p ${MP_TMP_INSTALL_PATH}/dev
	mknod -m 0600 ${MP_TMP_INSTALL_PATH}/dev/console c 5 1
	mknod ${MP_TMP_INSTALL_PATH}/dev/null c 1 3
	mkdir -p ${MP_TMP_INSTALL_PATH}/sys
	mkdir -p ${MP_TMP_INSTALL_PATH}/proc
	mkdir -p ${MP_TMP_INSTALL_PATH}/var/run
	mkdir -p ${MP_TMP_INSTALL_PATH}/tmp
	for i in $(echo 0 1 2 3 4 5 6 7 8); do
		mknod ${MP_TMP_INSTALL_PATH}/dev/tty${i} c 4 $i
	done
}

#! /bin/bash
set -ex

. /etc/mpbox.conf

. ${MP_PATH}/profiles/global_config.sh

#. ${MP_PATH}/bin/gvar.sh

#. ${MP_PATH/bin/utils.sh


help() {
	echo "toolchains-build [name]"
}

path_santiy_check() {
	p=${1}

	if [ ${p} == "/" -o ${p} == "" ]; then
		echo "Danger Path: ${p}"
		exit
	fi
}

# import toolchain config
TOOLCHAIN_PATH=${1}
TOOLCHAIN_BUILD_PKG=${2}

if [ ${TOOLCHAIN_PATH} != "" ]; then
	. ${MP_PATH}/toolchains/${TOOLCHAIN_PATH}/config.sh
else
	help
	exit
fi

if [ ! -d ${MP_BUILD_PATH} ]; then
	mkdir -p ${MP_BUILD_PATH}
else
	path_santiy_check ${MP_BUILD_PATH}
	d=`ls ${MP_BUILD_PATH}`
	if [ "$d" != "" ]; then
		rm ${MP_BUILD_PATH}/* -r
	fi
fi

if [ ! -d ${MP_TMP_INSTALL_PATH} ]; then
	mkdir -p ${MP_TMP_INSTALL_PATH}
else
	path_santiy_check ${MP_TMP_INSTALL_PATH}
	d=`ls ${MP_TMP_INSTALL_PATH}`
	if [ "$d" != "" ]; then
		rm ${MP_TMP_INSTALL_PATH}/* -r
	fi
fi

if [ ! -d ${MP_TC_INSTALL_PATH} ]; then
	mkdir -p ${MP_TC_INSTALL_PATH}
fi

if [ ! -d ${MP_TC_SYSROOT_PATH} ]; then
	mkdir -p ${MP_TC_SYSROOT_PATH}
fi

cd ${MP_BUILD_PATH}

PATH=${PATH}:${MP_TC_INSTALL_PATH}/bin:${MP_TC_INSTALL_PATH}/${MP_TC_TARGET_TRI}/bin

for pkg in ${MP_TC_PACKAGES}; do
	if [ "${TOOLCHAIN_BUILD_PKG}" != "" ]; then
		if [ "${TOOLCHAIN_BUILD_PKG}" != "${pkg}" ]; then
			continue
		fi
	fi

	. ${MP_PATH}/toolchains/${TOOLCHAIN_PATH}/${pkg}.sh
	echo "Start building package: ${pkg}"
	${pkg}_perform
	
	path_santiy_check ${MP_BUILD_PATH}
	rm ${MP_BUILD_PATH}/* -r
	cd ${MP_BUILD_PATH}
done



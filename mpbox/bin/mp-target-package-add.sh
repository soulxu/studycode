#! /bin/bash
set -ex

# mpbox install path
if [ ! -f /etc/mpbox.conf ]; then
	echo "Can not find mpbox.conf."
	exit
fi

. /etc/mpbox.conf

if [ "${MP_PATH}" == "" ]; then
	echo "Undefine mpbox path."
	exit
fi

# mpbox global config
. ${MP_PATH}/profiles/global_config.sh

# mpbox global variable
. ${MP_PATH}/bin/gvar.sh

# mpbox some functions
. ${MP_PATH}/bin/utils.sh

help() {
	echo "toolchains-build [name]"
}

# check the directory is not root or current
path_santiy_check() {
	p=${1}

	if [ ${p} == "/" -o ${p} == "" ]; then
		echo "Danger Path: ${p}"
		exit
	fi
}

if [ ! -L ${MP_PATH}/targets/current ]; then
	echo "Current target didn't exist."
	exit
fi

if [ -f ${MP_PATH}/targets/current/profile/config.sh ]; then
        . ${MP_PATH}/targets/current/profile/config.sh
else
        echo "The profile of current target didn't exist."
        exit
fi

if [ -f ${MP_PATH}/targets/current/toolchain/config.sh ]; then
	. ${MP_PATH}/targets/current/toolchain/config.sh
else
	echo "The toolchain of current target didn't exist."
	exit
fi

if [ ! -d ${MP_BUILD_PATH} ]; then
	mkdir -p ${MP_BUILD_PATH}
else
	path_santiy_check ${MP_BUILD_PATH}
	rm ${MP_BUILD_PATH}/ -r
	mkdir -p ${MP_BUILD_PATH}
fi

cd ${MP_BUILD_PATH}

if [ ! -d ${MP_TMP_INSTALL_PATH} ]; then
	mkdir -p ${MP_TMP_INSTALL_PATH}
else
	path_santiy_check ${MP_TMP_INSTALL_PATH}
	rm ${MP_TMP_INSTALL_PATH}/ -r
	mkdir -p ${MP_TMP_INSTALL_PATH}
fi

PATH=${PATH}:${MP_TC_INSTALL_PATH}/bin:${MP_TC_INSTALL_PATH}/${MP_TC_TARGET_TRI}/bin

tc_build_pkg=${1}

if [ "${tc_build_pkg}" == "" ]; then
	help
	exit
fi

for pkg in ${MP_BUILD_PKGS}; do
	if [ "${tc_build_pkg}" != "" ]; then
		if [ "${tc_build_pkg}" != "${pkg%-*}" ]; then
			continue
		fi
	fi

	PKG_PATH="${MP_PATH}/packages/${pkg%-*}/"
	. ${MP_PATH}/packages/${pkg%-*}/${pkg}.sh
	echo "Start building package: ${pkg}"
	${pkg}_perform

	if [ -f ${MP_PATH}/packages/${pkg%-*}/${pkg}.files ]; then
		for f in $(cat ${MP_PATH}/packages/${pkg%-*}/${pkg}.files); do
			install -D {MP_TMP_INSTALL_PATH}/$f ${MP_PATH}/targets/current/rootfs/
		done
	else 	
		mkdir -p ${MP_PATH}/targets/current/installed/${pkg%-*}
        	cd ${MP_TMP_INSTALL_PATH}
		find . > ${MP_PATH}/targets/current/installed/${pkg%-*}/content
		cd -
		cp -a ${MP_TMP_INSTALL_PATH}/* ${MP_PATH}/targets/current/rootfs/
	fi

	path_santiy_check ${MP_BUILD_PATH}
	rm ${MP_BUILD_PATH} -r
	mkdir ${MP_BUILD_PATH}
	path_santiy_check ${MP_TMP_INSTALL_PATH}
	rm ${MP_TMP_INSTALL_PATH} -r
	mkdir ${MP_TMP_INSTALL_PATH}
done

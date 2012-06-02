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
fi

PATH=${PATH}:${MP_TC_INSTALL_PATH}/bin:${MP_TC_INSTALL_PATH}/${MP_TC_TARGET_TRI}/bin

tc_build_pkg=${1}

if [ "${tc_build_pkg}" == "" ]; then
	help
	exit
fi

for f in $(cat ${MP_PATH}/targets/current/installed/${tc_build_pkg}/content); do
	if [ -f ${MP_PATH}/targets/current/rootfs/${f} -o -L ${MP_PATH}/targets/current/rootfs/${f} ]; then
		rm ${MP_PATH}/targets/current/rootfs/${f}
		echo "Remove ${MP_PATH}/targets/current/rootfs/${f}"
	fi
done


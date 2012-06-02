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

# import toolchain config
tc_name=${1}

# used to compile only one pkg
tc_build_pkg=${2}

if [ "$tc_build_pkg" == "" ]; then
	if [ -d ${MP_PATH}/toolchains/installed/${tc_name} ]; then
		echo "toolchain: ${tc_name} has already installed."
		exit
	fi
fi

# read toolchain config
if [ ${tc_name} != "" ]; then
	. ${MP_PATH}/toolchains/${tc_name}/config.sh
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

for pkg in ${MP_BUILD_PKGS}; do
	if [ "${tc_build_pkg}" != "" ]; then
		if [ "${tc_build_pkg}" != "${pkg%-*}" ]; then
			continue
		fi
	fi

	. ${MP_PATH}/packages/${pkg%-*}/${pkg}.sh
	echo "Start building package: ${pkg}"
	${pkg}_perform
	
	path_santiy_check ${MP_BUILD_PATH}
	rm ${MP_BUILD_PATH}/* -r
	cd ${MP_BUILD_PATH}
done

tc_installed_path= ${MP_PATH}/toolchains/installed
if [ ! -d ${tc_installed_path} ]; then
	mkdir -p  ${tc_installed_path}
fi

mkdir ${tc_installed_path}/${tc_name}


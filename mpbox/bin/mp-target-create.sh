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

tg_name=${1}
tg_profile=${2}

if [ "$tg_name" == "" -o "$tg_profile" == "" ]; then
	help
	exit
fi

if [ ! -f ${MP_PATH}/profiles/${tg_profile}/config.sh ]; then
	echo "Profiles didn't exist: ${MP_PATH}/profiles/${tg_profile}/config.sh ."
	exit
fi

. ${MP_PATH}/profiles/${tg_profile}/config.sh

if [ -d ${MP_PATH}/targets/${tg_name} ]; then
	echo "Target has already existed."
	exit
fi


mkdir -p ${MP_PATH}/targets/${tg_name}

if [ -L ${MP_PATH}/targets/current ]; then
	rm ${MP_PATH}/targets/current
fi

# link current targets.
ln -sf ${MP_PATH}/targets/${tg_name} ${MP_PATH}/targets/current
# link the profile of current target to current directory.
ln -sf ${MP_PATH}/profiles/${tg_profile} ${MP_PATH}/targets/current/profile

mkdir -p ${MP_PATH}/targets/${tg_name}/rootfs

if [ ! -f ${MP_PATH}/toolchains/${MP_PROFILE_TOOLCHAIN}/config.sh ]; then
	echo "toolchain didn't exist : ${MP_PATH}/toolchains/${MP_PROFILE_TOOLCHAIN}/config.sh ."
	exit
fi

. ${MP_PATH}/toolchains/${MP_PROFILE_TOOLCHAIN}/config.sh

# link target rootfs to toolchain's sysroot path
if [ -f ${MP_TC_SYSROOT_PATH} ]; then
	rm ${MP_TC_SYSROOT_PATH} -r
fi
ln -sf ${MP_PATH}/targets/${tg_name}/rootfs ${MP_TC_SYSROOT_PATH}

# link toolchain's profile to current target.
ln -sf ${MP_PATH}/toolchains/${MP_PROFILE_TOOLCHAIN} ${MP_PATH}/targets/current/toolchain




MP_BUILD_PACKAGES() {
	name=${1}
	version=${2}
	MP_BUILD_PKGS+="${name}-${version} "
}

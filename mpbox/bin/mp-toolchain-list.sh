#!/bin/bash
if [ ! -f /etc/mpbox.conf ]; then
	echo "Can not find mpbox.conf"
	exit
fi 

. /etc/mpbox.conf

if [ "${MP_PATH}" == "" ]; then
	echo "Undefined mpbox path"
	exit
fi

tc=`ls ${MP_PATH}/toolchains`

if [ -d ${MP_PATH}/toolchains/installed ]; then
	installed=`ls ${MP_PATH}/toolchains/installed`
fi

it=""

for t in $tc; do
	if [ "$t" == "installed" ]; then
		continue;
	fi

	it=`echo ${installed} | grep ${t}`	
	if [ "${it}" == "${t}" ]; then
		it="(installed)"
	else
		it=""
	fi

	echo "$t $it"
done

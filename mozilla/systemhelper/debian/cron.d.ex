#
# Regular cron jobs for the systemhelper package
#
0 4	* * *	root	[ -x /usr/bin/systemhelper_maintenance ] && /usr/bin/systemhelper_maintenance

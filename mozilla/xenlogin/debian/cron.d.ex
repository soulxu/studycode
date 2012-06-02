#
# Regular cron jobs for the xenlogin package
#
0 4	* * *	root	[ -x /usr/bin/xenlogin_maintenance ] && /usr/bin/xenlogin_maintenance

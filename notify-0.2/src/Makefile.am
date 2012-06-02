AM_CFLAGS = `pkg-config --cflags glib-2.0`
AM_LDFLAGS = `pkg-config --libs glib-2.0`
bin_PROGRAMS = notifyfs
notifyfs_SOURCES = notifyfs.c notifyfs.h
notifyfs_LDADD = libnotify.a
noinst_LIBRARIES = libnotify.a
lib_LIBRARIES = libnotify.a
libnotify_a_SOURCES = notify.c notify.h



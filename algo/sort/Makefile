CFLAGS+=-g -Wall

SUBDIR=sortplugin

.PHONY:all subdir cleansub

all: sort subdir

subdir:
	LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)" make -C $(SUBDIR)

sort: subdir main.c
	$(CC) main.c -I./sortplugin -lsort -L./sortplugin -o sort $(CFLAGS) $(LDFLAGS)


cleansub:
	$(MAKE) -C $(SUBDIR) clean

clean: cleansub
	rm *.o sort

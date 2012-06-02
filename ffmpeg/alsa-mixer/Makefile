all:mixer

CFLAGS += -I/usr/include/alsa/

mixer:main.o
	$(CC) -o mixer main.o -lasound

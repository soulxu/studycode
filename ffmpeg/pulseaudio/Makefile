LDFLAGS+= -lavformat -lavcodec -lpulse -lpulse-simple

all: mp3player

mp3player: main.o
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm *.o mp3player

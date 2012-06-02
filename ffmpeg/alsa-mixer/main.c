
#include <stdio.h>
/*
#include <global.h>
#include <control.h>
#include <conf.h>
#include <mixer.h>
*/
#include <asoundlib.h>

int main(int argc, char **argv) {
	snd_mixer_t *mixer;
	snd_mixer_elem_t *elem;

	int result = 0;

	if ((result = snd_mixer_open(&mixer, 0)) < 0) {
		perror("can not open mixer:");
		return -1;
	}

	if ((result = snd_mixer_attach(mixer, "default")) < 0) {
		perror("snd mixer attach error");
		snd_mixer_close(mixer);
		return -2;
	}

	if ((result = snd_mixer_selem_register(mixer, NULL, NULL)) < 0) {
		perror("reigster mixer error");
		snd_mixer_close(mixer);
		return -3;
	}

	if ((result = snd_mixer_load(mixer)) < 0) {
		perror("mixer load error:");
		snd_mixer_close(mixer);
		return -4;
	}

	for (elem = snd_mixer_first_elem(mixer); elem; elem = snd_mixer_elem_next(elem)) {
		if ((snd_mixer_elem_get_type(elem) == SND_MIXER_ELEM_SIMPLE) && (snd_mixer_selem_is_active(elem))) {
			printf("mixer elem: %s\n", snd_mixer_selem_get_name(elem));

			if (strcmp(snd_mixer_selem_get_name(elem), "Master") == 0) {
				snd_mixer_selem_set_playback_volume_range(elem, 0, 100);
				snd_mixer_selem_set_playback_volume_all(elem, 100);
			}
		}
	}

	snd_mixer_close(mixer);

	return 0;
}

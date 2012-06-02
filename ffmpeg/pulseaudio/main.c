#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <dirent.h>
#include <getopt.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

int iter_dir(char ***files, char *dirname) {
	DIR *dir = opendir(dirname);

	if (dir == NULL) {
		perror("can not open input directory.");
		return;
	}

	struct dirent *ent = NULL;
	int count = 0;

	while ((ent = readdir(dir)) != NULL) {
		if (strcmp(ent->d_name, ".") == 0) {
			continue;
		}

		if (strcmp(ent->d_name, "..") == 0) {
			continue;
		}

		count++;		
	}

	closedir(dir);
	*files = (char **)malloc(sizeof(char **) * count);

	dir = opendir(dirname);
	count = 0;

	while ((ent = readdir(dir)) != NULL) {
		if (strcmp(ent->d_name, ".") == 0) {
			continue;
		}

		if (strcmp(ent->d_name, "..") == 0) {
			continue;
		}

		(*files)[count] = (char *)malloc(strlen(ent->d_name) + 1);
		memset((*files)[count], 0, strlen(ent->d_name) + 1);
		strcpy((*files)[count], ent->d_name);
		count++;
	}

	return count;
}

int main(int argc, char **argv) {
	AVFormatContext *formatCtx = NULL;
	AVCodecContext *codecCtx = NULL;
	AVCodec *codec = NULL;
	AVPacket packet;

	uint8_t sample_buf[AVCODEC_MAX_AUDIO_FRAME_SIZE] = {0};
	int buf_size = sizeof(sample_buf);
	int decodec_size = 0;
	int len = 0;
	char **input_files = NULL;
	int opt = 0;
	int count = 0;
	int i = 0;

	int error = 0;
	pa_simple *ps = NULL;	
	pa_sample_spec pss= {0};

	while ((opt = getopt(argc, argv, "d:i:")) != -1) {
		switch (opt) {
		case 'd':
			count = iter_dir(&input_files, optarg);
			chdir(optarg);
			break;
		case 'i':
			input_files = (char **)malloc(sizeof(char **));
			input_files[0] = (char *)malloc(strlen(optarg) + 1);
			memset(input_files[0], 0, strlen(optarg + 1));
			strcpy(input_files[0], optarg);
			count = 1;
			break;
		default:
			printf("mp3player usage:\n"
				"\t-d [directory] set input directory\n"
				"\t-i [file] set input file\n");
			return -1;
		}
	}

	av_register_all();
	
	for (i = 0; i < count; i++) {
	    printf("play audio file: %s\n", input_files[i]);
	    if (av_open_input_file(&formatCtx, 
		    input_files[i], 
		    NULL, 
		    0, 
		    NULL) != 0) 
	    {
		    fprintf(stderr, "can not open input file.\n");
		    return -1;
	    }

	    if (av_find_stream_info(formatCtx) < 0) {
		    fprintf(stderr, "can not find stream info.\n");
		    return -1;
	    }

	    dump_format(formatCtx, 0, input_files[i], 0);

	    printf("streams: %d\n", formatCtx->nb_streams);
	    codecCtx = formatCtx->streams[0]->codec;	

	    switch (codecCtx->sample_fmt) {
	    case SAMPLE_FMT_S16:
		    pss.format = PA_SAMPLE_S16LE;
		    break;
	    case SAMPLE_FMT_U8:
		    pss.format = PA_SAMPLE_U8;
		    break;
	    default:
		    fprintf(stderr, "can not support this format for dsp.\n");	
		    return -1;
	    }

		pss.channels = codecCtx->channels;

	    pss.rate = codecCtx->sample_rate;

		printf("channels: %d\n", pss.channels);
		printf("rate: %d\n", pss.rate);
		printf("format: %d\n", pss.format);

		ps = pa_simple_new(NULL, 
				input_files[i],
				PA_STREAM_PLAYBACK,
				NULL,
				"Music",
				&pss,
				NULL,
				NULL,
				&error);
		
		if (ps == NULL) {
			fprintf(stderr, "can not get new pulase stream: %s\n", pa_strerror(error));
			return -1;
		}

	    codec = avcodec_find_decoder(codecCtx->codec_id);

	    if (codec == NULL) {
		    fprintf(stderr, "can not find codec.\n");
		    return -1;
	    }

	    if (avcodec_open(codecCtx, codec) < 0) {
		    fprintf(stderr, "can not open codec.\n");
		    return -1;
	    }

	    while (av_read_frame(formatCtx, &packet) >= 0) {
		    buf_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
		    decodec_size = avcodec_decode_audio2(codecCtx, 
			    (int16_t *)sample_buf, 
			    &buf_size, 
			    packet.data, packet.size);

		    if (decodec_size < 0) {
			    fprintf(stderr, "can not decode\n");
			    return -1;
		    }

			len = pa_simple_write(ps, sample_buf, buf_size, &error);

		    if (len < 0) {
			    fprintf(stderr, "pa_sample_write() failed: %s\n", pa_strerror(error));
			    return -1;
		    }
		
		    av_free_packet(&packet);
	    }

	    avcodec_close(codecCtx);
	    av_close_input_file(formatCtx);
		pa_simple_free(ps);
	}

	for (i = 0; i < count; i++) {
		free(input_files[count]);
	}

	free(input_files);

	return 0;
}

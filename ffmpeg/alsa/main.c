#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <dirent.h>
#include <getopt.h>

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
	int format = AFMT_S16_LE;
	char **input_files = NULL;
	int opt = 0;
	int count = 0;
	int i = 0;

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

	int dsp_fd = open("/dev/dsp", O_WRONLY);

	if (dsp_fd < 0) {
		perror("can not open dsp.");
		return -1;
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
	    printf("format = %d\n", codecCtx->sample_fmt);	

	    switch (codecCtx->sample_fmt) {
	    case SAMPLE_FMT_U8:
		    format = AFMT_U8;
		    break;
	    case SAMPLE_FMT_S16:
		    format = AFMT_S16_LE;
		    break;
	    default:
		    fprintf(stderr, "can not support this format for dsp.\n");	
		    return -1;
	    }

	    if (ioctl(dsp_fd, SNDCTL_DSP_SETFMT, &format) == -1) {
		    perror("can not set format.");
		    return -1;
	    }
	
	    int channels = 2;

	    printf("channels: %d\n", codecCtx->channels);	

	    if (ioctl(dsp_fd, SNDCTL_DSP_CHANNELS, &channels) == -1) {
		    perror("can not set channels.");
		    return -1;
	    }

	    int sample_rate = codecCtx->sample_rate;

	    printf("sample_rate = %d\n", sample_rate); 

	    if (ioctl(dsp_fd, SNDCTL_DSP_SPEED, &sample_rate) == -1) {
		    perror("can not set sample rate.");
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

		    len = write(dsp_fd, sample_buf, buf_size);

	    //	printf("%d:%d:%d:%d\n", decodec_size, packet.size, len, buf_size);	

		    if (len < 0) {
			    perror("can not write data to dsp");
			    return -1;
		    }
		
		    av_free_packet(&packet);
	    }

	    avcodec_close(codecCtx);
	    av_close_input_file(formatCtx);
	}

	for (i = 0; i < count; i++) {
		free(input_files[count]);
	}

	free(input_files);

	close(dsp_fd);
	return 0;
}

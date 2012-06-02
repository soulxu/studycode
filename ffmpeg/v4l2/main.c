#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <malloc.h>
#include <linux/videodev2.h>

#include "../../utils/Debug.h"

struct buffer {
	void *start;
	size_t length;
} * buffers;


void print_cap(struct v4l2_capability *cap) {
    D_PVAR_STR(cap->driver);
    D_PVAR_STR(cap->card);
    D_PVAR_STR(cap->bus_info);
    D_PVAR_INT(cap->version);

    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VIDEO_CAPTURE);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VIDEO_OUTPUT);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VIDEO_OVERLAY);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VBI_CAPTURE);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VBI_OUTPUT);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_SLICED_VBI_CAPTURE);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_SLICED_VBI_OUTPUT);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_RDS_CAPTURE);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_VIDEO_OUTPUT_OVERLAY);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_TUNER);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_AUDIO);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_RADIO);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_READWRITE);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_ASYNCIO);
    D_PVAR_EMU(cap->capabilities,V4L2_CAP_STREAMING);
}

int main(int argc, char **argv) {
	int width = 640;
	int height = 480;
    int fd = open("/dev/video0", O_RDWR | O_NONBLOCK);
    int stat = 0;

    if (fd < 0) {
        D_ERROR("can not open device.");
        return -1;
    }

    struct v4l2_capability cap = {0};
    stat = ioctl(fd, VIDIOC_QUERYCAP, &cap);

    if (stat == -1) {
        D_ERROR("can not get device capability.");
        return -1;
    }

    print_cap(&cap);

    int input_index = 0;
    stat = ioctl(fd, VIDIOC_G_INPUT, &input_index);

    if (stat == -1) {
        D_ERROR("can not get current input");
        return -1;
    }


    D_PVAR_INT(input_index);
    struct v4l2_input input;
    memset(&input, 0, sizeof(input));
    input.index = 0;

    D_PRINT("enum input");

    do {
        stat = ioctl(fd, VIDIOC_ENUMINPUT, &input);

        if (stat == -1) {
            break;
        }

        D_PVAR_INT(input.index);
        D_PVAR_STR(input.name);
        input.index++;
    } while (1);

    D_PRINT("enum input end");


    v4l2_std_id std;
    do {
        stat = ioctl(fd, VIDIOC_QUERYSTD, &std);
    } while (stat == -1 && errno == EAGAIN);
    if (stat == -1) {
        D_ERROR("can not get current video standard.");
        //return -1;
    }

    struct v4l2_standard standard;
    memset(&standard, 0, sizeof(standard));

    D_PRINT("enum video standard.");
    while (1) {
        stat = ioctl(fd, VIDIOC_ENUMSTD, &standard);

        if (stat == -1) {
            break;
        }

        D_PVAR_INT(standard.index);
        D_PVAR_STR(standard.name);
        if (std == standard.id) {
            D_PRINT("above is current video standard.");
        }

        standard.index++;
    }
    D_PRINT("enum video standard end.");



    struct v4l2_fmtdesc fmtdesc;
    memset(&fmtdesc, 0, sizeof(fmtdesc));
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    D_PRINT("enum image format.");
    while (1) {
        stat = ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc);

        if (stat == -1) {
            break;
        }

        D_PVAR_INT(fmtdesc.index);
        D_PVAR_STR(fmtdesc.description);
        fmtdesc.index++;
    }
    D_PRINT("enum image format end.");


    struct v4l2_format fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    D_PRINT("set format");

    stat = ioctl(fd, VIDIOC_S_FMT, &fmt);

    if (stat == -1) {
    	D_ERROR("can not set video format");
    	return -1;
    }

    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_JPEG) {
    	D_ERROR("can not set specific format");
    	struct v4l2_fmtdesc fmtqury;
    	memset(&fmtqury, 0, sizeof(fmtqury));

    	fmtqury.pixelformat == fmt.fmt.pix.pixelformat;
    	stat = ioctl(fd, VIDIOC_ENUM_FMT, &fmtqury);

    	if (stat == -1) {
    		printf("real format: %s\n", fmtqury.description);
    	}
    	printf("format = %d\n", fmt.fmt.pix.pixelformat);
    	return -1;
    }

    struct v4l2_requestbuffers req;

    memset(&req, 0, sizeof(struct v4l2_requestbuffers));

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    stat = ioctl(fd, VIDIOC_REQBUFS, &req);

    if (stat == -1) {
    	D_ERROR("can not require buffers");
    	return -1;
    }

    buffers = (struct buffer *)malloc(sizeof(struct buffer) * req.count);

    int i = 0;
    for (i = 0; i < req.count; i++) {
    	struct v4l2_buffer buf;
    	memset(&buf, 0, sizeof(buf));

    	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    	buf.memory = V4L2_MEMORY_MMAP;
    	buf.index = i;

    	stat = ioctl(fd, VIDIOC_QUERYBUF, &buf);

    	if (stat == -1) {
    		D_ERROR("can not query buffer");
    		return -1;
    	}

    	buffers[i].length = buf.length;
    	buffers[i].start = mmap(NULL, buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, buf.m.offset);

    	if (MAP_FAILED == buffers[i].start) {
    		D_ERROR("mmap error");
    		return -1;
    	}

    	stat = ioctl(fd, VIDIOC_QBUF, &buf);

    	if (stat == -1) {
    		D_ERROR("can not put buf in queue");
    		return -1;
    	}
    }




    enum v4l2_buf_type stream_type =  V4L2_BUF_TYPE_VIDEO_CAPTURE;

    D_PRINT("stream on.");
    stat = ioctl(fd, VIDIOC_STREAMON, &stream_type);

    if (stat == -1) {
    	D_ERROR("can not turn stream on");
    	return -1;
    }

    i = 0;
    char filename[4096] = {0};

    D_PRINT("start loop");

    while (1) {
    	fd_set fds;
    	FD_ZERO(&fds);
    	FD_SET(fd, &fds);
    	int ret = 0;
    	ret = select(fd + 1, &fds, NULL, NULL, NULL);

    	if (ret == -1) {
    		if (EINTR == errno) {
    			continue;
    		}

    		D_ERROR("select error.");
    		return -1;
    	}

    	struct v4l2_buffer buf;
    	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    	buf.memory = V4L2_MEMORY_MMAP;
    	stat = ioctl(fd, VIDIOC_DQBUF, &buf);

    	if (stat == -1) {
    		D_ERROR("can not out queue");
    		return -1;
    	}


    	sprintf(filename, "out/frame%d.jpg", i);

    	printf("index: %d, out: %s\n", buf.index, filename);
    	FILE *out = fopen(filename, "wb");

    	//fprintf(out, "P6\n%d %d\n255\n",640, 480);

    	fwrite(buffers[buf.index].start, 1, buf.length, out);
    	fclose(out);

    	ioctl(fd, VIDIOC_QBUF, &buf);
    	i++;
    }


    stat = ioctl(fd, VIDIOC_STREAMOFF, &stream_type);

        if (stat == -1) {
        	D_ERROR("can not turn stream off");
        	return -1;
        }
    close(fd);
    return 0;
}

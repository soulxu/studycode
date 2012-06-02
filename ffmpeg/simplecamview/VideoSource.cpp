#include "VideoSource.h"

#include "../../utils/QTDebug.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

#define VIDEO_DEV "/dev/video0"

VideoSource::VideoSource(int width, int height) :
    m_width(width),
    m_height(height),
    m_buffers(NULL),
    m_bufferNum(DEFAULT_BUF_NUM)
{

}

VideoSource::~VideoSource() {
    closeDevice();
}

bool VideoSource::openDevice(const QString &device) {
    int fd = open(qPrintable(device), O_RDWR | O_NONBLOCK);

    if (fd < 0) {
        DPRINT("can not open device.");
        return false;
    }

    m_notifier =
            new QSocketNotifier(fd, QSocketNotifier::Read, this);


    if (!checkCapability()) {
        DPRINT("this device can not support stream type");
        closeDevice();
        return false;
    }

    if (!setFormat()) {
        DPRINT("can not set device format");
        closeDevice();
        return false;
    }

    if (!initMem()) {
        DPRINT("can not initial memory buffer");
        closeDevice();
        return false;
    }

    return true;
}

bool VideoSource::start() {
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int stat = 0;

    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readFrame(int)));

    stat = ioctl(m_notifier->socket(), VIDIOC_STREAMON, &type);

    if (stat == -1) {
        DPRINT("can not turn stream on.");
        return false;
    }

    return true;
}

void VideoSource::stop() {
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(m_notifier->socket(), VIDIOC_STREAMOFF, &type);
}

void VideoSource::readFrame(int fd) {
    int stat = 0;
    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    stat = ioctl(fd, VIDIOC_DQBUF, &buf);

    if (stat == -1) {
        DPRINT("can not get buf frome queue.");
        return;
    }

    DPRINT("buffer index: %d", buf.index);
    emit receiveFrame(&m_buffers[buf.index]);

    ioctl(fd, VIDIOC_QBUF, &buf);
}

bool VideoSource::setFormat() {
    int stat = 0;
    struct v4l2_format fmt;

    memset(&fmt, 0, sizeof(fmt));

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = m_width;
    fmt.fmt.pix.height = m_height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    stat = ioctl(m_notifier->socket(), VIDIOC_S_FMT, &fmt);

    if (stat == -1) {
        if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_JPEG) {
            DPRINT("device can not support sepcific format.");
        }
        else {
            DPRINT("can not set format.");
        }

        return false;
    }

    return true;
}

bool VideoSource::initMem() {
    int stat = 0;
    struct v4l2_requestbuffers req;
    memset(&req, 0, sizeof(struct v4l2_requestbuffers));

    req.count = m_bufferNum;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    stat = ioctl(m_notifier->socket(), VIDIOC_REQBUFS, &req);

    if (stat == -1) {
        DPRINT("can not require buffers");
    }

    m_bufferNum = req.count;
    m_buffers = new struct Buffer[m_bufferNum];
    DPRINT("request buffer number: %d", m_bufferNum);

    for (int i = 0; i < m_bufferNum; i++) {
        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(buf));

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        stat  = ioctl(m_notifier->socket(), VIDIOC_QUERYBUF, &buf);

        if (stat == -1) {
            DPRINT("can not query buffer");
            return false;
        }

        m_buffers[buf.index].length = buf.length;
        m_buffers[buf.index].start = mmap(NULL,
                                          buf.length,
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED,
                                          m_notifier->socket(),
                                          buf.m.offset);

        stat = ioctl(m_notifier->socket(), VIDIOC_QBUF, &buf);

        if (stat == -1) {
            DPRINT("can not put buffer in queue.");
            return false;
        }
    }

    return true;
}

void VideoSource::closeDevice() {
    if (m_notifier->isEnabled()) {
        m_notifier->setEnabled(false);
        close(m_notifier->socket());

        if (m_buffers != NULL) {
            delete m_buffers;
        }
    }
}

bool VideoSource::checkCapability() {
    int stat = 0;
    struct v4l2_capability cap;

    memset(&cap, 0, sizeof(cap));
    stat = ioctl(m_notifier->socket(), VIDIOC_QUERYCAP, &cap);

    if (stat == -1) {
        DPRINT("can not get device capability.");
        return false;
    }

    if ((cap.capabilities & V4L2_CAP_STREAMING) &&
        (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        return true;
    }

    return false;
}

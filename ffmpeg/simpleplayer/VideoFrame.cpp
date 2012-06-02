#include "VideoFrame.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

void *VideoFrame::getData() const {
    return m_rawData->data[0];
}

VideoFrame::VideoFrame(AVFrame *data, long long pts, FrameType type) : Frame(type, pts), m_rawData(data) {

}

VideoFrame::~VideoFrame() {
    avpicture_free((AVPicture *)m_rawData);
    av_free(m_rawData);
}

int VideoFrame::getPerLineSize() const {
    return this->m_rawData->linesize[0];
}

#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include "Frame.h"

struct AVFrame;

class VideoFrame : public Frame {
public:
    VideoFrame(AVFrame *data, long long pts, FrameType type);
    virtual ~VideoFrame();

    virtual void *getData() const;

    AVFrame *getAVFrame() const {
        return m_rawData;
    }

    int getPerLineSize() const;

private:
    AVFrame *m_rawData;
};

#endif // VIDEOFRAME_H

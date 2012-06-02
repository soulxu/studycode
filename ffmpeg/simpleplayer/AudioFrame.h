#ifndef AUDIOFRAME_H
#define AUDIOFRAME_H

#include "Frame.h"

class AudioFrame : public Frame {
public:
    AudioFrame(quint8 *buf, int size, int pts, FrameType type);
    virtual ~AudioFrame();
    virtual void *getData() const;
    int getSize() const { return m_size; }

private:
    quint8 *m_buf;
    int m_size;
    FrameType m_type;
};

#endif // AUDIOFRAME_H

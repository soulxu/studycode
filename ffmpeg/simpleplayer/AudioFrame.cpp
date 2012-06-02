#include "AudioFrame.h"

#include <stdlib.h>

AudioFrame::AudioFrame(quint8 *buf, int size, int pts, FrameType type) :
        Frame(type, pts),
        m_buf(buf),
        m_size(size)
{

}

AudioFrame::~AudioFrame() {
    free(m_buf);
}

void *AudioFrame::getData() const {
    return m_buf;
}

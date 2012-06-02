#ifndef FRAME_H
#define FRAME_H

#include <QtGlobal>

class Frame {
public:
    enum FrameType {
        VideoFrame,
        AudioFrame
    };

    Frame(FrameType type, long long int pts) : m_type(type), m_pts(pts) { }
    virtual ~Frame() { }

    virtual void *getData() const {
        return NULL;
    }

    FrameType getType() const {
        return m_type;
    }

    long long int getPts() const {
        return m_pts;
    }

private:
    FrameType m_type;
    long long int m_pts;
};

#endif // FRAME_H

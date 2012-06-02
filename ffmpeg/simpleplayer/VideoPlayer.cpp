#include "VideoPlayer.h"

#include <DataSource.h>
#include <DataCacher.h>
#include <VideoFrame.h>

#include "../../utils/QTDebug.h"

VideoPlayer::VideoPlayer(DataSource *source, DataCacher *cacher, uchar *buf, long long *current) :
        m_source(source),
        m_cacher(cacher),
        m_buf(buf),
        m_current(current)
{

}

void VideoPlayer::play() {
    this->start();
}

void VideoPlayer::run() {
    while (1) {
        int base = m_source->getBaseTime();
        VideoFrame *frame = NULL;
        DPRINT("current: %lld", *m_current);

        //m_mutex.lock();
        m_waitTime.wait(&m_mutex);
        //m_mutex.unlock();

        while ((frame = (VideoFrame *)m_cacher->getTopVideoFrame()) != NULL) {
            long long current = *m_current;
            if (frame->getPts() != current) {
                if (frame->getPts() > current) {
                    m_mutex.lock();
                    m_waitTime.wait(&m_mutex);
                    DPRINT("too fast: %lld, %d, %lld > %lld", frame->getPts(), (int)m_source->getBaseTime(), frame->getPts() * (int)m_source->getBaseTime(), current);
                    m_mutex.unlock();
                    continue;
                }

                if (frame->getPts() < current) {
                    DPRINT("too late: %lld, %d, %lld < %lld", frame->getPts(), (int)m_source->getBaseTime(), frame->getPts() * (int)m_source->getBaseTime(), current);
                    delete m_cacher->getVideoFrame();

                    continue;
                }
            }

            frame = (VideoFrame *)m_cacher->getVideoFrame();

            memcpy(m_buf, frame->getData(), frame->getPerLineSize() * m_source->height());
            emit updateImg();

            delete frame;
            //m_waitTime.wait(&m_mutex);
            QThread::yieldCurrentThread();
            break;
        }


    }
}

void VideoPlayer::wake(long long current) {
    //m_mutex.lock();
    //m_current = current;
    //m_mutex.unlock();
    m_waitTime.wakeAll();
}

void VideoPlayer::key(long long current) {

}

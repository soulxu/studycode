#include "DataCacher.h"

#include "DataSource.h"
#include "Frame.h"

#include "../../utils/QTDebug.h"

DataCacher::DataCacher(DataSource *source, int size) :
        m_size(size),
        m_source(source),
        m_isFinished(false)
{

}

void DataCacher::run() {
    Frame *frame = NULL;

    while (1) {
        m_mutex.lock();

        if ((m_videoQueue.size() >= m_size) && (m_audioQueue.size() >= m_size)) {
            m_cacheNotFull.wait(&m_mutex);
        }

        m_mutex.unlock();

        frame = m_source->readFrame();

        if (frame == NULL) {
            m_isFinished = true;
            break;
        }

        //DPRINT("get packet");

        switch (frame->getType()) {
        case Frame::AudioFrame:
            m_mutex.lock();
            m_audioQueue.enqueue(frame);
            m_mutex.unlock();
            break;

        case Frame::VideoFrame:
            m_mutex.lock();
            m_videoQueue.enqueue(frame);
            m_mutex.unlock();
            break;
        }

        m_cacheNotEmpty.wakeAll();
    }
}

Frame *DataCacher::getTopVideoFrame() {
    m_mutex.lock();

    while (m_videoQueue.isEmpty()) {
        if (m_isFinished) {
            m_mutex.unlock();
            return NULL;
        }

        m_cacheNotEmpty.wait(&m_mutex);
    }

    Frame *frame = m_videoQueue.head();

    m_cacheNotFull.wakeAll();

    m_mutex.unlock();

    return frame;
}

Frame *DataCacher::getVideoFrame() {
    m_mutex.lock();

    while (m_videoQueue.isEmpty()) {
        m_mutex.unlock();
        if (m_isFinished) {
            return NULL;
        }

        m_cacheNotEmpty.wait(&m_mutex);
    }

    Frame *frame = m_videoQueue.dequeue();

    m_cacheNotFull.wakeAll();

    m_mutex.unlock();

    return frame;

}

Frame *DataCacher::getTopAudioFrame() {
    m_mutex.lock();

    while (m_audioQueue.isEmpty()) {
        if (m_isFinished) {
            m_mutex.unlock();
            return NULL;
        }

        m_cacheNotEmpty.wait(&m_mutex);
    }

    Frame *frame = m_audioQueue.head();

    m_cacheNotFull.wakeAll();


    m_mutex.unlock();

    return frame;
}

Frame *DataCacher::getAudioFrame() {
    m_mutex.lock();

    while (m_audioQueue.isEmpty()) {
        if (m_isFinished) {
            m_mutex.unlock();
            return NULL;
        }

        m_cacheNotEmpty.wait(&m_mutex);
    }

    Frame *frame = m_audioQueue.dequeue();

    m_cacheNotFull.wakeAll();

    m_mutex.unlock();

    return frame;
}

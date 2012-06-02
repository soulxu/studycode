#ifndef DATACACHER_H
#define DATACACHER_H

#include <QThread>
#include <QQueue>
#include <QWaitCondition>
#include <QMutex>

class DataSource;
class Frame;

class DataCacher : public QThread {
public:
    DataCacher(DataSource *source, int size);
    Frame *getTopVideoFrame();
    Frame *getVideoFrame();
    Frame *getTopAudioFrame();
    Frame *getAudioFrame();

    int getVideoSize() { return m_videoQueue.size(); }
    int getAudioSize() { return m_audioQueue.size(); }

protected:
    virtual void run();

private:
    QQueue<Frame *> m_videoQueue;
    QQueue<Frame *> m_audioQueue;
    int m_size;
    DataSource *m_source;
    QWaitCondition m_cacheNotFull;
    QWaitCondition m_cacheNotEmpty;
    QMutex m_mutex;
    bool m_isFinished;
};

#endif // DATACACHER_H

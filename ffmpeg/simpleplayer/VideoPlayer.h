#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>

class DataSource;
class DataCacher;

class VideoPlayer : public QThread {
    Q_OBJECT
public:
    VideoPlayer(DataSource *source,
                DataCacher *cacher,
                uchar *buf, long long *current);

    void play();

public slots:
    void key(long long current);
    void wake(long long current);

protected:
    virtual void run();

signals:
    void updateImg();

private:
    DataSource *m_source;
    DataCacher *m_cacher;
    uchar *m_buf;
    QMutex m_mutex;
    QWaitCondition m_waitTime;
    long long *m_current;
};

#endif // VIDEOPLAYER_H

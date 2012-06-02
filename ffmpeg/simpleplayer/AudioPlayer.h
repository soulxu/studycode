#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class DataSource;
class DataCacher;
struct pa_simple;
struct pa_sample_spec;

class AudioPlayer : public QThread {
    Q_OBJECT
public:
    AudioPlayer(DataSource *source, DataCacher *cacher, long long *current);
    ~AudioPlayer();
    void initAudioDevice();

public slots:
    void wake(long long current);

protected:
    virtual void run();

private:
    DataSource *m_source;
    DataCacher *m_cacher;
    pa_simple *m_pa;
    pa_sample_spec *m_pss;
    int m_error;
    QWaitCondition m_waitTime;
    QMutex m_mutex;
    long long *m_current;
};

#endif // AUDIOPLAYER_H

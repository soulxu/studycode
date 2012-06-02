#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H

#include "DataSource.h"
#include "DataCacher.h"

#include <QWidget>
#include <QTimer>

class AudioPlayer;
class VideoPlayer;
class DataSource;
class DataCacher;

class SimplePlayer : public QWidget {
    Q_OBJECT
public:
    SimplePlayer(DataSource *source, DataCacher *cacher);

    void play();

signals:
    void key(long long current);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void timeout();
    void updateImg();

private:
    DataSource *m_source;
    DataCacher *m_cacher;
    QTimer m_timer;
    long long int m_current;
    QImage *m_buf;
    VideoPlayer *m_videoPlayer;
    AudioPlayer *m_audioPlayer;
};

#endif // SIMPLEPLAYER_H

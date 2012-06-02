#include "SimplePlayer.h"

#include "VideoFrame.h"
#include "../../utils/QTDebug.h"
#include "AudioPlayer.h"
#include "VideoPlayer.h"

#include <QDateTime>
#include <QPainter>

SimplePlayer::SimplePlayer(DataSource *source, DataCacher *cacher) :
        m_source(source),
        m_cacher(cacher),
        m_current(0),
        m_buf(NULL)
{

}

void SimplePlayer::play() {
    m_buf = new QImage(m_source->width(), m_source->height(), QImage::Format_RGB888);
    m_videoPlayer = new VideoPlayer(m_source, m_cacher, m_buf->bits(), &m_current);
    this->connect(this, SIGNAL(key(long long)), m_videoPlayer, SLOT(key(long long)));
    this->connect(m_videoPlayer, SIGNAL(updateImg()), this, SLOT(updateImg()));
    this->connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    m_audioPlayer = new AudioPlayer(m_source, m_cacher, &m_current);
    m_audioPlayer->initAudioDevice();

    m_videoPlayer->play();
    m_audioPlayer->start();

    DPRINT("%lf, %ld", m_source->getBaseTime() * 1000, (long)(m_source->getBaseTime() * 1000));
    this->m_timer.start(m_source->getTimeBase() * 1000);
}

void SimplePlayer::timeout() {

    //DPRINT("timeout : %lld", m_current);
    m_videoPlayer->wake(m_current);
    m_audioPlayer->wake(m_current);
    m_current++;
    //m_videoPlayer->key(m_current);
    //DPRINT("%s", qPrintable(QDateTime::currentDateTime().toString()));
}

void SimplePlayer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (m_buf != NULL) {
        painter.drawImage(0, 0, *m_buf);
    }
}

void SimplePlayer::updateImg() {
    this->update();
}

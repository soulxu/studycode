#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QSocketNotifier>

struct Buffer {
    void *start;
    size_t length;
};

class VideoSource : public QObject {
    Q_OBJECT
public:
    static const int DEFAULT_BUF_NUM = 5;
    VideoSource(int width, int height);
    ~VideoSource();

    bool openDevice(const QString &device);
    bool start();
    void stop();
    void closeDevice();

signals:
    void receiveFrame(Buffer *buf);

private slots:
    void readFrame(int fd);

private:
    bool checkCapability();
    bool setFormat();
    bool initMem();

private:
    QSocketNotifier *m_notifier;
    int m_width;
    int m_height;
    struct Buffer *m_buffers;
    int m_bufferNum;
};

#endif // VIDEOSOURCE_H

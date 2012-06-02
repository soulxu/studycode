#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Frame.h"

#include <QString>
#include <QObject>

struct AVFormatContext;
struct AVCodec;
struct AVFrame;
struct AVCodecContext;
struct SwsContext;
struct AVPacket;

class DataSource : public QObject {
    Q_OBJECT
public:
    enum AudioFormat {
        FMT_NONE,
        FMT_U8,
        FMT_S16,
        FMT_S32,
        FMT_FLT,
        FMT_DBL,
    };

    DataSource(const QString &filename);
    virtual ~DataSource();

    bool open();
    void close();

    Frame *readFrame();

    int width();
    int height();

    double getTimeBase();
    double getBaseTime();

    int getAudioSampleRate();
    int getChannel();
    AudioFormat getSampleFormat();

private:
    bool openCodec(AVCodecContext *codecCtx, AVCodec **codec);
    void closeCodec();
    AVFrame *decodeVideo(AVCodecContext *codecCtx, AVPacket *packet);
    quint8 *decodeAudio(AVCodecContext *codecCtx, AVPacket *packet, int *size);
    void closeInputFile();

private:
    QString m_filename;
    AVFormatContext *m_formatCtx;
    AVCodec *m_videoCodec;
    AVCodec *m_audioCodec;
    AVFrame *m_rawFrame;
    SwsContext *m_swsCtx;
    int m_videoStream;
    int m_audioStream;
    long long m_currentAudioPts;
    long long m_currentVideoPts;
    double m_timeBase;
};

#endif // DATASOURCE_H

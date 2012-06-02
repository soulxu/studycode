#include "DataSource.h"

#include "VideoFrame.h"
#include "AudioFrame.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "../../utils/QTDebug.h"

DataSource::DataSource(const QString &filename) :
        m_filename(filename),
        m_formatCtx(NULL),
        m_videoCodec(NULL),
        m_audioCodec(NULL),
        m_rawFrame(NULL),
        m_swsCtx(NULL),
        m_videoStream(-1),
        m_audioStream(-1),
        m_currentVideoPts(0),
        m_currentAudioPts(0),
        m_timeBase(0)
{

}

DataSource::~DataSource() {
    this->close();
}

DataSource::AudioFormat DataSource::getSampleFormat() {
    switch (m_formatCtx->streams[m_audioStream]->codec->sample_fmt) {
    case SAMPLE_FMT_U8:
            return FMT_U8;

    case SAMPLE_FMT_S16:
            return FMT_S16;

    case SAMPLE_FMT_S32:
            return FMT_S32;

    case SAMPLE_FMT_FLT:
            return FMT_FLT;

    case SAMPLE_FMT_DBL:
            return FMT_DBL;
    }

    return FMT_NONE;
}

int DataSource::getAudioSampleRate() {
    return m_formatCtx->streams[m_audioStream]->codec->sample_rate;
}

int DataSource::getChannel() {
    return m_formatCtx->streams[m_audioStream]->codec->channels;
}

int DataSource::width() {
    return m_formatCtx->streams[m_videoStream]->codec->width;
}
int DataSource::height() {
    return m_formatCtx->streams[m_videoStream]->codec->height;
}

bool DataSource::openCodec(AVCodecContext *codecCtx, AVCodec **codec) {
    *codec = avcodec_find_decoder(codecCtx->codec_id);

    if (*codec == NULL) {
        DPRINT("can not find codec.");
        return false;
    }

    if (avcodec_open(codecCtx, *codec) < 0) {
        DPRINT("can not open codec.");
        return false;
    }

    return true;
}

void DataSource::closeCodec() {
    for (uint i = 0; i < m_formatCtx->nb_streams; i++) {
        avcodec_close(m_formatCtx->streams[i]->codec);
    }
}

bool DataSource::open() {
    if (av_open_input_file(&m_formatCtx,
                           qPrintable(m_filename),
                           NULL,
                           0,
                           NULL) != 0)
    {
        DPRINT("can not open file.");
        return false;
    }

    if(av_find_stream_info(m_formatCtx) < 0) {
        DPRINT("can not find stream info.");
        return false;
    }

    dump_format(m_formatCtx, 0, 0, 0);

    AVCodecContext *codecCtx = NULL;

    for (uint i = 0; i < m_formatCtx->nb_streams; i++) {
        codecCtx = m_formatCtx->streams[i]->codec;

        if (codecCtx->codec_type == CODEC_TYPE_VIDEO) {
            m_videoStream = i;
            //DPRINT("video stream index: %d - %dx%d", m_videoStream, codecCtx->width, codecCtx->height);

            if (!this->openCodec(codecCtx, &m_videoCodec)) {
                closeInputFile();
                DPRINT("can not open video codec.");
                return false;
            }

            this->m_swsCtx = sws_getContext(codecCtx->width,
                                            codecCtx->height,
                                            codecCtx->pix_fmt,
                                            codecCtx->width,
                                            codecCtx->height,
                                            PIX_FMT_RGB24,
                                            SWS_BICUBIC,
                                            NULL,
                                            NULL,
                                            NULL);

            if (this->m_swsCtx == NULL) {
                closeInputFile();
                DPRINT("can not get swscale context");
                return false;
            }

            m_timeBase = av_q2d(m_formatCtx->streams[m_videoStream]->time_base);
            m_rawFrame = avcodec_alloc_frame();
        }
        else if (codecCtx->codec_type == CODEC_TYPE_AUDIO) {
            m_audioStream = i;

            if (!this->openCodec(codecCtx, &m_audioCodec)) {
                closeInputFile();
                DPRINT("can not open audio codec.");
                return false;
            }
        }
    }

    return true;
}

void DataSource::close() {
    av_free(m_rawFrame);
    closeCodec();
    closeInputFile();
}

void DataSource::closeInputFile() {
    if (m_formatCtx != NULL) {
        av_close_input_file(m_formatCtx);
        m_formatCtx = NULL;
    }
}

double DataSource::getTimeBase() {
    return av_q2d(m_formatCtx->streams[m_videoStream]->time_base);
}

double DataSource::getBaseTime() {
    return m_formatCtx->streams[m_videoStream]->time_base.den * 1.0 / m_formatCtx->streams[m_videoStream]->time_base.num;
}

Frame *DataSource::readFrame() {
    AVPacket packet;

    //DPRINT("%d, %d", m_formatCtx->streams[m_videoStream]->time_base.num, m_formatCtx->streams[m_videoStream]->time_base.den);
    while (av_read_frame(m_formatCtx, &packet) >= 0) {
        if (packet.stream_index == m_videoStream) {
            //DPRINT("video packet pts %lld", packet.pts);
            if (packet.pts != AV_NOPTS_VALUE) {
                //DPRINT("video set pts %lld", packet.pts);
                if (packet.pts > m_currentVideoPts) {
                    m_currentVideoPts = packet.pts;
                }
            }

            AVFrame *f = decodeVideo(m_formatCtx->streams[m_videoStream]->codec, &packet);

            if (f != NULL) {
                //DPRINT("video pts: %lf, %lf", videoTimeBase, m_currentPts * videoTimeBase);
                Frame *ret = new VideoFrame(f,
                                            m_currentVideoPts,
                                            Frame::VideoFrame);
                av_free_packet(&packet);
                return ret;
            }
        }
        else if (packet.stream_index == m_audioStream) {
            //DPRINT("audio packet pts %lld", packet.pts);
            if (packet.pts != AV_NOPTS_VALUE) {
                //DPRINT("audio set pts %lld", packet.pts);
                if (packet.pts > m_currentAudioPts) {
                    m_currentAudioPts = packet.pts;
                }
            }
            int size = 0;
            uint8_t *buf = decodeAudio(m_formatCtx->streams[m_audioStream]->codec,
                                       &packet,
                                       &size);

            if (buf != NULL) {
                Frame *ret = new AudioFrame(buf, size, m_currentAudioPts, Frame::AudioFrame);
                return ret;
            }
        }

        av_free_packet(&packet);
    }

    return NULL;
}

quint8 *DataSource::decodeAudio(AVCodecContext *codecCtx, AVPacket *packet, int *size) {
    uint8_t *sampleBuf = NULL;
    int decodeSize = 0;
    *size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
    sampleBuf = (uint8_t *)malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE * sizeof(uint8_t));
    decodeSize = avcodec_decode_audio2(codecCtx,
                                  (int16_t *)sampleBuf,
                                  size,
                                  packet->data,
                                  packet->size);

    if (*size < 0) {
        free(sampleBuf);
        DPRINT("can ont decode data.");
        return NULL;
    }

    return sampleBuf;
}

AVFrame *DataSource::decodeVideo(AVCodecContext *codecCtx, AVPacket *packet) {
    int frameFinished = 0;
    avcodec_decode_video(codecCtx,
                         m_rawFrame,
                         &frameFinished,
                         packet->data,
                         packet->size);

    if (frameFinished) {
        AVFrame *f = avcodec_alloc_frame();

        if (f == NULL) {
            DPRINT("can not alloc frame.");
            return NULL;
        }

        avpicture_alloc((AVPicture *)f,
                        PIX_FMT_RGB24,
                        codecCtx->width,
                        codecCtx->height);

        sws_scale(this->m_swsCtx,
                  m_rawFrame->data,
                  m_rawFrame->linesize,
                  0,
                  codecCtx->height,
                  f->data,
                  f->linesize);

        return f;
    }

    return NULL;
}

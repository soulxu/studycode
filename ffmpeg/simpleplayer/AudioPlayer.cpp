#include "AudioPlayer.h"

#include "DataCacher.h"
#include "DataSource.h"
#include "AudioFrame.h"

extern "C" {
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>
}

#include "../../utils/QTDebug.h"

AudioPlayer::AudioPlayer(DataSource *source, DataCacher *cacher, long long *current) :
        m_source(source),
        m_cacher(cacher),
        m_pa(NULL),
        m_pss(NULL),
        m_current(current)
{
    m_pss = (pa_sample_spec *)malloc(sizeof(pa_sample_spec));
    memset(m_pss, 0, sizeof(m_pss));
}

AudioPlayer::~AudioPlayer() {
    free(m_pss);
}

void AudioPlayer::initAudioDevice() {
    switch (m_source->getSampleFormat()) {
    case DataSource::FMT_U8:
        m_pss->format = PA_SAMPLE_U8;
        break;
    case DataSource::FMT_S16:
        m_pss->format = PA_SAMPLE_S16LE;
        break;
    default:
        DPRINT("error");
    }

    m_pss->channels = m_source->getChannel();
    m_pss->rate = m_source->getAudioSampleRate();

    m_pa = pa_simple_new(NULL,
                         "video",
                         PA_STREAM_PLAYBACK,
                         NULL,
                         "Music",
                         m_pss,
                         NULL,
                         NULL,
                         &m_error);

    Q_ASSERT(m_pa != NULL);
}

void AudioPlayer::wake(long long current) {
    //DPRINT("sound awake");
    //m_mutex.lock();
    //m_current = current;
    //m_mutex.unlock();
    m_waitTime.wakeAll();
}

void AudioPlayer::run() {
    while (1) {
        AudioFrame *f = static_cast<AudioFrame *>(m_cacher->getTopAudioFrame());

        if (f == NULL) {
            return;
        }

        //m_mutex.lock();
        m_waitTime.wait(&m_mutex);

        if (f->getPts() != *m_current) {
            if (f->getPts() > *m_current) {
                //m_mutex.unlock();
                //DPRINT("<");
                continue;
            }

        }

        //m_mutex.unlock();

        while (1) {
            f = static_cast<AudioFrame *>(m_cacher->getAudioFrame());

            int len = 0;
            int size = f->getSize();
            uchar *data = (uchar *)f->getData();

            DPRINT("audio: %ld", f->getPts());
            len = pa_simple_write(m_pa, data, size, &m_error);

            if (len < 0) {
               DPRINT("%s", pa_strerror(m_error));
               break;
            }

            delete f;
            QThread::yieldCurrentThread();
            m_waitTime.wait(&m_mutex);
        }
    }
}


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "DataSource.h"
#include "VideoFrame.h"
#include "DataCacher.h"

#include "SimplePlayer.h"

#include <QApplication>

#define TEST_FILE "./test.avi"

void saveFrameInfo(AVFrame *frame,
                                const QString &filename,
                                int width,
                                int height)
{
        FILE *out;
        int y = 0;

        out = fopen(qPrintable(filename), "wb");

        fprintf(out, "P6\n%d %d\n255\n", width, height);
        for (y = 0; y < height; y++) {
                fwrite(frame->data[0] + y *frame->linesize[0],
                                1,
                                width * 3,
                                out);
        }

        fclose(out);
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    av_register_all();
    DataSource d(TEST_FILE);

    if (!d.open()) {
        qDebug("can not open data source.");
        return -1;
    }

    DataCacher cacher(&d, 20);
    cacher.start();
    qDebug("read");

    SimplePlayer player(&d, &cacher);
    player.show();
    player.play();

    qDebug("readend");
    app.exec();
    return 0;
}

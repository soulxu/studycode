#include <QtGui/QApplication>
#include "widget.h"
#include "VideoSource.h"

#define DEVICE "/dev/video0"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    VideoSource source(640, 480);
    if (!source.openDevice(DEVICE)) {
        qDebug("can not open device to exit app.");
        exit(-1);
    }

    source.start();
    Widget w;
    QObject::connect(&source, SIGNAL(receiveFrame(Buffer *)), &w, SLOT(processFrame(Buffer *)));
    w.show();
    return app.exec();
}

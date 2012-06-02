#include <QtGui/QApplication>
#include "widget.h"
#include "TpListener.h"
#include "TipWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TpListener listener;
    listener.initConnection();
    TipWidget tip("Soulxu", "This is a test message!");
    tip.show();
    return a.exec();
}

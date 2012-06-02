#include <QtGui/QApplication>
#include <TelepathyQt4/Debug>
#include <TelepathyQt4/Constants>
#include <TelepathyQt4/Types>

#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tp::registerTypes();
//    Tp::enableDebug(true);
//    Tp::enableWarnings(true);

    Widget w;
    w.show();

    return a.exec();
}

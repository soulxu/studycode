#include <QApplication>

#include "CarInterface.h"
#include "Test.h"
int main(int argc, char **argv) {
	QApplication app(argc, argv);
        qRegisterMetaType<DoubleInt>("DoubleInt");
        qRegisterMetaType<DoubleIntList>("DoubleIntList");

	qDBusRegisterMetaType<StringMapList>();
	qDBusRegisterMetaType<Map>();
        qDBusRegisterMetaType<DoubleInt>();
        qDBusRegisterMetaType<DoubleIntList>();

        CarInterface *interface = new CarInterface("com.soulxu.qtdbus",
                                                   "/com/soulxu/qtdbus/car",
                                                   QDBusConnection::sessionBus());
        Test *t = new Test();
        QObject::connect(interface, SIGNAL(stoped(DoubleIntList)), t, SLOT(test()));

        QDBusPendingReply<DoubleIntList> reply = interface->test1();

        reply.waitForFinished();

        DoubleIntList val = reply.value();

        //qDebug("%d, %d", val.i1, val.i2);

	if (!reply.isValid()) {
		qDebug("reply is invaild: %s.", qPrintable(reply.error().message()));
		exit(1);
	}

        qDebug("%d", val.size());

	return app.exec();
}

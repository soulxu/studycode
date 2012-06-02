#include <QApplication>
#include <QtDBus>

#include "CarAdaptor.h"
#include "Car.h"

int main(int argc, char **argv) {
        QApplication app(argc, argv);
        qRegisterMetaType<DoubleInt>("DoubleInt");
        qRegisterMetaType<DoubleIntList>("DoubleInt");
        qDBusRegisterMetaType<StringMapList>();
        qDBusRegisterMetaType<Map>();
        qDBusRegisterMetaType<DoubleInt>();
        qDBusRegisterMetaType<DoubleIntList>();
	QDBusConnection conn = QDBusConnection::sessionBus();
        Car car;
        CarAdaptor *adaptor = new CarAdaptor(&car);
	conn.registerService("com.soulxu.qtdbus");
        conn.registerObject("/com/soulxu/qtdbus/car", &car);
	return app.exec();
}

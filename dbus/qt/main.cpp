#include <QCoreApplication>
#include <QDBusConnection>

#include "CarAdaptor.h"

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	CarAdaptor *adp = new CarAdaptor(&app);
	QDBusConnection::sessionBus().registerService("com.soulxu.dbus.qt");
	QDBusConnection::sessionBus().registerObject("/com/soulxu/dbus/qt", &app);
	return app.exec();
}

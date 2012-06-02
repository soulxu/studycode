#include "CustomType.h"
/*
QDBusArgument& operator<<(QDBusArgument &arg, const StringMapList &s) {
	return operator<<(arg, (QList< QMap<QString, QString> >)s);
}
*/

QDBusArgument& operator<<(QDBusArgument& arg, const DoubleInt& s) {
    arg.beginStructure();
    arg << s.i1 << s.i2;
    arg.endStructure();
    return arg;
}

const QDBusArgument& operator>>(const QDBusArgument& arg, DoubleInt& s) {
    arg.beginStructure();
    arg >> s.i1 >> s.i2;
    arg.endStructure();
    return arg;
}

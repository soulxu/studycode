#ifndef _CUSTOM_TYPE_H_
#define _CUSTOM_TYPE_H_

#include <QList>
#include <QMap>
#include <QString>
#include <QtDBus>

typedef QMap<QString, QString> Map;
typedef QList< Map > StringMapList;

Q_DECLARE_METATYPE(StringMapList)
//QDBusArgument& operator<<(QDBusArgument&, StringMapList&);

Q_DECLARE_METATYPE(Map)

class DoubleInt {
public:
    int i1;
    int i2;
};

Q_DECLARE_METATYPE(DoubleInt);

typedef QList<DoubleInt> DoubleIntList;

Q_DECLARE_METATYPE(DoubleIntList);

QDBusArgument& operator<<(QDBusArgument&, const DoubleInt&);
const QDBusArgument& operator>>(const QDBusArgument&, DoubleInt&);

/*
class StringMapList : QObject {
	Q_OBJECT
public:
}
*/
#endif

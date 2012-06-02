#include "Car.h"

StringMapList Car::speed(int i) {
    StringMapList list;
    QMap<QString, QString> map;
    map.insert("aa", "bb");
    list.append(map);
    return list;
}

int Car::startup() {
    return 33;
}

DoubleInt Car::test() {
    qDebug("test");
    DoubleInt ret;
    ret.i1 = 11;
    ret.i2 = 22;
    return ret;
}

DoubleIntList Car::test1() {
    qDebug("test1");
    DoubleIntList ret;
    DoubleInt i;
    i.i1 = 22;
    i.i2 = 33;

    ret.append(i);
    return ret;
}

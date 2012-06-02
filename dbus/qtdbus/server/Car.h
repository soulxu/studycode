#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <../CustomType.h>

class Car : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE int startup();
    Q_INVOKABLE StringMapList speed(int i);
    Q_INVOKABLE DoubleInt test();
    Q_INVOKABLE DoubleIntList test1();
};

#endif // CAR_H

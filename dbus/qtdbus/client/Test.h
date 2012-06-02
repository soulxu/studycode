#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test : public QObject {
    Q_OBJECT
public slots:
    void test() {
        qDebug("test slot");
    }

};

#endif // TEST_H

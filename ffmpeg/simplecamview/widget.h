#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>

#include "VideoSource.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void processFrame(Buffer *buf);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_imgBuf;
};

#endif // WIDGET_H

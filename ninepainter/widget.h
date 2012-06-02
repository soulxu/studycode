#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>

class SkinPainter;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    SkinPainter *m_skin;
};

#endif // WIDGET_H

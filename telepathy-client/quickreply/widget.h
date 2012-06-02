#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QPropertyAnimation>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void initOpaciteAnimation();

protected:
    virtual void showEvent(QShowEvent *event);

private:
    QPropertyAnimation *m_anWidgetOp;
    QPropertyAnimation *m_anMsg;
};

#endif // WIDGET_H

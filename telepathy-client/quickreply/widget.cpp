#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->initOpaciteAnimation();
}

void Widget::initOpaciteAnimation() {
    //this->setFixedSize(0, 0);
    this->setWindowOpacity(1.0);
    this->m_anWidgetOp->setTargetObject(this);
    this->m_anWidgetOp->setPropertyName("windowOpacity");
    this->m_anWidgetOp->setDuration(5000);
    this->m_anWidgetOp->setStartValue(1.0);
    this->m_anWidgetOp->setEndValue(0);
}

Widget::~Widget()
{

}

void Widget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    this->m_anWidgetOp->start();
}

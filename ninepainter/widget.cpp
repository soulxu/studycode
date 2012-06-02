#include "widget.h"

#include "SkinPainter.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_skin = new SkinPainter(8, 8, 8, 8, QPixmap("/home/soulxu/2011_1_10/images/PlayMusic-slider-bg.png"));

}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setBrush(QBrush(QColor(0, 0, 0)));
    p.drawRect(0, 0, this->width(), this->height());
    m_skin->draw(100, 100, 500, 500, p);
}

Widget::~Widget()
{

}

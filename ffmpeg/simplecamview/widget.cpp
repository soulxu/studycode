#include "widget.h"

#include <QPainter>

#include <stdio.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

}

Widget::~Widget()
{

}

void Widget::processFrame(Buffer *buf) {
//        static int i = 0;
//        char filename[4096] = {0};
//        sprintf(filename, "out/frame%d.jpg", i);
//
//        FILE *out = fopen(filename, "wb");
//
//        //fprintf(out, "P6\n%d %d\n255\n",640, 480);
//
//        fwrite(buf->start, 1, buf->length, out);
//        fclose(out);
//        i++;
    m_imgBuf.loadFromData((const uchar *)buf->start, buf->length, "JPG");
    this->update();
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_imgBuf);
}

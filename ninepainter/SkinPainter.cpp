#include "SkinPainter.h"

SkinPainter::SkinPainter(int top, int bottom, int left, int right, QPixmap source) :
        m_top(top),
        m_bottom(bottom),
        m_left(left),
        m_right(right),
        m_source(source)
{

}

void SkinPainter::draw(int x, int y, int w, int h, QPainter &painter) {
    QRect rect1(0, 0, m_left, m_top);
    QRect rect2(m_left, 0, m_source.width() - m_left - m_right, m_top);
    QRect rect3(m_source.width() - m_right, 0, m_right, m_top);

    QRect rect4(0, m_top, m_left, m_source.height() - m_top - m_bottom);
    QRect rect5(m_left, m_top, m_source.width() - m_left - m_right, m_source.height() - m_top - m_bottom);
    QRect rect6(m_source.width() - m_right, m_top, m_right, m_source.height() - m_top - m_bottom);

    QRect rect7(0, m_source.height() - m_bottom, m_left, m_bottom);
    QRect rect8(m_left, m_source.height() - m_bottom, m_source.width() - m_left - m_right, m_bottom);
    QRect rect9(m_source.width() - m_right, m_source.height() - m_bottom, m_right, m_bottom);

    QPixmap p1 = m_source.copy(rect1);
    QPixmap p2 = m_source.copy(rect2);
    QPixmap p3 = m_source.copy(rect3);

    QPixmap p4 = m_source.copy(rect4);
    QPixmap p5 = m_source.copy(rect5);
    QPixmap p6 = m_source.copy(rect6);

    QPixmap p7 = m_source.copy(rect7);
    QPixmap p8 = m_source.copy(rect8);
    QPixmap p9 = m_source.copy(rect9);

    painter.drawPixmap(x, y, p1);
    qDebug("+x = %d, y = %d", x, y);
    //p2 = p2.scaledToWidth(w - p1.width() - p3.width());
    for (int i = 0; i < w - p1.width() - p3.width(); i += p2.width()) {
        qDebug("x = %d, y = %d", x + p1.width() + i, y);
        painter.drawPixmap(x + p1.width() + i, y, p2);
    }
    qDebug("-x = %d, y = %d", x + w - p3.width(), y);
    painter.drawPixmap(x + w - p3.width(), y, p3);
/*
    p4 = p4.scaledToHeight(h - p1.height() - p7.height());
    painter.drawPixmap(x, y + p1.height(), p4);
    p5 = p5.scaledToWidth(w - p1.width() - p3.width());
    p5 = p5.scaledToHeight(h - p1.height() - p7.height());
    painter.drawPixmap(x + p4.width(), y + p1.height(), p5);
    p6 = p6.scaledToHeight(h - p1.height() - p7.height());
    painter.drawPixmap(x + p4.width() + p5.width(), y + p3.height(), p6);

    painter.drawPixmap(x, y + p1.height() + p4.height(), p7);
    p8 = p8.scaledToWidth(w - p1.width() - p3.width());
    p8 = p8.scaledToHeight(h - p1.height() - p7.height());
    painter.drawPixmap(x + p7.width(), y + p2.height() + p5.height(), p8);
    painter.drawPixmap(x + p7.width() + p8.width(), y + p3.height() + p6.height(), p9);
    */
}

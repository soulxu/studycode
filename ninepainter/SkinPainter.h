#ifndef SKINPAINTER_H
#define SKINPAINTER_H

#include <QPixmap>
#include <QPainter>

class SkinPainter {
public:
    SkinPainter(int top, int bottom, int left, int right, QPixmap source);

    void draw(int x, int y, int w, int h, QPainter &painter);

private:
    int m_top;
    int m_bottom;
    int m_left;
    int m_right;
    QPixmap m_source;
};

#endif // SKINPAINTER_H

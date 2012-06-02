#ifndef RECT_H
#define RECT_H

#include <QGraphicsRectItem>

class QPropertyAnimation;
class QStateMachine;

class Rect : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ rect WRITE setRect NOTIFY rectChange)

public:
    Rect(QGraphicsItem *parent = NULL);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void rectChange();
    void rectDragStart();
    void rectDragEnd();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void updatePosition(Rect *rect);

private slots:
    void slRectChange();

private:
    bool m_enterDrag;
    int m_x;
    int m_y;
    QRectF m_lastRect;
    QPropertyAnimation *m_rectUpAn;
    QPropertyAnimation *m_rectDownAn;
    QStateMachine *m_mainStatus;
};

#endif // RECT_H

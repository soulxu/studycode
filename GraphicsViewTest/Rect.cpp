#include "Rect.h"

#include <QPainter>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>

Rect::Rect(QGraphicsItem *parent) :  m_x(0), m_y(0), QGraphicsRectItem(parent) {
    this->setRect(m_x, m_y, 100, 100);
    this->setAcceptDrops(true);
    QObject::connect(this, SIGNAL(rectChange()), this, SLOT(slRectChange()));
    this->m_rectUpAn = new QPropertyAnimation(this, "rect"); // the animation will change rect and emit rectChange signal
    this->m_rectDownAn = new QPropertyAnimation(this, "rect");

    this->m_rectUpAn->setDuration(150);
    this->m_rectUpAn->setStartValue(this->rect()); // animation start point
    this->m_rectUpAn->setKeyValueAt(0.7, QRectF(-6, -6, 120, 120)); // animation end point
    this->m_rectUpAn->setEndValue(QRectF(-3, -3, 110, 110));

    this->m_rectDownAn->setDuration(150);;
    this->m_rectDownAn->setStartValue(this->rect());
    this->m_rectDownAn->setEndValue(QRectF(0, 0, 100, 100));

    this->m_mainStatus = new QStateMachine(this);
    QState *rectDragStart = new QState(this->m_mainStatus);
    QState *rectDragEnd = new QState(this->m_mainStatus);

    QSignalTransition *transition = rectDragStart->addTransition(this, SIGNAL(rectDragStart()), rectDragEnd);
    transition->addAnimation(this->m_rectUpAn);

    transition = rectDragEnd->addTransition(this, SIGNAL(rectDragEnd()), rectDragStart);
    transition->addAnimation(this->m_rectDownAn);

    this->m_mainStatus->addState(rectDragStart);
    this->m_mainStatus->addState(rectDragEnd);
    this->m_mainStatus->setInitialState(rectDragStart);

    this->m_mainStatus->start();

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFlag(QGraphicsItem::ItemAcceptsInputMethod, true);
}

void Rect::slRectChange() {
    qDebug("rectchange");
    this->update();
}

void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        painter->eraseRect(this->m_lastRect);
        QBrush brush;
        brush.setColor(QColor(50, 50, 50));
        painter->setBrush(brush);
        painter->fillRect(this->rect(), Qt::SolidPattern);
}

void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit rectDragStart();
    }

    QGraphicsRectItem::mousePressEvent(event);
}

void Rect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit rectDragEnd();
    }

    QGraphicsRectItem::mouseReleaseEvent(event);
}

void Rect::updatePosition(Rect *rect) {
    QRectF intersected = this->rect().intersected(rect->rect());

    if (intersected.width() >= intersected.height()) {
        if (this->x() == intersected.x()) {
            this->setX(this->x() + intersected.width());
        }
        else {
            this->setX(this->x() - intersected.width());
        }
    }
    else {
        if (this->y() == intersected.y()) {
            this->setY(this->y() + intersected.height());
        }
        else {
            this->setY(this->y() - intersected.height());
        }
    }
}

void Rect::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    /*
        this->m_lastRect = this->rect();
        qDebug("button: %f,%f", event->buttonDownScenePos(Qt::LeftButton).x(), event->buttonDownScenePos(Qt::LeftButton).y());
        qDebug("last: %f, %f", event->lastScenePos().x(), event->lastScenePos().y());
        qDebug("just: %f, %f", event->screenPos().x(), event->screenPos().y());
        this->setX(this->x() + event->scenePos().x() - event->lastScenePos().x());
        this->setY(this->y() + event->scenePos().y() - event->lastScenePos().y());
        */
        QList<QGraphicsItem *> items = this->collidingItems();

        for (int i = 0; i < items.size(); i++) {
            ((Rect *)items.at(i))->updatePosition(this);
        }

        this->update();

    QGraphicsRectItem::mouseMoveEvent(event);
}

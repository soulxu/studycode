#include "TipWidget.h"

#include <QPainter>
#include <QRect>
#include <QLineEdit>

TipWidget::TipWidget(const QString &title, const QString &msg) : m_msg(msg), m_title(title) {
    this->move(0, 100);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->initAnWidgetOp();

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QColor(255, 142, 0));
    this->setPalette(palette);

    this->m_edit = new QLineEdit(this);
    this->m_edit->move(20, 60);
    this->setWindowOpacity(0.95);
}

void TipWidget::initAnWidgetOp() {
    this->m_anWidgetOp = new QPropertyAnimation(this, "size");
    this->m_anWidgetOp->setDuration(500);
    this->m_anWidgetOp->setStartValue(QSize(0, 60));
    this->m_anWidgetOp->setEndValue(QSize(200, 100));
}

void TipWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    this->m_anWidgetOp->start();
}

void TipWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QWidget::paintEvent(event);
    QRect titleRect = this->geometry();
    titleRect.setX(10);
    titleRect.setY(20);
    titleRect.setWidth(this->width());
    titleRect.setHeight(this->height());

    QRect msgRect = this->geometry();
    msgRect.setX(10);
    msgRect.setY(35);
    msgRect.setWidth(this->width());
    msgRect.setHeight(this->height());

    painter.drawText(titleRect, this->m_title);
    painter.drawText(msgRect, this->m_msg);
}

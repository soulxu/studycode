#ifndef TIPWIDGET_H
#define TIPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class QLineEdit;

class TipWidget : public QWidget {
    Q_OBJECT
public:
    TipWidget(const QString &title, const QString &msg);

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    void initAnWidgetOp();

private:
    QPropertyAnimation *m_anWidgetOp;
    QString m_msg;
    QString m_title;
    QLineEdit *m_edit;
};

#endif // TIPWIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/ConnectionManager>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void accountCreated(const QString &path);
    void accountManagerReady(Tp::PendingOperation *op);
    void cmReady(Tp::PendingOperation *op);
    void cnReady(Tp::PendingOperation *op);
    void cnConnected(Tp::PendingOperation *op);

private:
    Tp::AccountManagerPtr m_AmPtr;
    Tp::ConnectionManagerPtr m_CmPtr;
};

#endif // WIDGET_H

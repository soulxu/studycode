#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QObject>
#include <TelepathyQt4/Connection>

class ConnectionListener : public QObject {
    Q_OBJECT
public:
    ConnectionListener(Tp::ConnectionPtr ptr, QObject *object);

private slots:
    void statusChanged(Tp::Connection::Status newStatus, Tp::ConnectionStatusReason reason);

private:
    Tp::ConnectionPtr m_ptr;
};

#endif // CONNECTIONLISTENER_H

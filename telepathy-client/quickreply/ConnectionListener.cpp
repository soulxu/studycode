#include "ConnectionListener.h"

ConnectionListener::ConnectionListener(Tp::ConnectionPtr ptr, QObject *object) : QObject(object), m_ptr(ptr) {
    QObject::connect(ptr.data(), SIGNAL(statusChanged(Tp::Connection::Status,Tp::ConnectionStatusReason)),
                     this, SLOT(statusChanged(Tp::Connection::Status, Tp::ConnectionStatusReason)));
}

void ConnectionListener::statusChanged(Tp::Connection::Status newStatus, Tp::ConnectionStatusReason) {
    switch (newStatus) {
    case Tp::Connection::StatusDisconnected:
            qDebug("ConnectionListener StatusDisconnected");
            break;
    case Tp::Connection::StatusConnecting:
            qDebug("ConnectionListener StatusConnecting");
        break;
    case Tp::Connection::StatusConnected:
                qDebug("ConnectionListener StatusConnected");
        break;
    case Tp::Connection::StatusUnknown:
                qDebug("ConnectionListener StatusUnknown");
        break;
    }
}

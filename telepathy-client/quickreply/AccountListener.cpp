#include "AccountListener.h"

#include <TelepathyQt4/PendingReady>

using namespace Tp;

AccountListener::AccountListener(AccountPtr ptr) : m_accPtr(ptr) {
    QObject::connect(ptr.data()->becomeReady(), SIGNAL(finished(Tp::PendingOperation *)), this, SLOT(accountReady(Tp::PendingOperation *)));

    QObject::connect(m_accPtr.data(), SIGNAL(statusChanged(Tp::ConnectionStatus,
                                                                Tp::ConnectionStatusReason,
                                                                const QString &, const QVariantMap &)),
                     this, SLOT(statusChanged(Tp::ConnectionStatus,
                                              Tp::ConnectionStatusReason,
                                              const QString &, const QVariantMap &)));
}

void AccountListener::accountReady(Tp::PendingOperation *op) {
    QObject::connect(this->m_accPtr.data(), SIGNAL(currentPresenceChanged(const Tp::SimplePresence &)), this, SLOT(accountPresenceChanged(const Tp::SimplePresence &)));
}

void AccountListener::accountPresenceChanged(const Tp::SimplePresence &presence) {
    qDebug("Presence change: %s - %s", qPrintable(presence.status), qPrintable(presence.statusMessage));
}

void AccountListener::statusChanged(Tp::ConnectionStatus status,
                                         Tp::ConnectionStatusReason statusReason,
                                         const QString &error, const QVariantMap &errorDetails) {
    switch (status) {
    case Tp::Connection::StatusDisconnected:
            qDebug("ConnectionListener StatusDisconnected");
            break;
    case Tp::Connection::StatusConnecting:
            qDebug("ConnectionListener StatusConnecting");
            PendingChannelRequest *requset = this->m_accPtr->ensureTextChat("wj2007002@gmail.com");
            if (request != NULL) {
                QObject::connect(request, SIGNAL(channelRequestCreated(const Tp::ChannelRequestPtr)), this, SLOT(channelRequestCreated(const Tp::ChannelRequestPtr)));
            }

        break;
    case Tp::Connection::StatusConnected:
                qDebug("ConnectionListener StatusConnected");
        break;
    case Tp::Connection::StatusUnknown:
                qDebug("ConnectionListener StatusUnknown");
        break;
    }
}

void AccountListener::channelRequestCreated(const Tp::ChannelRequestPtr request) {

}

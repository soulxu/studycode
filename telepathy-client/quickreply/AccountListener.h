#ifndef ACCOUNTLISTENER_H
#define ACCOUNTLISTENER_H

#include <QObject>
#include <TelepathyQt4/Account>
//#include <ConnectionListener.h>

class AccountListener : public QObject {
    Q_OBJECT
public:
    AccountListener(Tp::AccountPtr ptr);

private slots:
    void accountReady(Tp::PendingOperation *op);
    void accountPresenceChanged(const Tp::SimplePresence &presence);
    void statusChanged(Tp::ConnectionStatus status,
                Tp::ConnectionStatusReason statusReason,
                const QString &error, const QVariantMap &errorDetails);


    void channelRequestCreated(const Tp::ChannelRequestPtr request);
private:
    Tp::AccountPtr m_accPtr;
    //ConnectionListener *m_connListener;
};

#endif // ACCOUNTLISTENER_H

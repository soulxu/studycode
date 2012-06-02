#ifndef TPLISTENER_H
#define TPLISTENER_H

#include <TelepathyQt4/AccountManager>
#include <QString>
#include <QList>

class AccountListener;

class TpListener : public QObject {
    Q_OBJECT
public:
    void initConnection();

private slots:
    void accountCreated(const QString &path);
    void accountManagerReady(Tp::PendingOperation *op);

private:
    Tp::AccountManagerPtr m_amPtr;
    QList<AccountListener *> m_accountPtrs;
};

#endif // TPLISTENER_H

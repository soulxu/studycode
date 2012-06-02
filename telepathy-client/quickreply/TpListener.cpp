#include "TpListener.h"

#include <TelepathyQt4/PendingReady>
#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/PendingAccount>

#include "AccountListener.h"

using namespace Tp;

void TpListener::initConnection() {
    this->m_amPtr = AccountManager::create();
    QObject::connect(this->m_amPtr.data(), SIGNAL(accountCreated(QString)), this, SLOT(accountCreated(QString)));
    QObject::connect(this->m_amPtr->becomeReady(), SIGNAL(finished(Tp::PendingOperation *)), this, SLOT(accountManagerReady(Tp::PendingOperation *)));
}


void TpListener::accountCreated(const QString &path) {
    qDebug("account created: %s", qPrintable(path));
}

void TpListener::accountManagerReady(Tp::PendingOperation *op) {
    qDebug("Account Manager Ready");
    QStringList accountPaths = this->m_amPtr->validAccountPaths();
    AccountPtr ptr;

    for (int i = 0; i < accountPaths.size(); i++) {
        qDebug("Valid Account Path: %s", qPrintable(accountPaths.at(i)));
        ptr = Account::create(this->m_amPtr->dbusConnection(), this->m_amPtr->busName(), accountPaths.at(i));
        AccountListener *l = new AccountListener(ptr);
        this->m_accountPtrs.append(l);
    }
}


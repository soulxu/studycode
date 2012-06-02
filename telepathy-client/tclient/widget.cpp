#include "widget.h"

#include <QList>

#include <TelepathyQt4/PendingConnection>
#include <TelepathyQt4/PendingReady>

using namespace Tp;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->m_AmPtr = AccountManager::create();
    QObject::connect(this->m_AmPtr.data(), SIGNAL(accountCreated(const QString &)), this, SLOT(accountCreated(const QString &)));

    QList<AccountPtr> accountList = this->m_AmPtr->allAccounts();
    QStringList valist = this->m_AmPtr->validAccountPaths();
    qDebug("ttest: %d", valist.size());

    for (int i = 0; i < valist.size(); i++) {
        qDebug("ttest:accout: %s", qPrintable(valist.at(i)));
    }

    this->m_CmPtr = ConnectionManager::create("gabble");

    QObject::connect(this->m_CmPtr->becomeReady(), SIGNAL(finished(Tp::PendingOperation *)), this, SLOT(cmReady(Tp::PendingOperation *)));

}

Widget::~Widget()
{

}

void Widget::cmReady(Tp::PendingOperation *op) {
    QVariantMap params;

    params.insert("account", "soulxu@gmail.com");
    params.insert("password", "Soulxu#6235891");

    PendingConnection *pconn = this->m_CmPtr->requestConnection("jabber", params);
    QObject::connect(pconn, SIGNAL(finished(Tp::PendingOperation *)), SLOT(cnReady(Tp::PendingOperation *)));

}

void Widget::cnReady(Tp::PendingOperation *op) {
    PendingConnection *pconn = qobject_cast<PendingConnection *>(op);

    ConnectionPtr conn = pconn->connection();

    QObject::connect(conn->requestConnect(), SIGNAL(finished(Tp::PendingOperation *)), this, SLOT(cnConnected(Tp::PendingOperation *)));

}

void Widget::cnConnected(Tp::PendingOperation *op) {
    Tp::PendingReady *conn = qobject_cast<Tp::PendingReady *>(op);
    conn->blockSignals()
}

void Widget::accountManagerReady(Tp::PendingOperation *op) {
    QStringList apath = this->m_AmPtr->allAccountPaths();

    for (int i = 0; i < apath.size(); i++) {
        qDebug("ttest: %s", qPrintable(apath.at(i)));
    }
}

void Widget::accountCreated(const QString &path) {
    qDebug("ttest: accountcreated: %s", qPrintable(path));

}

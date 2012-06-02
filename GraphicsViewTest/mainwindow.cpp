#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QToolBar>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QHBoxLayout>
#include <QPropertyAnimation>

#include <QApplication>

#include "Rect.h"

//#include "CustomItem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createUI();
}

void MainWindow::createUI() {
    this->m_mainBar = new QMenuBar(this);
    this->m_statusBar = new QStatusBar(this);

    this->setMenuBar(this->m_mainBar);
    this->setStatusBar(this->m_statusBar);

    QMenu *fileMenu = this->m_mainBar->addMenu("&File");
    QAction *exitAct = fileMenu->addAction("&Exit");

    QObject::connect(exitAct, SIGNAL(triggered()), this, SLOT(slMenuExit()));

    QMenu *helpMenu = this->m_mainBar->addMenu("&Help");
    helpMenu->addAction("&About");

    this->m_layout = new QHBoxLayout();
    QWidget *widget = new QWidget(this);

    this->setCentralWidget(widget);
    widget->setLayout(this->m_layout);

    this->m_mainView = new QGraphicsView(this);
    this->m_secView = new QGraphicsView(this);

    QTransform transform;
    transform.rotate(20);

    this->m_secView->setTransform(transform);
    this->m_layout->addWidget(this->m_mainView);
    this->m_layout->addWidget(this->m_secView);

    this->m_mainToolBar = this->addToolBar("");
    this->m_mainToolBar->addAction("Rect", this, SLOT(addRect()));

    this->m_mainSence = new QGraphicsScene(this->m_mainView);

    this->m_mainView->setScene(this->m_mainSence);
    this->m_secView->setScene(this->m_mainSence);
    this->setFixedSize(500, 500);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slMenuExit() {
    qApp->exit(0);
}

void MainWindow::addRect() {
    qDebug("addRect");
    //QGraphicsItem *newItem = new CustomItem();
    //newItem->setPos(0, 0);
    //this->m_mainSence->addItem(newItem);
}

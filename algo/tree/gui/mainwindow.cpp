#include "mainwindow.h"

#include <../node.h>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (int i = 0; i < m_painters.size(); i++) {
        this->m_painters.at(i)->paint(&painter);
    }
}

void MainWindow::addTreePainter(TreePainter<int> *painter) {
    this->m_painters.append(painter);
}

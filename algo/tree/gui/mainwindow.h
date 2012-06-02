#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "TreePainter.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addTreePainter(TreePainter<int> *painter);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QList<TreePainter<int> *>  m_painters;
    QGraphicsView m_view;
    QGraphicsScene m_scene;
};

#endif // MAINWINDOW_H

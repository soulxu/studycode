#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QMenuBar;
class QStatusBar;
class QGraphicsView;
class QToolBar;
class QGraphicsScene;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createUI();

private slots:
    void slMenuExit();
    void addRect();

private:
    QMenuBar *m_mainBar;
    QStatusBar *m_statusBar;
    QGraphicsView *m_mainView;
    QToolBar *m_mainToolBar;
    QGraphicsScene *m_mainSence;
    QGraphicsView *m_secView;
    QHBoxLayout *m_layout;

};

#endif // MAINWINDOW_H

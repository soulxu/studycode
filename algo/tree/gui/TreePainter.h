#ifndef TREEPAINTER_H
#define TREEPAINTER_H

#include <../node.h>
#include <QRect>
#include <QPainter>

#include <math.h>

template <class T>
class TreePainter {
public:
    TreePainter(Node<T> *tree);
    TreePainter(Node<T> *tree, int x, int y, int width, int height);

    void setX(int x);
    void setY(int y);

    void setWidth(int width);
    void setHeight(int height);

    void paint(QPainter *painter) const;

    void setTree(Node<T> *tree);
    Node<T> *getTree() const;

private:
    void drawNode(QPainter *painter, T t, int x, int y) const;
    void drawTree(QPainter *painter, Node<T> *node, int x, int y) const;

private:
    Node<T> *m_tree;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

template <class T>
void TreePainter<T>::setWidth(int width) {
    m_width = width;
}

template <class T>
void TreePainter<T>::setHeight(int height) {
    m_height = height;
}

template <class T>
void TreePainter<T>::setTree(Node<T> *tree) {
    this->m_tree = tree;
}

template <class T>
Node<T> *TreePainter<T>::getTree() const {
    return m_tree;
}

template <class T>
TreePainter<T>::TreePainter(Node<T> *tree) :
    m_tree(tree),
    m_x(0),
    m_y(0),
    m_width(5),
    m_height(30)
{

}

template <class T>
TreePainter<T>::TreePainter(Node<T> *tree, int x, int y, int width, int height) :
    m_tree(tree),
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{

}

template <class T>
void TreePainter<T>::drawTree(QPainter *painter, Node<T> *node, int x, int y) const {
    if (node == NULL) {
        qDebug("the node is null");
        return;
    }

    qDebug("%d", node->getHeight());
    int i = pow(2, node->getHeight() - 1);

    if (node->getLeft() != NULL) {
        painter->drawLine(x, y, x - m_width * i, y + m_height);
        this->drawTree(painter, node->getLeft(), x - (m_width * i), y + m_height);
    }

    if (node->getRight() != NULL) {
        painter->drawLine(x, y, x + m_width * i, y + m_height);
        this->drawTree(painter, node->getRight(), x + (m_width * i), y + m_height);
    }

    this->drawNode(painter, node->getValue(), x, y);
}

template <class T>
void TreePainter<T>::setX(int x) {
    this->m_x = x;
}

template <class T>
void TreePainter<T>::setY(int y) {
    this->m_y = y;
}

template <class T>
void TreePainter<T>::paint(QPainter *painter) const {
    if (m_tree != NULL) {
        this->drawTree(painter, this->m_tree, m_x, m_y);
    }
}

template <class T>
void TreePainter<T>::drawNode(QPainter *painter, T t, int x, int y) const {
    QBrush brush;
    QPen pen;
    pen.setColor(QColor(0, 0, 0));

    brush.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setPen(pen);
    QRect rect;
    rect.setX(x - 10);
    rect.setY(y - 10);
    rect.setWidth(20);
    rect.setHeight(20);

    QPointF point(x, y);
    painter->drawEllipse(point, 10, 10);
    painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(t));
}


#endif // TREEPAINTER_H

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <../node.h>
#include <../search_tree.h>
#include <../search_tree_f.h>

#include <../avl_tree.h>

#include "TreePainter.h"

void createNode(Node<int> *n) {
    int r = random() % 100;

    qDebug("%d", r);
    Node<int> *child = new Node<int>(r);

    if ((r % 2) == 0) {
        n->setLeft(child);
    }
    else {
        n->setRight(child);
    }

    if (r == 0) {
        return;
    }

    createNode(child);
}

Node<int> *createTree() {
    Node<int> *n = new Node<int>(1);
    //createNode(n);
    n->setLeft(new Node<int>(2));
    n->setRight(new Node<int>(3));
    n->getLeft()->setRight(new Node<int>(4));
    n->getLeft()->setLeft(new Node<int>(5));
    n->getLeft()->getRight()->setRight(new Node<int>(6));
    n->getRight()->setLeft(new Node<int>(7));
    n->getRight()->getLeft()->setLeft(new Node<int>(9));
    n->getRight()->setRight(new Node<int>(8));
    return n;
}

Node<int> *createSearchTree(SearchTree<int> **tree) {

    int n = random() % 10;

    *tree = new SearchTree<int>(n);

    for (int i = 0; i < 10; i++) {
        n = random() % 10;
        (*tree)->insert(n);
    }

    return (*tree)->getRoot();
}

Node<int> *createAVLTree(AVLTree<int> **tree) {

    int n = random() % 20;

    *tree = new AVLTree<int>();

    for (int i = 0; i < 20; i++) {
        n = random() % 20;
        (*tree)->insert(n);
        qDebug("insert: %d", n);
    }

    return (*tree)->getRoot();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //AVLTree<int> *tree = NULL;
    //Node<int> *root = createAVLTree(&tree);

    SearchTreeF<int> *st = new SearchTreeF<int>();
    st->insert(2);
    st->insert(1);
    st->insert(3);
    st->insert(4);

    qDebug("Min %d", st->findMin()->getValue());
    qDebug("Max %d", st->findMax()->getValue());
    qDebug("Find %d", st->find(3)->getValue());
    qDebug("Contain: %d", st->contain(4));

    TreePainter<int> painter(st->getRoot(), 300, 100, 5, 30);

    SearchTreeF<int> st2 = *st;
    st2.remove(3);
    TreePainter<int> painter2(st2.getRoot(), 500, 100, 5, 30);

    MainWindow w;
    w.addTreePainter(&painter);
    w.addTreePainter(&painter2);
    w.show();

    //qDebug("contain: %d", tree->contain(10));
    return a.exec();
}

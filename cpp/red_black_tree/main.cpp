#include <QCoreApplication>
#include "rbtree.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    //return a.exec();
    vector<int> v;
    v.push_back(10);
    v.push_back(6);
    v.push_back(11);
    v.push_back(3);
    v.push_back(5);
    //v.push_back(1);
    RBTree * T = new RBTree(v);
    T->preOrder();
    T->inOrder();
    T->rotateRight();
    T->preOrder();
    T->inOrder();
    delete T;
    return 0;
}

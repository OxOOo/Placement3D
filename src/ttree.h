#ifndef T_TREE_H
#define T_TREE_H

#include "box.h"

class TTreeNode
{
public:
    TTreeNode();
    ~TTreeNode();
};

class TTree
{
public:
    TTree(const BoxList &boxes);
    ~TTree();
};

#endif // T_TREE_H

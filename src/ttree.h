#ifndef T_TREE_H
#define T_TREE_H

#include "box.h"

#include <vector>

class TTreeNode
{
public:
    TTreeNode();
    ~TTreeNode();

    PlacedBox box;
    TTreeNode *l, *m, *r, *fa;
};

class TTree
{
public:
    enum SonType{Left = 0, Mid, Right};

    TTree(const BoxList &boxes);
    ~TTree();

    /// Delete the box p
    void Delete(int p);

    /// Insert the box p as box q's child
    void InsertAsChild(int p, int q);

    /// Insert the box p to box q's place and let box q be the k-th chlid of box p
    void InsertToReplace(int p, int q, SonType k);

    /// Swap 2 boxed at T-tree
    void Swap(int p, int q);

    /// Rotation box p around the axis at direction dir
    void Rotate(int p, int dir);

    /// Get the minimum bounding box of the placement according to T-tree
    virtual int GetVolume() = 0;

    /// Get the optimal solution
    virtual Solution GetSolution() = 0;

private:
    /// size of box
    const int N;
    /// root of T-tree
    TTreeNode* root;
    /// array of T-tree nodes
    TTreeNode* nodes;

    /// Get T-tree node by box id
    TTreeNode* getNodeById(int id);
};

#endif // T_TREE_H

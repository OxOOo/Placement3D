#ifndef T_TREE_H
#define T_TREE_H

#include "box.h"
#include "solution.h"

#include <vector>
#include <cstdlib>

class TTreeNode
{
public:
    TTreeNode();
    ~TTreeNode();

    TTreeNode *l, *m, *r, *fa;
    TTreeNode *b_l, *b_r;
    PlacedBox box;

    /// Is a leaf node
    bool IsLeaf() { return l == NULL && m == NULL && r == NULL; }

    /// Copy q to p except box information
    static void Copy(TTreeNode *nodep, TTreeNode *nodeq)
    {
        nodep->l = nodeq->l;
        nodep->m = nodeq->m;
        nodep->r = nodeq->r;
        nodep->fa = nodeq->fa;
    }
};

class TTree
{
public:
    enum SonType {Left = 0, Mid, Right};

    TTree(const BoxList &boxes);
    TTree(const TTree &tree);
    virtual ~TTree();

    /// Move a box to another place randomly
    void Move();

    /// Swap 2 boxed at T-tree
    void Swap(int p, int q);

    /// Rotation box p around the axis at direction dir
    void Rotate(int p, int dir);

    /// Print the T-tree
    void Print() const { print(root); }

    /// Get the optimal solution
    virtual Solution GetSolution() = 0;

    /// Debug the solution
    void Debug();

protected:
    /// size of box
    const int N;
    /// root of T-tree
    TTreeNode* root;
    /// array of T-tree nodes
    TTreeNode* nodes;

    /// Recursive to delete the Tree Node p
    void deleteNode(TTreeNode *nodep);

    /// Delete the box p
    void deleteBox(int p);

    /// Insert the box p as box q's child
    void insertAsChild(int p, int q);

    /// Insert the box p to box q's place and let box q be the k-th chlid of box p
    void insertToReplace(int p, int q, SonType k);

    /// Recursive to print
    void print(TTreeNode* node) const;

    /// Get T-tree node by box id
    TTreeNode* getNodeById(int id) const { return &nodes[id]; }
    int getIdByNode(TTreeNode* node) const { return node == NULL ? -1 : node - nodes; }
};

#endif // T_TREE_H

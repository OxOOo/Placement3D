#ifndef T_TREE_H
#define T_TREE_H

#include "box.h"
#include "solution.h"

#include <vector>
#include <cstdlib>

/*

TTree是一颗三叉树，每一种3维箱子的放置方案，都对应一颗TTree
在TTree中如果B是A的左儿子，表示B在A箱子的上面，中儿子表示B在A箱子的左边,右儿子表示B在A箱子的右边
对于一颗TTree，我们可以通过一种方式，将它分解成若干二叉树，从而构造出该TTree对应的3维箱子的放置方案

*/

/// 一个TTreeNode表示一个Box
/// 左儿子表示在该箱子的上面
/// 中儿子表示在该箱子的左边
/// 右儿子表示在该箱子的右边
class TTreeNode
{
public:
    TTreeNode();
    ~TTreeNode();

    /// l, m, r, fa 是 TTree的左儿子，中儿子，友儿子和父亲
    TTreeNode *l, *m, *r, *fa;
    /// b_l, b_r 是从 TTree上分离出来的二叉树的左右儿子，其父亲节点和TTree一样
    TTreeNode *b_l, *b_r;
    /// 储存box的相关信息
    PlacedBox box;

    /// Is a leaf node
    bool IsLeaf() const { return l == NULL && m == NULL && r == NULL; }

    /// Is the root of T-tree
    bool IsRoot() const { return fa == NULL; }

    /// Copy q to p without box information
    static void CopyWithoutBox(TTreeNode *nodep, TTreeNode *nodeq)
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
    void deleteNode(TTreeNode *node);

    /// Delete the box p
    void deleteBox(int p);

    /// Insert the box p as box q's child
    void insertAsChild(int p, int q);

    /// Insert the box p to box q's place and let box q be the k-th chlid of box p
    void insertToReplace(int p, int q);

    /// Recursive to print
    void print(TTreeNode* node) const;

    /// Get T-tree node by box id
    TTreeNode* getNodeById(int id) const { return &nodes[id]; }
    int getIdByNode(TTreeNode* node) const { return node == NULL ? -1 : node - nodes; }
};

#endif // T_TREE_H

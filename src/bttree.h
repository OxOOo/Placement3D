#ifndef B_T_TREE_H
#define B_T_TREE_H

#include "ttree.h"

#include <vector>
#include <stack>

class BTTree : public TTree
{
public:
    BTTree(const BoxList &boxes);
    BTTree(const BTTree& tree);
    virtual ~BTTree();

    /// 继承自TTree，每次运行会重新计算方案
    /// Get the optimal solution
    Solution GetSolution() override;

private:
    /// 每次放置的时候，储存已经放置了哪些节点，每次计算方案的时候清空
    std::vector<TTreeNode*> placed_nodes;

    /// 对一颗TTree分解成一颗二叉树和若干和这个二叉树相邻的节点，相邻节点放在S中
    TTreeNode* treeDecomposition(TTreeNode* root, std::stack<TTreeNode*>& S);
    /// 对一颗二叉树的每个节点进行放置
    void binaryTreePacking(TTreeNode *root);
    /// 对单独的一个点进行放置，L里面储存该节点所属的二叉树已经放置了哪些节点
    void placeModule(TTreeNode* n, std::vector<TTreeNode*>& L);
    /// 对一颗TTree进行放置，计算方案就是调用这个函数
    void treePacking(TTreeNode* root);

    /// 判断[x1,x2]和[y1,y2]有没有重叠
    bool isCross(int x1, int x2, int y1, int y2);
    /// 判断两个已经确定YZ坐标的节点在YZ平面上的投影有没有重叠
    bool isCrossYZ(TTreeNode *a, TTreeNode *b);
};

#endif // XY_T_TREE_H

#ifndef B_T_TREE_H
#define B_T_TREE_H

#include "ttree.h"

#include <vector>
#include <stack>

class BTTree : public TTree
{
public:
    BTTree(const BoxList &boxes);
    virtual ~BTTree();

    /// A cloned T-tree
    TTree* Clone() override;

    /// Get the optimal solution
    Solution GetSolution() override;

private:
    std::vector<TTreeNode*> placed_nodes;

    TTreeNode* treeDecomposition(TTreeNode* root, std::stack<TTreeNode*>& S);
    void binaryTreePacking(TTreeNode *root);
    void placeModule(TTreeNode* n, std::vector<TTreeNode*>& L);
    void treePacking(TTreeNode* root);

    bool isCross(int x1, int x2, int y1, int y2);
    bool isCrossYZ(TTreeNode *a, TTreeNode *b);
};

#endif // XY_T_TREE_H

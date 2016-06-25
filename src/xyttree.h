#ifndef XY_T_TREE_H
#define XY_T_TREE_H

#include "ttree.h"

// 和论文不同
// 优先XY坐标
// 没有3叉变2叉

class XYTTree : public TTree
{
public:
    XYTTree(const BoxList &boxes);
    virtual ~XYTTree();

    /// Get the optimal solution
    virtual Solution GetSolution();

private:
};

#endif // XY_T_TREE_H

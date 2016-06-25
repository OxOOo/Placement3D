#include "xyttree.h"

XYTTree::XYTTree(const BoxList &boxes)
    : TTree(boxes)
{
}

XYTTree::~XYTTree()
{

}

/// Get the optimal solution
Solution XYTTree::GetSolution()
{
    return Solution();
}

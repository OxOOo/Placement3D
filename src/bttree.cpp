#include "bttree.h"
#include <cstdlib>
#include <iostream>

using namespace std;

BTTree::BTTree(const BoxList &boxes)
    : TTree(boxes)
{
}

BTTree::~BTTree(){}

/// Get the optimal solution
Solution BTTree::GetSolution()
{
    treePacking(root);
    Solution solution;
    for(int i = 0; i < (int)placed_nodes.size(); i ++) {
        placed_nodes[i]->box.Solve2();
        solution.Add(placed_nodes[i]->box);

        // PlacedBox box = placed_nodes[i]->box;
        // cout << "placed box " << char(placed_nodes[i] - nodes + 'A') << endl;
        // cout << "lwh : " << box.l << " " << box.w << " " << box.h << endl;
        // cout << "xyz : " << box.x << " " << box.y << " " << box.z << endl;
    }
    return solution;
}

TTreeNode* BTTree::treeDecomposition(TTreeNode* root, std::stack<TTreeNode*>& S)
{
    stack<TTreeNode*> SS;
    SS.push(root);
    while (!SS.empty()) {
        TTreeNode *m = SS.top(); SS.pop();
        if (m->m != NULL) {
            SS.push(m->m);
            m->b_r = m->m;
        } else m->b_r = NULL;
        if (m->l != NULL) {
            SS.push(m->l);
            m->b_l = m->l;
        } else m->b_l = NULL;
        if (m->r != NULL) {
            S.push(m->r);
        }
    }
    return root;
}

void BTTree::binaryTreePacking(TTreeNode *root)
{
    stack<TTreeNode*> S;
    vector<TTreeNode*> L;
    TTreeNode* p = root;
    placeModule(p, L);
    if (p->b_r != NULL)
        S.push(p->b_r);
    if (p->b_l != NULL)
        S.push(p->b_l);
    while (!S.empty()) {
        TTreeNode* p = S.top(); S.pop();
        placeModule(p, L);
        if (p->b_r != NULL)
            S.push(p->b_r);
        if (p->b_l != NULL)
            S.push(p->b_l);
    }
}

void BTTree::placeModule(TTreeNode* n, vector<TTreeNode*> &L)
{
    if (n->fa == NULL) {
        n->box.SetXYZ(0, 0, 0);
        placed_nodes.push_back(n);
        L.push_back(n);
        return;
    }
    if (n->fa->b_l == n) {
        n->box.z = n->fa->box.z + n->fa->box.h;
    } else {
        n->box.z = n->fa->box.z;
    }

    {// find y
        if (n->fa->r == n)
            n->box.y = n->fa->box.y;
        else {
            n->box.y = 0;
            for(int i = 0; i < (int)L.size(); i ++)
                if (isCross(n->box.z, n->box.z+n->box.h,
                    L[i]->box.z, L[i]->box.z+L[i]->box.h)) {
                        n->box.y = max(n->box.y, L[i]->box.y + L[i]->box.w);
                    }
        }
    }
    {// find x
        n->box.x = 0;
        for(int i = 0; i < (int)placed_nodes.size(); i ++)
            if (isCrossYZ(n, placed_nodes[i])) {
                n->box.x = max(n->box.x, placed_nodes[i]->box.x + placed_nodes[i]->box.l);
            }
    }
    placed_nodes.push_back(n);
    L.push_back(n);
}

void BTTree::treePacking(TTreeNode* root)
{
    placed_nodes.clear();

    stack<TTreeNode*> S;
    TTreeNode* bt;
    bt = treeDecomposition(root, S);
    binaryTreePacking(bt);
    while (!S.empty()) {
        TTreeNode* n = S.top(); S.pop();
        bt = treeDecomposition(n, S);
        binaryTreePacking(bt);
    }
}

bool BTTree::isCross(int x1, int x2, int y1, int y2)
{
    if (x1 > x2)swap(x1, x2);
    if (y1 > y2)swap(y1, y2);
    return max(x1, y1) < min(x2, y2);
}

bool BTTree::isCrossYZ(TTreeNode *a, TTreeNode *b)
{
    return isCross(a->box.y, a->box.y+a->box.w, b->box.y, b->box.y+b->box.w) &&
        isCross(a->box.z, a->box.z+a->box.h, b->box.z, b->box.z+b->box.h);
}

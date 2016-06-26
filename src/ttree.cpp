#include "random.h"
#include "ttree.h"

#include <cstdlib>
#include <iostream>

using namespace std;

TTreeNode::TTreeNode()
    : l(NULL), m(NULL), r(NULL), fa(NULL),
      b_l(NULL), b_r(NULL)
{

}

TTreeNode::~TTreeNode()
{

}

TTree::TTree(const BoxList &boxes)
    : N((int)boxes.size())
{
    nodes = new TTreeNode[N];
    for (int i = 0; i < N; i ++)
        nodes[i].box.SetBox(boxes[i]);

    root = getNodeById(0);
    for (int i = 1; i < N; ++i)
    {
        while (1)
        {
            SonType j = (SonType)Random::nextInt(3);
            int k = Random::nextInt(i);
            if (j == Left && nodes[k].l == NULL)
            {
                nodes[k].l = &nodes[i];
                nodes[i].fa = &nodes[k];
                break;
            }
            if (j == Mid && nodes[k].m == NULL)
            {
                nodes[k].m = &nodes[i];
                nodes[i].fa = &nodes[k];
                break;
            }
            if (j == Right && nodes[k].r == NULL)
            {
                nodes[k].r = &nodes[i];
                nodes[i].fa = &nodes[k];
                break;
            }
        }
    }
}

TTree::TTree(const TTree &tree)
    : N(tree.N)
{
    auto copy = [&](TTreeNode* node)
    {
        int id = tree.getIdByNode(node);
        return id == -1 ? NULL : getNodeById(id);
    };

    nodes = new TTreeNode[N];
    for (int i = 0; i < N; i ++)
    {
        nodes[i].box = tree.nodes[i].box;
        nodes[i].l = copy(tree.nodes[i].l);
        nodes[i].m = copy(tree.nodes[i].m);
        nodes[i].r = copy(tree.nodes[i].r);
        nodes[i].fa = copy(tree.nodes[i].fa);
        nodes[i].b_l = copy(tree.nodes[i].b_l);
        nodes[i].b_r = copy(tree.nodes[i].b_r);
    }
    root = copy(tree.root);
}

TTree::~TTree()
{
    delete[] nodes;
}

void TTree::deleteBox(int p)
{
    TTreeNode* now = getNodeById(p);
    deleteNode(now);
}

void TTree::deleteNode(TTreeNode* nodep)
{
    TTreeNode* tmp;
    int soncnt = 0;
    if (nodep->l != NULL) ++soncnt;
    if (nodep->m != NULL) ++soncnt;
    if (nodep->r != NULL) ++soncnt;
    if (soncnt)
    {
        bool flag = 1;
        while (flag)
        {
            SonType i = (SonType)Random::nextInt(3);
            if (i == Left  && nodep->l != NULL) tmp = nodep->l ,flag = 0;
            if (i == Mid   && nodep->m != NULL) tmp = nodep->m ,flag = 0;
            if (i == Right && nodep->r != NULL) tmp = nodep->r ,flag = 0;
        }
    }
    else
        tmp = NULL;
    deleteNode(tmp);
    TTreeNode::Copy(tmp, nodep);
    if (nodep->fa->l == nodep) nodep->fa->l = tmp;
    if (nodep->fa->m == nodep) nodep->fa->m = tmp;
    if (nodep->fa->r == nodep) nodep->fa->r = tmp;
    nodep->fa = nodep->l = nodep->m = nodep->r = NULL;
}

void TTree::insertAsChild(int p, int q)
{
    TTreeNode* nodep = getNodeById(p);
    TTreeNode* nodeq = getNodeById(q);
    if (!nodeq->IsLeaf())
    {
        cerr << "It's not a leaf! Fail to Insert!!" << endl;
        return ;
    }
    nodep->fa = nodeq;
    SonType i = (SonType)Random::nextInt(3);
    if (i == Left)
        nodeq->l = nodep;
    if (i == Mid)
        nodeq->m = nodep;
    if (i == Right)
        nodeq->r = nodep;
}

void TTree::insertToReplace(int p, int q, SonType k)
{
    TTreeNode* nodep = getNodeById(p);
    TTreeNode* nodeq = getNodeById(q);
    if (nodeq->fa->l == nodeq)
        nodeq->fa->l = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
    if (nodeq->fa->m == nodeq)
        nodeq->fa->m = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
    if (nodeq->fa->r == nodeq)
        nodeq->fa->r = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
    if (k == Left)
        nodep->l = nodeq;
    if (k == Mid)
        nodep->m = nodeq;
    if (k == Right)
        nodep->r = nodeq;
}

void TTree::print(TTreeNode* node) const
{
    if (node == NULL) return;
    printf("%d \t\t father: %d \t"
       "left: %d \t middle: %d \t right: %d\n", getIdByNode(node),
                                                getIdByNode(node->fa),
                                                getIdByNode(node->l),
                                                getIdByNode(node->m),
                                                getIdByNode(node->r));

    printf("%d %d %d  %d %d %d\n\n", node->box.x, node->box.y, node->box.z,
                                     node->box.l, node->box.w, node->box.h);

    print(node->l);
    print(node->m);
    print(node->r);
}

void TTree::Move()
{
    int p, q;
    while (1)
    {
        p = Random::nextInt(N), q = Random::nextInt(N);
        if (p != q) break;
    }

    deleteBox(p);
    if (!getNodeById(q)->IsLeaf())
        insertToReplace(p, q, (SonType)Random::nextInt(3));
    else if (Random::nextInt(2))
        insertToReplace(p, q, (SonType)Random::nextInt(3));
    else
        insertAsChild(p, q);
}

void TTree::Swap(int p, int q)
{
    TTreeNode* nownode1 = getNodeById(p);
    TTreeNode* nownode2 = getNodeById(q);
    swap(nownode1->l, nownode2->l);
    swap(nownode1->m, nownode2->m);
    swap(nownode1->r, nownode2->r);
    swap(nownode1->fa, nownode2->fa);
}

void TTree::Rotate(int p, int dir) // assume that at first it is l w h
{
    TTreeNode* nodep = getNodeById(p);
    switch (dir)
    {
    case 0: // l h w
        swap(nodep->box.h, nodep->box.w);
        break;
    case 1: // w l h
        swap(nodep->box.l, nodep->box.w);
        break;
    case 2: // h w l
        swap(nodep->box.h, nodep->box.l);
        break;
    default:
        break;
    }
}

void TTree::Debug()
{
    // FIXME 内存泄漏
    nodes = new TTreeNode[6];
    TTreeNode *a = nodes+0;
    TTreeNode *b = nodes+1;
    TTreeNode *c = nodes+2;
    TTreeNode *d = nodes+3;
    TTreeNode *e = nodes+4;
    TTreeNode *f = nodes+5;

    a->box.SetBox(Box(5, 3, 4));
    b->box.SetBox(Box(2, 2, 3));
    c->box.SetBox(Box(2, 2, 1));
    d->box.SetBox(Box(2, 3, 3));
    e->box.SetBox(Box(2, 3, 1));
    f->box.SetBox(Box(5, 1, 4));

    root = a;
    b->fa = a; a->m = b;
    d->fa = a; a->r = d;
    c->fa = b; b->l = c;
    f->fa = b; b->r = f;
    e->fa = d; d->l = e;

    Solution solution = GetSolution();
    cout << "bounding box volume : " << solution.GetBoundingBoxVolume() << endl;
    cout << "should be : " << 7*5*4 << endl;
}

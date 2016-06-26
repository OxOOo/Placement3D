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

void TTree::deleteNode(TTreeNode* node)
{
    if (node == NULL) return;
    TTreeNode* tmp;
    if (!node->IsLeaf())
    {
        bool flag = 1;
        while (flag)
        {
            SonType i = (SonType)Random::nextInt(3);
            if (i == Left  && node->l != NULL) tmp = node->l, flag = 0;
            if (i == Mid   && node->m != NULL) tmp = node->m, flag = 0;
            if (i == Right && node->r != NULL) tmp = node->r, flag = 0;
        }
        deleteNode(tmp);
        TTreeNode::CopyWithoutBox(tmp, node);
        if (tmp->l != NULL) tmp->l->fa = tmp;
        if (tmp->m != NULL) tmp->m->fa = tmp;
        if (tmp->r != NULL) tmp->r->fa = tmp;
    }
    else
        tmp = NULL;

    if (node->IsRoot())
        root = tmp;
    else
    {
        if (node->fa->l == node) node->fa->l = tmp;
        if (node->fa->m == node) node->fa->m = tmp;
        if (node->fa->r == node) node->fa->r = tmp;
    }
    node->fa = node->l = node->m = node->r = NULL;
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

    SonType k = (SonType)Random::nextInt(3);
    if (k == Left)
        nodeq->l = nodep;
    if (k == Mid)
        nodeq->m = nodep;
    if (k == Right)
        nodeq->r = nodep;
}

void TTree::insertToReplace(int p, int q)
{
    TTreeNode* nodep = getNodeById(p);
    TTreeNode* nodeq = getNodeById(q);

    if (nodeq->IsRoot())
        root = nodep, nodep->fa = NULL, nodeq->fa = nodep;
    else
    {
        if (nodeq->fa->l == nodeq)
            nodeq->fa->l = nodep;
        else if (nodeq->fa->m == nodeq)
            nodeq->fa->m = nodep;
        else if (nodeq->fa->r == nodeq)
            nodeq->fa->r = nodep;
        nodep->fa = nodeq->fa, nodeq->fa = nodep;
    }

    SonType k = (SonType)Random::nextInt(3);
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
    printf("%d \t father: %d \t"
       "left: %d \t middle: %d \t right: %d \t\t", getIdByNode(node),
                                                   getIdByNode(node->fa),
                                                   getIdByNode(node->l),
                                                   getIdByNode(node->m),
                                                   getIdByNode(node->r));

    printf("%d %d %d \t %d %d %d\n", node->box.x, node->box.y, node->box.z,
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
        insertToReplace(p, q);
    else if (Random::nextInt(2))
        insertToReplace(p, q);
    else
        insertAsChild(p, q);
}

void TTree::Swap(int p, int q)
{
    TTreeNode* nownode1 = getNodeById(p);
    TTreeNode* nownode2 = getNodeById(q);
    swap(nownode1->box, nownode2->box);
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

#include "ttree.h"
#include <cstdlib>
#include <iostream>

using namespace std;

TTreeNode::TTreeNode()
{

}

TTreeNode::~TTreeNode()
{

}

TTree::TTree(const BoxList &boxes)
	: N((int)boxes.size())
{
	nodes = new TTreeNode[N];
	root = getNodeById(0);
	for (int i = 1; i < N; ++i)
	{
		while (1)
		{
			SonType j = (SonType)(rand() % 3);
			int k = rand() % i;
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

TTree::~TTree()
{
	delete[] nodes;
}

void TTree::Delete(int p)
{
	// FIXME
	TTreeNode* now = getNodeById(p);
	if (now->fa->l == now) now->fa->l = NULL;
	else
		if (now->fa->m == now) now->fa->m = NULL;
		else
			if (now->fa->r == now) now->fa->r = NULL;
	if (now->l == NULL && now->m == NULL && now->r == NULL)
	{
		now->fa = NULL;
		return ;
	}
	while (1)
	{
		int i = rand() % 3;
		if (i == 0 && now->l != NULL)
		{

		}

	}
}

TTreeNode* TTree::getNodeById(int id)
{
	return &nodes[id];
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

void TTree::InsertAsChild(int p, int q)
{
	TTreeNode* nodep = getNodeById(p);
	TTreeNode* nodeq = getNodeById(q);
	if (nodeq->l != NULL || nodeq->m != NULL || nodeq->r != NULL)
	{
		cerr << "It's not a leaf! Fail to Insert!!" << endl;
		return ;
	}
	nodep->fa = nodeq;
	int i = rand() % 3;
	if (i == 0)
		nodeq->l = nodep;
	if (i == 1)
		nodeq->m = nodep;
	if (i == 2)
		nodeq->r = nodep;
}

void TTree::InsertToReplace(int p, int q, SonType k)
{
	TTreeNode* nodep = getNodeById(p);
	TTreeNode* nodeq = getNodeById(q);
	if (nodeq->fa->l == nodeq)
		nodeq->fa->l = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
	if (nodeq->fa->m == nodeq)
		nodeq->fa->m = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
	if (nodeq->fa->r == nodeq)
		nodeq->fa->r = nodep, nodep->fa = nodeq->fa, nodeq->fa = nodep;
	if (k == 0)
		nodep->l = nodeq;
	if (k == 1)
		nodep->m = nodeq;
	if (k == 2)
		nodep->r = nodeq;
}

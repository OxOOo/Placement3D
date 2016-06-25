#include "placement3d.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

Placement3D::Placement3D(const BoxList& boxes)
    : boxes(boxes)
{

}

Placement3D::~Placement3D()
{

}

BoxList Placement3D::LoadBoxesFromFile(const string& fileName)
{
    FILE* fin  = fopen(fileName.c_str(), "r");
    BoxList boxes;
    int n;

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y, z, l, w, h;
        fscanf(fin, "%d%d%d", &l, &w, &h);
        boxes.push_back(Box(l, w, h));
    }
    fclose(fin);

    return boxes;
}

Solution Placement3D::LoadSolutionFromFile(const string& fileName)
{
    FILE* fin  = fopen(fileName.c_str(), "r");
    Solution sol;
    int n;

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y, z, l, w, h;
        fscanf(fin, "%d%d%d", &x, &y, &z);
        fscanf(fin, "%d%d%d", &l, &w, &h);
        sol.Add(x, y, z, l, w, h);
    }
    fclose(fin);

    return sol;
}

bool Placement3D::SaveBoxesToFile(const string& fileName, const BoxList& boxes)
{

}

bool Placement3D::SaveSolutionToFile(const string& fileName, const Solution& sol)
{

}

void Placement3D::solve()
{

}

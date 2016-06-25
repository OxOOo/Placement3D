#include "random.h"
#include "bttree.h"
#include "placement3d.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

Placement3D::Placement3D(const BoxList& boxes)
    : n(boxes.size()), boxes(boxes)
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
        int l, w, h;
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

/// Simulated Annealing
void Placement3D::solve()
{
    const double INIT_TEMPERATURE = 1000;
    const double TEMPERATURE_DOWN_FACTOR = 0.99;
    const double VOLUME_FACTOR = 1;

    TTree* tree = new BTTree(boxes);
    double T = INIT_TEMPERATURE;
	double value = tree->GetSolution().GetBoundingBoxVolume() * VOLUME_FACTOR;

	for (;T > 0.01; T *= TEMPERATURE_DOWN_FACTOR)
    {
		for (int k = 0; k < 100; k++)
        {
			// Get next status
			TTree* newTree = tree->Clone();
            int oper = Random::nextInt(3), p, q, dir;
            switch (oper)
            {
            case 0: // Move p
                p = Random::nextInt(n);
                newTree->Move(p);
                break;
            case 1: // Swap p q
                p = Random::nextInt(n);
                q = Random::nextInt(n);
                newTree->Swap(p, q);
                break;
            case 2: // Rotate p dir
                p = Random::nextInt(n);
                dir = Random::nextInt(5);
                newTree->Rotate(p, dir);
                break;
            }

            // Get next status value
            Solution newSol = newTree->GetSolution();
            int newValue = newSol.GetBoundingBoxVolume() * VOLUME_FACTOR;
			double d = newValue - value;

			// Accept
			if (d < 0 || Random::nextDouble() < exp(- d / T))
            {
                sol = newSol;
                value = newValue;
                delete tree;
                tree = newTree;
			}
		}

        tree->Print();
        cout << "temperature: " << T << " \t\t"
             << "value: "       << value << " \t\t"
             << "volume: "      << value << endl;
	}
    delete tree;
}

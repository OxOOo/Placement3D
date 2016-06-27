#include "random.h"
#include "bttree.h"
#include "placement3d.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

Placement3D::Placement3D(const BoxList& boxes)
    : n(boxes.size()), boxes(boxes), is_debug(false),
      status_factor(10),
      volume_factor(1),
      lowest_temperature(0.01),
      temperature_down_factor(0.99)
{

}

Placement3D::~Placement3D()
{

}

/// Simulated Annealing
void Placement3D::solve()
{
    // Get initial temperature
    double maxV = 0, minV = 1e9;
    for (int i = 0; i < n * status_factor; i++)
    {
        BTTree tmp(boxes);
        double val = tmp.GetSolution().GetBoundingBoxVolume() * volume_factor;
        maxV = max(maxV, val);
        minV = min(minV, val);
    }
    double T = (maxV - minV) / log(1 / 0.8) / 2;

    TTree* tree = new BTTree(boxes);
    sol = tree->GetSolution();
    double value = sol.GetBoundingBoxVolume() * volume_factor;

    for (;T > lowest_temperature; T *= temperature_down_factor)
    {
        int times = 0;
        for (int k = 0; k < n * status_factor; k++)
        {
            // Get next status
            TTree* newTree = new BTTree(*((BTTree*)tree));
            int oper = Random::nextInt(3), p, q, dir;
            switch (oper)
            {
            case 0: // Move
                newTree->Move();
                break;
            case 1: // Swap p q
                p = Random::nextInt(n);
                q = Random::nextInt(n);
                newTree->Swap(p, q);
                break;
            case 2: // Rotate p dir
                p = Random::nextInt(n);
                dir = Random::nextInt(3);
                newTree->Rotate(p, dir);
                break;
            }

            // Get next status value
            Solution newSol = newTree->GetSolution();
            int newValue = newSol.GetBoundingBoxVolume() * volume_factor;
            double d = newValue - value;

            // Accept
            if (d < 0 || Random::nextDouble() < exp(- d / T))
            {
                sol = newSol;
                value = newValue;
                delete tree;
                tree = newTree;
                times++;
            }
            else
                delete newTree;
        }

        if (is_debug)
        {
            cout << "Temp.: "         << T << " \t"
                 << "Value: "         << value << " \t"
                 << "Volume: "        << sol.GetBoundingBoxVolume() << " \t"
                 << "Accept prob.: "  << times / (n * status_factor) << endl;
        }
    }
    delete tree;
}

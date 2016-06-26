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

/// Simulated Annealing
void Placement3D::solve()
{
    const double INIT_TEMPERATURE = 10000;
    const double TEMPERATURE_DOWN_FACTOR = 0.99;
    const double VOLUME_FACTOR = 1;

    TTree* tree = new BTTree(boxes);
    sol = tree->GetSolution();
    double T = INIT_TEMPERATURE;
    double value = sol.GetBoundingBoxVolume() * VOLUME_FACTOR;

    for (;T > 0.01; T *= TEMPERATURE_DOWN_FACTOR)
    {
        for (int k = 0; k < 10 * n; k++)
        {
            // Get next status
            TTree* newTree = new BTTree(*((BTTree*)tree));
            int oper = Random::nextInt(3), p, q, dir;
            //cout<<oper<<endl;
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

        /*tree->Print();
        cout << "temperature: " << T << " \t"
             << "value: "       << value << " \t"
             << "volume: "      << sol.GetBoundingBoxVolume() << endl;
        */
    }
    delete tree;
}

#include "placement3d.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    BoxList boxes = Box::LoadBoxesFromFile("box.txt");

    Placement3D* p3d = new Placement3D(boxes);
	p3d->GetSolution();
    p3d->SaveSolutionToFile("sol.txt");
    return 0;
}

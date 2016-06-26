#include <iostream>
#include <placement3d.h>

using namespace std;

Solution solution;

int main()
{
    srand(time(0));
    BoxList boxes = Box::LoadBoxesFromFile("box.txt");

    Placement3D* p3d = new Placement3D(boxes);
    //p3d->SetDebug();
    //p3d->SetStatusFactor(50);

    solution = p3d->GetSolution();
    delete p3d;

    cout << "Optimal solution: " << solution.GetBoundingBoxVolume() << endl;
    Solution::SaveSolutionToFile("sol.txt", solution);

    return 0;
}

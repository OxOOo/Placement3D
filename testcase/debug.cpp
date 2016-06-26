#include <iostream>
#include <placement3d.h>

using namespace std;

Solution solution;

int main()
{
    BoxList boxes = Box::LoadBoxesFromFile("box.txt");

    Placement3D* p3d = new Placement3D(boxes);
    solution = p3d->GetSolution();
    delete p3d;

    cout << "Optimal solution: " << solution.GetBoundingBoxVolume() << endl;
    Solution::SaveSolutionToFile("box.sol", solution);

    return 0;
}
